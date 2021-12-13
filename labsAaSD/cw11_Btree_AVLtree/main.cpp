#include "BTree.h"

//#include <iostream>
//#include "BTree.h"
////#include "temp.hpp"
//
int main() {
    BTree tree(2);
    tree.insert(5);
    tree.insert(1);
    tree.insert(8);
    tree.insert(9); // FIXME теряется память
    tree.remove(1);
    tree.remove(5);
    tree.remove(9);
    tree.remove(8);

    int z = 2;
//    tree.insert(5);
//    tree.insert(7);
//    tree.insert(10);
//    tree.insert(12);
    tree.traverse();
    return 0;
}
//    int k = 5;
//    std::cout << ++(k);
//
//    BTree<int> btree(2, [](int a, int b){return a < b;}, [](int a){ std::cout << a;});
//    btree.insert(3);
//    btree.insert(5);
//    btree.insert(1);
//    btree.insert(2);
//    btree.insert(-5);
//    int z = 2;
////    btree1.print();
////    std::cout << "------------------------\n";
////    btree1.insert(1);
////    btree1.print();
////    std::cout << "------------------------\n";
////    btree1.insert(2);
////    btree1.print();
////    std::cout << "------------------------\n";
////    btree1.insert(2);
////    btree1.print();
////    std::cout << "------------------------\n";
////    btree1.insert(2);
////    btree1.print();
////    std::cout << "------------------------\n";
////    btree1.insert(2);
////    btree1.print();
////    std::cout << "------------------------\n";
////    btree1.insert(2);
////    btree1.print();
////    std::cout << "------------------------\n";
////    btree1.remove(2);
////    btree1.print();
////    int z = 2;
////    BTree<int> bTree(3);
////    bTree.insert(5);
////    bTree.insert(2);
////    bTree.insert(16);
////    bTree.insert(1);
////    bTree.insert(34);
////    bTree.insert(8);
//
////    std::vector<int> init(2, 1);
////    BTree<int> bTree(4, init);
////
////
////    /// Search tests
////    BTreeNode<int> root(false,{4, 17, 31}, {
////            BTreeNode<int>(true, {1, 2, 3}, {}),
////            BTreeNode<int>(true, {7, 9, 11, 13, 16}, {}),
////            BTreeNode<int>(true, {19, 26, 27}, {}),
////            BTreeNode<int>(true, {96, 97, 99}, {}),
////    });
////    bTree.fakeInsert(root);
////    std::cout << bTree.contains(5) << "\n";
////    std::cout << bTree.contains(11) << "\n";
////    std::cout << bTree.contains(12) << "\n";
////    std::cout << bTree.contains(13) << "\n";
////    std::cout << bTree.contains(27) << "\n";
////    std::cout << bTree.contains(31) << "\n";
////    std::cout << bTree.contains(100) << "\n";
////    std::cout << bTree.contains(99) << "\n";
////    std::cout << bTree.contains(19) << "\n";
////    std::cout << "-----------------\n";
////    root = BTreeNode<int>(true, {5}, {});
////    bTree.fakeInsert(root);
////    std::cout << bTree.contains(5) << "\n";
////    std::cout << bTree.contains(11) << "\n";
////    std::cout << bTree.contains(12) << "\n";
////    std::cout << bTree.contains(13) << "\n";
////    std::cout << bTree.contains(27) << "\n";
//    return 0;
//}
