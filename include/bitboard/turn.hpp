#pragma once

#include <bitboard/bitboard_export.hpp>
#include <bitboard/figure.hpp>
#include <bitboard/position.hpp>

namespace bitboard
{

/**
* @brief Represents a chess turn (move).
*
* Encapsulates move information: start/end positions, promotion figure (if pawn promotion),
* and flags for validity, promotion (is a pawn promotion), and triviality (simple move).
* Optimized for size (2 bytes).
*/
class BITBOARD_EXPORT Turn
{
    public:
    /**
    * @brief Default constructor, creates an invalid Turn.
    */
    constexpr Turn() noexcept = default;

    /**
    * @brief Copy constructor.
    */
    constexpr Turn(const Turn& other) = default;

    /**
    * @brief Constructs a Turn with start and end positions; invalidates on invalid positions.
    * @param from The starting position.
    * @param to The ending position.
    */
    constexpr Turn(Position from, Position to) noexcept;

    /**
    * @brief Constructs a Turn with start/end positions and the promotion figure; invalidates on invalid input.
    * @param from The starting position.
    * @param to The ending position.
    * @param figure The figure to which a pawn promotes (if applicable).
    */
    constexpr Turn(Position from, Position to, Figure figure) noexcept;

    /**
    * @brief Constructs a Turn from chess notation; invalidates on parsing errors or invalid positions.
    * @param chess_format A string in chess notation.
    */
    explicit Turn(std::string_view chess_format);

    /**
    * @brief Converts the Turn to a string (e.g., algebraic notation).
    * @return String representation of the turn.
    */
    [[nodiscard]] std::string toString() const;

    /**
    * @brief Equality operator.
    */
    constexpr bool operator==(const Turn& other) const = default;

    /**
    * @brief Inequality operator.
    */
    constexpr bool operator!=(const Turn& other) const = default;

    /**
    * @brief Assignment operator.
    */
    constexpr Turn& operator=(const Turn& other) = default;

    /**
    * @brief Gets the starting position.
    * @return The starting position.
    */
    [[nodiscard]] constexpr Position from() const noexcept;

    /**
    * @brief Gets the ending position.
    * @return The ending position.
    */
    [[nodiscard]] constexpr Position to() const noexcept;

    /**
    * @brief Gets the promotion figure.
    * @return The promotion figure (Figure::kEmpty if not a promotion).
    */
    [[nodiscard]] constexpr Figure figure() const noexcept;

    /**
    * @brief Checks if the Turn is valid (constructed without errors).
    * @return True if valid, false otherwise.
    */
    [[nodiscard]] constexpr bool valid() const noexcept;

    /**
    * @brief Checks if the Turn involves a pawn promotion.
    * @return True if promotion, false otherwise.
    */
    [[nodiscard]] constexpr bool promotion() const noexcept;

    /**
    * @brief Checks if the Turn is a simple move (not castling, capture, etc.).
    * @return True if a simple move, false otherwise.
    */
    [[nodiscard]] constexpr bool trivial() const noexcept;

    /**
    * @brief Unsafely constructs a Turn without validation. Use with caution.
    * @param from The starting position.
    * @param to The ending position.
    * @param trivial Whether the turn is a simple move.
    * @return A Turn object.
    */
    static constexpr Turn unsafeConstruct(Position from, Position to, bool trivial) noexcept;

    /**
    * @brief Unsafely constructs a Turn with a promotion figure without validation. Use with caution.
    * @param from The starting position.
    * @param to The ending position.
    * @param figure The promotion figure.
    * @param trivial Whether the turn is a simple move.
    * @return A Turn object.
    */
    static constexpr Turn unsafeConstruct(Position from, Position to, Figure figure, bool trivial) noexcept;

    private:
    constexpr Turn(Position from, Position to, bool trivial);
    constexpr Turn(Position from, Position to, Figure figure, bool trivial);

    uint16_t m_from : 6 = 0;
    uint16_t m_to : 6 = 0;
    uint16_t m_trivial : 1 = 0;
    uint16_t m_figure : 3 = static_cast<uint16_t>(Figure::kEmpty);
};

/**
* @brief Ensures Turn size is exactly 2 bytes for efficiency.
*/
static_assert(sizeof(Turn) == 2, "Turn must be exactly 2 bytes!");

constexpr Turn::Turn(Position from, Position to) noexcept : m_from(from.index()), m_to(to.index())
{
    if (!from.valid() || !to.valid())
    {
        m_from = 0;
        m_to = 0;
    }
}

constexpr Turn::Turn(Position from, Position to, Figure figure) noexcept : m_from(from.index()), m_to(to.index()), m_figure(static_cast<uint16_t>(figure))
{
  if (!from.valid() || !to.valid() || figure == Figure::kEmpty
      || figure == Figure::kPawn || figure == Figure::kBKing)
  {
    m_from = 0;
    m_to = 0;
    m_figure = static_cast<uint16_t>(Figure::kEmpty);
    }
}

inline Turn::Turn(std::string_view chess_format) { // NOLINT

}

inline std::string Turn::toString() const { return "";}// NOLINT

constexpr Position Turn::from() const noexcept {
    return Position(m_from);
}

constexpr Position Turn::to() const noexcept {
    return Position(m_to);
}

constexpr Figure Turn::figure() const noexcept {
    return static_cast<Figure>(m_figure);
}

constexpr bool Turn::valid() const noexcept {
    return m_from != 0 || m_to != 0;
}

constexpr bool Turn::promotion() const noexcept {
    return static_cast<Figure>(m_figure) != Figure::kEmpty;
}

constexpr bool Turn::trivial() const noexcept {
   return m_trivial;
}

constexpr Turn Turn::unsafeConstruct(Position from,
                                  Position to,
                                  bool trivial) noexcept
{
    return Turn(from,to,Figure::kEmpty,trivial);
}

constexpr Turn Turn::unsafeConstruct(Position from,
                                  Position to,
                                  Figure figure,
                                  bool trivial) noexcept
{
    return Turn(from,to,figure,trivial);
}

constexpr Turn::Turn(Position from, Position to, bool trivial): m_from(from.index()), m_to(to.index()), m_trivial(trivial) {
}

constexpr Turn::Turn(Position from, Position to, Figure figure, bool trivial): m_from(from.index()), m_to(to.index()),m_trivial(trivial),m_figure(static_cast<uint16_t>(figure)){
}

}  // namespace bitboard
