#pragma once

#include <cstdint>
#include <string>
#include <string_view>

#include <bitboard/bitboard_export.hpp>

/*
+--+--+--+--+--+--+--+--+
| 0| 1| 2| 3| 4| 5| 6| 7|
+--+--+--+--+--+--+--+--+
| 8| 9|10|11|12|13|14|15|
+--+--+--+--+--+--+--+--+
|16|17|18|19|20|21|22|23|
+--+--+--+--+--+--+--+--+
|24|25|26|27|28|29|30|31|
+--+--+--+--+--+--+--+--+
|32|33|34|35|36|37|38|39|
+--+--+--+--+--+--+--+--+
|40|41|42|43|44|45|46|47|
+--+--+--+--+--+--+--+--+
|48|49|50|51|52|53|54|55|
+--+--+--+--+--+--+--+--+
|56|57|58|59|60|61|62|63|
+--+--+--+--+--+--+--+--+
*/

namespace bitboard
{

constexpr uint8_t kBoardSize = 8;
constexpr uint8_t kPositionSize = 63;
constexpr uint8_t kPositionInvalid = 64;

/**
 * @brief The Position class describes a chess position
 */
class BITBOARD_EXPORT Position
{
public:
  constexpr Position() noexcept;

  constexpr explicit Position(uint8_t index) noexcept;

  constexpr Position(uint8_t x_pos, uint8_t y_pos) noexcept;

  constexpr explicit Position(std::string_view string);

  [[nodiscard]] constexpr auto valid() const noexcept -> bool;

  [[nodiscard]] constexpr auto index() const noexcept -> uint8_t;

  [[nodiscard]] constexpr auto x() const noexcept -> uint8_t;

  [[nodiscard]] constexpr auto y() const noexcept -> uint8_t;

  [[nodiscard]] constexpr auto rotate() const noexcept -> Position;

  [[nodiscard]] auto toString() const -> std::string;

  constexpr auto operator==(const Position& pos) const noexcept -> bool;

  constexpr auto operator!=(const Position& pos) const noexcept -> bool;

  constexpr auto operator<(const Position& pos) const noexcept -> bool;

private:
  uint8_t m_index;
};

inline auto Position::toString() const -> std::string
{
  if (!valid()) {
    return "--";
  }
  std::string str = "00";
  str[0] = static_cast<char>('a' + x());
  str[1] = static_cast<char>('8' - y());
  return str;
}

constexpr auto Position::operator==(const Position& pos) const noexcept -> bool
{
  return m_index == pos.m_index;
}

constexpr auto Position::operator!=(const Position& pos) const noexcept -> bool
{
  return m_index != pos.m_index;
}

constexpr auto Position::operator<(const Position& pos) const noexcept -> bool
{
  return m_index < pos.m_index;
}

constexpr Position::Position(uint8_t x_pos, uint8_t y_pos) noexcept
    : m_index((y_pos * kBoardSize) + x_pos)
{
}

constexpr Position::Position() noexcept
    : m_index(kPositionInvalid)
{
}

constexpr Position::Position(uint8_t index) noexcept
    : m_index(index)
{
}

constexpr Position::Position(std::string_view string)
{
  if (string.size() == 2 && string[0] >= 'a' && string[0] <= 'h'
      && string[1] >= '1' && string[1] <= '8')
  {
    *this = Position(static_cast<uint8_t>(string[0] - 'a'),
                     static_cast<uint8_t>('8' - string[1]));
  } else {
    *this = {};
  }
}

constexpr auto Position::valid() const noexcept -> bool
{
  return m_index < kPositionInvalid;
}

constexpr auto Position::index() const noexcept -> uint8_t
{
  return m_index;
}

constexpr auto Position::x() const noexcept -> uint8_t
{
  return m_index % 8;
}

constexpr auto Position::y() const noexcept -> uint8_t
{
  return m_index / 8;
}

constexpr auto Position::rotate() const noexcept -> Position
{
  return Position(63 - m_index);
}

constexpr Position operator"" _p(const char* str, const std::size_t len)
{
  return Position(std::string_view(str, len));
}

constexpr uint8_t operator"" _pv(const char* str, const std::size_t len)
{
  return Position(std::string_view(str, len)).index();
}

}  // namespace bitboard
