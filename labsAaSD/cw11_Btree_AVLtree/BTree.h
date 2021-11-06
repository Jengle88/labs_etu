#pragma once
#include <vector>
#include <cstdlib>
#include <iostream>

template<typename T>
class BTreeNode {
    bool leaf = true; // это лист?
    std::vector<T> keys; // ключи (пользовательский тип)
    std::vector<BTreeNode> children; // массив детей
};

template<typename T>
class BTree {
    unsigned int degree = 2; // степень дерева
    BTreeNode<T> root; // элемент - корень дерева
    bool (*lessThan)(T a, T b); // компаратор меньше
    void (*printKey)(T value); // вывод ключа

public:
    BTree(unsigned int degree, std::vector<T> &array,
          bool (*lessThan)(T a, T b) = [](T a, T b){ return a < b; },
          bool (*printKey)(T value) = [](T value) {std::cout << value; });
    void add(T value);
};

template<typename T>
BTree<T>::BTree(unsigned int degree, std::vector<T> &array, bool (*lessThan)(T, T), bool (*printKey)(T)) {
    this->degree = degree;
    // TODO: придумать инициализацию дерева (в худшем случае - вставку всего массива) и инициализацию root
    for (int i = 0; i < array.size(); ++i) {
        add(array[i]); // FIXME исправить
    }
    this->lessThan = lessThan;
    this->printKey = printKey;
}



