#include "BTree.h"

//#include <iostream>
#include <vector>
#include <algorithm>
//#include "BTree.h"
//
int main() {
    srand(time(0));
//    BTree tree(2);
//    std::vector<int> input = {16, 11, 15, 23, 12, 9, 0};
//    std::vector<int> arr;
//    for (int i = 0; i < input.size(); ++i) {
//        if (i == 6) {
//            int z = 2;
//        }
//        tree.insert(input[i]);
//        std::clog << "log" << i+1 << ": ";
//        tree.traverse(arr);
//        std::clog << '\n';
//    }
//    std::vector<int> arr;
//    tree.insert(16);
//    std::clog << "log1: ";
//    tree.traverse(arr);
//    std::clog << '\n';
//    tree.insert(11);
//    std::clog << "log1: ";
//    tree.traverse(arr);
//    std::clog << '\n';
//    tree.insert(15);
//    tree.insert(23);
//    tree.insert(12);
//    tree.insert(9);
//    tree.insert(0);
//    tree.traverse(arr);
//    int z = 2;

    while (true) {
        std::vector<int> inputArr;
        BTree tree(5);
        for (int i = 0; i < 7000; ++i) {
            int key = rand() % 30000;
            if (tree.search(key).first == nullptr) {
                inputArr.push_back(key);
                tree.insert(key);
            }
            else
                i--;
//        tree.insert(rand() % 5000);
        }
        std::vector<int> arr;
        tree.traverse(arr);
        if (!std::is_sorted(arr.begin(), arr.end()))
            int z = 2;
    }

    std::cout << " ||";
//    tree.remove(1);
//    tree.remove(5);
//    tree.remove(9);
//    tree.remove(826);
//    tree.remove(8);
//    tree.remove(39);

    return 0;
}
