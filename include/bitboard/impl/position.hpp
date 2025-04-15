#pragma once

namespace bitboard
{

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
