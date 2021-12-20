#include <iostream>
#include "AVLTreeNode.h"

unsigned char AVLTreeNode::getHeight(const std::shared_ptr<AVLTreeNode>& node) const {
    return node ? node->height : 0;
}

int AVLTreeNode::getBalanceFactor(const std::shared_ptr<AVLTreeNode>& node) const {
    return getHeight(node->right) - getHeight(node->left); // разница между высотой двух поддеревьев
}

void AVLTreeNode::fixHeight(std::shared_ptr<AVLTreeNode> &node) const {
    unsigned char heightL = getHeight(node->left);
    unsigned char heightR = getHeight(node->right);
    node->height = (heightL > heightR ? heightL : heightR) + 1; // перерасчёт высоты
}

std::shared_ptr<AVLTreeNode> AVLTreeNode::smallRightRotate(std::shared_ptr<AVLTreeNode> &pNode) {
    std::shared_ptr<AVLTreeNode> qNode = pNode->left;
    pNode->left = qNode->right;
    qNode->right = pNode;
    fixHeight(pNode);
    fixHeight(qNode);
    return qNode;
}

std::shared_ptr<AVLTreeNode> AVLTreeNode::smallLeftRotate(std::shared_ptr<AVLTreeNode> &qNode) {
    std::shared_ptr<AVLTreeNode> pNode = qNode->right; // симметрия с правым
    qNode->right = pNode->left;
    pNode->left = qNode;
    fixHeight(qNode);
    fixHeight(pNode);
    return pNode;
}

std::shared_ptr<AVLTreeNode> AVLTreeNode::balance(std::shared_ptr<AVLTreeNode>& pNode) {
    fixHeight(pNode);
    if (getBalanceFactor(pNode) == 2) { // правый большой поворот
        if (getBalanceFactor(pNode->right) < 0)
            pNode->right = smallRightRotate(pNode->right);
        return smallLeftRotate(pNode);
    } else if (getBalanceFactor(pNode) == -2) { // левый большой поворот
        if (getBalanceFactor(pNode->left) > 0)
            pNode->left = smallLeftRotate(pNode->left);
        return smallRightRotate(pNode);
    }
    return pNode; // балансировка не требуется
}

std::shared_ptr<AVLTreeNode> AVLTreeNode::insert(std::shared_ptr<AVLTreeNode> &pNode, int key) {
    if (pNode == nullptr)
        return std::make_shared<AVLTreeNode>(key);
    if (key < pNode->key)
        pNode->left = insert(pNode->left, key); // вставка в левое поддерево
    else
        pNode->right = insert(pNode->right, key); // вставка в правое поддерево
    return balance(pNode); // балансировка дерева при выходе
}

std::shared_ptr<AVLTreeNode> AVLTreeNode::findMinNode(std::shared_ptr<AVLTreeNode> &pNode) const {
    return pNode->left ? findMinNode(pNode->left) : pNode;
}

std::shared_ptr<AVLTreeNode> AVLTreeNode::removeMin(std::shared_ptr<AVLTreeNode> &pNode) {
    if (pNode->left == nullptr)
        return pNode->right; // так как дерево сбалансированное и у вершины в правой части лишь один элемент
    pNode->left = removeMin(pNode->left);
    return balance(pNode);
}

std::shared_ptr<AVLTreeNode> AVLTreeNode::remove(std::shared_ptr<AVLTreeNode> &pNode, int key) {
    if (pNode == nullptr) // ключ не нашёлся
        return nullptr;
    if (key < pNode->key) // процесс поиска вершины с ключом
        pNode->left = remove(pNode->left, key);
    else if (key > pNode->key)
        pNode->right = remove(pNode->right, key);
    else { // когда нашли нужную вершину
        std::shared_ptr<AVLTreeNode> lNode = pNode->left;
        std::shared_ptr<AVLTreeNode> rNode = pNode->right;
        pNode.reset(); // удаляем указатель на вершину
        // нужно найти правую малую вершину и заменить ей удаляемую
        if (rNode == nullptr) // если правой вершины нет, то подвешиваем за левую
            return lNode;
        std::shared_ptr<AVLTreeNode> minNode = findMinNode(rNode);
        minNode->right = removeMin(rNode); // заменяем вершину и ставим справа поддерево без правой минимальной вершины
        minNode->left = lNode; // левое поддерево сохраняем
        return balance(minNode);
    }
    return balance(pNode);
}

void AVLTreeNode::traverse(const std::shared_ptr<AVLTreeNode> &pNode) const {
    if (pNode == nullptr)
        return;
    if (pNode->left != nullptr) // выводим левую часть
        traverse(pNode->left);
    std::cout << pNode->key << ' '; // выводим ключ
    if (pNode->right != nullptr)
        traverse(pNode->right); // выводим правую часть
}

const std::shared_ptr<AVLTreeNode> &AVLTreeNode::search(const std::shared_ptr<AVLTreeNode> &pNode, int key) const {
    if (pNode == nullptr || pNode->key == key) // если пришли к конечной ситуации
        return pNode;
    if (pNode->key > key)
        return pNode->search(pNode->left, key); // ищем в левом поддереве
    else
        return pNode->search(pNode->right, key); // ищем в правом поддереве
}

void AVLTreeNode::getArray(const std::shared_ptr<AVLTreeNode> &pNode, std::vector<int> &array) const {
    if (pNode == nullptr) // по аналогии с traverse
        return;
    if (pNode->left != nullptr)
        getArray(pNode->left, array);
    array.push_back(pNode->key);
    if (pNode->right != nullptr)
        getArray(pNode->right, array);
}
