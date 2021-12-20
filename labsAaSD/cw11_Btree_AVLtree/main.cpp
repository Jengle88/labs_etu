#include "BTree/BTree.h"
#include "AVLTree/AVLTree.h"

#include <random>
#include <vector>
#include <algorithm>
int main() {
    srand(time(0));

    AVLTree avlTree;
    BTree bTree(2);
    std::vector<int> values;
    for (int i = 0; i < 80000; ++i) {
        int z = rand() % 600000;
        values.push_back(z);
        avlTree.insert(z);
        bTree.insert(z);
    }
    std::shuffle(values.begin(), values.end(), std::mt19937(std::random_device()()));
    for (int i = 0; i < values.size(); ++i) {
        if (i % 10 == 0) {
            auto avlTreeArray = avlTree.getArray();
            auto bTreeArray = bTree.getArray();
            if (avlTreeArray == bTreeArray && std::is_sorted(avlTreeArray.begin(), avlTreeArray.end()))
                std::cout << "Good\n";
            else {
                std::cout << "Bad!!!!!!!!!!!!!!!\n";
                break;
            }

        }
        avlTree.remove(values[i]);
        bTree.remove(values[i]);
    }
    return 0;
}
