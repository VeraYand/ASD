#pragma once

//перенести в ветку algorithms в проект Algorithms
template <class T>
struct Node {
    T value;
    Node <T>* next;

    Node(T value_, Node <T>* next_ = nullptr): value(value_), next(next_){}
    Node(const Node <T>& other) : value(other->value), next(next->next) {}
};

template <class T>
class List {
    Node<T>* _head, * _tail;
    size_t _count;
public:
    List();
    List(const List<T>&);
    ~List();

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

    //friend std::ostream& operator<<(std::ostream& os, const List<T>& list); //++

};

template <class T>
List<T>::List() : _head(nullptr), _tail(nullptr), _count(0) {}

template <class T>
List<T>::List(const List<T>& other) : _head(nullptr), _tail(nullptr), _count(0) {
    Node<T>* current = other._head;
    while (current != nullptr) {
        push_back(current->value);
        current = current->next;
    }
}

template <class T>
List<T>::~List() {
    while (!is_empty()) {
        pop_front();
    }
}

template <class T>
Node<T>* List<T>::head() { return _head; }

template <class T>
Node<T>* List<T>::tail() { return _tail; }

template <class T>
bool List<T>::is_empty() {
    return _head == nullptr;
}

template <class T>
void List<T>::push_front(const T& val) noexcept {
    Node <T>* node = new Node<T>(val);
    if (is_empty()) {
        _count += 1;
        _head = node;
        _tail = node;
        return;
    }
    node->next = _head;
    _head = node;
    _count += 1;
};

template <class T>
void List<T>::push_back(const T& val) noexcept {
    Node <T>* node = new Node<T>(val);
    if (is_empty()) {
        _count += 1;
        _head = node;
        _tail = node;
        return;
    }
    _tail->next = node;
    _tail = node;
    _count += 1;
};

template <class T>
void List<T>::insert(Node <T>* node, const T& val) {
    if (is_empty() || node == nullptr) {
        throw std::logic_error("Error! List or node is empty.");
    }
    Node <T>* new_node = new Node<T>(val);
    new_node->next = node->next;
    node->next = new_node;

    if (node == _tail) {   
        _tail = new_node;
    }
    _count += 1;
};
template <class T>
void List<T>::insert(size_t pos, const T& val) {
    if (pos == 0) {
        push_front(val);
    }
    if (pos == _count - 1) {
        push_back(val);
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
void List<T>::pop_back() {
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
    Node <T>* cur = _head;
    while (cur->next != tail()) {
        cur = cur->next;
    }
    delete _tail;
    _tail = cur;
    cur->next = nullptr;
};

template <class T>
void List<T>::pop_front() {
    if (is_empty()) {
        throw std::logic_error("Error! List is empty.");
    }

    Node<T>* node = _head;
    _head = _head->next;
    delete node;

    if (_head == nullptr) {
        _tail = nullptr;
    }
    _count--;
}

template <class T>
void List<T>::erase(Node<T>* node) {
    if (node == nullptr || node->next == nullptr) {
        throw std::invalid_argument("Invalid node.");
    }

    Node<T>* to_delete = node->next;
    node->next = to_delete->next;

    if (to_delete == _tail) {
        _tail = node;
    }

    delete to_delete;
    _count--;
}

template <class T>
void List<T>::erase(size_t pos) {
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

//template <class T>
//std::ostream& operator<<(std::ostream& os, const List<T>& list) {
//  Node<T>* cur = list.head();
//  os << "[";
//  while (cur != nullptr) {
//    os << cur->value;
//    if (cur->next != nullptr) {
//      os << " ";
//    }
//    cur = cur->next;
//  }
//  os << "]";
//  return os;
//}
