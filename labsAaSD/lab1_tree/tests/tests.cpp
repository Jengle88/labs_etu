#include <catch2/catch.hpp>
#include "../source/solve.hpp"

TEST_CASE("Height tests", "[test]")
{
    REQUIRE(solveHeight(5, {4, -1, 4, 1, 1}) == 3);
    REQUIRE(solveHeight(5, {-1, 0, 4, 0, 3}) == 4);
    REQUIRE(solveHeight(1, {-1}) == 1);
    REQUIRE(solveHeight(0, {}) == 0);
    REQUIRE(solveHeight(8, {-1, 0, 1, 1, 3, 0, 5, 4}) == 5);
    REQUIRE(solveHeight(10, {-1, 0, 1, 1, 3, 0, 5, 4, 6, 8}) == 5);
    REQUIRE(solveHeight(3, {-1, 0, 1}) == 3);
    REQUIRE(solveHeight(2, {-1, 0}) == 2);
}
TEST_CASE("DFS test", "[test]")
{
    REQUIRE(solveDFS(5, {-1, 0, 0, 1, 1}) == 10);
    REQUIRE(solveDFS(4, {-1, 0, 0, 0}) == 6);
    REQUIRE(solveDFS(0, {}) == 0);
    REQUIRE(solveDFS(1, {-1}) == 0);
}
