#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include "../lib_queue_on_list/queue_on_list.h"

template <class TKey, class TValue>
struct NodeTree {
	std::pair<TKey,TValue> data;
	NodeTree<TKey, TValue>* left, * right;
	NodeTree(const TKey& key, const TValue& value) : data(key, value), left(nullptr), right(nullptr) {}
};

template <class TKey, class TValue>
class Tree {
	NodeTree<TKey, TValue>* _root;
	size_t _size;

public:
	Tree() : _root(nullptr), _size(0) {}
	~Tree() { clear(); }

	size_t size() const noexcept;
	NodeTree<TKey, TValue>* root() const;
	bool is_empty() const noexcept;

	void insert(const TKey& key, const TValue& value) noexcept;
	void erase(const TKey& key);
	TValue* found(const TKey& key)const noexcept;
	void clear() noexcept;
	void print_W() const noexcept;
	void print_LCR() const noexcept;
	void print_LRC() const noexcept;
	void print_CLR() const noexcept;
	void print_table(std::ostream& out) const noexcept;
	void print_beatiful() const noexcept;

private:
	void print_LCR_rec(NodeTree<TKey, TValue>*) const noexcept;
	void print_LRC_rec(NodeTree<TKey, TValue>*) const noexcept;
	void print_CLR_rec(NodeTree<TKey, TValue>*) const noexcept;
	void print_beatiful_rec(NodeTree<TKey, TValue>*, int depth) const noexcept;
	void clear_rec(NodeTree<TKey, TValue>* node) noexcept;
	NodeTree<TKey, TValue>* find_parent(const TKey& key) const;


};

template <class TKey, class TValue>
size_t Tree<TKey, TValue>::size() const noexcept{ return _size; }

template <class TKey, class TValue>
bool Tree<TKey, TValue>::is_empty() const noexcept { return _root == nullptr; }

template <class TKey, class TValue>
void Tree<TKey, TValue>::insert(const TKey& key, const TValue& value) noexcept{
	NodeTree<TKey, TValue>* node = new NodeTree<TKey, TValue>(key, value);
	if (is_empty()) {
		_root = node;
		_size++;
		return;
	}

	Queue<NodeTree<TKey, TValue>*> q;
	q.push(_root);

	while (!q.is_empty()) {
		NodeTree<TKey, TValue>* temp = q.head();
		q.pop();

		if (!temp->left) {
			temp->left = node;
			_size++;
			return;
		}
		else q.push(temp->left);

		if (!temp->right) {
			temp->right = node;
			_size++;
			return;
		}
		else q.push(temp->right);
	}
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::erase(const TKey& key) {
	if (is_empty()) {
		throw std::logic_error("Can't erase empty tree!");
	}

	NodeTree<TKey, TValue>* parent = nullptr;
	NodeTree<TKey, TValue>* to_delete = nullptr;

	if (_root->data.first == key) {
		to_delete = _root;
	}
	else {
		parent = find_parent(key);
		if (!parent) {
			throw std::logic_error("Key not found!");
		}
		if (parent->left && parent->left->data.first == key) {
			to_delete = parent->left;
		}
		else if (parent->right) {
			to_delete = parent->right;
		}
	}

	NodeTree<TKey, TValue>* deepest = _root;
	NodeTree<TKey, TValue>* deepest_parent = nullptr;
	Queue<NodeTree<TKey, TValue>*> q;
	q.push(_root);

	while (!q.is_empty()) {
		deepest = q.head();
		q.pop();

		if (deepest->left) {
			deepest_parent = deepest;
			q.push(deepest->left);
		}
		if (deepest->right) {
			deepest_parent = deepest;
			q.push(deepest->right);
		}
	}

	if (to_delete == _root && !_root->left && !_root->right) {
		delete _root;
		_root = nullptr;
		_size = 0;
		return;
	}

	to_delete->data = deepest->data;

	if (deepest_parent->right == deepest) {
		deepest_parent->right = nullptr;
	}
	else {
		deepest_parent->left = nullptr;
	}
	delete deepest;
	_size--;
}
template <class TKey, class TValue>
NodeTree<TKey, TValue>* Tree<TKey,TValue>::root() const { return _root; }

template <class TKey, class TValue>
void Tree<TKey,TValue>::clear() noexcept{
	clear_rec(_root);
	_root = nullptr;
	_size = 0;
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::clear_rec(NodeTree<TKey, TValue>* node) noexcept {
	if (node == nullptr) { return; }
	clear_rec(node->left);
	clear_rec(node->right);
	delete node;
}

template <class TKey, class TValue>
TValue* Tree<TKey, TValue>::found(const TKey& key) const noexcept {
	if (is_empty()) return nullptr;
	if (_root->data.first == key) {
		return &(_root->data.second);
	}
	NodeTree<TKey, TValue>* parent = find_parent(key);
	if (!parent) return nullptr;
	if (parent->left && parent->left->data.first == key) {
		return &(parent->left->data.second);
	}
	if (parent->right && parent->right->data.first == key) {
		return &(parent->right->data.second);
	}
	return nullptr;
}

template <class TKey, class TValue>
NodeTree<TKey, TValue>* Tree<TKey, TValue>::find_parent(const TKey& key) const {
	if (is_empty()) return nullptr;
	if (_root->data.first == key) return _root;
	NodeTree<TKey, TValue>* cur = nullptr;
	Queue<NodeTree<TKey, TValue>*> q;
	q.push(_root);
	while (!q.is_empty()) {
		cur = q.head();
		q.pop();
		if (cur->left && cur->left->data.first == key) {
			return cur;
		}
		if (cur->right && cur->right->data.first == key) {
			return cur;
		}
		if (cur->left) q.push(cur->left);
		if (cur->right) q.push(cur->right);
	}
	return nullptr;
}


template <class TKey, class TValue>
void Tree<TKey, TValue>::print_W() const noexcept{
	if (is_empty()) return;
	NodeTree<TKey, TValue>* cur = nullptr;
	Queue<NodeTree<TKey, TValue>*> q;
	q.push(_root);

	while (!q.is_empty()) {
		cur = q.head();
		std::cout << cur->data.second << "";
		q.pop();
		if (cur->left) q.push(cur->left);
		if (cur->right) q.push(cur->right);
	}
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_LCR() const noexcept{
	print_LCR_rec(_root);
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_LRC() const noexcept{
	print_LRC_rec(_root);
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_CLR() const noexcept{
	print_CLR_rec(_root);
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_LCR_rec(NodeTree<TKey, TValue>* node) const noexcept{
	if (node == nullptr) return;
	print_LCR_rec(node->left);
	std::cout << node->data.second << "";
	print_LCR_rec(node->right);
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_LRC_rec(NodeTree<TKey, TValue>* node) const noexcept{
	if (node == nullptr) return;
	print_LRC_rec(node->left);
	print_LRC_rec(node->right);
	std::cout << node->data.second << "";
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_CLR_rec(NodeTree<TKey, TValue>* node) const noexcept{
	if (node == nullptr) return;
	std::cout << node->data.second << "";
	print_CLR_rec(node->left);
	print_CLR_rec(node->right);
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_table(std::ostream& out) const noexcept {
	if (is_empty()) return;
	NodeTree<TKey, TValue>* cur = nullptr;
	Queue<NodeTree<TKey, TValue>*> q;
	q.push(_root);
	out << "{";
	while (!q.is_empty()) {
		cur = q.head();
		out << "[" << cur->data.first << ":" << cur->data.second << "]";
		q.pop();
		if (cur->left) q.push(cur->left);
		if (cur->right) q.push(cur->right);
	}
	out << "}";
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_beatiful() const noexcept {
	print_beatiful_rec(_root, 0);
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_beatiful_rec(NodeTree<TKey, TValue>* node, int depth) const noexcept {
	if (node == nullptr) return;

	print_beatiful_rec(node->right, depth + 1);

	for (int i = 0; i < depth; i++) {
		std::cout << "    ";  
	}
	std::cout << node->data.first << ":" << node->data.second << std::endl;

	print_beatiful_rec(node->left, depth + 1);
}