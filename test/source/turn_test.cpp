#include <bitboard/turn.hpp>
#include <catch2/catch_test_macros.hpp>

#include "bitboard/figure.hpp"
#include "bitboard/position.hpp"

using bitboard::Figure;
using bitboard::Position;
using bitboard::Turn;

TEST_CASE("Turn default constructor creates invalid turn", "[Turn]")
{
  Turn turn;
  REQUIRE_FALSE(turn.valid());
  REQUIRE(turn.from().index() == 0);
  REQUIRE(turn.to().index() == 0);
  REQUIRE(turn.figure() == Figure::kEmpty);
  REQUIRE_FALSE(turn.promotion());
  REQUIRE_FALSE(turn.trivial());
}

TEST_CASE("Turn(Position, Position) - valid positions", "[Turn]")
{
  Position from(12);
  Position to(28);
  Turn turn(from, to);
  REQUIRE(turn.valid());
  REQUIRE(turn.from() == from);
  REQUIRE(turn.to() == to);
  REQUIRE(turn.figure() == Figure::kEmpty);
  REQUIRE_FALSE(turn.promotion());
}

TEST_CASE("Turn(Position, Position) - invalid positions", "[Turn]")
{
  Position invalid_from(128);  // out of bounds
  Position to(10);
  Turn turn(invalid_from, to);
  REQUIRE_FALSE(turn.valid());
}

TEST_CASE("Turn(Position, Position, Figure) - valid promotion", "[Turn]")
{
  Position from(8);  // e7
  Position to(0);  // e8
  Turn turn(from, to, Figure::kQueen);
  REQUIRE(turn.valid());
  REQUIRE(turn.promotion());
  REQUIRE(turn.figure() == Figure::kQueen);
}

TEST_CASE("Turn(Position, Position, Figure) - invalid promotion figure",
          "[Turn]")
{
  Position from(8);
  Position to(0);
  Turn turn(from, to, Figure::kPawn);  // pawn cannot be a promotion target
  REQUIRE_FALSE(turn.valid());
}

TEST_CASE("Turn::unsafeConstruct without promotion", "[Turn]")
{
  Position from(3);
  Position to(27);
  Turn turn = Turn::unsafeConstruct(from, to, true);
  REQUIRE(turn.valid());
  REQUIRE(turn.from() == from);
  REQUIRE(turn.to() == to);
  REQUIRE_FALSE(turn.promotion());
  REQUIRE(turn.trivial());
}

TEST_CASE("Turn::unsafeConstruct with promotion", "[Turn]")
{
  Position from(6);
  Position to(14);
  Turn turn = Turn::unsafeConstruct(from, to, Figure::kKnight, false);
  REQUIRE(turn.valid());
  REQUIRE(turn.promotion());
  REQUIRE(turn.figure() == Figure::kKnight);
  REQUIRE_FALSE(turn.trivial());
}

TEST_CASE("Turn operator== and operator!=", "[Turn]")
{
  Position from(10);
  Position to(20);
  Turn a(from, to);
  Turn b(from, to);
  Turn c(Position(11), Position(21));
  REQUIRE(a == b);
  REQUIRE(a != c);
}
