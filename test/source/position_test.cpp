#include <bitboard/position.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

using bitboard::Position;
using bitboard::kPositionInvalid;

TEST_CASE("Test Position() - default constructor")
{
    REQUIRE(Position().valid() == false);
    REQUIRE(Position().index() == kPositionInvalid);
}

TEST_CASE("Test Position(int) - valid index")
{
    REQUIRE(Position(0).valid() == true);
    REQUIRE(Position(0).index() == 0);
    REQUIRE(Position(63).valid() == true);
    REQUIRE(Position(63).index() == 63);

    REQUIRE(Position(0).x() == 0);
    REQUIRE(Position(0).y() == 0);
    REQUIRE(Position(63).x() == 7);
    REQUIRE(Position(63).y() == 7);
}

TEST_CASE("Test Position(int) - invalid index")
{
    REQUIRE(Position(64).valid() == false);
    REQUIRE(Position(64).index() >= kPositionInvalid);
    REQUIRE(Position(100).valid() == false);
    REQUIRE(Position(100).index() >= kPositionInvalid);
}

TEST_CASE("Test Position(int, int) - valid coordinates")
{
    REQUIRE(Position(0, 0).valid() == true);
    REQUIRE(Position(0, 0).index() == 0);
    REQUIRE(Position(7, 7).valid() == true);
    REQUIRE(Position(7, 7).index() == 63);
    REQUIRE(Position(3, 4).valid() == true);
    REQUIRE(Position(3, 4).index() == 35);

    REQUIRE(Position(0, 0).x() == 0);
    REQUIRE(Position(0, 0).y() == 0);
    REQUIRE(Position(7, 7).x() == 7);
    REQUIRE(Position(7, 7).y() == 7);
    REQUIRE(Position(3, 4).x() == 3);
    REQUIRE(Position(3, 4).y() == 4);
}

TEST_CASE("Test Position(int, int) - invalid coordinates")
{
    REQUIRE(Position(8, 0).valid() == false);
    REQUIRE(Position(0, 8).valid() == false);
    REQUIRE(Position(8, 8).valid() == false);
    REQUIRE(Position(static_cast<uint8_t>(-1), 0).valid() == false);
    REQUIRE(Position(0,static_cast<uint8_t>(-1)).valid() == false);
}

TEST_CASE("Test Position(std::string_view) - valid string")
{
    REQUIRE(Position("a1").valid() == true);
    REQUIRE(Position("a1").index() == 0);
    REQUIRE(Position("h8").valid() == true);
    REQUIRE(Position("h8").index() == 63);
    REQUIRE(Position("c5").valid() == true);
    REQUIRE(Position("c5").index() == 34);

    REQUIRE(Position("a1").x() == 0);
    REQUIRE(Position("a1").y() == 0);
    REQUIRE(Position("h8").x() == 7);
    REQUIRE(Position("h8").y() == 7);
    REQUIRE(Position("c5").x() == 2);
    REQUIRE(Position("c5").y() == 4);
}

TEST_CASE("Test Position(std::string_view) - invalid string")
{
    REQUIRE(Position("").valid() == false);
    REQUIRE(Position("a").valid() == false);
    REQUIRE(Position("1").valid() == false);
    REQUIRE(Position("aa").valid() == false);
    REQUIRE(Position("11").valid() == false);
    REQUIRE(Position("i1").valid() == false);
    REQUIRE(Position("a9").valid() == false);
    REQUIRE(Position("a0").valid() == false);
    REQUIRE(Position("h9").valid() == false);
    REQUIRE(Position("01").valid() == false);
}

TEST_CASE("Test valid()")
{
    REQUIRE(Position().valid() == false);
    REQUIRE(Position(0).valid() == true);
    REQUIRE(Position(63).valid() == true);
    REQUIRE(Position(64).valid() == false);
    REQUIRE(Position(3, 4).valid() == true);
    REQUIRE(Position(8, 0).valid() == false);
    REQUIRE(Position("a1").valid() == true);
    REQUIRE(Position("i9").valid() == false);
}

TEST_CASE("Test index()")
{
    REQUIRE(Position().index() == kPositionInvalid);
    REQUIRE(Position(0).index() == 0);
    REQUIRE(Position(63).index() == 63);
    REQUIRE(Position(64).index() == kPositionInvalid);
    REQUIRE(Position(3, 4).index() == 35);
    REQUIRE(Position(8, 0).index() == kPositionInvalid);
    REQUIRE(Position("a1").index() == 0);
    REQUIRE(Position("h8").index() == 63);
    REQUIRE(Position("i9").index() == kPositionInvalid);
}

TEST_CASE("Test x() - valid")
{
    REQUIRE(Position(0).x() == 0);
    REQUIRE(Position(7).x() == 7);
    REQUIRE(Position(35).x() == 3);
    REQUIRE(Position("a1").x() == 0);
    REQUIRE(Position("h8").x() == 7);
    REQUIRE(Position("d3").x() == 3);
}

TEST_CASE("Test x() - invalid")
{
    REQUIRE_THROWS_AS(Position().x(), std::out_of_range);
    REQUIRE_THROWS_AS(Position(64).x(), std::out_of_range);
    REQUIRE_THROWS_AS(Position(8, 0).x(), std::out_of_range);
    REQUIRE_THROWS_AS(Position("i1").x(), std::out_of_range);
}

TEST_CASE("Test y() - valid")
{
    REQUIRE(Position(0).y() == 0);
    REQUIRE(Position(7).y() == 0);
    REQUIRE(Position(56).y() == 7);
    REQUIRE(Position(35).y() == 4);
    REQUIRE(Position("a1").y() == 0);
    REQUIRE(Position("h8").y() == 7);
    REQUIRE(Position("d3").y() == 2);
}

TEST_CASE("Test y() - invalid")
{
    REQUIRE_THROWS_AS(Position().y(), std::out_of_range);
    REQUIRE_THROWS_AS(Position(64).y(), std::out_of_range);
    REQUIRE_THROWS_AS(Position(8, 0).y(), std::out_of_range);
    REQUIRE_THROWS_AS(Position("i1").y(), std::out_of_range);
}

TEST_CASE("Test rotate()")
{
    REQUIRE(Position().rotate().valid() == false);
    REQUIRE(Position(0).rotate().index() == 63);   // a1 -> h8
    REQUIRE(Position(63).rotate().index() == 0);   // h8 -> a1
    REQUIRE(Position(35).rotate().index() == 28);  // d5 -> e4
    REQUIRE(Position("a1").rotate().toString() == "h8");
    REQUIRE(Position("h8").rotate().toString() == "a1");
    REQUIRE(Position("d5").rotate().toString() == "e4");
    REQUIRE(Position("c3").rotate().toString() == "f6");
}

TEST_CASE("Test toString()")
{
    REQUIRE(Position().toString() == "-");
    REQUIRE(Position(0).toString() == "a1");
    REQUIRE(Position(7).toString() == "h1");
    REQUIRE(Position(56).toString() == "a8");
    REQUIRE(Position(63).toString() == "h8");
    REQUIRE(Position(35).toString() == "d5");
    REQUIRE(Position(3, 4).toString() == "d5");
    REQUIRE(Position("a1").toString() == "a1");
    REQUIRE(Position("h8").toString() == "h8");
}

TEST_CASE("Test operator==()")
{
    REQUIRE(Position() == Position());
    REQUIRE(Position(0) == Position(0));
    REQUIRE(Position(63) == Position(63));
    REQUIRE(Position(3, 4) == Position(3, 4));
    REQUIRE(Position("a1") == Position("a1"));
    REQUIRE(Position("h8") == Position("h8"));

    REQUIRE_FALSE(Position() == Position(0));
    REQUIRE_FALSE(Position(0) == Position(1));
    REQUIRE_FALSE(Position(3, 4) == Position(4, 3));
    REQUIRE_FALSE(Position("a1") == Position("b1"));
    REQUIRE_FALSE(Position("h8") == Position("g7"));
}

TEST_CASE("Test operator!=()")
{
    REQUIRE_FALSE(Position() != Position());
    REQUIRE_FALSE(Position(0) != Position(0));
    REQUIRE_FALSE(Position(63) != Position(63));
    REQUIRE_FALSE(Position(3, 4) != Position(3, 4));
    REQUIRE_FALSE(Position("a1") != Position("a1"));
    REQUIRE_FALSE(Position("h8") != Position("h8"));

    REQUIRE(Position() != Position(0));
    REQUIRE(Position(0) != Position(1));
    REQUIRE(Position(3, 4) != Position(4, 3));
    REQUIRE(Position("a1") != Position("b1"));
    REQUIRE(Position("h8") != Position("g7"));
}

TEST_CASE("Test operator<()")
{
    REQUIRE(Position(0) < Position(1));
    REQUIRE(Position(3) < Position(35));
    REQUIRE(Position("a1") < Position("a2"));
    REQUIRE(Position("a1") < Position("b1"));
    REQUIRE(Position("h7") < Position("h8"));

    REQUIRE_FALSE(Position(0) < Position(0));
    REQUIRE_FALSE(Position(1) < Position(0));
    REQUIRE_FALSE(Position(35) < Position(3));
    REQUIRE_FALSE(Position("a2") < Position("a1"));
    REQUIRE_FALSE(Position("b1") < Position("a1"));
    REQUIRE_FALSE(Position("h8") < Position("h7"));
    REQUIRE_FALSE(Position() < Position(0));
    REQUIRE_FALSE(Position(0) < Position());
    REQUIRE_FALSE(Position() < Position());
}

TEST_CASE("Test unsafeX()")
{
    REQUIRE(Position::unsafeX(Position(0)) == 0);
    REQUIRE(Position::unsafeX(Position(7)) == 7);
    REQUIRE(Position::unsafeX(Position(35)) == 3);
    REQUIRE(Position::unsafeX(Position(63)) == 7);
}

TEST_CASE("Test unsafeY()")
{
    REQUIRE(Position::unsafeY(Position(0)) == 0);
    REQUIRE(Position::unsafeY(Position(7)) == 0);
    REQUIRE(Position::unsafeY(Position(35)) == 4);
    REQUIRE(Position::unsafeY(Position(56)) == 7);
}

TEST_CASE("Test unsafeConstruct(int8_t, int8_t)")
{
    REQUIRE(Position::unsafeConstruct(0, 0).index() == 0);
    REQUIRE(Position::unsafeConstruct(7, 7).index() == 63);
    REQUIRE(Position::unsafeConstruct(3, 4).index() == 35);
    REQUIRE(Position::unsafeConstruct(0, 0).valid() == true);
    REQUIRE(Position::unsafeConstruct(7, 7).valid() == true);
}
