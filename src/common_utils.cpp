/*
 * common_utils.cpp
 *
 *  Created on: Sept. 24, 2017
 *      Author: Pyrad
 */


#include <stdio.h>

#include <iostream>
#include <cmath>
#include <algorithm>
#include <limits.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <sstream>

#include <boost/algorithm/string.hpp>

#include "common_utils.hpp"

namespace common_utils {

int** get_matrix(int row, int col) {
	if(row < 2 || col < 2) {
		printf("Error getting matrix\n");
		return NULL;
	}

	int **m = new int*[row];
	for(int i = 0; i < row; i++) {
		m[i] = new int[col];
	}

	return m;
}

void free_matrix(int **m, int row, int col) {
	if(!m) {
		return ;
	}

	if(row < 2 || col < 2) {
		printf("Error getting matrix\n");
		return ;
	}

	for(int j = 0; j < row; j++) {
		delete [] m[j];
	}
	delete [] m;


}

void copy_matrix(int **from, int **to, const int row, const int col) {
	if(!from || !to || row <= 0 || col <= 0) {
		return ;
	}

	for(int i = 0; i < row; i++) {
		for(int j = 0; j < col; j++) {
			to[i][j] = from[i][j];
		}
	}
}






// Random digits generator
// [a, b]
int gen_random_int_1(const int& a, const int& b) {
    srand((unsigned)time(NULL));
    return a + rand() % (b - a + 1);
}
// [a, b)
int gen_random_int_2(const int& a, const int& b) {
    srand((unsigned)time(NULL));
    return a + rand() % (b - a);
}
// (a, b]
int gen_random_int_3(const int& a, const int& b) {
    srand((unsigned)time(NULL));
    return a + rand() % (b - a) + 1;
}
// (a, b)
int gen_random_int_4(const int& a, const int& b) {
    srand((unsigned)time(NULL));
    return a + rand() % (b - a + 1) - 1;
}
// (0, 1)
int gen_random_double_0to1() {
	return rand() / (double) RAND_MAX;
}


void VISIT(node* h) {
    if(h) {
        printf("%d ", h->value);
    } else {
        printf("INVALID_NODE_NULL ");
    }
}

node* construct_tree_from_array(const int* nds, int size) {
    assert(size > 0);
    node* *p = new node*[size];
    node* head = new node(nds[0]);
    p[0] = head;
    for(int i = 1; i < size; i++) {
        node *cur = new node(nds[i]);
        p[i] = cur;
        int parent = (i - 1) / 2;
        if( i % 2 == 0) {
            p[parent]->right = cur;
        } else {
            p[parent]->left = cur;
        }
    }

    delete [] p;

    return head;
}

node* construct_tree_from_full_tree_array(const std::string &str) {
    if (str.empty()) {
        return nullptr;
    }

    std::vector<std::string> svec;
    boost::split(svec, str, boost::is_any_of(","), boost::token_compress_on);

    int size = svec.size();

    node **p = new node*[size];
    assert(svec.front() != "#");
    node *head = new node(std::stoi(svec.front()));
    p[0] = head;

    for(int i = 1; i < size; ++i) {
        if (svec[i] == "#") {
            continue;
        }

        node *cur = new node(std::stoi(svec[i]));
        p[i] = cur;
        int parent = (i - 1) / 2;
        if( i % 2 == 0) {
            p[parent]->right = cur;
        } else {
            p[parent]->left = cur;
        }
    }

    delete [] p;

    return head;
}

// --------- Delete a tree ---------
void DELETE_TREE_NODE(node* h) {
    if(h) {
        delete h;
    }
}

void pre_order_release(node* h) {
    if(!h) {
        return ;
    }
    DELETE_TREE_NODE(h);
    pre_order_release(h->left);
    pre_order_release(h->right);
}

void in_order_release(node* h) {
    if(!h) {
        return ;
    }
    in_order_release(h->left);
    DELETE_TREE_NODE(h);
    in_order_release(h->right);
}

void post_order_release(node* h) {
    if(!h) {
        return ;
    }
    post_order_release(h->left);
    post_order_release(h->right);
    DELETE_TREE_NODE(h);
}

void release_tree(node* h, int which_method) {
    switch(which_method) {
        case 0:
            pre_order_release(h);
            break;
        case 1:
            in_order_release(h);
            break;
        case 2:
            post_order_release(h);
            break;
        default:
            post_order_release(h);
    }
    std::cout << "(Tree is released)" << std::endl;
}
// --------- End of delete a tree ---------

// Tree traversal in recursive method
void pre_order(node* h) {
    if(!h) {
        return ;
    }
    VISIT(h);
    pre_order(h->left);
    pre_order(h->right);
}

void in_order(node* h) {
    if(!h) {
        return ;
    }
    in_order(h->left);
    VISIT(h);
    in_order(h->right);
}

void post_order(node* h) {
    if(!h) {
        return ;
    }
    post_order(h->left);
    post_order(h->right);
    VISIT(h);
}

// Clone a tree
node* clone_tree(node* head) {
	if(!head) {
		return NULL;
	}
	if(!head->left && !head->right) {
		return new node(head->value);
	}

	node* h = new node(head->value);
	h->left = clone_tree(head->left);
	h->right = clone_tree(head->right);

	return h;
}

// Get height of a tree
int tree_height(node* head) {
	if(!head) {
		return 0;
	}

	return std::max(tree_height(head->left), tree_height(head->right)) + 1;
}

void print_array(const int *a, int s) {
	for(int i = 0; i < s; i++) {
		std::cout << a[i] << " ";
	}
	std::cout << std::endl;
}

void print_char_array(char* arr, const int size, bool separator) {
	if(!arr) {
		printf("(Array might be empty\n)");
		return ;
	}
	if(size < 0) {
		printf("Error array size\n");
		return ;
	}

	for(int i = 0; i < size; i++) {
		if(separator) {
			printf("%c ", arr[i]);
		} else {
			printf("%c", arr[i]);
		}
	}
	printf("\n");
}

void print_string_vector(const std::vector<std::string>& svec) {
    for(std::vector<std::string>::const_iterator itr = svec.begin(); itr != svec.end(); itr++) {
        std::cout << *itr << " ";
    }
	std::cout << std::endl;
}

void print_int_vector(const std::vector<int>& vec) {
    for(std::vector<int>::const_iterator itr = vec.begin(); itr != vec.end(); itr++) {
        std::cout << *itr << " ";
    }
	std::cout << std::endl;
}

template<typename T>
void print_vector(const std::vector<T>& vec) {
    size_t vsize = vec.size();
    for(size_t i = 0; i < vsize; i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
}

template<typename T>
void print_vector_vector(const std::vector<std::vector<T> >& vecv) {
    size_t vsize = vecv.size();
    for(size_t i = 0; i < vsize; i++) {
        std::cout << "vector " << i + 1 << ": ";
        size_t size = vecv[i].size();
        for(size_t j = 0; j < size; j++) {
            std::cout << vecv[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void swap(std::vector<int>& vec, int i, int j) {
	if(vec.empty()) {
		return ;
	}

	const int len = vec.size();
	if(i < 0 || i >= len || j < 0 || j > len) {
		return ;
	}

	int _temp = vec[i];
	vec[i] = vec[j];
	vec[j] = _temp;

	return ;
}


// ------------------------------------------
// Create a linked list of a given number
lnode* gen_linked_list(int number) {
    if(number <= 0) {
        return NULL;
    }

    if(number > 1) {
        printf("(%d seconds would cost to create a linked list of %d nodes)\n", number, number);
    } else {
        printf("(%d second would cost to create a linked list of %d node)\n", number, number);
    }
    lnode dummy(-1);
    lnode *p(&dummy);

    const int rand_lower = -20000;
    const int rand_upper = 20000;

    for(int i = 0; i < number; i++) {
        sleep(1);
        p->next = new lnode(gen_random_int_1(rand_lower, rand_upper));
        p = p->next;
    }

    return dummy.next;
}

void delete_linked_list(lnode *p) {
    if(!p) {
        return ;
    }

    int cnt = 0;
    while(p) {
        lnode *n = p->next;
        delete p;
        cnt++;
        p = n;
    }

    printf("(Linked list(%d in total) is released)\n", cnt);
}

void print_link(lnode* p) {
    if(!p) {
        printf("(linked list is empty)\n");
        return ;
    }
    while(p) {
        printf("%d ", p->value);
        p = p->next;
    }
    printf("\n");
}

lnode* reverse(lnode* head) {
	if(!head) {
		return NULL;
	}

	lnode *pre = NULL;
	lnode *next = head;
	lnode *cur = head;
	while(cur) {
		next = cur->next;
		cur->next = pre;
		pre = cur;
		cur = next;
	}

	return pre;
}

bool is_list_has_loop(lnode *head) {
	if(!head || !head->next || !head->next->next) {
		return false;
	}

	lnode *slow = head;
	lnode *fast = head->next->next;
	while(fast->next && fast->next->next) {
		if(slow == fast) {
			return true;
		}
		fast = fast->next->next;
		slow = slow->next;
	}
	return false;
}

// Simple length
int list_length(lnode* h) {
	// Must insure there's no loop inside
	if(is_list_has_loop(h)) {
		return -1;
	}

	lnode* p = h;
	int l = 0;
	while(p) {
		l++;
		p = p->next;
	}

	return l;
}

lnode* remove_a_node_from_linked_list(lnode *head, lnode *n) {
	if(!head || !n) {
		return head;
	}

	if(head == n) {
		lnode *t = head->next;
		head->next = NULL;
		head = t;
		return t;
	}

	lnode *p = head;
	while(p->next) {
		if(p->next == n) {
			p->next = p->next->next;
			return head;
		}
		p = p->next;
	}

	return head;
}

lnode* find_min_node(lnode *head) {
	if(!head) {
		return head;
	}

	int v = head->value;
	lnode *pmin = head;
	lnode *p = head;

	while(p) {
		if(p->value < v) {
			pmin = p;
			v = p->value;
		}
		p = p->next;
	}

	return pmin;
}



template <typename T>
void print_matrix(const int& r, const int& c, T** m) {
    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            std::cout << m[i][j] << " ";
        }
        std::cout << std::endl;
    }
}



const std::string int_to_string(const int num) {
	std::stringstream ss;
	ss << num;
	std::string nstr(ss.str());

	return nstr;
}


char* convert_to_chars(const std::string& str, int& size) {
	printf("Need to delete the array returned after use\n");
	if(str.empty()) {
		size = 0;
		return NULL;
	}

	std::size_t len = str.size();
	size = len;
	char *chars = new char[len];
	for(std::size_t i = 0; i < len; i++) {
		chars[i] = str[i];
	}

	return chars;
}


std::vector<std::string> convert_to_string_vector(const std::string ss[], const int size) {
	if(size <= 0) {
		return std::vector<std::string>();
	}

	std::vector<std::string> svec;
	for(int i = 0; i < size; i++) {
		svec.push_back(ss[i]);
	}
	return svec;
}














} // namespace common_utils

