#include "AVLTree.h"

void AVLTree::traverse() {
    root->traverse(root);
}

const std::shared_ptr<AVLTreeNode>& AVLTree::search(int key) const {
    if (root == nullptr || root->key == key)
        return root;
    if (root->key > key)
        return root->search(root->left, key);
    else
        return root->search(root->right, key);
}

void AVLTree::insert(int key) {
    root = root->insert(root, key);
}

void AVLTree::remove(int key) {
    root = root->remove(root, key);
}

std::vector<int> AVLTree::getArray() {
    std::vector<int> result;
    root->getArray(root, result);
    return result;
}
