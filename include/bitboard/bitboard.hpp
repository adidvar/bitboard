#pragma once

#include <bitboard/bitboard_export.hpp>
#include <bitboard/color.hpp>
#include <bitboard/figure.hpp>
#include <bitboard/position.hpp>
#include <bitboard/turn.hpp>

namespace bitboard
{

/**
 * @brief Represents a 64-bit unsigned integer used for bitboard fields.
 */
using bitboard_field = uint64_t;
/**
 * @brief Represents a 64-bit unsigned integer used for hashing bitboards.
 */
using bitboard_hash = uint64_t;
/**
 * @brief The maximum number of half-moves allowed in a chess game before a draw
 * can be claimed by the fifty-move rule.
 *
 * This value seems high for 50-move rule (usually 100 ply or 50 full moves),
 * double check its purpose. Assuming it's for something else, like game state
 * tracking limits.
 */
static constexpr auto kChessMaxTurns = 216;

/**
 * @brief Represents a chess board using bitboards for piece placement and
 * state.
 */
class BITBOARD_EXPORT BitBoard
{
public:
  /**
   * @brief Enumerates flags representing various aspects of the board state.
   */
  enum struct Flags : uint8_t
  {
    kFlagsDefault = 0, /**< Default state, no special flags set. */
    kFlagsColor = 1, /**< Flag indicating whose turn it is (typically 1 for
                        white, 0 for black if used as a bit). */
    kFlagsElPassant = 2, /**< Flag indicating if an en passant capture is
                            possible on the previous move. */
    kFlagsWhiteOo =
        4, /**< Flag indicating if white has the right to castle kingside. */
    kFlagsWhiteOoo =
        8, /**< Flag indicating if white has the right to castle queenside. */
    kFlagsBlackOo =
        16, /**< Flag indicating if black has the right to castle kingside. */
    kFlagsBlackOoo =
        32, /**< Flag indicating if black has the right to castle queenside. */
    kFlagsUpperBound =
        64 /**< Upper bound for flags, useful for iteration or validation. */
  };

  /**
   * @brief Default constructor. Creates an empty or uninitialized board.
   */
  BitBoard() = default;
  /**
   * @brief Deleted move constructor to prevent moving BitBoard objects.
   */
  BitBoard(BitBoard&&) = delete;
  /**
   * @brief Copy constructor. Creates a deep copy of another BitBoard object.
   * @param board The BitBoard object to copy from.
   */
  BitBoard(const BitBoard& board) = default;
  /**
   * @brief Constructor that initializes the board state from a Forsyth-Edwards
   * Notation (FEN) string view.
   * @param fen_line The FEN string view representing the desired board state.
   * @throws std::invalid_argument, if FEN is invalid
   */
  explicit BitBoard(std::string_view fen_line);
  /**
   * @brief Deleted move assignment operator to prevent moving BitBoard objects.
   */
  BitBoard& operator=(BitBoard&&) = delete;
  /**
   * @brief Copy assignment operator. Assigns the state of another BitBoard
   * object to this one.
   * @param board The BitBoard object to copy from.
   * @return A reference to the modified BitBoard object.
   */
  BitBoard& operator=(const BitBoard&) = default;
  /**
   * @brief Gets the current turn number.
   * @return The current turn number.
   */
  [[nodiscard]] constexpr Turn turn() const;
  /**
   * @brief Generates the FEN string representation of the current board state.
   * @return The FEN string.
   */
  [[nodiscard]] std::string fen() const;
  /**
   * @brief Calculates and returns the Zobrist hash of the current board state.
   * @return The board hash.
   */
  [[nodiscard]] constexpr bitboard_hash hash() const;
  /**
   * @brief Gets the side whose turn it is.
   * @return The color (side) whose turn it is.
   */
  [[nodiscard]] constexpr Color side() const noexcept;
  /**
   * @brief Gets the state of certain flag.
   * @return The state.
   */
  [[nodiscard]] constexpr bool checkFlag(Flags flag) const noexcept;
  /**
   * @brief Gets the current board flags.
   * @return The current flags.
   */
  [[nodiscard]] constexpr Flags flags() const noexcept;
  /**
   * @brief Gets the figure at a specific position on the board.
   * @param position The position to get the figure from.
   * @return The figure at the specified position, or an empty figure if the
   * position is empty or invalid.
   */
  [[nodiscard]] Figure get(Position position) const noexcept;
  /**
   * @brief Equality operator. Checks if two BitBoard objects represent the same
   * board state.
   * @param board The other BitBoard object to compare with.
   * @return True if the boards are equal, false otherwise.
   */
  bool operator==(const BitBoard& board) const = default;
  /**
   * @brief Inequality operator. Checks if two BitBoard objects represent
   * different board states.
   * @param board The other BitBoard object to compare with.
   * @return True if the boards are not equal, false otherwise.
   */
  bool operator!=(const BitBoard& board) const = default;

protected:
  // bitboards white
  /**
   * @brief Bitboard representing the positions of white pawns.
   */
  bitboard_field m_white_pawn = 0;
  /**
   * @brief Bitboard representing the positions of white knights.
   */
  bitboard_field m_white_knight = 0;
  /**
   * @brief Bitboard representing the positions of white bishops.
   */
  bitboard_field m_white_bishop = 0;
  /**
   * @brief Bitboard representing the positions of white rooks.
   */
  bitboard_field m_white_rook = 0;
  /**
   * @brief Bitboard representing the positions of white queens.
   */
  bitboard_field m_white_queen = 0;
  /**
   * @brief Bitboard representing the positions of white kings.
   */
  bitboard_field m_white_king = 0;
  // bitboards black
  /**
   * @brief Bitboard representing the positions of black pawns.
   */
  bitboard_field m_black_pawn = 0;
  /**
   * @brief Bitboard representing the positions of black knights.
   */
  bitboard_field m_black_knight = 0;
  /**
   * @brief Bitboard representing the positions of black bishops.
   */
  bitboard_field m_black_bishop = 0;
  /**
   * @brief Bitboard representing the positions of black rooks.
   */
  bitboard_field m_black_rook = 0;
  /**
   * @brief Bitboard representing the positions of black queens.
   */
  bitboard_field m_black_queen = 0;
  /**
   * @brief Bitboard representing the positions of black kings.
   */
  bitboard_field m_black_king = 0;
  // other state
  /**
   * @brief The Zobrist hash of the current board state.
   */
  bitboard_hash m_hash = 0;
  /**
   * @brief Retrieves or calculates the previous turn number.
   * @return The previous turn number.
   * @note This signature looks like a method, not a member variable. If it's
   * intended as a variable, the declaration is incomplete.
   */
  Turn m_prev_turn;

  /**
   * @brief Flags representing the current board state (e.g., castling rights,
   * en passant).
   */
  Flags m_flags = Flags::kFlagsDefault;

  friend class BitBoardSerializer;
};

/**
 * @brief External constant string containing the standard starting position in
 * FEN format.
 */
BITBOARD_EXPORT extern const char* const kStartPosition;
/**
 * @brief External constant BitBoard object representing the standard starting
 * position.
 */
BITBOARD_EXPORT extern const BitBoard kStartBitBoard;

constexpr Turn BitBoard::turn() const
{
  return m_prev_turn;
}

constexpr bitboard_hash BitBoard::hash() const
{
  return m_hash;
}

constexpr Color BitBoard::side() const noexcept
{
  return checkFlag(Flags::kFlagsColor) ? Color::kBlack : Color::kWhite;
}

constexpr bool BitBoard::checkFlag(Flags flag) const noexcept
{
  return (static_cast<uint>(m_flags) & static_cast<uint>(flag)) != 0;
}

constexpr BitBoard::Flags BitBoard::flags() const noexcept
{
  return m_flags;
}

}  // namespace bitboard
