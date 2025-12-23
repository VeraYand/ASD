#include "algoritms.h"

//#define ISLOOPED
//#define ISLOOPEDPOS
//#define BRECKETS
//#define HAREANDTURTLE
#define ISLOOPEDPOS

#ifdef BRECKETS
#include<string>
#include"../lib_stack/stack.h"

//перенести в ветку algorithms в проект Algorithms

bool check_breckets(std::string str) {
	Stack<char> stack(str.length());
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == '(' || str[i] == '{' || str[i] == '[') {
			stack.push(str[i]);
		}
		else if (str[i] == ')' || str[i] == '}' || str[i] == ']') {
			if (stack.is_empty()) {
				return false;
			}

			char top = stack.top();
			if ((str[i] == ')' && top == '(') ||
				(str[i] == '}' && top == '{') ||
				(str[i] == ']' && top == '[')) {
				stack.pop();
			}
			else {
				return false;
			}
		}
	}
	return stack.is_empty();
}


#endif 


#ifdef ISLOOPED
#include "../lib_list/list.h"

template<class T>
void expend_directions(Node<T>** cur, Node<T>** next, Node<T>** prev) {
	*next = (*cur)->next;
	(*cur)->next = *prev;
	*prev = *cur;
	*cur = *next;
}

template<class T>
bool is_looped(List<T>(*list)) {
	Node<T>* prev = nullptr;
	Node<T>* cur = (*list).head();
	Node<T>* next = cur->next;
	Node<T>* first = (*list).head();
	bool res = false;

	while (next != nullptr) {
		expend_directions(&cur, &next, &prev);
		if (next == first) {
			res = true;
			break;
		}
	}
	cur = prev;
	prev = nullptr;
	while (cur != nullptr) {
		expend_directions(&cur, &next, &prev);
	}

	return res;
}
#endif // ISLOOPED

#ifdef HAREANDTURTLE
#include "../lib_list/list.h"

template<class T>
bool is_looped_two(List<T>(*list)) {
	Node<T>* first = (*list).head();

	Node<T>* hare = first;
	Node<T>* turtle = first;

	while (hare != nullptr && hare->next != nullptr) {
		hare = hare->next->next;  
		turtle = turtle->next;   

		if (hare == turtle) {
			return true;
		}
	}
	return false;
}

#endif 

#ifdef ISLOOPEDPOS
#include "../lib_list/list.h"

template<class T>
int is_looped_pos(List<T>(*list)) {
	bool isLooped = false;
	Node<T>* first = (*list).head();

	Node<T>* hare = first;
	Node<T>* turtle = first;

	while (hare != nullptr && hare->next != nullptr) {
		hare = hare->next->next;
		turtle = turtle->next;

		if (hare == turtle) {
			isLooped = true;
			break;
		}
	}
	turtle = first;
	if (isLooped == true) {
		while (hare != nullptr && hare->next != nullptr) {
			hare = hare->next;
			turtle = turtle->next;
			if (hare == turtle) {
				return turtle->value;
			}
		}
	}
	return NULL;
}


#endif // ISLOOPEDPOS
