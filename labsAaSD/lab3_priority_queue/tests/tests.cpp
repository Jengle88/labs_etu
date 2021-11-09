#include <catch2/catch.hpp>
#include "../sources/solve.hpp"

bool testCase(int n, int m, const std::vector<int> &arrayDuration, const std::vector<ResultTask> &arrayResult) {
    auto answer = solve(n, m, arrayDuration);
    bool ok = true;
    for (int i = 0; i < m; ++i) {
        if (answer[i] != arrayResult[i]) {
            ok = false;
            break;
        }
    }
    delete[] answer;
    return ok;
}


TEST_CASE("mainTests", "[test]")
{
    REQUIRE(testCase(1, 1, {5}, {ResultTask(0, 0)}));
    REQUIRE(testCase(1, 2, {5, 2}, {ResultTask(0, 0), ResultTask(0, 5)}));
    REQUIRE(testCase(2, 2, {5, 2}, {ResultTask(0, 0), ResultTask(1, 0)}));
    REQUIRE(testCase(3, 2, {5, 2}, {ResultTask(0, 0), ResultTask(1, 0)}));
    REQUIRE(testCase(3, 10, {1, 1, 1, 2, 2, 2, 3, 3, 3, 4}, {
            ResultTask(0, 0), ResultTask(1, 0), ResultTask(2, 0), ResultTask(0, 1), ResultTask(1, 1), ResultTask(2, 1),
            ResultTask(0, 3), ResultTask(1, 3), ResultTask(2, 3), ResultTask(0, 6)
    }));
    REQUIRE(testCase(3, 10, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, {
            ResultTask(0, 0), ResultTask(1, 0), ResultTask(2, 0), ResultTask(0, 1), ResultTask(1, 2), ResultTask(2, 3),
            ResultTask(0, 5), ResultTask(1, 7), ResultTask(2, 9), ResultTask(0, 12)
    }));
}

