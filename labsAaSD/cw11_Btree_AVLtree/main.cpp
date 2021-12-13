#include "BTree.h"

//#include <iostream>
//#include "BTree.h"
//
int main() {
    BTree tree(2);
    tree.insert(5);
    tree.insert(1);
    tree.insert(8);
    tree.insert(9);
    tree.insert(55);
    tree.insert(11);
    tree.insert(826);
    tree.insert(39);
    tree.insert(58);
    tree.insert(91);
    tree.insert(80);
    tree.insert(4);
    tree.traverse();
    std::cout << " ||";
    tree.remove(1);
    tree.remove(5);
    tree.remove(9);
    tree.remove(826);
    tree.remove(8);
    tree.remove(39);
    tree.traverse();
    auto finder = tree.search(39);
    int z = 2;

    return 0;
}
