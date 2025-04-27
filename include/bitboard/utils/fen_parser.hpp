#pragma once

#include <exception>
#include <string>
#include <string_view>
#include <variant>

#include "bitboard/bitboard.hpp"

namespace bitboard
{

/**
 * @brief Exception class for errors encountered during FEN string parsing.
 */
class ParseFenError : public std::exception
{
public:
  ParseFenError(std::string_view fen, std::string_view error)
      : m_fen(fen)
      , m_error(error)
  {
  }

private:
  /**
   * @brief The FEN string that failed to parse.
   */
  std::string m_fen;
  /**
   * @brief A description of the parsing error.
   */
  std::string m_error;
};

/**
 * @brief A utility class for serializing and deserializing BitBoard objects,
 * primarily using FEN format.
 */
class BitBoardSerializer
{
public:
  /**
   * @brief Parses a portion of a Forsyth-Edwards Notation (FEN) string view and
   * constructs or updates a BitBoard object.
   *
   * If parsing is successful, the index will be increased by the number of
   * characters read from the fen view.
   *
   * @param fen The FEN string view to parse.
   * @param index A reference to the current parsing index within the fen view.
   * Modified upon success.
   * @return A std::variant containing either the successfully parsed BitBoard
   * object or a ParseFenError if parsing fails.
   */
  static std::variant<BitBoard, ParseFenError> parseFen(std::string_view fen,
                                                        size_t& index);
  /**
   * @brief Converts a BitBoard object into its complete Forsyth-Edwards
   * Notation (FEN) string representation.
   * @param board The BitBoard object to serialize.
   * @return The FEN string representing the board state.
   */
  static std::string toFen(const BitBoard& board);

protected:
  static bool parseFigures(BitBoard& board, std::string_view view);
  static bool parseColor(BitBoard& board, std::string_view view);
  static bool parseCastling(BitBoard& board, std::string_view view);
  static bool parseElPassant(BitBoard& board, std::string_view view);

  static void combineFigures(const BitBoard& board, std::string& str);
  static void combineColor(const BitBoard& board, std::string& str);
  static void combineCastling(const BitBoard& board, std::string& str);
  static void combineElPassant(const BitBoard& board, std::string& str);
};

}  // namespace bitboard
