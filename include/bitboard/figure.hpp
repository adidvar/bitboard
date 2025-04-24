#pragma once

#include <cstdint>

namespace bitboard
{
/**
 * @brief Enumerates chess figures with color encoding.
 *
 * This enum represents different chess pieces, including their color.
 * Positive values represent white pieces, negative values represent black
 * pieces, and zero represents an empty square.  The numerical value (absolute
 * value) also corresponds to a simple ordering of piece types, useful in some
 * evaluation functions.
 */
enum struct Figure : int8_t
{
  kEmpty = 0,

  kPawn = 1,
  kKnight = 2,
  kBishop = 3,
  kRook = 4,
  kQueen = 5,
  kKing = 6,

  kWPawn = 1,
  kWKnight = 2,
  kWBishop = 3,
  kWRook = 4,
  kWQueen = 5,
  kWKing = 6,

  kBPawn = -1,
  kBKnight = -2,
  kBBishop = -3,
  kBRook = -4,
  kBQueen = -5,
  kBKing = -6,
};

}  // namespace bitboard
