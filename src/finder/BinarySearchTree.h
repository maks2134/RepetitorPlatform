#ifndef REPETITORPLATFORM_BINARYSEARCHTREE_H
#define REPETITORPLATFORM_BINARYSEARCHTREE_H

#include <QList>

template <typename T>
class BinarySearchTree {
private:
    struct Node {
        T data;
        Node *left;
        Node *right;

        Node(const T &data) : data(data), left(nullptr), right(nullptr) {}
    };

    Node *root;

    void insert(Node *&node, const T &data) {
        if (!node) {
            node = new Node(data);
            return;
        }
        if (data < node->data) {
            insert(node->left, data);
        } else {
            insert(node->right, data);
        }
    }

    void search(Node *node, const T &key, QList<T> &results, bool (*equals)(const T &, const T &)) const {
        if (!node) return;

        if (equals(node->data, key)) {
            results.append(node->data);
        }
        search(node->left, key, results, equals);
        search(node->right, key, results, equals);
    }

    void clear(Node *node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree() { clear(root); }

    void insert(const T &data) {
        insert(root, data);
    }

    QList<T> search(const T &key, bool (*equals)(const T &, const T &)) const {
        QList<T> results;
        search(root, key, results, equals);
        return results;
    }

    void clear() {
        clear(root);
        root = nullptr;
    }
};

#endif