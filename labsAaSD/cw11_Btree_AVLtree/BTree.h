#pragma once

#include <iostream>
#include <deque>
#include <memory>
#include <vector>


class BTreeNode {
    bool leaf;
    int deg;
    int size;
    std::vector<int> keys;
    std::vector<std::shared_ptr<BTreeNode>> children;

    void fillNode() {
        for (auto &child: this->children) {
            if (child == nullptr)
                child = std::make_shared<BTreeNode>(deg, true);
        }
    }

    // Находим индекс первой позиции, равный или больший, чем ключ
    int findEqualGreaterKey(int key) {
        int index = 0;
        // Условия выхода из цикла:
        // 1.index == num, то есть сканировать все
        // 2.index < size, т.е. найти ключ или больше ключа
        while (index < size && keys[index] < key)
            ++index;
        return index;
    }


    void remove(int key) {
        int index = findEqualGreaterKey(key);
        if (index < size && keys[index] == key) {// Если ключ найден в этом узле
            if (leaf) // ключ находится в листовом узле
                removeFromLeaf(index);
            else // ключ отсутствует в листовом узле
                removeFromNonLeaf(index);
        } else {
            if (leaf) { // Если узел является листовым узлом, то этот узел не входит в B-дерево
                std::cout << "The key " << key << " does not exist in the tree\n";
                return;
            }

            // В противном случае удаляемый ключ существует в поддереве с корнем в этом узле

            // Этот флаг указывает, существует ли ключ в поддереве с корнем в последнем дочернем узле узла
            // Когда index равно size, сравнивается весь узел, и флаг равен true
            bool flag = (index == size);

            if (children[index]->size < deg) // Когда дочерний узел узла не заполнен, сначала заполняем его
                fill(index);

            // Если последний дочерний узел был объединен, то он должен был быть объединен с предыдущим дочерним узлом, поэтому мы рекурсивно переходим к (index-1) -ому дочернему узлу.
            // В противном случае мы рекурсивно переходим к (index) -ому дочернему узлу, который теперь имеет как минимум ключи наименьшей степени
            if (flag && index > size)
                children[index - 1]->remove(key);
            else
                children[index]->remove(key);
        }
    }

    void removeFromLeaf(int index) {
        // возвращаемся из index
        for (int i = index + 1; i < size; ++i)
            keys[i - 1] = keys[i];
        size--;
    }

    void removeFromNonLeaf(int index) {
        int key = keys[index];

        // Если поддерево перед ключом (children [index]) имеет не менее deg ключей
        // Затем находим предшественника key 'pred' в поддереве с корнем в children [index]
        // Заменить ключ на 'pred', рекурсивно удалить 'pred' в дочерних [index]
        if (children[index]->size >= deg) {
            int predecessor = getPredecessor(index);
            keys[index] = predecessor;
            children[index]->remove(predecessor);
        }
            // Если у детей [index] меньше ключей, чем у deg, проверяем дочерние элементы [index + 1]
            // Если дочерние элементы [index + 1] имеют хотя бы ключи deg, в поддереве с корнем дочерние элементы [index + 1]
            // Находим преемника ключа 'succ' для рекурсивного удаления succ в дочерних элементах [index + 1]
        else if (children[index + 1]->size >= deg) {
            int successor = getSuccessor(index);
            keys[index] = successor;
            children[index + 1]->remove(successor);
        }
            // Если размеры children [index] и children [index + 1] меньше deg
            // то объединяем ключ и дочерние элементы [index + 1] в дочерние элементы [index]
            // Теперь children [index] содержит ключ 2t-1
            // Освобождаем дочерние элементы [index + 1], рекурсивно удаляем ключ в children [index]
        else {
            merge(index);
            children[index]->remove(key);
        }
    }

    int getPredecessor(int index) { // Узел-предшественник должен найти крайний правый узел из левого поддерева
        // Продолжаем двигаться к крайнему правому узлу, пока не достигнем листового узла
        auto cur = children[index];
        while (!cur->leaf)
            cur = cur->children[cur->size];
        return cur->keys[cur->size - 1];
    }

    int getSuccessor(int index) { // Узел-преемник находится от правого поддерева к левому
        // Продолжаем перемещать крайний левый узел от дочерних [index + 1], пока не достигнем конечного узла
        auto cur = children[index + 1];
        while (!cur->leaf)
            cur = cur->children[0];
        return cur->keys[0];
    }

    // Заполняем дочерние элементы [index], у которых меньше ключей deg
    void fill(int index) {
        // Если предыдущий дочерний узел имеет несколько ключей deg - 1, заимствовать из них
        if (index != 0 && children[index - 1]->size >= deg) {
            borrowFromPrev(index);
            // Последний дочерний узел имеет несколько ключей deg - 1, заимствовать от них
        } else if (index != size && children[index + 1]->size >= deg)
            borrowFromNext(index);
        else {
            // объединить потомков [index] и его брата
            // Если children [index] - последний дочерний узел
            // затем объединить его с предыдущим дочерним узлом, иначе объединить его со следующим братом
            if (index != size)
                merge(index);
            else
                merge(index - 1);
        }
    }

    // Заимствуем ключ у потомков [index-1] и вставляем его в потомки [index]
    void borrowFromPrev(int index) {
        auto child = children[index];
        auto sibling = children[index - 1];

        // Последний ключ из дочерних [index-1] переходит к родительскому узлу
        // ключ [index-1] из недополнения родительского узла вставляется как первый ключ в дочерних [index]
        // Следовательно, sibling уменьшается на единицу, а children увеличивается на единицу
        for (int i = child->size - 1; i >= 0; --i) // дети [index] продвигаются вперед
            child->keys[i + 1] = child->keys[i];
        if (!child->leaf) {  // Если дочерний узел [index] не является листовым, переместите его дочерний узел назад
            for (int i = child->size; i >= 0; --i) {
                child->children[i + 1] = child->children[i];
            }
        }

        // Устанавливаем первый ключ дочернего узла на ключи текущего узла [index-1]
        child->keys[0] = keys[index - 1];
        if (!child->leaf) { // Устанавливаем последний дочерний узел в качестве первого дочернего узла дочерних элементов [index]
            child->children[0] = sibling->children[sibling->size];
        }

        // Перемещаем последний ключ брата к последнему из текущего узла
        keys[index - 1] = sibling->keys[sibling->size - 1];
        child->size++;
        sibling->size--;

    }

    // Симметричный с заимствованием FromPrev
    void borrowFromNext(int index) {
        auto child = children[index];
        auto sibling = children[index + 1];
        child->keys[child->size] = keys[index];

        if (!child->leaf) {
            child->children[child->size + 1] = sibling->children[0];
        }

        keys[index] = sibling->keys[0];

        for (int i = 1; i < sibling->size; ++i)
            sibling->keys[i - 1] = sibling->keys[i];

        if (!sibling->leaf) {
            for (int i = 1; i <= sibling->size; ++i) {
                sibling->children[i - 1] = sibling->children[i];
            }
        }
        child->size++;
        sibling->size--;
    }

    // объединить children [index + 1] в children [index]
    void merge(int index) {
        auto child = children[index];
        auto sibling = children[index + 1];

        // Вставляем последний ключ текущего узла в позицию deg - 1 дочернего узла
        child->keys[deg - 1] = keys[index];

        // ключи: children [index + 1] скопированы в children [index]
        for (int i = 0; i < sibling->size; ++i)
            child->keys[i + deg] = sibling->keys[i];

        // children: children [index + 1] скопированы в children [index]
        if (!child->leaf) {
            for (int i = 0; i <= sibling->size; ++i) {
                child->children[i + deg] = sibling->children[i];
            }
        }

        // Перемещаем ключи вперед, но не зазор, вызванный перемещением ключей [index] к дочерним [index]
        for (int i = index + 1; i < size; ++i)
            keys[i - 1] = keys[i];
        // Перемещаем соответствующий дочерний узел вперед
        for (int i = index + 2; i <= size; ++i)
            children[i - 1] = children[i];

        child->size += sibling->size + 1;
        size--;
    }

    void insertNotFull(int key) {
        int i = size - 1; // Инициализируем i индексом самого правого значения

        if (leaf) { // Когда это листовой узел
            while (i >= 0 && keys[i] > key) {
                keys[i + 1] = keys[i]; // ключи возвращаются
                i--;
            }
            keys[i + 1] = key;
            size++;
        } else {
            // Находим позицию дочернего узла, который нужно вставить
            while (i >= 0 && keys[i] > key)
                i--;
            if (children[i + 1]->size == 2 * deg - 1) { // Когда дочерний узел заполнен
                splitChildNode(i + 1, children[i + 1]);
                // После разделения ключ в середине дочернего узла перемещается наверх, а дочерний узел разделяется на два
                if (keys[i + 1] < key)
                    i++;
            }
            children[i + 1]->insertNotFull(key); // теперь есть пространство для добавления
        }
    }

    void splitChildNode(int index, std::shared_ptr<BTreeNode> node) {
        // Сначала создаем узел, содержащий ключи от deg-1 до конца
        auto tempNode = std::make_shared<BTreeNode>(node->deg, node->leaf);
        tempNode->size = deg - 1;

        // Передаем все атрибуты node в tempNode
        for (int i = 0; i < deg - 1; ++i)
            tempNode->keys[i] = node->keys[i + deg];
        if (!node->leaf) {
            for (int i = 0; i < deg; ++i)
                tempNode->children[i] = node->children[i + deg];
        }
        tempNode->fillNode();
        node->size = deg - 1;

        // Вставляем новый дочерний узел в дочерний узел
        for (int i = size; i >= index + 1; --i)
            children[i + 1] = children[i];

        children[index + 1] = tempNode;
        // Перемещаем ключ по node к этому узлу
        for (int i = size - 1; i >= index; --i) {
            keys[i + 1] = keys[i];
        }
        keys[index] = node->keys[deg - 1];
        size++;
    }

    void traverse(std::vector<int> &arr) const {
        int i;
        for (i = 0; i < size; ++i) {
            if (!leaf)
                children[i]->traverse(arr);
            arr.push_back(keys[i]);
//            std::clog << ' ' << keys[i];
        }

        if (!leaf) // нужно, чтобы пойти в самого правого ребёнка вершины
            children[i]->traverse(arr);
    }

    std::pair<const BTreeNode*, int> search(int key) {
        int i = findEqualGreaterKey(key);
        if (keys[i] == key)
            return {this, i};
        if (leaf)
            return {nullptr, -1};
        return children[i]->search(key);
    }
public:
    BTreeNode(int deg, bool leaf) {
        this->deg = deg;
        this->leaf = leaf;
        this->keys.resize(2 * this->deg - 1); // Узел имеет не более 2 * deg - 1 ключей
        this->children.resize(2 * this->deg);
        this->size = 0;
    }

    friend class std::shared_ptr<BTreeNode>;
    friend class BTree;
};

class BTree {
    std::shared_ptr<BTreeNode> root;
    int deg;
public:
    BTree(int deg) {
        this->root = nullptr;
        this->deg = deg;
    }

    void traverse(std::vector<int> &arr) const {
        if (root != nullptr)
            root->traverse(arr);
    }

    // Функция для поиска ключа
    std::pair<const BTreeNode*, int> search(int key) {
        return root == nullptr ? std::make_pair(nullptr, -1) : root->search(key);
    }

    void insert(int key) {
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

    void remove(int key) {
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
};











