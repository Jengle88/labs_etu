#pragma once

#include <vector>
#include <memory>
#include <iostream>

class BTreeNode {
    bool leaf;
    int deg;
    int size;
    std::vector<int> keys;
    std::vector<std::shared_ptr<BTreeNode>> children;

    void fillNode();

    // Находим индекс первой позиции, равный или больший, чем ключ
    int findEqualGreaterKey(int key);

    void remove(int key);

    void removeFromLeaf(int index);

    void removeFromNonLeaf(int index);

    int getPredecessor(int index);

    int getSuccessor(int index);

    // Заполняем дочерние элементы [index], у которых меньше ключей deg
    void fill(int index);

    // Заимствуем ключ у потомков [index-1] и вставляем его в потомки [index]
    void borrowFromPrev(int index);

    // Симметричный с заимствованием FromPrev
    void borrowFromNext(int index);

    // объединить children [index + 1] в children [index]
    void merge(int index);

    void insertNotFull(int key);

    void splitChildNode(int index, std::shared_ptr<BTreeNode> node);

    void traverse() const;

    void getArray(std::vector<int> &array);

    std::pair<const BTreeNode*, int> search(int key);
public:
    BTreeNode(int deg, bool leaf);

    friend class BTree;
};
