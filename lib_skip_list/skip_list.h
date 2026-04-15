#pragma once
#include <iostream>
#include "../lib_list/list.h"
#include <random>
#include <iomanip>

template <typename TKey, typename TValue>
struct SkipNode {
    std::pair<TKey, TValue> data;
    SkipNode** next; 
    size_t level; 

    SkipNode(TKey key, TValue value, size_t lvl) : level(lvl) {
        data = std::make_pair(key, value);
        next = new SkipNode * [lvl + 1];
        for (size_t i = 0; i <= lvl; ++i) next[i] = nullptr;
    }

    ~SkipNode() {
        delete[] next;
    }
};

template <typename TKey, typename TValue>
class SkipList {
    using Node = SkipNode<TKey, TValue>;

    size_t _MAX_LVLS;
    size_t _lvls;
    List<Node*> _heads; 

public:
    SkipList(size_t max_lvls = 10) : _MAX_LVLS(max_lvls), _lvls(0) {
        for (size_t i = 0; i < _MAX_LVLS; ++i) {
            _heads.push_back(nullptr);
        }
    }
    size_t flip_coin() const noexcept {
        size_t lvl = 0;
        while (lvl < _MAX_LVLS - 1 && (rand() % 100 < 50)) {
            lvl++;
        }
        return lvl;
    }

    Node* get_head_at(size_t lvl) const {
        auto it = _heads.begin();
        for (size_t i = 0; i < lvl; ++i) ++it;
        return *it;
    }

    void insert(const TKey key, const TValue value) {
        std::vector<Node*> update(_MAX_LVLS, nullptr);
        Node* current = nullptr;

        for (int i = (int)_lvls; i >= 0; --i) {
            if (current == nullptr) {
                current = get_head_at(i);
                if (current == nullptr || current->data.first > key) {
                    update[i] = nullptr;
                    current = nullptr; 
                    continue;
                }
            }

            while (current->next[i] != nullptr && current->next[i]->data.first < key) {
                current = current->next[i];
            }
            update[i] = current;
        }

        size_t new_lvl = flip_coin();
        if (new_lvl > _lvls) {
            _lvls = new_lvl;
        }

        Node* newNode = new Node(key, value, new_lvl);

        for (size_t i = 0; i <= new_lvl; ++i) {
            if (update[i] == nullptr) {
                newNode->next[i] = get_head_at(i);

                _heads.erase(i);
                _heads.insert(i, newNode);
            }
            else {
                newNode->next[i] = update[i]->next[i];
                update[i]->next[i] = newNode;
            }
        }
    }

    void print() const noexcept {
        for (int i = (int)_lvls; i >= 0; --i) {
            Node* node = get_head_at(i);
            std::cout << "Level " << i << ": [HEAD] -> ";
            while (node != nullptr) {
                std::cout << "(" << node->data.first << ":" << node->data.second << ") -> ";
                node = node->next[i];
            }
            std::cout << "nullptr\n";
        }
    }

    Node* find_nearest(const TKey key) const {
        Node* current = nullptr;

        for (int i = (int)_lvls; i >= 0; --i) {
            if (current == nullptr) {
                Node* head = get_head_at(i);
                if (head == nullptr || head->data.first > key) {
                    continue;
                }
                current = head;
            }

            while (current->next[i] != nullptr && current->next[i]->data.first <= key) {
                current = current->next[i];
            }
        }

        return current;
    }
};






