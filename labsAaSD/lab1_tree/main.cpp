#include <iostream>
#include <vector>
#include "test.h"

struct Node {
	std::vector<int> edges;
	Node(std::vector<int> edges) : edges(edges) {}
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
	}

	bool setRoot(int root) {
		if (0 <= root && root < tree.size()) {
			this->root = root;
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
		if (startNode < 0 || startNode >= tree.size())
			return 0;
		int maxHeight = 0;
		for(auto node : tree[startNode].edges)
			maxHeight = std::max(maxHeight, calcHeights(node));
		return maxHeight + 1;
	}
};

int solve(int n, std::vector<int> parents) {
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

int main() {
#ifdef TESTING
	test(3, solve, 5, {4, -1, 4, 1, 1});
	test(4, solve, 5, {-1, 0, 4, 0, 3});
	test(1, solve, 1, {-1});
	test(0, solve, 0, {});
	test(5, solve, 8, {-1, 0, 1, 1, 3, 0, 5, 4});
	test(5, solve, 10, {-1, 0, 1, 1, 3, 0, 5, 4, 6, 8});
	test(3, solve, 3, {-1, 0, 1});
	test(2, solve, 2, {-1, 0});
#else
	int size;
	std::cin >> size;
	std::vector<int> parents(size);
	for(auto &parent : parents)
		std::cin >> parent;
	std::cout << solve(size, parents);
#endif
	return 0;
}
