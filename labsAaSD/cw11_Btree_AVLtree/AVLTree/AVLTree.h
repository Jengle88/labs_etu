#pragma once

#include <vector>
#include "AVLTreeNode.h"

class AVLTree {
    std::shared_ptr<AVLTreeNode> root = nullptr;
public:
    AVLTree() = default;
    void traverse();
    std::vector<int> getArray();
    const std::shared_ptr<AVLTreeNode>& search(int key) const;
    void insert(int key);
    void remove(int key);
};









