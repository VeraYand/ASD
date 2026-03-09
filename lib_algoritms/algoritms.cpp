#include "algoritms.h"

//#define ISLOOPED
//#define ISLOOPEDPOS
//#define BRECKETS
//#define HAREANDTURTLE
//#define ISLOOPEDPOS
#define LABIRINT

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

#ifdef LABIRINT
#include "../lib_dsu/dsu.h"
#include "../lib_matrix/matrix.h"

void get_data(int& X, int& Y, int& N, int& M);
Matrix<int> generate(int X, int Y, int N, int M);
void print(Matrix<int>& labirint, int N, int M);
int correct_data(int N, int M, int num);

int correct_data(int N, int M, int num) {
	return (num >= 0 && num < N * M);}

void get_data(int& X, int& Y, int& N, int& M) {
	std::cout << "Enter the height of the maze: ";
	std::cin >> N;
	std::cout << "Enter the width of the maze: ";
	std::cin >> M;
	std::cout << "Select the entry cell: ";
	std::cin >> X;
	while (!correct_data(N, M, X)) {
		std::cout << "Wrong data! Select the entry cell: ";
		std::cin >> X;
	}
	std::cout << "Select the exit cell: ";
	std::cin >> Y;
	while (!correct_data(N, M, Y)) {
		std::cout << "Wrong data! Select the exit cell: ";
		std::cin >> Y;
	}

}

void print(Matrix<int>& labirint, int N, int M) {
	for (int i = 0; i < 2 * N + 1; ++i) {
		if (i % 2 == 0) {
			for (int j = 0; j < M; ++j) {
				std::cout << "+"; 
				if (labirint[i][j] == 1) { 
					std::cout << "---";
				}
				else {                     
					std::cout << "   ";
				}
			}
			std::cout << "+\n"; 
		}
		else {
			for (int j = 0; j < M + 1; ++j) {
				if (labirint[i][j] == 1) { 
					std::cout << "|   ";
				}
				else {                      
					std::cout << "    ";
				}
			}
			std::cout << "\n";
		}
	}
}

Matrix<int> generate(int X, int Y, int N, int M) {
	int rows = 2 * N + 1;
	int cols = M + 1;
	Matrix<int> labirint(rows, cols, 1);

	int size = N * M;
	DSU dsu(size);
	srand(time(NULL));

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			int current_room = i * M + j;

			if (j < M - 1) {
				if (rand() % 100 < 40) {
					int right_room = i * M + (j + 1);
					if (dsu.find(current_room) != dsu.find(right_room)) {
						dsu.dsu_union(current_room, right_room);
						labirint[2 * i + 1][j + 1] = 0;
					}
				}
			}

			if (i < N - 1) {
				if (rand() % 100 < 40) {
					int bottom_room = (i + 1) * M + j;
					if (dsu.find(current_room) != dsu.find(bottom_room)) {
						dsu.dsu_union(current_room, bottom_room);
						labirint[2 * i + 2][j] = 0;
					}
				}
			}
		}
	}


	while (dsu.find(X) != dsu.find(Y)) {
		int i = rand() % N;
		int j = rand() % M;
		int current_room = i * M + j;
		int direction = rand() % 100;

		if (direction < 50 && j < M - 1) {
			int right_room = i * M + (j + 1);
			if (dsu.find(current_room) != dsu.find(right_room)) {
				dsu.dsu_union(current_room, right_room);
				labirint[2 * i + 1][j + 1] = 0;
			}
		}
		else if (direction >= 50 && i < N - 1) {
			int bottom_room = (i + 1) * M + j;
			if (dsu.find(current_room) != dsu.find(bottom_room)) {
				dsu.dsu_union(current_room, bottom_room);
				labirint[2 * i + 2][j] = 0;
			}
		}
	} 

	int x_col = X % M;
	labirint[0][x_col] = 0;

	int y_col = Y % M;
	labirint[2 * N][y_col] = 0;

	return labirint;
}

#endif
