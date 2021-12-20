#pragma once

#include <memory>
#include <vector>

class AVLTreeNode {
    int key;
    unsigned char height;
    std::shared_ptr<AVLTreeNode> left;
    std::shared_ptr<AVLTreeNode> right;

    // починить высоту
    void fixHeight(std::shared_ptr<AVLTreeNode>& node) const;

    // малый правый поворот
    std::shared_ptr<AVLTreeNode> smallRightRotate(std::shared_ptr<AVLTreeNode>& pNode);

    // малый левый поворот
    std::shared_ptr<AVLTreeNode> smallLeftRotate(std::shared_ptr<AVLTreeNode>& qNode);

    // балансировка большим поворотом
    std::shared_ptr<AVLTreeNode> balance(std::shared_ptr<AVLTreeNode>& pNode);

    // ищем вершину с самым маленьким ключом
    std::shared_ptr<AVLTreeNode> findMinNode(std::shared_ptr<AVLTreeNode>& pNode) const;

    // удаление узла с минимальным ключом из дерева p
    std::shared_ptr<AVLTreeNode> removeMin(std::shared_ptr<AVLTreeNode>& pNode);

    // получить разницу между высотами
    int getBalanceFactor(const std::shared_ptr<AVLTreeNode>& node) const;

public:
    explicit AVLTreeNode(int k) : key(k), height(1), left(nullptr), right(nullptr) {}

    // получить высоту (защита от nullptr)
    unsigned char getHeight(const std::shared_ptr<AVLTreeNode>& node) const;

    // получить массив данных
    void getArray(const std::shared_ptr<AVLTreeNode> &pNode, std::vector<int> &array) const;

    // пройтись и вывести все элементы поддерева
    void traverse(const std::shared_ptr<AVLTreeNode>& pNode) const;

    const std::shared_ptr<AVLTreeNode>& search(const std::shared_ptr<AVLTreeNode>& pNode, int key) const;
    // вставка элемента key в поддерево с корнем pNode
    std::shared_ptr<AVLTreeNode> insert(std::shared_ptr<AVLTreeNode>& pNode, int key);

    // удаление ключа k из дерева p
    std::shared_ptr<AVLTreeNode> remove(std::shared_ptr<AVLTreeNode>& pNode, int key);

    friend class AVLTree;
};


