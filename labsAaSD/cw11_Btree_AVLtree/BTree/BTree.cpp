#include "BTree.h"

BTree::BTree(int deg) {
    this->root = nullptr;
    this->deg = deg;
}

void BTree::traverse() const {
    if (root != nullptr)
        root->traverse();
}

std::pair<const BTreeNode *, int> BTree::search(int key) {
    return root == nullptr ? std::make_pair(nullptr, -1) : root->search(key);
}

void BTree::insert(int key) {
    if (root == nullptr) { // корень не создавался
        (root = std::make_shared<BTreeNode>(deg, true))->fillNode();
        root->keys[0] = key;
        root->size = 1;
    } else {
        // Когда корневой узел заполнится, дерево станет выше
        if (root->size == 2 * deg - 1) {
            auto newNode = std::make_shared<BTreeNode>(deg, false);
            newNode->children[0] = root;
            newNode->fillNode();
            newNode->splitChildNode(0, root);
            int i = 0;
            if (newNode->keys[0] < key)
                i++;
            newNode->children[i]->insertNotFull(key);
            root = newNode;
        } else
            root->insertNotFull(key);
    }
}

void BTree::remove(int key) {
    if (root == nullptr) {
        std::cout << "The tree is empty";
        return;
    }
    root->remove(key);
    if (root->size == 0) {
        if (root->leaf) {
            root = nullptr;
        }
        else {
            root = std::move(root->children[0]);
        }
    }
}

std::vector<int> BTree::getArray() const {
    std::vector<int> result;
    root->getArray(result);
    return result;
}
