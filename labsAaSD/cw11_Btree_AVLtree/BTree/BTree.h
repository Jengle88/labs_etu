#pragma once

#include <iostream>
#include <deque>
#include <memory>
#include <vector>
#include "BTreeNode.h"


class BTree {
    std::shared_ptr<BTreeNode> root;
    int deg;
public:
    explicit BTree(int deg);

    void traverse() const;

    std::vector<int> getArray() const;

    std::pair<const BTreeNode*, int> search(int key);

    void insert(int key);

    void remove(int key);
};















