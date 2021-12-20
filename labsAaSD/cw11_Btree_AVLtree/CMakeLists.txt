cmake_minimum_required(VERSION 3.20)
project(cw11_Btree_AVLtree)

set(CMAKE_CXX_STANDARD 17)

add_executable(cw11_Btree_AVLtree main.cpp BTree/BTree.cpp BTree/BTree.h AVLTree/AVLTree.cpp AVLTree/AVLTree.h BTree/BTreeNode.cpp BTree/BTreeNode.h AVLTree/AVLTreeNode.cpp AVLTree/AVLTreeNode.h)
