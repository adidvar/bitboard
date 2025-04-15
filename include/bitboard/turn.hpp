#pragma once

#include <bitboard/bitboard_export.hpp>
#include <bitboard/figure.hpp>
#include <bitboard/position.hpp>

namespace bitboard
{

class BITBOARD_EXPORT Turn
{
public:
  constexpr Turn();
  constexpr Turn(const Turn& other) = default;

  constexpr Turn(Position from, Position to, bool trivial = false);
  constexpr Turn(Position from,
                 Position to,
                 Figure figure,
                 bool trivial = false);

  explicit Turn(std::string_view chess_format);
  [[nodiscard]] std::string toString() const;

  constexpr bool operator==(const Turn& other) const = default;
  constexpr bool operator!=(const Turn& other) const = default;

  constexpr Turn& operator=(const Turn& other) = default;

  [[nodiscard]] constexpr Position from() const noexcept;
  [[nodiscard]] constexpr Position to() const noexcept;
  [[nodiscard]] constexpr Figure figure() const noexcept;

  [[nodiscard]] constexpr bool valid() const noexcept;
  [[nodiscard]] constexpr bool transform() const noexcept;
  [[nodiscard]] constexpr bool trivial() const noexcept;

  constexpr void setFigure(Figure figure);

private:
  uint16_t m_from : 6;
  uint16_t m_to : 6;
  uint16_t m_trivial : 1 = 0;
  uint16_t m_figure : 3 = static_cast<uint16_t>(Figure::kEmpty);
};

}  // namespace bitboard
