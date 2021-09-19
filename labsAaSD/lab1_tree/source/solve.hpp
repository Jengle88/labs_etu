#include <iostream>
#include <vector>

struct Node {
    int val = 0;
    std::vector<int> edges;
    Node(std::vector<int> edges, int val) : val(val), edges(edges) {}
    Node() {}
};

class Tree {
private:
    int root;
    std::vector<Node> tree;

public:
    Tree(int size) {
        root = -1;
        tree.resize(size);
        for (int i = 0; i < tree.size(); ++i) {
            tree[i].val = i;
        }
    }

    bool setRoot(int newRoot) {
        if (0 <= newRoot && (size_t)newRoot < tree.size()) {
            this->root = newRoot;
            return true;
        }
        else return false;
    }

    bool putEdge(int parent, int child) {
        if (0 <= parent && parent < tree.size() && 0 <= child && child <= tree.size()) {
            tree[parent].edges.push_back(child);
            return true;
        }
        else return false;
    }

    int getRoot() const {
        return this->root;
    }

    int calcHeights(int startNode) {
        if (startNode < 0 || (size_t)startNode >= tree.size())
            return 0;
        int maxHeight = 0;
        for(auto node : tree[startNode].edges)
            maxHeight = std::max(maxHeight, calcHeights(node));
        return maxHeight + 1;
    }

    int doDFS(int startNode, int (func)(Node node)) {
        int res = 0;
        if (startNode < 0 || (size_t)startNode >= tree.size())
            return 0;
        for(auto node : tree[startNode].edges) {
            res += doDFS(node, func);
        }
        return res + func(tree[startNode]);
    }
};

int func(Node node) {
    return node.val;
}

int solveHeight(int n, std::vector<int> parents) {
    int size = n;
    Tree tree = Tree(size);
    int parent;
    for (int i = 0; i < size; ++i) {
        parent = parents[i];
        if (parent == -1)
            tree.setRoot(i);
        else
            tree.putEdge(parent, i);
    }
    return tree.calcHeights(tree.getRoot());
}

int solveDFS(int n, std::vector<int> parents) {
    int size = n;
    Tree tree = Tree(size);
    int parent;
    for (int i = 0; i < size; ++i) {
        parent = parents[i];
        if (parent == -1)
            tree.setRoot(i);
        else
            tree.putEdge(parent, i);
    }
    return tree.doDFS(tree.getRoot(), func);
}