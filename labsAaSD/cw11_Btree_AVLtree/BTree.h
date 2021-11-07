#pragma once

#include <vector>
#include <cstdlib>
#include <iostream>

template<typename T>
struct BTreeNode {
    bool leaf;
    T* keys; // ключи (пользовательский тип)
    BTreeNode<T>** children; // массив указателей на детей
    int currSize;
};

#define NEW_ROOT 2
#define MODIFIED_NOT_ROOT 1
#define NOT_MODIFIED 0

template<typename T>
class BTree {
    unsigned int t = 2; // степень дерева
    BTreeNode<T>* root; // элемент - корень дерева
    bool (*lessThan)(T a, T b); // компаратор меньше
    void (*printKey)(T value); // вывод ключа

    void initNode(BTreeNode<T>* node);
    void freeNode(BTreeNode<T>* node);
    int findIndex(BTreeNode<T> *node, T key);
    int nodeInsert(BTreeNode<T> *node, T key);
    T nodeDelete(BTreeNode<T> *node, int index);
    void splitChild(BTreeNode<T>* node, int index);
    char mergeChildren(BTreeNode<T> *parent, int index);
    char fixChildSize(BTreeNode<T> *parent, int index);
public:
    BTree(unsigned int degree,
          bool (*lessThan)(T a, T b) = [](T a, T b) { return a < b; },
          void (*printKey)(T value) = [](T value) { std::cout << value; });
    ~BTree<T>();


    void insert(T key);
    void fakeInsert(BTreeNode<T> root);
    bool contains(T key);
};

template<typename T>
BTree<T>::BTree(unsigned int degree, bool (*lessThan)(T, T), void (*printKey)(T))
: lessThan(lessThan), printKey(printKey) {
    t = degree;
    root = new BTreeNode<T>;
    initNode(root);
    root->leaf = true;
}

template<typename T>
BTree<T>::~BTree<T>() {
    freeNode(root);
}

/// Начальная инициализация узла.
template<typename T>
void BTree<T>::initNode(BTreeNode<T> *node) {
    node->currSize = 0;
    node->keys = new T[2 * t - 1];
    node->children = new BTreeNode<T>*[2 * t];

}

/// Освобождение памяти, выделенной под узел.
template<typename T>
void BTree<T>::freeNode(BTreeNode<T>* node) {
    if (!node->leaf) {
        for (int i = 0; i <= node->currSize ; ++i) {
            freeNode(node->children[i]);
        }
    }
    delete node->children;
    delete node->keys;
    delete node;
}

/// Поиск индекса элемента k среди ключей узла.
/// Если К нет среди ключей, то возвращается индекс поддерева,
/// в котором он может содержаться.
template<typename T>
int BTree<T>::findIndex(BTreeNode<T> *node, T key) {
    int resIndex = 0;
    while (resIndex < node->currSize && lessThan(node->keys[resIndex], key))
        resIndex++;
    return resIndex;
}

/// Вставка ключа key в узел node
/// Возвращает индекс ключа key в node->key.
template<typename T>
int BTree<T>::nodeInsert(BTreeNode<T> *node, T key) {
    int index;
    // Освобождает место для ключа key
    for (index = node->currSize; index > 0 && lessThan(key, node->keys[index-1]) ; index--) {
        node->keys[index] = node->keys[index - 1];
        node->children[index + 1] = node->children[index];
    }
    // Вставляет key
    node->children[index + 1] = node->children[index];
    node->keys[index] = key;
    node->currSize++;

    return index;
}

/// Удаление ключа под номером index из узла
/// Возвращает значение удалённого ключа.
template<typename T>
T BTree<T>::nodeDelete(BTreeNode<T> *node, int index) {
    T res = node->keys[index];
    node->currSize--;
    while (index < node->currSize) {
        node->keys[index] = node->keys[index + 1];
        node->children[index + 1] = node->children[index + 2];
        index++;
    }
    return res;
}

/// функция для разделения узла, который слишком большой
/// node - узел для разбиения
/// index - индекс в массиве детей узла для разбиения
template<typename T>
void BTree<T>::splitChild(BTreeNode<T> *node, int index) {
    // toSplit - узел для разделения
    BTreeNode<T> *toSplit = node->children[index];
    // newNode - новый узел
    auto *newNode = new BTreeNode<T>;
    initNode(newNode);
    newNode->leaf = toSplit->leaf;
    newNode->currSize = t - 1;
    // Копируем вторую половину из узла для разделения в новый узел
    for (int i = 0; i < t - 1; ++i) {
        newNode->keys[i] = toSplit->keys[i + t];
    }
    if (!toSplit->leaf) {
        for (int i = 0; i < t; ++i) {
            newNode->children[i] = toSplit->children[i + t];
        }
    }
    toSplit->currSize = t - 1;

    nodeInsert(node, toSplit->keys[t - 1]);
    node->children[index + 1] = newNode;
}

/// Сливает i и i+1 ребёнка родительского узла воедино
/// Возвращает индикатор стороннего эффекта от операции
template<typename T>
char BTree<T>::mergeChildren(BTreeNode<T> *parent, int index) {
    BTreeNode<T> *leftChild = parent->children[index];
    BTreeNode<T> *rightChild = parent->children[index + 1];

    // Перемещаем элемент из родителя в левого потомка
    leftChild->keys[leftChild->currSize] = nodeDelete(parent, index);
    int j = ++(leftChild->currSize);

    // Перемещаем всё из правого потомка в левого
    for (int k = 0; k < rightChild->currSize; ++k) {
        leftChild->keys[j + k] = rightChild->keys[k];
        leftChild->children[j + k] = rightChild->children[k];
    }
    leftChild->currSize += rightChild->currSize;
    leftChild->children[leftChild->currSize] = rightChild->children[rightChild->currSize];

    // Освобождаем память, выделенную под правого потомка
    delete rightChild->children;
    delete rightChild->keys;
    delete rightChild;

    // Заменяем корень на левого потомка(т.к если родитель пуст, то он - корень)
    // Также освобождаем память, выделенную
    if (parent->currSize == 0) {
        root = leftChild;
        delete parent->children;
        delete parent->keys;
        delete parent;
        return NEW_ROOT;
    }
    return MODIFIED_NOT_ROOT;
}

/// Проверка на сохранение свойства B-дерева - каждый дочерний узел имеет как минимум t-1 элемент
/// Если это не так, то свойство фиксится
/// Возвращает отчёт о предпринятых действиях
template<typename T>
char BTree<T>::fixChildSize(BTreeNode<T> *parent, int index) {
    BTreeNode<T> *child = parent->children[index];

    if (child->currSize < t) { // если нужно исправить
        // пробуем перенести из левого потомка
        if (index != 0 && parent->children[index - 1]->currSize >= t) {
            BTreeNode<T> *leftChild = parent->children[index - 1];
            // если есть последовательность равных ключей, то сдвигаем потомков
            for (int i = nodeInsert(child, parent->keys[index - 1]); i != 0; --i) { // HARD ???
                child->children[i] = child->children[i - 1]; //если ключи схожи, то переносим
            }
            // забираем самого правого потомка у левого потомка
            child->children[0] = leftChild->children[leftChild->currSize];
            parent->keys[index - 1] = nodeDelete(leftChild, leftChild->currSize - 1);
        } else if (index != parent->currSize && parent->children[index + 1]->currSize >= t) {
            // Пробуем перенести из правого потомка
            BTreeNode<T> *rightChild = parent->children[index + 1];
            // Перемещаем ключ из родителя в потомка
            nodeInsert(child, parent->keys[index]);
            child->children[child->currSize] = rightChild->children[0];
            rightChild->children[0] = rightChild->children[1]; // делаем смещение вместо
            // перемещаем ключ из правого потомка в родителя (забираем)
            parent->key[index] = nodeDelete(rightChild, 0);
        } else if (index != 0)
            return mergeChildren(parent, index -1);
        else
            return mergeChildren(parent, index);
        return MODIFIED_NOT_ROOT;
    }
    // не пришлось ничего делать
    return NOT_MODIFIED;
}


/// Вставляем ключ k в дерево
template<typename T>
void BTree<T>::insert(T key) {
    // если корень заполнен - разбиваем его
    if (root->currSize == 2 * t - 1) {
        auto *newRoot = new BTreeNode<T>;
        initNode(newRoot);
        newRoot->leaf = false;
        newRoot->children[0] = root;
        root = newRoot;
        splitChild(newRoot, 0);
    }

    BTreeNode<T> *curr = root;
    while (!curr->leaf) {
        // ищем потомка, который подойдёт
         int index = curr->currSize - 1;
        while (index >= 0 && lessThan(key, curr->keys[index])) {
            index--;
        }
        index++;
        // разбиваем потомка, если он полон
        if (curr->children[index]->currSize == 2 * t - 1) {
            splitChild(curr, index);
            if (lessThan(curr->keys[index], key)) {
                index++;
            }
        }
        curr = curr->children[index];
    }
    nodeInsert(curr, key);
}



