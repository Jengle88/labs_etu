#pragma once
#include <vector>
#include <cstdlib>
#include <iostream>
template<typename T>
class BTree;

template<typename T>
class BTreeNode {
    std::vector<T> keys; // ключи (пользовательский тип)
    std::vector<BTreeNode> children; // массив детей
public:
    friend class BTree<T>;
    BTreeNode(std::vector<T> keys, std::vector<BTreeNode> children) : keys(keys), children(children){};
    BTreeNode() = default;
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
          void (*printKey)(T value) = [](T value) {std::cout << value; });
    void insert(T key);
    void fakeInsert(BTreeNode<T> root);
    bool contains(T key);
};

template<typename T>
BTree<T>::BTree(unsigned int degree, std::vector<T> &array, bool (*lessThan)(T, T), void (*printKey)(T)) {
    this->degree = degree;
    // TODO: придумать инициализацию дерева (в худшем случае - вставку всего массива) и инициализацию root
    for (int i = 0; i < array.size(); ++i) {
//        insert(array[i]); // FIXME исправить
    }
    this->lessThan = lessThan;
    this->printKey = printKey;
}

template<typename T> // Рабочий
bool BTree<T>::contains(T key) {
    const BTreeNode<T>* tempNode = &root;
    while (true) {
        if (tempNode == nullptr || tempNode->keys.empty()) { // дальше искать нет смысла, выходим
            return false;
        }
        if (lessThan(key, tempNode->keys.front())) { // меньше всех
            tempNode = tempNode->children.empty() ? nullptr : &(tempNode->children.front()); // безопасная проверка листа
            continue;
        }
        bool rangeFound = false;
        for (int i = 0; i < tempNode->keys.size(); ++i) {
            if (key == tempNode->keys[i]) // нашли элемент // TODO заменить на пользовательский equal?
                return true;
            else if (lessThan(key, tempNode->keys[i])) { // нашли промежуток для элемента
                rangeFound = true;
                tempNode = tempNode->children.empty() ? nullptr : &(tempNode->children[i]);
                break;
            }
        }
        if (!rangeFound) // больше всех
            tempNode = tempNode->children.empty() ? nullptr : &(tempNode->children.back());
    }
}

template<typename T>
void BTree<T>::fakeInsert(BTreeNode<T> root) {
    this->root = root;
}

template<typename T>
void BTree<T>::insert(T key) {

}



