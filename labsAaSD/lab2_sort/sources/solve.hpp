#include <iostream>
#include <vector>


class SquareMatrix {
    int size;
    int id;
    std::vector<std::vector<int>> matrix;
public:

    SquareMatrix() {}

    SquareMatrix(int id, std::vector<std::vector<int>> matrix) : id(id), size(matrix.size()), matrix(matrix) {}

    int calcTrace() const {
        int res = 0;
        for (int i = 0; i < this->size; ++i) {
            res += this->matrix[i][i];
        }
        return res;
    }

    int getId() const {
        return id;
    }

    friend bool operator==(const SquareMatrix &val1, const SquareMatrix &val2) {
        return (val1.calcTrace() == val2.calcTrace());
    }

    friend bool operator<(const SquareMatrix &val1, const SquareMatrix &val2) {
        return (val1.calcTrace() < val2.calcTrace());
    }

    friend bool operator<=(const SquareMatrix &val1, const SquareMatrix &val2) {
        return val1 < val2 || val1 == val2;
    }

};


class SortLibs {
    template<typename T>
    static std::vector<T> mergeArray(const std::vector<T> &array1, const std::vector<T> &array2,
                                     bool (*compareLessEqual)(const T &, const T &)) {
        std::vector<T> result;
        result.reserve(array1.size() + array2.size());
        int index1 = 0, index2 = 0;
        while (index1 != array1.size() && index2 != array2.size()) {
            if (compareLessEqual(array1[index1], array2[index2]))
                result.push_back(array1[index1++]);
            else
                result.push_back(array2[index2++]);
        }
        if (index1 == array1.size()) {
            while (index2 < array2.size()) {
                result.push_back(array2[index2++]);
            }
        } else {
            while (index1 < array1.size()) {
                result.push_back(array1[index1++]);
            }
        }
        return result;
    }

    template<typename T>
    static constexpr std::vector<T> mergeSubSortStable(const std::vector<T> &array, int l, int r,
                                                       bool (*compareLessEqual)(const T &, const T &),
                                                       void (*printInfo)(const std::vector<T> &) = [](
                                                               const std::vector<T> &) {}
    ) {
        if (l < 0 || r >= array.size() || l > r)
            return {};
        if (l == r)
            return std::vector<T>{array[l]};
        else {
            std::vector<T> leftArray = mergeSubSortStable(array, l, (r + l - 1) / 2, compareLessEqual);
            std::vector<T> rightArray = mergeSubSortStable(array, (r + l - 1) / 2 + 1, r, compareLessEqual);
            auto res = mergeArray(leftArray, rightArray, compareLessEqual);
            printInfo(res);
            return res;
        }
    }

public:
    template<class T>
    static constexpr void mergeSortStable(std::vector<T> &array,
                                          bool (*compareLessEqual)(const T &, const T &) = [](const T &left,
                                                                                              const T &right) {
                                              return left <= right;
                                          },
                                          void (*printInfo)(const std::vector<T> &) = [](const std::vector<T> & arr) {}) {
        int l = 0, r = array.size() - 1;
        auto leftArray = mergeSubSortStable(array, l, (r + l - 1) / 2, compareLessEqual);
        auto rightArray = mergeSubSortStable(array, (r + l - 1) / 2 + 1, r, compareLessEqual);
        array = mergeArray(leftArray, rightArray, compareLessEqual);
        printInfo(array);
    }
};