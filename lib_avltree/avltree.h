#pragma once

#include <cstddef>
#include <stdexcept>
#include <iostream>
#include <utility>
#include <algorithm>

template <typename TKey, typename TValue>
struct AVLNode {
    std::pair<TKey, TValue> data;
    AVLNode* left;
    AVLNode* right;
    AVLNode* parent;
    size_t height;

    AVLNode(const TKey& key, const TValue& value)
        : data(key, value), left(nullptr), right(nullptr), parent(nullptr), height(1) {
    }
};

template <typename TKey, typename TValue>
class AVLTree {
private:
    AVLNode<TKey, TValue>* _root;

    void clear(AVLNode<TKey, TValue>* node);
    void print_rec(AVLNode<TKey, TValue>* node) const;

    size_t get_height(AVLNode<TKey, TValue>* node) const;
    void recalc_height(AVLNode<TKey, TValue>* node);
    int calc_balance(AVLNode<TKey, TValue>* node);

    void left_rotate(AVLNode<TKey, TValue>* node);
    void right_rotate(AVLNode<TKey, TValue>* node);

    void RR(AVLNode<TKey, TValue>* node);
    void LL(AVLNode<TKey, TValue>* node);
    void RL(AVLNode<TKey, TValue>* node);
    void LR(AVLNode<TKey, TValue>* node);
    void recover_balance(AVLNode<TKey, TValue>* node);

    AVLNode<TKey, TValue>* find_min(AVLNode<TKey, TValue>* node) const;
    void balance_after_insert(AVLNode<TKey, TValue>* node);
    void balance_after_erase(AVLNode<TKey, TValue>* node);

public:
    AVLTree() : _root(nullptr) {}
    ~AVLTree() {
        clear(_root);
    }

    TValue* found(const TKey& key) const;
    bool is_empty() const noexcept { return _root == nullptr; }
    void insert(const TKey& key, const TValue& value);
    void print(std::ostream& out) const noexcept;
    void erase(const TKey& key);

    std::pair<TKey, TValue> get_root_data() const;
};


template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::clear(AVLNode<TKey, TValue>* node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

template <typename TKey, typename TValue>
size_t AVLTree<TKey, TValue>::get_height(AVLNode<TKey, TValue>* node) const {
    if (node != nullptr) {
        return node->height;
    }
    else {
        return 0;
    }
}

template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::recalc_height(AVLNode<TKey, TValue>* node) {
    if (node) {
        node->height = 1 + std::max(get_height(node->left), get_height(node->right));
    }
}

template <typename TKey, typename TValue>
int AVLTree<TKey, TValue>::calc_balance(AVLNode<TKey, TValue>* node) {
    if (!node) return 0;
    return get_height(node->right) - get_height(node->left);
}

template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::left_rotate(AVLNode<TKey, TValue>* node) {
    AVLNode<TKey, TValue>* G = node;
    AVLNode<TKey, TValue>* P = G->right;

    G->right = P->left;
    if (P->left) {
        P->left->parent = G;
    }

    P->parent = G->parent;
    if (!G->parent) {
        _root = P;
    }
    else if (G == G->parent->left) {
        G->parent->left = P;
    }
    else {
        G->parent->right = P;
    }

    P->left = G;
    G->parent = P;

    recalc_height(G);
    recalc_height(P);
}

template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::right_rotate(AVLNode<TKey, TValue>* node) {
    AVLNode<TKey, TValue>* G = node;
    AVLNode<TKey, TValue>* P = G->left;
    G->left = P->right;
    if (P->right) {
        P->right->parent = G;
    }
    P->parent = G->parent;
    if (!G->parent) {
        _root = P;
    }
    else if (G == G->parent->left) {
        G->parent->left = P;
    }
    else {
        G->parent->right = P;
    }

    P->right = G;
    G->parent = P;

    recalc_height(G);
    recalc_height(P);
}

template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::RR(AVLNode<TKey, TValue>* node) {
    left_rotate(node);
}

template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::LL(AVLNode<TKey, TValue>* node) {
    right_rotate(node);
}

template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::RL(AVLNode<TKey, TValue>* node) {
    right_rotate(node->right);
    left_rotate(node);
}

template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::LR(AVLNode<TKey, TValue>* node) {
    left_rotate(node->left);
    right_rotate(node);
}

template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::recover_balance(AVLNode<TKey, TValue>* node) {
    int balance = calc_balance(node);

    if (balance > 1) { 
        if (calc_balance(node->right) < 0) {
            RL(node);
        }
        else {
            RR(node);
        }
    }
    else if (balance < -1) { 
        if (calc_balance(node->left) > 0) {
            LR(node);
        }
        else {
            LL(node);
        }
    }
}

template <typename TKey, typename TValue>
AVLNode<TKey, TValue>* AVLTree<TKey, TValue>::find_min(AVLNode<TKey, TValue>* node) const {
    while (node && node->left) {
        node = node->left;
    }
    return node;
}

template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::balance_after_insert(AVLNode<TKey, TValue>* node) {
    AVLNode<TKey, TValue>* cur = node;

    while (cur) {
        size_t prev_height = cur->height;
        recalc_height(cur);

        int balance = calc_balance(cur);
        if (abs(balance) > 1) {
            recover_balance(cur);
            break; 
        }

        if (prev_height == cur->height) {
            break; 
        }

        cur = cur->parent;
    }
}

template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::balance_after_erase(AVLNode<TKey, TValue>* node) {
    while (node) {
        recalc_height(node);
        int balance = calc_balance(node);

        if (abs(balance) > 1) {
            recover_balance(node);
        }

        node = node->parent;
    }
}


template <typename TKey, typename TValue>
TValue* AVLTree<TKey, TValue>::found(const TKey& key) const {
    AVLNode<TKey, TValue>* cur = _root;
    while (cur) {
        if (key < cur->data.first) {
            cur = cur->left;
        }
        else if (key > cur->data.first) {
            cur = cur->right;
        }
        else {
            return &(cur->data.second);
        }
    }
    return nullptr;
}

template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    AVLNode<TKey, TValue>* new_node = new AVLNode<TKey, TValue>(key, value);

    if (!_root) {
        _root = new_node;
        return;
    }

    AVLNode<TKey, TValue>* cur = _root;
    AVLNode<TKey, TValue>* parent = nullptr;

    while (cur) {
        parent = cur;
        if (key < cur->data.first) {
            cur = cur->left;
        }
        else if (key > cur->data.first) {
            cur = cur->right;
        }
        else {
            delete new_node;
            throw std::logic_error("Key already exists");
        }
    }

    new_node->parent = parent;
    if (key < parent->data.first) {
        parent->left = new_node;
    }
    else {
        parent->right = new_node;
    }

    balance_after_insert(parent);
}

template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::erase(const TKey& key) {
    if (!_root) return;

    AVLNode<TKey, TValue>* node = _root;

    while (node && node->data.first != key) {
        if (key < node->data.first) {
            node = node->left;
        }
        else {
            node = node->right;
        }
    }

    if (!node) return; 

    AVLNode<TKey, TValue>* parent_to_balance = nullptr;

    if (!node->left && !node->right) {
        parent_to_balance = node->parent;
        if (!parent_to_balance) {
            delete _root;
            _root = nullptr;
            return;
        }
        if (parent_to_balance->left == node) {
            parent_to_balance->left = nullptr;
        }
        else {
            parent_to_balance->right = nullptr;
        }
        delete node;
    }
    else if (!node->left) {
        parent_to_balance = node->parent;
        if (!parent_to_balance) {
            _root = node->right;
            node->right->parent = nullptr;
        }
        else {
            if (parent_to_balance->left == node) {
                parent_to_balance->left = node->right;
            }
            else {
                parent_to_balance->right = node->right;
            }
            node->right->parent = parent_to_balance;
        }
        delete node;
    }
    else if (!node->right) {
        parent_to_balance = node->parent;
        if (!parent_to_balance) {
            _root = node->left;
            node->left->parent = nullptr;
        }
        else {
            if (parent_to_balance->left == node) {
                parent_to_balance->left = node->left;
            }
            else {
                parent_to_balance->right = node->left;
            }
            node->left->parent = parent_to_balance;
        }
        delete node;
    }

    else {
        AVLNode<TKey, TValue>* successor = find_min(node->right);
        node->data = successor->data;

        parent_to_balance = successor->parent;

        if (parent_to_balance == node) {
            node->right = successor->right;
            if (successor->right) {
                successor->right->parent = node;
            }
        }
        else {
            parent_to_balance->left = successor->right;
            if (successor->right) {
                successor->right->parent = parent_to_balance;
            }
        }
        delete successor;
    }

    if (parent_to_balance) {
        balance_after_erase(parent_to_balance);
    }
}

template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::print_rec(AVLNode<TKey, TValue>* node) const {
    if (node) {
        print_rec(node->left);
        std::cout << "[" << node->data.first << ": " << node->data.second
            << " h=" << node->height << "] ";
        print_rec(node->right);
    }
}

template <typename TKey, typename TValue>
void AVLTree<TKey, TValue>::print(std::ostream& out) const noexcept {
    print_rec(_root);
    out << std::endl;
}

template <typename TKey, typename TValue>
std::pair<TKey, TValue> AVLTree<TKey, TValue>::get_root_data() const {
    if (!_root) {
        throw std::logic_error("Tree is empty");
    }
    return _root->data;
}