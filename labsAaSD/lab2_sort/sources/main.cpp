#include <iostream>
#include <vector>

class SquareMatrix {
    int size;
    int id;
    std::vector<std::vector<int>> matrix;
public:

    SquareMatrix() {}

    SquareMatrix(int id, std::vector<std::vector<int>> matrix) : size(matrix.size()), id(id), matrix(matrix) {}

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


class Functional {
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
    static std::vector<T> mergeSubSortStable(const std::vector<T> &array, int l, int r,
                                             bool (*compareLessEqual)(const T &, const T &)) {
        if (l < 0 || r >= array.size() || l > r)
            return {};
        if (l == r)
            return std::vector<T>{array[l]};
        else {
            std::vector<T> leftArray = mergeSubSortStable(array, l, (r + l - 1) / 2, compareLessEqual);
            std::vector<T> rightArray = mergeSubSortStable(array, (r + l - 1) / 2 + 1, r, compareLessEqual);
            auto res = mergeArray(leftArray, rightArray, compareLessEqual);
            return res;
        }
    }

    static std::vector<SquareMatrix> mergeSubSortStable(const std::vector<SquareMatrix> &array, int l, int r,
                                                        bool (*compareLessEqual)(const SquareMatrix &,
                                                                                 const SquareMatrix &)) {
        if (l < 0 || r >= array.size() || l > r)
            return {};
        if (l == r)
            return std::vector<SquareMatrix>{array[l]};
        else {
            std::vector<SquareMatrix> leftArray = mergeSubSortStable(array, l, (r + l - 1) / 2, compareLessEqual);
            std::vector<SquareMatrix> rightArray = mergeSubSortStable(array, (r + l - 1) / 2 + 1, r, compareLessEqual);
            auto res = mergeArray(leftArray, rightArray, compareLessEqual);
            for (int i = 0; i < res.size(); ++i) {
                std::cout << res[i].getId() << ' ';
            }
            std::cout << '\n';
            return res;
        }
    }

public:
    template<class T>
    static void mergeSortStable(std::vector<T> &array,
                                bool (*compareLessEqual)(const T &, const T &) = [](const T &left, const T &right) {
                                    return left <= right;
                                }) {
        int l = 0, r = array.size() - 1;
        auto leftArray = mergeSubSortStable(array, l, (r + l - 1) / 2, compareLessEqual);
        auto rightArray = mergeSubSortStable(array, (r + l - 1) / 2 + 1, r, compareLessEqual);
        array = mergeArray(leftArray, rightArray, compareLessEqual);
    }

    static void mergeSortStable(std::vector<SquareMatrix> &array,
                                bool (*compareLessEqual)(const SquareMatrix &, const SquareMatrix &) = [](
                                        const SquareMatrix &left, const SquareMatrix &right) {
                                    return left <= right;
                                }) {
        int l = 0, r = array.size() - 1;
        auto leftArray = mergeSubSortStable(array, l, (r + l - 1) / 2, compareLessEqual);
        auto rightArray = mergeSubSortStable(array, (r + l - 1) / 2 + 1, r, compareLessEqual);
        array = mergeArray(leftArray, rightArray, compareLessEqual);
        for (int i = 0; i < array.size(); ++i) {
            std::cout << array[i].getId() << ' ';
        }
        std::cout << '\n';
    }
};


int main() {
    int n;
    std::cin >> n;
    std::vector<SquareMatrix> matrixArray(n);
    for (int i = 0; i < n; ++i) {
        int matrixSize;
        std::cin >> matrixSize;
        std::vector<std::vector<int>> matrix(matrixSize, std::vector<int>(matrixSize));
        for (int j = 0; j < matrixSize; ++j) {
            for (int k = 0; k < matrixSize; ++k) {
                std::cin >> matrix[j][k];
            }
        }
        matrixArray[i] = SquareMatrix(i, matrix);
    }
    Functional::mergeSortStable(matrixArray);
    for (auto &item: matrixArray) {
        std::cout << item.getId() << ' ';
    }
    return 0;
}
