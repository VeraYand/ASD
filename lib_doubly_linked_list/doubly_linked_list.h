#pragma once

//перенести в ветку algorithms в проект Algorithms
template <class T>
struct Node {
    T value;
    Node <T>* next;
    Node <T>* prev;

    Node(T value_, Node <T>* next_ = nullptr, Node <T>* prev_ = nullptr): value(value_), next(next_), prev(prev_) {}
    Node(const Node <T>& other) : value(other->value), next(nullptr), prev(nullptr) {}
};

template <class T>
class DoublyLinkedList {
    Node<T>* _head, * _tail;
    size_t _count;
public:
    DoublyLinkedList();
    DoublyLinkedList(const DoublyLinkedList<T>&);
    ~DoublyLinkedList();

    bool is_empty();
    Node <T>* head();
    Node <T>* tail();

    void push_front(const T& value) noexcept;
    void push_back(const T& value) noexcept;
    void insert(size_t pos, const T& value);
    void insert(Node <T>* node, const T& value);

    void pop_front();
    void pop_back();
    void erase(Node <T>* node);
    void erase(size_t pos);

};

template <class T>
DoublyLinkedList<T>::DoublyLinkedList() : _head(nullptr), _tail(nullptr), _count(0) {}

template <class T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& other) : _head(nullptr), _tail(nullptr), _count(0) {
    Node<T>* current = other._head;
    while (current != nullptr) {
        push_back(current->value);
        current = current->next;
    }
}

template <class T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    while (!is_empty()) {
        pop_front();
    }
}

template <class T>
Node<T>* DoublyLinkedList<T>::head() { return _head; }

template <class T>
Node<T>* DoublyLinkedList<T>::tail() { return _tail; }

template <class T>
bool DoublyLinkedList<T>::is_empty() {
    return _head == nullptr;
}

template <class T>
void DoublyLinkedList<T>::push_front(const T& val) noexcept {
    Node <T>* node = new Node<T>(val);
    if (!(is_empty())) {
        _head->prev = node;
        node->next = _head;
    }
    else {
        _tail = node;
    }

    _head = node;
    _count++;
};

template <class T>
void DoublyLinkedList<T>::push_back(const T& val) noexcept {
    Node <T>* node = new Node<T>(val);
    if (!(is_empty())) {
        _tail->next = node;
        node->prev = _tail;
    }
    else {
        _head = node;
    }
    _tail = node;
    _count ++;
};

template <class T>
void DoublyLinkedList<T>::insert(Node <T>* node, const T& val) {
    if (is_empty() || node == nullptr ) {
        throw std::logic_error("Error! List or node is empty.");
    }

    if (node == _tail) {
        push_back(val);
        return;
    }

    Node <T>* new_node = new Node<T>(val);
    node->next->prev = new_node;
    new_node->next = node->next;
    new_node->prev = node;
    node->next = new_node;

    _count ++;
};
template <class T>
void DoublyLinkedList<T>::insert(size_t pos, const T& val) {
    if (pos == 0) {
        push_front(val);
        return;
    }
    if (pos == _count - 1) {
        push_back(val);
        return;
    }
    Node <T>* cur = _head;
    size_t cur_pos = 0;
    while (cur != nullptr) {
        if (cur_pos == pos - 1) {
            break;
        }
        cur_pos++;
        cur = cur->next;
    }
    if (cur == nullptr) {
        throw std::logic_error("Error! Position out of range.");
    }
    
    insert(cur, val);
};


template <class T>
void DoublyLinkedList<T>::pop_back() {
    if (is_empty()) {
        throw std::logic_error("Error! List is empty.");
    }
    if (_tail == _head) {
        delete _head;
        _head = nullptr;
        _tail = nullptr;
        _count--;
        return;
    }
    Node<T>* to_delete = _tail;
    _tail = _tail->prev;
    _tail->next = nullptr;
    delete to_delete;
    _count--;
};

template <class T>
void DoublyLinkedList<T>::pop_front() {
    if (is_empty()) {
        throw std::logic_error("Error! List is empty.");
    }

    Node<T>* node = _head;
    _head = _head->next;
    if (_head != nullptr) {
        _head->prev = nullptr;
    }
    else {
        _tail = nullptr;
    }

    delete node;
    _count--;
}

template <class T>
void DoublyLinkedList<T>::erase(Node<T>* node) {
    if (node == nullptr || node->next == nullptr) {
        throw std::invalid_argument("Invalid node.");
    }

    Node<T>* to_delete = node->next;
    if (to_delete == _tail) {
        _tail = node;
        _count--;
        _tail->next = nullptr;
        return;
    }
    to_delete->next->prev = node;
    node->next = to_delete->next;


    _count--;
}

template <class T>
void DoublyLinkedList<T>::erase(size_t pos) {
    if (pos >= _count) {
        throw std::out_of_range("Error! Position out of range.");
    }

    if (pos == 0) {
        pop_front();
        return;
    }

    if (pos == _count - 1) {
        pop_back();
        return;
    }

    Node<T>* cur = _head;
    for (size_t i = 0; i < pos - 1; i++) {
        cur = cur->next;
    }

    erase(cur);
}


