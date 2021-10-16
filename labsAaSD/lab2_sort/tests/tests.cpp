#include <catch2/catch.hpp>
#include "../sources/solve.hpp"

template<typename T>
bool testCase(std::vector<T> testCase) {
    auto test = testCase;
    SortLibs::mergeSortStable(test);
    std::stable_sort(testCase.begin(), testCase.end());
    return test == testCase;
}



TEMPLATE_TEST_CASE("Template test case", "[vector][template]", int, double, SquareMatrix) {
    REQUIRE(testCase(std::vector<TestType>{}));
}


TEST_CASE("Simple type sort tests", "[test]")
{
    REQUIRE(testCase(std::vector<int>{}));
    REQUIRE(testCase(std::vector<int>{1}));
    REQUIRE(testCase(std::vector<int>{-1}));
    REQUIRE(testCase(std::vector<double>{-1.0, -1.0, 96.0, 12.0, -15.0}));
    REQUIRE(testCase(std::vector<int>{5, -6, 9, 9, 9, -3, 14, 35}));
    REQUIRE(testCase(std::vector<int>{5, -6, 9, 9, -3, 14, 35}));
}

TEST_CASE("SquareMatrix type sort tests", "[test]")
{
    auto matrix1 = std::vector<std::vector<int>>{{1, 2, 3},
                                                 {4, 5, 6},
                                                 {7, 8, 9}};
    auto matrix2 = std::vector<std::vector<int>>{{1}};
    auto matrix3 = std::vector<std::vector<int>>{{-1}};
    auto matrix4 = std::vector<std::vector<int>>{{1, 1, 1},
                                                 {1, -3, 1},
                                                 {1, 1, 1}};
    auto matrix5 = std::vector<std::vector<int>>{{1, 1, 1, 2},
                                                 {1, -2, 1, 8},
                                                 {1, 1, 1, 9},
                                                 {1, -1, -1, 9}};

    REQUIRE(testCase(std::vector<SquareMatrix>{}));

    REQUIRE(testCase(std::vector<SquareMatrix>{SquareMatrix(0, matrix1)}));

    REQUIRE(testCase(std::vector<SquareMatrix>{SquareMatrix(0, matrix1),
                                               SquareMatrix(1, matrix2)}));

    REQUIRE(testCase(std::vector<SquareMatrix>{SquareMatrix(0, matrix2),
                                               SquareMatrix(1, matrix3)}));

    REQUIRE(testCase(std::vector<SquareMatrix>{SquareMatrix(0, matrix1),
                                               SquareMatrix(1, matrix2),
                                               SquareMatrix(2, matrix3),
                                               SquareMatrix(3, matrix4),
                                               SquareMatrix(4, matrix5)}));

}
