#pragma once

#include <cstddef>  
#include <stdexcept> 
#include <iostream>
#include <utility>

template <typename TKey, typename TValue>
struct Node {
	std::pair<TKey, TValue> data;
	Node* left;
	Node* right;

	Node(const TKey& key, const TValue& value) :
		data(key, value), left(nullptr), right(nullptr) {
	}
};

template <typename TKey, typename TValue>
class BSTree {
	Node<TKey, TValue>* _root;

public:
	BSTree() : _root(nullptr) {}
	~BSTree() {
		clear(_root);
	}

	TValue* found(const TKey& key) const;
	bool is_empty() const noexcept { return _root == nullptr; }
	void insert(const TKey& key, const TValue& value);
	void print(std::ostream& out) const noexcept;
	void erase(const TKey& key);

private:
	void clear(Node<TKey, TValue>* node);
	void print_rec(Node<TKey, TValue>* node) const;

	Node<TKey, TValue>* erase_rec(Node<TKey, TValue>* node, const TKey& key);

	Node<TKey, TValue>* find_min(Node<TKey, TValue>* node) const {
		while (node && node->left) node = node->left;
		return node;
	}
};

template <typename TKey, typename TValue>
void BSTree<TKey, TValue>::clear(Node<TKey, TValue>* node) {
	if (node) {
		clear(node->left);
		clear(node->right);
		delete node;
	}
}

template <typename TKey, typename TValue>
TValue* BSTree<TKey, TValue>::found(const TKey& key) const {
	Node<TKey, TValue>* cur = _root;
	while (cur) {
		if (key < cur->data.first) cur = cur->left;
		else if (key > cur->data.first) cur = cur->right;
		else return &(cur->data.second);
	}
	return nullptr;
}

template <typename TKey, typename TValue>
void BSTree<TKey, TValue>::insert(const TKey& key, const TValue& value) {
	if (!_root) {
		_root = new Node<TKey, TValue>(key, value);
		return;
	}
	Node<TKey, TValue>* cur = _root;
	Node<TKey, TValue>* parent = nullptr;
	while (cur) {
		parent = cur;
		if (key < cur->data.first) cur = cur->left;
		else if (key > cur->data.first) cur = cur->right;
		else throw std::logic_error("Key already exists");
	}
	if (key < parent->data.first) parent->left = new Node<TKey, TValue>(key, value);
	else parent->right = new Node<TKey, TValue>(key, value);
}

template <typename TKey, typename TValue>
void BSTree<TKey, TValue>::erase(const TKey& key) {
	_root = erase_rec(_root, key);
}

template <typename TKey, typename TValue>
Node<TKey, TValue>* BSTree<TKey, TValue>::erase_rec(Node<TKey, TValue>* node, const TKey& key) {
	if (!node) return nullptr;

	if (key < node->data.first) {
		node->left = erase_rec(node->left, key);
	}
	else if (key > node->data.first) {
		node->right = erase_rec(node->right, key);
	}
	else {
		if (!node->left) {
			Node<TKey, TValue>* temp = node->right;
			delete node;
			return temp;
		}
		else if (!node->right) {
			Node<TKey, TValue>* temp = node->left;
			delete node;
			return temp;
		}

		Node<TKey, TValue>* temp = find_min(node->right);
		node->data = temp->data;
		node->right = erase_rec(node->right, temp->data.first);
	}
	return node;
}

template <typename TKey, typename TValue>
void BSTree<TKey, TValue>::print_rec(Node<TKey, TValue>* node) const {
	if (node) {
		print_rec(node->left);
		std::cout << "[" << node->data.first << ": " << node->data.second << "] ";
		print_rec(node->right);
	}
}

template <typename TKey, typename TValue>
void BSTree<TKey, TValue>::print(std::ostream& out) const noexcept {
	print_rec(_root);
	out << std::endl;
}

