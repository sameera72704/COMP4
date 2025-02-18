// copyrightr 2024 Sakinala Sameera
#include <sstream>
#include <ostream>
#include <iostream>
#include <SFML/System/Vector2.hpp>

namespace sf {
template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector2<T>& vec) {
return os << "(" << vec.x << ", " << vec.y << ")";
}
}

#define BOOST_TEST_MODULE SokobanTests
#include <boost/test/included/unit_test.hpp>
#include "Sokoban.hpp"

// Fixture setup for consistent game state initialization across tests
struct GameFixture {
    SB::Sokoban game;
    GameFixture() {
        std::stringstream ss;
        ss << "5 5\n"
           << "#####\n"
           << "#@.A#\n"
           << "#.a.#\n"
           << "#...#\n"
           << "#####\n";
        ss >> game;
    }
};

BOOST_FIXTURE_TEST_SUITE(SokobanTests, GameFixture)

BOOST_AUTO_TEST_CASE(BasicMovement) {
    auto initialPos = game.playerLoc();
    std::cout << "Initial position: " << initialPos << std::endl;

    game.movePlayer(SB::Direction::Right);
    auto newPos = game.playerLoc();
    std::cout << "Position after moving right: " << newPos << std::endl;

    BOOST_TEST(newPos.x == initialPos.x + 1);
    BOOST_TEST(newPos.y == initialPos.y);
}

BOOST_AUTO_TEST_CASE(WallCollision) {
    auto initialPos = game.playerLoc();
    game.movePlayer(SB::Direction::Up);
    BOOST_TEST(game.playerLoc() == initialPos);
}

BOOST_AUTO_TEST_CASE(BoxPushing) {
    auto initialPos = game.playerLoc();
    game.movePlayer(SB::Direction::Right);
    auto posAfterOneMove = game.playerLoc();
    std::cout << "Position after one move right: "
    << posAfterOneMove << std::endl;

    game.movePlayer(SB::Direction::Right);
    auto posAfterTwoMoves = game.playerLoc();
    std::cout << "Position after two moves right: "
    << posAfterTwoMoves << std::endl;

    BOOST_TEST(posAfterTwoMoves.x == initialPos.x + 2);
    BOOST_TEST(posAfterTwoMoves.y == initialPos.y);
    BOOST_CHECK_EQUAL(game.getTile(3, 1), 'A');
}

BOOST_AUTO_TEST_CASE(WinCondition) {
    std::cout << "Initial game state:" << std::endl << game << std::endl;

    game.movePlayer(SB::Direction::Right);
    game.movePlayer(SB::Direction::Right);
    game.movePlayer(SB::Direction::Down);
    BOOST_CHECK(!game.isWon());
    std::cout << "Game state before final move:"
    << std::endl << game << std::endl;

    game.movePlayer(SB::Direction::Right);
    std::cout << "Game state after final move:"
    << std::endl << game << std::endl;
    std::cout << "Is won: " << (game.isWon() ? "true" : "false") << std::endl;

    BOOST_CHECK_MESSAGE(game.isWon(),
    "Game should be won when all boxes are on storage locations");
}

BOOST_AUTO_TEST_CASE(ResetGame) {
    auto initialPos = game.playerLoc();
    game.movePlayer(SB::Direction::Right);
    game.movePlayer(SB::Direction::Right);
    game.reset();
    BOOST_TEST(game.playerLoc() == initialPos);
}

BOOST_AUTO_TEST_CASE(TestSwap) {
    std::stringstream ss;
    ss << "5 5\n"
       << "#####\n"
       << "#@aA#\n"
       << "#...#\n"
       << "#...#\n"
       << "#####\n";
    SB::Sokoban game;
    ss >> game;

    game.movePlayer(SB::Direction::Up);
    game.movePlayer(SB::Direction::Down);
    game.movePlayer(SB::Direction::Right);
    game.movePlayer(SB::Direction::Right);
    game.movePlayer(SB::Direction::Up);
    game.movePlayer(SB::Direction::Left);

    BOOST_CHECK(game.isWon());
}
BOOST_AUTO_TEST_SUITE_END()
