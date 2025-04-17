#pragma once

#include <cstdint>
#include <stdexcept>
#include <string>
#include <string_view>

#include <bitboard/bitboard_export.hpp>

namespace bitboard
{
/**
 * @brief Constant representing the size of the chessboard (8x8).
 */
constexpr uint8_t kBoardSize = 8;

/**
 * @brief Constant representing the maximum valid position index on the board (0 to 63).
 */
constexpr uint8_t kPositionSize = 63;

/**
 * @brief Constant representing an invalid position index.
 */
constexpr uint8_t kPositionInvalid = 64;

/**
 * @brief The Position class describes a chess position on the board.
 *
 * Internally, the position is represented by a single `uint8_t` index,
 * ranging from 0 to 63, where 0 corresponds to the bottom-left square (A1)
 * and 63 corresponds to the top-right square (H8). An invalid position
 * is represented by the index `kPositionInvalid` (64).
 *
 * +--+--+--+--+--+--+--+--+
 * | 0| 1| 2| 3| 4| 5| 6| 7|
 * +--+--+--+--+--+--+--+--+
 * | 8| 9|10|11|12|13|14|15|
 * +--+--+--+--+--+--+--+--+
 * |16|17|18|19|20|21|22|23|
 * +--+--+--+--+--+--+--+--+
 * |24|25|26|27|28|29|30|31|
 * +--+--+--+--+--+--+--+--+
 * |32|33|34|35|36|37|38|39|
 * +--+--+--+--+--+--+--+--+
 * |40|41|42|43|44|45|46|47|
 * +--+--+--+--+--+--+--+--+
 * |48|49|50|51|52|53|54|55|
 * +--+--+--+--+--+--+--+--+
 * |56|57|58|59|60|61|62|63|
 * +--+--+--+--+--+--+--+--+
 *
 */
class BITBOARD_EXPORT Position
{
public:
    using int_t = uint8_t;
    /**
     * @brief Default constructor.
     *
     * Initializes the position to an invalid state.
     */
    constexpr Position() noexcept;

    /**
     * @brief Explicit constructor from a linear index.
     *
     * Initializes the position with the given index. If the index is out of
     * the valid range (0-63), the position is invalidated.
     *
     * @param index The linear index of the position (0-63).
     */
    constexpr explicit Position(int_t index) noexcept;

    /**
     * @brief Constructor from x and y coordinates.
     *
     * Initializes the position with the given x and y coordinates (0-7).
     * The x-coordinate represents the column (A=0, H=7), and the y-coordinate
     * represents the row (1=0, 8=7). If the coordinates are out of the valid
     * range, the position is invalidated.
     *
     * @param x_pos The x-coordinate (column) of the position (0-7).
     * @param y_pos The y-coordinate (row) of the position (0-7).
     */
    constexpr Position(int_t x_pos, int_t y_pos) noexcept;

    /**
     * @brief Explicit constructor from a string representation (e.g., "a1", "H8").
     *
     * Initializes the position from a standard algebraic notation string.
     * The string should be two characters long, with the first character
     * being a lowercase letter from 'a' to 'h' (representing the column)
     * and the second character being a digit from '1' to '8' (representing the row).
     * If the string is invalid, the position is invalidated.
     *
     * @param string The algebraic notation string representing the position.
     */
    constexpr explicit Position(std::string_view string);

    /**
     * @brief Checks if the position is valid.
     *
     * A position is considered valid if its internal index is within the
     * range 0 to 63.
     *
     * @return True if the position is valid, false otherwise.
     */
    [[nodiscard]] constexpr auto valid() const noexcept -> bool;

    /**
     * @brief Returns the linear index of the position.
     *
     * The index ranges from 0 (A1) to 63 (H8).
     *
     * @return The linear index of the position.
     */
    [[nodiscard]] constexpr auto index() const noexcept -> int_t;

    /**
     * @brief Returns the x-coordinate (column) of the position.
     *
     * The x-coordinate ranges from 0 (A) to 7 (H).
     *
     * @return The x-coordinate of the position.
     * @throws std::out_of_range If the position is invalid.
     */
    [[nodiscard]] auto x() const -> int_t;

    /**
     * @brief Returns the y-coordinate (row) of the position.
     *
     * The y-coordinate ranges from 0 (rank 1) to 7 (rank 8).
     *
     * @return The y-coordinate of the position.
     * @throws std::out_of_range If the position is invalid.
     */
    [[nodiscard]] auto y() const -> int_t;

    /**
     * @brief Rotates the position 180 degrees on the board.
     *
     * This operation effectively mirrors the position across the center of the board.
     * An invalid position remains invalid after rotation.
     *
     * @return A new Position object representing the rotated position. Returns an invalid Position if the original is invalid.
     */
    [[nodiscard]] constexpr auto rotate() const noexcept -> Position;

    /**
     * @brief Converts the position to its algebraic notation string representation.
     *
     * For example, index 0 becomes "a1", and index 63 becomes "h8".
     *
     * @return The algebraic notation string of the position.
     */
    [[nodiscard]] auto toString() const -> std::string;

    /**
     * @brief Equality comparison operator.
     *
     * Checks if two Position objects represent the same position on the board.
     *
     * @param pos The other Position object to compare with.
     * @return True if the positions are equal, false otherwise.
     */
    constexpr auto operator==(const Position& pos) const noexcept -> bool;

    /**
     * @brief Inequality comparison operator.
     *
     * Checks if two Position objects represent different positions on the board.
     *
     * @param pos The other Position object to compare with.
     * @return True if the positions are different, false otherwise.
     */
    constexpr auto operator!=(const Position& pos) const noexcept -> bool;

    /**
     * @brief Less than comparison operator.
     *
     * Compares two Position objects based on their internal index.
     *
     * @param pos The other Position object to compare with.
     * @return True if the current position's index is less than the other position's index, false otherwise.
     */
    constexpr auto operator<(const Position& pos) const noexcept -> bool;

    /**
     * @brief Returns the unsafe x-coordinate (column) of a Position without validity checks.
     */
    constexpr static uint8_t unsafeX(Position pos);

    /**
     * @brief Returns the unsafe y-coordinate (row) of a Position without validity checks.
     */
    constexpr static uint8_t unsafeY(Position pos);

    /**
     * @brief Unsafely constructs a Position object from a (x,y) without validity checks.
     */
    constexpr static Position unsafeConstruct(int_t x, int_t y);

private:
    /**
     * @brief The internal representation of the position as a linear index (0-63) or kPositionInvalid (64).
     */
    uint8_t m_index;
};

constexpr Position::Position() noexcept
    : m_index(kPositionInvalid)
{
}

constexpr Position::Position(uint8_t index) noexcept
    : m_index(index)
{
}

constexpr Position::Position(uint8_t x_pos, uint8_t y_pos) noexcept
    : m_index(static_cast<uint8_t>((y_pos * kBoardSize) + x_pos))
{
    if(x_pos > 7 || y_pos > 7)
        m_index = kPositionInvalid;
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

inline auto Position::x() const -> uint8_t
{
    if(!valid())
        throw std::out_of_range("called x() on invalid position");
    return m_index % kBoardSize;
}

inline auto Position::y() const -> uint8_t
{
    if(!valid())
        throw std::out_of_range("called y() on invalid position");
    return m_index / kBoardSize;
}

constexpr auto Position::rotate() const noexcept -> Position
{
  return Position(kPositionSize - m_index);
}

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

constexpr Position operator"" _p(const char* str, const std::size_t len)
{
  return Position(std::string_view(str, len));
}

constexpr Position::int_t operator"" _pv(const char* str, const std::size_t len)
{
  return Position(std::string_view(str, len)).index();
}

constexpr uint8_t Position::unsafeX(Position pos){
    return pos.m_index % kBoardSize;
}

constexpr uint8_t Position::unsafeY(Position pos){
    return pos.m_index / kBoardSize;
}

constexpr Position Position::unsafeConstruct(int_t x, int_t y){
    return Position(static_cast<uint8_t>((y * kBoardSize) + x));
}

}  // namespace bitboard
