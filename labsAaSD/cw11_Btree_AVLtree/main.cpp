#include <iostream>
#include "BTree.h"


int main() {
    std::vector<int> init(2, 1);
    BTree<int> bTree(4, init);


    /// Search tests
    BTreeNode<int> root({4, 17, 31}, {
            BTreeNode<int>({1, 2, 3}, {}),
            BTreeNode<int>({7, 9, 11, 13, 16}, {}),
            BTreeNode<int>({19, 26, 27}, {}),
            BTreeNode<int>({96, 97, 99}, {}),
    });
    bTree.fakeInsert(root);
    std::cout << bTree.contains(5) << "\n";
    std::cout << bTree.contains(11) << "\n";
    std::cout << bTree.contains(12) << "\n";
    std::cout << bTree.contains(13) << "\n";
    std::cout << bTree.contains(27) << "\n";
    std::cout << bTree.contains(31) << "\n";
    std::cout << bTree.contains(100) << "\n";
    std::cout << bTree.contains(99) << "\n";
    std::cout << bTree.contains(19) << "\n";
    std::cout << "-----------------\n";
    root = BTreeNode<int>({5}, {});
    bTree.fakeInsert(root);
    std::cout << bTree.contains(5) << "\n";
    std::cout << bTree.contains(11) << "\n";
    std::cout << bTree.contains(12) << "\n";
    std::cout << bTree.contains(13) << "\n";
    std::cout << bTree.contains(27) << "\n";
    return 0;
}
