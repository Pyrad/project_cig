/*
 * common_utils.hpp
 *
 *  Created on: Sept. 19, 2017
 *      Author: Pyrad
 */

#ifndef COMMON_UTILS_HPP_
#define COMMON_UTILS_HPP_

#include <string>
#include <vector>
#include <deque>
#include <iostream>
#include <functional>

namespace common_utils {

// ****************************************
//
// CLASS & STRUCT DEFINITIONS
//
// ****************************************
// Binary tree node definition
class binary_tree_node {
public:
    binary_tree_node(int v): left(NULL), right(NULL), value(v) { }
    ~binary_tree_node() { }

public:
    binary_tree_node* left;
    binary_tree_node* right;
    int value;
};

// Binary tree node with sibling definition
class binary_tree_node_with_sibling : public binary_tree_node {
public:
    binary_tree_node_with_sibling(int v): binary_tree_node(v), next(NULL) { }

public:
    binary_tree_node* next;
};

// Linked list node definition
class linked_list_node {
public:
    linked_list_node(int v): next(NULL), value(v) { }

public:
    linked_list_node *next;
    int value;
};

// Double linked list node definition
class double_linked_list_node {
public:
	double_linked_list_node(int v) : pre(NULL), next(NULL), value(v){}

public:
	double_linked_list_node *pre;
	double_linked_list_node *next;
	int value;
};

// ****************************************
//
// Type Definitions
//
// ****************************************
typedef binary_tree_node node;
typedef binary_tree_node_with_sibling snode;
typedef linked_list_node lnode;
typedef double_linked_list_node dlnode;


// ****************************************
//
// Matrix Operations
//
// ****************************************
int** get_matrix(int row, int col);

void free_matrix(int **m, int row, int col);

void copy_matrix(int **from, int **to, const int row, const int col);

template <typename T>
void print_matrix(const int& r, const int& c, T** m);


// ****************************************
//
// Binary Tree Operations
//
// ****************************************
void VISIT(node* h);

node* construct_tree_from_array(const int* nds, int size);
node* construct_tree_from_full_tree_array(const std::string &str);

node* create_random_binary_tree(int height, int minlimit=0, int maxlimit=RAND_MAX, bool full=false);
node* create_random_binary_tree_full(int height, int minlimit=0, int maxlimit=RAND_MAX);

// --------- Delete a tree ---------
void DELETE_TREE_NODE(node* h);

void pre_order_release(node* h);

void in_order_release(node* h);

void post_order_release(node* h);

void release_tree(node* h, int which_method = 99);
// --------- End of delete a tree ---------

// Tree traversal in recursive method
void pre_order(node* h) ;

void in_order(node* h);

void post_order(node* h);

void pre_order(node* h, const std::function<void(node*)> &func);

// Tree traversal by level
void visit_tree_by_level(node* head, const std::function<void(node*)> &func = std::function<void(node*)>(VISIT));

// Clone a tree
node* clone_tree(node* head);

// Get height of a tree
int tree_height(node* head);


// ****************************************
//
// Random digits generator
//
// ****************************************
int gen_random_int(const int& a, const int& b, const bool left_open=false, const bool right_open=false);
// (0, 1)
int gen_random_double_0to1();



// ****************************************
//
// Array & Vector Related
//
// ****************************************
void print_array(const int *a, int s);
void print_char_array(char* arr, const int size, bool separator = true);

void print_string_vector(const std::vector<std::string>& svec);

void print_int_vector(const std::vector<int>& vec);

template<typename T>
void print_vector(const std::vector<T>& vec);

template<typename T>
void print_vector_vector(const std::vector<std::vector<T> >& vecv);

void swap(std::vector<int>& vec, int i, int j);


// ****************************************
//
// Linked List Operations
//
// ****************************************
//Create a linked list of a given number
lnode* gen_linked_list(int number);

void delete_linked_list(lnode *p);

void print_link(lnode* p);

lnode* reverse(lnode* h);

bool is_list_has_loop(lnode *h);

int list_length(lnode* h);

lnode* remove_a_node_from_linked_list(lnode *head, lnode *n);

lnode* find_min_node(lnode *head);







// ****************************************
//
// Conversions
//
// ****************************************
const std::string int_to_string(const int num);

char* convert_to_chars(const std::string& str, int& size);

std::vector<std::string> convert_to_string_vector(const std::string ss[], const int size);








// ****************************************
//
// For debugging use
//
// ****************************************
template<typename T>
void print_deque(const std::deque<T>& deq) {
	for(typename std::deque<T>::const_iterator i = deq.begin(); i != deq.end(); i++) {
		std::cout << *i << " ";
	}
	std::cout << std::endl;
}






} // namespace common_utils


#endif /* COMMON_UTILS_HPP_ */
