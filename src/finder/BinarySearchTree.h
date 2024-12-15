#ifndef BINARYSEARCHTREE_CONTAINER_H
#define BINARYSEARCHTREE_CONTAINER_H

#include <iostream>
#include <stack>
#include <optional>
#include <QVector>

template <typename K, typename V>
class BinarySearchTree {
private:
    struct Node {
        K key;
        V value;
        Node *left;
        Node *right;

        Node(const K &key, const V &value) : key(key), value(value), left(nullptr), right(nullptr) {}
    };

    Node *root;

    // Вспомогательные методы для рекурсивной работы
    void insert(Node *&node, const K &key, const V &value) {
        if (!node) {
            node = new Node(key, value);
            return;
        }
        if (key < node->key) {
            insert(node->left, key, value);
        } else {
            insert(node->right, key, value);
        }
    }

    Node *remove(Node *node, const K &key) {
        if (!node) return nullptr;

        if (key < node->key) {
            node->left = remove(node->left, key);
        } else if (key > node->key) {
            node->right = remove(node->right, key);
        } else {
            if (!node->left) {
                Node *rightChild = node->right;
                delete node;
                return rightChild;
            } else if (!node->right) {
                Node *leftChild = node->left;
                delete node;
                return leftChild;
            }

            Node *minLargerNode = findMin(node->right);
            node->key = minLargerNode->key;
            node->value = minLargerNode->value;
            node->right = remove(node->right, minLargerNode->key);
        }
        return node;
    }

    Node *findMin(Node *node) const {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }

    void clear(Node *node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

    void print(Node *node) const {
        if (!node) return;
        print(node->left);
        std::cout << node->key << ": " << node->value << " ";
        print(node->right);
    }

public:
    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree() { clear(root); }

    void add(const K &key, const V &value) { insert(root, key, value); }

    void remove(const K &key) { root = remove(root, key); }

    void print() const {
        print(root);
        std::cout << std::endl;
    }

    // Итератор
    class Iterator {
    private:
        Node *current;
        std::stack<Node *> nodeStack;

        void pushLeft(Node *node) {
            while (node) {
                nodeStack.push(node);
                node = node->left;
            }
        }

    public:
        Iterator(Node *root) : current(nullptr) {
            pushLeft(root);
            if (!nodeStack.empty()) {
                current = nodeStack.top();
                nodeStack.pop();
            }
        }

        // Операторы
        Iterator &operator++() {
            if (current->right) {
                pushLeft(current->right);
            }
            if (!nodeStack.empty()) {
                current = nodeStack.top();
                nodeStack.pop();
            } else {
                current = nullptr;
            }
            return *this;
        }

        K &key() const {
            return current->key;
        }

        V &value() const {
            return current->value;
        }

        bool operator==(const Iterator &other) const {
            return current == other.current;
        }

        bool operator!=(const Iterator &other) const {
            return current != other.current;
        }
    };

    // Методы для работы с итераторами
    Iterator begin() const {
        return Iterator(root);
    }

    Iterator end() const {
        return Iterator(nullptr);
    }

    bool contains(const K &key) const {
        Node *current = root;
        while (current) {
            if (key < current->key) {
                current = current->left;
            } else if (key > current->key) {
                current = current->right;
            } else {
                return true;
            }
        }
        return false;
    }

    V& operator[](const K &key) {
        Node *current = root;
        while (current) {
            if (key < current->key) {
                current = current->left;
            } else if (key > current->key) {
                current = current->right;
            } else {
                return current->value;
            }
        }
        // Если ключа нет, вставим новый узел с пустым значением
        add(key, V());
        return operator[](key); // Возвращаем добавленное значение
    }
};

#endif // BINARYSEARCHTREE_CONTAINER_H
