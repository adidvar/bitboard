#pragma once

#include <cstdint>

namespace bitboard
{

/**
 * @brief Enumerates the two colors in chess.
 */
enum struct Color : int8_t
{
  kWhite = -1,
  kBlack = 1,
};

}  // namespace bitboard
