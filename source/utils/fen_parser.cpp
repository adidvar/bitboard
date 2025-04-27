#include <algorithm>
#include <array>
#include <map>

#include <bitboard/utils/fen_parser.hpp>

#include "bitboard/bitboard.hpp"
#include "bitboard/figure.hpp"

namespace
{

using bitboard::BitBoard;
using bitboard::Figure;

constexpr const std::string_view kStartString = "startpos";

constexpr const char kCombineSeperator = ' ';
constexpr const std::array<char, 3> kParseSeperators {' ', '\n', '\t'};

const std::map<char, Figure> kStringToFigure {{' ', Figure::kEmpty},
                                              {'p', Figure::kBPawn},
                                              {'n', Figure::kBKnight},
                                              {'b', Figure::kBBishop},
                                              {'r', Figure::kBRook},
                                              {'q', Figure::kBQueen},
                                              {'k', Figure::kBKing},
                                              {'P', Figure::kWPawn},
                                              {'N', Figure::kWKnight},
                                              {'B', Figure::kWBishop},
                                              {'R', Figure::kWRook},
                                              {'Q', Figure::kWQueen},
                                              {'K', Figure::kWKing}};

const std::map<Figure, char> kFigureToString = {{Figure::kEmpty, ' '},
                                                {Figure::kBPawn, 'p'},
                                                {Figure::kBKnight, 'n'},
                                                {Figure::kBBishop, 'b'},
                                                {Figure::kBRook, 'r'},
                                                {Figure::kBQueen, 'q'},
                                                {Figure::kBKing, 'k'},
                                                {Figure::kWPawn, 'P'},
                                                {Figure::kWKnight, 'N'},
                                                {Figure::kWBishop, 'B'},
                                                {Figure::kWRook, 'R'},
                                                {Figure::kWQueen, 'Q'},
                                                {Figure::kWKing, 'K'}};

void skipSeperators(std ::string_view data, size_t& index)
{
  while (index < data.size()
         && std::ranges::find(kParseSeperators, data[index])
             != kParseSeperators.end())
  {
    index++;
  }
}

std::string_view readStringPart(std::string_view data, size_t& index)
{
  skipSeperators(data, index);
  auto begin = index;
  while (index < data.size()
         && std::ranges::find(kParseSeperators, data[index])
             == kParseSeperators.end())
  {
    index++;
  }
  auto end = index;
  skipSeperators(data, index);
  return data.substr(begin, end - begin);
}

bool parseNumber(std::string_view view)
{
  return std::ranges::all_of(
      view, [](char digit) -> bool { return std::isdigit(digit); });
}

}  // namespace

/*
void boardFromFen(std::string_view fen, bit_board& board, size_t& index)
{
  board = bit_board {nullptr};


  skipSeperators(fen, index);

  if (fen.substr(index).starts_with(start_string)) {
    board = bit_board {};
    index += start_string.size();
    return;
  }

  size_t position = 0;
  for (; index < fen.size() && position != 64; ++index) {
    const char character = fen.at(index);

    if (character == ' ')
      ;
    else if (s_to_f.contains(character)) {
      board = board.set(Position(position), s_to_f.at(character));
      position++;
    } else if (std::isdigit(character)) {
      if (int digit = character - '0'; digit > 0 && digit < 9) {
        position += digit;
      }
    } else if (character == '/') {
      position = ((position - 1) / 8) * 8 + 8;
    } else {
      throw FenError("invalid character");
    }
  }
  ++index;

  if (position != 64) {
    throw FenError("incompleted fen board");
  }

  std::string current_move, rooking, pawn;
  std::string static_move, move_counter;

  current_move = readStringPart(fen, index);

  if (index == fen.size()) {
    throw FenError("incompleted fen");
  }

  rooking = readStringPart(fen, index);

  if (index == fen.size()) {
    throw FenError("incompleted fen");
  }

  pawn = readStringPart(fen, index);

  if (index == fen.size()) {
    throw FenError("incompleted fen");
  }

  static_move = readStringPart(fen, index);

  if (index == fen.size()) {
    throw FenError("incompleted fen");
  }

  move_counter = readStringPart(fen, index);

  bit_board::Flags flags = bit_board::flags_default;

  if (current_move.front() == 'w')
    ;
  else if (current_move == "b") {
    flags = (bit_board::Flags)(flags | bit_board::flags_color);
  } else {
    throw FenError("incorrect current side");
  }

  if (pawn.size() == 2) {
    auto position = Position(pawn);
    if (!position.isValid()) {
      throw FenError("incorrect el passant");
    }
    if ((flags & bit_board::flags_color) == 0) {
      board = board.setTurn(
          Turn(Position(pawn).index() - 8, Position(pawn).index() + 8));
    } else {
      board = board.setTurn(
          Turn(Position(pawn).index() + 8, Position(pawn).index() - 8));
    }
    flags = (bit_board::Flags)(flags | bit_board::flags_el_passant);
  }

  for (char x : rooking) {
    switch (x) {
      case 'K':
        flags = (bit_board::Flags)(flags | bit_board::flags_white_oo);
        break;
      case 'Q':
        flags = (bit_board::Flags)(flags | bit_board::flags_white_ooo);
        break;
      case 'k':
        flags = (bit_board::Flags)(flags | bit_board::flags_black_oo);
        break;
      case 'q':
        flags = (bit_board::Flags)(flags | bit_board::flags_black_ooo);
        break;
      case '-':
        break;
      default:
        throw FenError("incorrect castling");
    }
  }
  board = board.setFlags(flags);
}

std::string boardToFen(const bit_board& board)
{
  char buffer[128] = {0};
  size_t position = 0;
  size_t bypass_counter = 0;
  for (size_t i = 0; i < 64; i++) {
    if (i % 8 == 0 && i != 0) {
      if (bypass_counter != 0) {
        buffer[position] = '0' + bypass_counter;
        position++;
        bypass_counter = 0;
      }

      buffer[position] = '/';
      position++;
    }
    if (board.get(i).isEmpty()) {
      bypass_counter++;
    } else {
      if (bypass_counter != 0) {
        buffer[position] = '0' + bypass_counter;
        position++;
        bypass_counter = 0;
      }
      buffer[position] = f_to_s.at(board.get(i));
      position++;
    }
  }

  if (bypass_counter != 0) {
    buffer[position] = '0' + bypass_counter;
    position++;
  }

  auto rooking_flags = board.getFlags();
  std::string string(buffer);
  string += ' ';
  string.push_back(rooking_flags & bit_board::flags_color ? 'b' : 'w');
  string += ' ';
  if ((rooking_flags
       & (bit_board::flags_black_oo | bit_board::flags_black_ooo
          | bit_board::flags_white_oo | bit_board::flags_white_ooo))
      == 0)
  {
    string.push_back('-');
  } else {
    if (rooking_flags & bit_board::flags_white_oo) {
      string += 'K';
    }
    if (rooking_flags & bit_board::flags_white_ooo) {
      string += 'Q';
    }
    if (rooking_flags & bit_board::flags_black_oo) {
      string += 'k';
    }
    if (rooking_flags & bit_board::flags_black_ooo) {
      string += 'q';
    }
  }
  string += ' ';

  if (rooking_flags & bit_board::flags_el_passant) {
    string +=
        Position((board.getTurn().from().index() +
        board.getTurn().to().index())
                 / 2)
            .toString();
  } else {
    string += '-';
  }

  string += ' ';
  string += std::to_string(0);
  string += ' ';
  string += std::to_string(0);
  return string;
}
*/

namespace bitboard
{

/*
 * rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1
 * 1) Figures part
 * 2) Color part
 * 3) Castling part
 * 4) El passant part
 * 5) Counter part
 * 6) Counter part
 */

std::variant<BitBoard, ParseFenError> BitBoardSerializer::parseFen(
    std::string_view fen, size_t& index)
{
  BitBoard board;
  auto i = index;

  auto figures_part = readStringPart(fen, i);

  if (figures_part == kStartString) {
    index = i;
    return {kStartBitBoard};
  }

  if (!parseFigures(board, figures_part)) {
    return ParseFenError(figures_part, "Failure to parse figures");
  }

  auto color_part = readStringPart(fen, i);
  if (!parseColor(board, color_part)) {
    return ParseFenError(color_part, "Failure to parse color");
  }

  auto castling_part = readStringPart(fen, i);
  if (!parseCastling(board, castling_part)) {
    return ParseFenError(castling_part, "Failure to parse castling");
  }

  auto elpassant_part = readStringPart(fen, i);
  if (!parseElPassant(board, elpassant_part)) {
    return ParseFenError(elpassant_part, "Failure to parse el-passant");
  }

  auto counter_1_part = readStringPart(fen, i);
  if (!parseNumber(counter_1_part)) {
    return ParseFenError(counter_1_part, "Failure to parse counter");
  }

  auto counter_2_part = readStringPart(fen, i);
  if (!parseNumber(counter_2_part)) {
    return ParseFenError(counter_2_part, "Failure to parse counter");
  }

  index = i;
  return {board};
}

std::string BitBoardSerializer::toFen(const BitBoard& board)
{
  std::string result;

  combineFigures(board, result);
  result.push_back(kCombineSeperator);
  combineColor(board, result);
  result.push_back(kCombineSeperator);
  combineCastling(board, result);
  result.push_back(kCombineSeperator);
  combineElPassant(board, result);
  result.push_back(kCombineSeperator);
  result.append("0 1");

  return result;
}

}  // namespace bitboard
