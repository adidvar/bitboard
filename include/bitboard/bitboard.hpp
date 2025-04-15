#pragma once

#include <bitboard/bitboard_export.hpp>
#include <bitboard/color.hpp>
#include <bitboard/figure.hpp>
#include <bitboard/position.hpp>
#include <bitboard/turn.hpp>

namespace bitboard
{

using bitboard_field = uint64_t;
using bitboard_hash = uint64_t;

static constexpr auto kChessMaxTurns = 216;

class BITBOARD_EXPORT BitBoard
{
public:
  enum struct Flags : uint8_t
  {
    kFlagsDefault = 0,
    kFlagsColor = 1,
    kFlagsElPassant = 2,
    kFlagsWhiteOo = 4,
    kFlagsWhiteOoo = 8,
    kFlagsBlackOo = 16,
    kFlagsBlackOoo = 32,
    kFlagsUpperBound = 64  // upper bound for generator
  };

  BitBoard() = default;
  BitBoard(BitBoard&&) = delete;
  BitBoard(const BitBoard& board) = default;

  explicit BitBoard(std::string_view fen_line);

  BitBoard& operator=(BitBoard&&) = delete;
  BitBoard& operator=(const BitBoard&) = default;

  void setTurn(Turn turn) const;
  void setFlags(Flags flags) const;
  void set(Position position, Figure figure) const;

  void swap(Position pos_1, Position pos_2) const;

  [[nodiscard]] Turn turn() const;
  [[nodiscard]] std::string fen() const;
  [[nodiscard]] bitboard_hash hash() const;
  [[nodiscard]] Color side() const noexcept;
  [[nodiscard]] Flags flags() const noexcept;
  [[nodiscard]] Figure get(Position position) const noexcept;

  bool operator==(const BitBoard& board) const = default;
  bool operator!=(const BitBoard& board) const = default;

protected:
  // bitboards white
  bitboard_field m_white_pawn = 0;
  bitboard_field m_white_knight = 0;
  bitboard_field m_white_bishop = 0;
  bitboard_field m_white_rook = 0;
  bitboard_field m_white_queen = 0;
  bitboard_field m_white_king = 0;
  // bitboards black
  bitboard_field m_black_pawn = 0;
  bitboard_field m_black_knight = 0;
  bitboard_field m_black_bishop = 0;
  bitboard_field m_black_rook = 0;
  bitboard_field m_black_queen = 0;
  bitboard_field m_black_king = 0;
  // other state
  bitboard_hash m_hash = 0;
  Turn m_prev_turn();
  Flags m_flags = Flags::kFlagsDefault;
};

BITBOARD_EXPORT extern const char* const kStartPosition;
BITBOARD_EXPORT extern const BitBoard kStartBitBoard;

}  // namespace bitboard
