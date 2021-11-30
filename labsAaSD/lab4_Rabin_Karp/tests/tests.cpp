#include <catch2/catch.hpp>
#include "../sources/solve.hpp"

bool testCase(const std::string &pattern, const std::string &text, const std::vector<int> &rightAnswer) {
    auto answer = solve(pattern, text);
    if (answer.size() != rightAnswer.size())
        return false;
    for (int i = 0; i < answer.size(); ++i) {
        if (answer[i] != rightAnswer[i]) {
            return false;
        }
    }
    return true;
}


TEST_CASE("mainTests", "[test]")
{
    REQUIRE(testCase("a", "a", {0}));
    REQUIRE(testCase("a", "z", {}));
    REQUIRE(testCase("a", "abababa", {0,2,4,6}));
    REQUIRE(testCase("aBa", "abaBazbaba", {2}));
    REQUIRE(testCase("aa", "aaaaaaaab", {0, 1, 2, 3, 4, 5, 6}));
    REQUIRE(testCase("aa", "baaaaaaaa", {1, 2, 3, 4, 5, 6, 7}));
    REQUIRE(testCase("qwezxc", "jashqwezxckasjkqwezxaqwezxc", {4, 21}));
    REQUIRE(testCase("zb", "JFApzbGPLMdkozbAGKaijgozbpaszzbAkgqAD", {4, 13, 23, 29}));
    REQUIRE(testCase("Zb", "JFApZbGPLMdkoZbAGKaijgoZbpaszZbAkgqAD", {4, 13, 23, 29}));
}

