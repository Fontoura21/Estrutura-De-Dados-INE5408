// Copyright [2023] <Rafael Correa Bitencourt>

#ifndef STRUCTURES_AVL_TREE_H
#define STRUCTURES_AVL_TREE_H

#include <algorithm>
#include <cstdlib>
#include "array_list.h"

namespace structures {


template<typename T>
class AVLTree {
public:
    AVLTree() {
        root_ = nullptr;
        size_ = 0;
    }
    ~AVLTree() {
        ArrayList<T> a = pre_order();
        while (!a.empty()) this->remove(a.pop_back());
    }

    void insert(const T& data) {
        root_ = insert_(data, root_);
        size_++;
    }

    void remove(const T& data) {
        if (contains(data)) {
            root_ = removeNode(data, root_);
            size_--;
        }
    }

    bool contains(const T& data) const {
        return containsNode(data, root_);
    }

    bool empty() const {
        return !size_;
    }

    std::size_t size() const {
        return size_;
    }

    int height() const {
        return height_(root_);
    }

    ArrayList<T> pre_order() const {
        ArrayList<T> v;
        if (root_) pre_order_(v, root_);
        return v;
    }

    ArrayList<T> in_order() const {
        ArrayList<T> v;
        if (root_) in_order_(v, root_);
        return v;
    }

    ArrayList<T> post_order() const {
        ArrayList<T> v;
        if (root_) post_order_(v, root_);
        return v;
    }

private:
    struct Node {
        explicit Node(const T& data_) {
            data = data_;
            height = 0;
            left = nullptr;
            right = nullptr;
        }

        T data;
        int height;
        Node* left;
        Node* right;
    };

    Node *insert_(const T& data_, Node *root) {
        if (!root) {
            return new Node(data_);
        } else if (data_ < root->data) {
            root->left = insert_(data_, root->left);
            if (std::abs(height_(root->left) - height_(root->right)) > 1) {
                if (data_ < root->left->data) root = simpleLeft(root);
                else
                    root = doubleLeft(root);
            } else {
                updateHeight(root);
            }
        } else if (data_ > (root->data)) {
            root->right = insert_(data_, root->right);
            if (std::abs(height_(root->left) - height_(root->right)) > 1) {
                if (data_ > root->right->data) root = simpleRight(root);
                else
                    root = doubleRight(root);
            } else {
                updateHeight(root);
            }
        }
        return root;
    }

    Node *removeNode(const T& data_, Node *root) {
        Node *aux = root;
        if (!root)
            return root;
        if (data_ < root->data) {
            root->left = removeNode(data_, root->left);
            return zigue_zague(root);
        } else if (data_ > root->data) {
            root->right = removeNode(data_, root->right);
            return zigue_zague(root);
        } else if (root->left && root->right) {
            aux = minimum(root->right);
            root->data = aux->data;
            root->right = removeNode(aux->data, root->right);
            return zigue_zague(root);
        } else if (root->left) {
            aux = root->left;
            delete root;
            return aux;
        } else if (root->right) {
            aux = root->right;
            delete root;
            return aux;
        } else {
            delete root;
            return nullptr;
        }
    }

    bool containsNode(const T& data_, Node *root) const {
        if (!root)
            return false;
        if (data_ < root->data)
            return containsNode(data_, root->left);
        else if (data_ > root->data)
            return containsNode(data_, root->right);
        else
            return true;
    }

    void updateHeight(Node *root) {
        root->height = maximum(height_(root->left), height_(root->right)) + 1;
    }

    Node* simpleLeft(Node *root) {
        Node *k1 = root->left;
        root->left = k1->right;
        k1->right = root;
        updateHeight(root);
        updateHeight(k1);
        return k1;
    }

    Node* simpleRight(Node *root) {
        Node *k1 = root->right;
        root->right = k1->left;
        k1->left = root;
        updateHeight(root);
        updateHeight(k1);
        return k1;
    }

    Node* doubleLeft(Node *root) {
        root->left = simpleRight(root->left);
        return simpleLeft(root);
    }

    Node* doubleRight(Node *root) {
        root->right = simpleLeft(root->right);
        return simpleRight(root);
    }

    void pre_order_(ArrayList<T>& v, Node *root) const {
        if (!root) return;
        v.push_back(root->data);
        pre_order_(v, root->left);
        pre_order_(v, root->right);
    }

    void in_order_(ArrayList<T>& v, Node *root) const {
        if (!root) return;
        in_order_(v, root->left);
        v.push_back(root->data);
        in_order_(v, root->right);
    }

    void post_order_(ArrayList<T>& v, Node *root) const {
        if (!root) return;
        post_order_(v, root->left);
        post_order_(v, root->right);
        v.push_back(root->data);
    }

    int height_(Node *root) const {
        if (!root) {
            return -1;
        }
        return root->height;
    }

    Node *minimum(Node *root) {
        if (!root) return nullptr;
        if (root->left) return minimum(root->left);
        else
            return root;
    }
    int maximum(int a, int b) {
        if (a > b) {
            return a;
        }
        return b;
    }

    Node *zigue_zague(Node *root) {
        updateHeight(root);
        Node *aux = root;
        if (height_(root->left) - height_(root->right) > 1) {
            if (height_(root->left->left) > height_(root->left->right))
                aux = simpleLeft(root);
            else
                aux = doubleLeft(root);
        } else if (height_(root->right) - height_(root->left) > 1) {
            if (height_(root->right->right) > height_(root->right->left))
                aux = simpleRight(root);
            else
                aux = doubleRight(root);
        }
        return aux;
    }

    Node* root_;
    std::size_t size_;
};

}  // namespace structures

#endif
