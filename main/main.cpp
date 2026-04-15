// Copyright 2024 Marina Usova
//#include "../lib_algoritms/algoritms.cpp"
//
//int X = 0, Y = 25, N = 5, M = 5;
//Matrix<int> labirint;
//
//int main() {
//    get_data(X, Y, N, M);
//    labirint = generate(X, Y, N, M); 
//    print(labirint, N, M);
//    return 0;
//}

//#define SKIPLIST
#ifdef SKIPLIST
#include "../lib_skip_list/skip_list.h"

int main() {
    SkipList<int, std::string> sl;
    sl.insert(10, "ten");
    sl.insert(20, "twenty");
    sl.insert(30, "thirty");
    sl.print();
	return 0;
}


#endif

#define BSTREE
#ifdef BSTREE
#include "../lib_bstree/bstree.h"

int main() {
    BSTree<int, std::string> tree;
    tree.insert(0, "null");
    tree.insert(3, "three");
    tree.insert(1, "one");
    tree.insert(2, "two");
    tree.insert(9, "nine");
    tree.print();
}

#endif

////#define EASY_EXAMPLE
//#define ALGORITHMS
////#define MATRIX_CALCULATOR
//#ifdef EASY_EXAMPLE
//
//#include <iostream>
//#include <iomanip>
//#include "../lib_easy_example/easy_example.h"
//
//int main() {
//  int a, b;
//  float result;
//
//  a = 1; b = 4;
//
//  try {
//      result = division(a, b);
//      std::cout << a << " / " << b << " = "
//          << std::setprecision(2) << result << std::endl;
//  } catch (std::exception err) {
//      std::cerr << err.what() << std::endl;
//  }
//
//  a = 1; b = 0;
//
//  try {
//      result = division(a, b);
//      std::cout << a << " / " << b << " = "
//          << std::setprecision(2) << result << std::endl;
//  } catch (std::exception err) {
//      std::cerr << err.what() << std::endl;
//  }
//
//  return 0;
//}
//
//#endif  // EASY_EXAMPLE
//#ifdef MATRIX_CALCULATOR
//#include <iostream>
//#include <conio.h>
//#include "../lib_matrix/matrix.h"
////#include "../lib_triangle_matrix/triangle_matrix.h"
//
//void message_type_matrix() {
//    std::cout << "\nChoise type of matrix: ";
//    std::cout << "\n 1. Base";
//    std::cout << "\n 2. Triangle";
//    std::cout << "\n 0. Exit";
//    std::cout << "\n Your choice: ";
//}
//
//void message_math_operation() {
//    std::cout << "\nChoise operation: ";
//    std::cout << "\n 1. Matrix addition";
//    std::cout << "\n 2. Subtract the matrix";
//    std::cout << "\n 3. Multiply the matrices";
//    std::cout << "\n 4. Multiply by a scalar";
//    std::cout << "\n 5. Add a scalar";
//    std::cout << "\n 6. Subtract a scalar";
//    std::cout << "\n 0. Exit";
//    std::cout << "\n Your choice: ";
//}
//
//void message_input_matrix() {
//    std::cout << "\nInput your matrix: ";  
//}
//
//void message_input_new_matrix() {
//    std::cout << "\nInput new matrix: ";
//}
//
//void input_scalar(int& a) {
//    std::cout << "\nInput your scalar: ";
//    std::cin >> a;
//}
//
//void message_output_result() {
//    std::cout << "\nYour result: ";
//}
//
//void message_continue() {
//    std::cout << "\nPress any key to select another action with result or exit.";
//}
//
//void message_matrix_size(int N, int M) {
//    std::cout << "\nMatrix size: " << N << "x" << M;
//
//}
//
//void input_triangle_matrix_size(int& size) {
//    while (1) {
//        std::cout << "\nInput matrix size: ";
//        std::cin >> size;
//        if (size > 0) {
//            break;
//        }
//        else {
//            std::cout << "\nIncorrect input. Try again.";
//        }
//    }
//}
//
//void input_matrix_high(int& M) {
//    while(1){
//        std::cout << "\nInput matrix high: ";
//        std::cin >> M;
//        if (M > 0) {
//            break;
//        }
//        else {
//            std::cout << "\nIncorrect input. Try again.";
//        }
//    }
//   
//
//}
//
//void input_matrix_width(int& N) {
//    while (1) {
//        std::cout << "\nInput matrix width: ";
//        std::cin >> N;
//        if (N > 0) {
//            break;
//        }
//        else {
//            std::cout << "\nIncorrect input. Try again.";
//        }
//    }
//
//}
//
//void handle_base_matrix() {
//    int N, M, user, a, new_N;
//    Matrix<int> first_matrix, second_matrix, res;
//    input_matrix_high(M);
//    input_matrix_width(N);
//    message_matrix_size(M, N);
//    message_input_matrix();
//    while (1) {
//        message_math_operation();
//        std::cin >> user;
//
//        if (user == 0) break;
//
//        switch (user)
//        {
//        case 1:
//            message_matrix_size(M, N);
//            message_input_new_matrix();
//            res = first_matrix + second_matrix;
//            message_output_result();
//            system("pause");
//            break;
//
//        case 2:
//            message_matrix_size(M, N);
//            message_input_new_matrix();
//            message_output_result();
//            system("pause");
//            break;
//
//        case 3:
//            input_matrix_width(new_N);
//            message_matrix_size(N, new_N);
//            message_input_new_matrix();
//            message_output_result();
//            system("pause");
//            break;
//
//        case 4:
//            input_scalar(a);
//            message_output_result();
//            system("pause");
//            break;
//
//        case 5:
//            input_scalar(a);
//            message_output_result();
//            system("pause");
//            break;
//        case 6:
//            input_scalar(a);
//            message_output_result();
//            system("pause");
//            break;
//
//
//        default:
//            break;
//        }
//    }
//}
//
//void handle_triangle_matrix() {
//    int size, user, a;
//
//    input_triangle_matrix_size(size);
//    message_matrix_size(size, size);
//    message_input_matrix();
//    while (1) {
//        message_math_operation();
//        std::cin >> user;
//
//        if (user == 0) break;
//
//        switch (user)
//        {
//        case 1:
//            message_matrix_size(size, size);
//            message_input_new_matrix();
//            message_output_result();
//            system("pause");
//            break;
//
//        case 2:
//            message_matrix_size(size, size);
//            message_input_new_matrix();
//            message_output_result();
//            system("pause");
//            break;
//
//        case 3:
//            message_matrix_size(size, size);
//            message_input_new_matrix();
//            message_output_result();
//            system("pause");
//            break;
//
//        case 4:
//            input_scalar(a);
//            message_output_result();
//            system("pause");
//            break;
//
//        case 5:
//            input_scalar(a);
//            message_output_result();
//            system("pause");
//            break;
//        case 6:
//            input_scalar(a);
//            message_output_result();
//            system("pause");
//            break;
//
//
//        default:
//            break;
//        }
//    }
//}
//
//int main() {
//    while (true) {
//        int type;
//
//        message_type_matrix();
//        std::cin >> type;
//
//        if (type == 0) break;
//
//        if (type == 1) {
//            handle_base_matrix();
//        }
//        else if (type == 2) {
//            handle_triangle_matrix();
//        }
//    }
//    
//    
//    return 0;
//}
//
//
//#endif
//
//

