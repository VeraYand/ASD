#pragma once

#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <cmath>
#include <iomanip>

template <typename T>
struct Node {
	T data;
	Node* left, * right;
	Node(T val) : data(val), left(nullptr), right(nullptr) {}
};

template <typename T>
class BinaryTree {
	Node<T>* _root;

public:
	BinaryTree() : _root(nullptr) {}
	~BinaryTree() { clear(_root); }

	// 1. Вставка по уровням (Level-order insertion)
	void insert(T value) {
		if (!_root) {
			_root = new Node<T>(value);
			return;
		}

		std::queue<Node<T>*> q;
		q.push(_root);

		while (!q.empty()) {
			Node<T>* temp = q.front();
			q.pop();

			if (!temp->left) {
				temp->left = new Node<T>(value);
				return;
			}
			else q.push(temp->left);

			if (!temp->right) {
				temp->right = new Node<T>(value);
				return;
			}
			else q.push(temp->right);
		}
	}

	// 2. Удаление последнего элемента и перенос данных
	void erase(T key) {
		if (!_root) return;
		if (!_root->left && !_root->right) {
			if (_root->data == key) {
				delete _root;
				_root = nullptr;
			}
			return;
		}

		Node<T>* target_node = nullptr;
		Node<T>* last_node = nullptr;
		Node<T>* last_parent = nullptr;

		// Поиск узла для удаления и последнего узла (и его родителя) через BFS
		std::queue<Node<T>*> q;
		q.push(_root);

		while (!q.empty()) {
			last_node = q.front();
			q.pop();

			if (last_node->data == key) target_node = last_node;

			if (last_node->left) {
				last_parent = last_node;
				q.push(last_node->left);
			}
			if (last_node->right) {
				last_parent = last_node;
				q.push(last_node->right);
			}
		}

		if (target_node) {
			T last_val = last_node->data;
			// Удаляем связь у родителя последнего узла
			if (last_parent->right == last_node) last_parent->right = nullptr;
			else last_parent->left = nullptr;

			delete last_node;
			// Переносим данные последнего узла в целевой
			target_node->data = last_val;
		}
	}

	// --- ОБХОДЫ ---

	// 1. Прямой (Pre-order): Корень -> Л -> П
	void preOrder(Node<T>* node) const {
		if (!node) return;
		std::cout << node->data << " ";
		preOrder(node->left);
		preOrder(node->right);
	}

	// 2. Симметричный (In-order): Л -> Корень -> П
	void inOrder(Node<T>* node) const {
		if (!node) return;
		inOrder(node->left);
		std::cout << node->data << " ";
		inOrder(node->right);
	}

	// 3. Обратный (Post-order): Л -> П -> Корень
	void postOrder(Node<T>* node) const {
		if (!node) return;
		postOrder(node->left);
		postOrder(node->right);
		std::cout << node->data << " ";
	}

	// 4. В ширину (Level-order)
	void levelOrder() const {
		if (!_root) return;
		std::queue<Node<T>*> q;
		q.push(_root);
		while (!q.empty()) {
			Node<T>* curr = q.front();
			q.pop();
			std::cout << curr->data << " ";
			if (curr->left) q.push(curr->left);
			if (curr->right) q.push(curr->right);
		}
	}

	// Геттер корня для вызова обходов
	Node<T>* getRoot() const { return _root; }

	// "Красивый" вывод в консоль
	void printTree(Node<T>* root, int space = 0, int height = 10) const {
		if (!root) return;
		space += height;
		printTree(root->right, space);
		std::cout << std::endl;
		for (int i = height; i < space; i++) std::cout << " ";
		std::cout << root->data << "\n";
		printTree(root->left, space);
	}

private:
	void clear(Node<T>* node) {
		if (node) {
			clear(node->left);
			clear(node->right);
			delete node;
		}
	}
};
