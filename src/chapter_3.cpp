/*
 * chapter_3.cpp
 *
 *  Created on: Oct. 5, 2017
 *      Author: Pyrad
 * Description: Source file of chapter 3 Binary Tree
 *   Intention: Solutions for problems in Chapter 3[Binary Tree] of Code Interview Guide
 */


#include "chapter_3.hpp"

#if 0
// Boost libraries
#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_io.hpp>
#include <boost/scoped_ptr.hpp>

#include <stdio.h>
#include <iostream>
#include <stack>
#include <sstream>
#include <vector>
#include <queue>
#include <deque>
#include <cstring>
#include <map>
#include <set>
#endif // 0

namespace C3 {

namespace CU = common_utils;

// [TIME_STAMP] Start at 20:07, 2017/09/24

// --------------------------------------------------------------------------------------------------------------
// 3.1 Traverse Methods of Binary Tree
// (1) Pre-Order Traverse (Recursive)
// (2) In-Order Traverse (Recursive)
// (3) Post-Order Traverse (Recursive)
// (4) Pre-Order Traverse (Non Recursive)
// (5) In-Order Traverse (Non Recursive)
// (6) Post-Order Traverse (Non Recursive)

void pre_order_traverse_recursive(CU::node *head) {
	if(!head) {
		return ;
	}

	CU::VISIT(head);
	pre_order_traverse_recursive(head->left);
	pre_order_traverse_recursive(head->right);
}

void in_order_traverse_recursive(CU::node *head) {
	if(!head) {
		return ;
	}

	pre_order_traverse_recursive(head->left);
	CU::VISIT(head);
	pre_order_traverse_recursive(head->right);
}

void post_order_traverse_recursive(CU::node *head) {
	if(!head) {
		return ;
	}

	pre_order_traverse_recursive(head->left);
	pre_order_traverse_recursive(head->right);
	CU::VISIT(head);
}

void pre_order_traverse_non_recursive(CU::node *head) {
	if(!head) {
		return ;
	}

	std::stack<CU::node*> stk;
	CU::node *p = head;
	while( p || !stk.empty()) {
		while(p) {
			CU::VISIT(p);
			stk.push(p);
			p = p->left;
		}
		p = stk.top();
		stk.pop();
		if(p->right) {
			p = p->right;
		} else {
			p = NULL;
		}
	}
}

void in_order_traverse_non_recursive(CU::node *head) {
	if(!head) {
		return ;
	}

	std::stack<CU::node*> stk;
	CU::node *p = head;
	while( p || !stk.empty()) {
		while(p) {
			stk.push(p);
			p = p->left;
		}
		p = stk.top();
		stk.pop();
		CU::VISIT(p);
		if(p->right) {
			p = p->right;
		} else {
			p = NULL;
		}
	}
}

void post_order_traverse_non_recursive(CU::node *head) {
	if(!head) {
		return ;
	}

	std::stack<CU::node*> stk1;
	std::stack<bool> stk2;
	CU::node *p = head;
	while(p || !stk1.empty()) {
		while(p) {
			stk1.push(p);
			stk2.push(false);
			p = p->left;
		}
		if(stk2.top() == false) {
			stk2.top() = true;
		} else {
			p = stk1.top();
			stk1.pop();
			CU::VISIT(p);
			stk2.pop();
		}
		if(p->right) {
			p = p->right;
		} else {
			p = NULL;
		}
	}
}

// --------------------------------------------------------------------------------------------------------------
// 3.2 Print The Boarder of A Binary Tree in Anti-Clockwise Order
// Use 2 methods
// (1) boarder nodes contain
//		<1> head
//		<2> leaf nodes
//		<3> left most node in a level
//		<4> right most node in a level
// (2) boarder nodes contain
//		<1> head
//		<2> leaf nodes
//		<3> nodes extended from tree's left boarder
//		<4> nodes extended from tree's right boarder


// Solution for 1st methods
int get_height(CU::node *head, int level) {
	if(!head) {
		return level;
	}

	int left_height = get_height(head->left, level + 1);
	int right_height = get_height(head->right, level + 1);

	return std::max(left_height, right_height);
}

int get_height(CU::node *head) {
	if(!head) {
		return 0;
	}

	return std::max(get_height(head->left), get_height(head->right)) + 1;
}

void get_left_right_most_nodes(CU::node *head, std::vector<std::pair<CU::node*, CU::node*> >& v, int lvl) {
	if(!head) {
		return ;
	}

	// Pre-Order traverse to get boarder nodes

	// Update left most boarder on level 'lvl'
	// Update just one time is enough
	v[lvl].first = v[lvl].first ? v[lvl].first : head;
	// Update right most boarder on level 'lvl'
	v[lvl].second = head;
	get_left_right_most_nodes(head->left, v, lvl + 1);
	get_left_right_most_nodes(head->right, v, lvl + 1);
}

// Print leaft nodes, except boarder nodes
void print_leaf_nodes(CU::node *head, std::vector<std::pair<CU::node*, CU::node*> >& v, int lvl) {
	if(!head) {
		return ;
	}

	if(!head->left && !head->right) {
		if(head->value != v[lvl].first->value && head->value != v[lvl].second->value) {
			printf("Node(%d) ", head->value);
		}
	}

	print_leaf_nodes(head->left, v, lvl + 1);
	print_leaf_nodes(head->right, v, lvl + 1);
}

void print_binary_tree_boarder(CU::node *head) {
	if(!head) {
		return ;
	}

	int height = get_height(head);

	std::vector<std::pair<CU::node*, CU::node*> > left_right_most_nodes;
	// Must get the size first
	left_right_most_nodes.resize(height);
	get_left_right_most_nodes(head, left_right_most_nodes, 0);

	// Print left boarder
	printf("Left boarder of tree:\n");
	for(int i = 0; i < height; i++) {
		printf("Node(%d) ", left_right_most_nodes[i].first->value);
	}
	printf("\n");

	// Print leaf nodes at the bottom
	print_leaf_nodes(head, left_right_most_nodes, 0);

	// Print right boarder, except it is the node of left boarder too
	printf("Right boarder of tree:\n");
	for(int i = 0; i < height; i++) {
		if(left_right_most_nodes[i].second != left_right_most_nodes[i].first) {
			printf("Node(%d) ", left_right_most_nodes[i].second->value);
		}
	}
	printf("\n");

}

// Solution for 2nd methods

void print_left_edge(CU::node* head, bool b) {
	if(!head) {
		return ;
	}

	if(b && !head->left && !head->right) {
		printf("Left Node(%d) ", head->value);
	}

	print_left_edge(head->left, b);
	print_left_edge(head->right, b && !head->left ? true : false);
}

void print_right_edge(CU::node* head, bool b) {
	if(!head) {
		return ;
	}

	print_right_edge(head->left, b && !head->right ? true : false);
	print_right_edge(head->right, b);

	if(b && !head->left && !head->right) {
		printf("Right Node(%d) ", head->value);
	}

}

void print_edges(CU::node* head) {
	if(!head) {
		return;
	}

	printf("Common Node(%d) ", head->value);
	if(head->left && head->right) {
		print_left_edge(head->left, true);
		print_right_edge(head->right, true);
	} else {
		print_edges(head->left ? head->left : head->right);
	}
}


// [TIME_STAMP] Stop at 21:55, 2017/09/24


// [TIME_STAMP] Start at 16:02, 2017/10/03

// --------------------------------------------------------------------------------------------------------------
// 3.3 Print a binary tree with perceptual method
// [SKIP]

// --------------------------------------------------------------------------------------------------------------
// 3.4 Serialization and deserialization of a binary tree
// (1) Method 1, use pre-order traverse to do serialization and deserialization
// (2) Method 2, use queue traverse to do serialization and deserialization

// Use pre-order to serialize the binary tree
void binary_tree_serialization_by_preorder_process(CU::node* head, std::string& str) {
	if(!head) {
		str += "#!";
		return ;
	}

	// Format is 3!12!#!7!56!#!#!
	// '#' means a null node
	// '!' means the end of a node
	std::stringstream sstr;
	sstr << head->value << "!";
	str += sstr.str();

	binary_tree_serialization_by_preorder_process(head->left, str);
	binary_tree_serialization_by_preorder_process(head->right, str);
}

std::string binary_tree_serialization_by_preorder(CU::node* head) {
	if(!head) {
		return "#!";
	}

	std::string res;
	binary_tree_serialization_by_preorder_process(head, res);

	return res;
}

// deserialization a string(generated by pre-order traverse) to create a binary tree
CU::node* deserialization_to_create_binary_tree_process(std::string& str) {
	if(str.empty()) {
		return NULL;
	}
	// If serialization is correct and if this node is NULL
	// if then str[0] should be '#' instantly
	if(str[0] == '#') {
        // before returning, should remove
        // the character and next character,
        // since they are "#!", which represents
        // an empty node
        assert(str[1] == '!'); // next one must be '!'
        str.erase(0, 2); // erase first 2 chars
		return NULL;
	}

    bool neg = false;
    if (str[0] == '-') {
        neg = true;
    }

	int res = 0;
	int len = (neg ? 1 : 0);
	for(std::size_t i = (neg ? 1 : 0); i < str.size(); i++) {
		if(str[i] == '!') {
			break;
		}
		res *= 10;
		res += str[i] - '0';
		len++;
	}

	str.erase(0, len + 1);
	CU::node* p = new CU::node(neg ? -res : res);

	p->left = deserialization_to_create_binary_tree_process(str);
	p->right = deserialization_to_create_binary_tree_process(str);

	return p;
}


// Method 2, use queue traverse to do serialization and deserialization
std::string binary_tree_serialization_by_queue(CU::node* head) {
	std::string res;

	if(!head) {
		return "#!";
	}

	std::queue<CU::node*> squeue;
	squeue.push(head);

	while(!squeue.empty()) {
		CU::node* p = squeue.front();
		squeue.pop();
		if(p) {
			squeue.push(p->left);
			squeue.push(p->right);
			std::stringstream sstr;
			sstr << p->value << "!";
		} else {
			std::stringstream sstr;
			sstr << "#!";
		}
	}

	return res;
}


CU::node* generate_node_by_string(const std::string& str) {
	if(str == "#") {
		return NULL;
	}

	int i = boost::lexical_cast<int>(str.c_str());
	return new CU::node(i);
}

CU::node* binary_tree_deserialization_by_queue(const std::string& s) {
	if(s.empty()) {
		return NULL;
	}

	std::string temp(s);
	std::vector<std::string> sv;
	boost::split(sv, temp, boost::is_any_of("!"), boost::token_compress_on);
	if(sv.empty() || sv[0] == "#") {
		return NULL;
	}

	std::queue<CU::node*> sq;
	int index = 0;
	CU::node* head = new CU::node(boost::lexical_cast<int>(sv[index++].c_str()));
	sq.push(head);
	while(!sq.empty()) {
		CU::node* p = sq.front();
		sq.pop();
		p->left = generate_node_by_string(sv[index++]);
		p->right = generate_node_by_string(sv[index++]);
		if(p->left) {
			sq.push(p->left);
		}
		if(p->right) {
			sq.push(p->right);
		}
	}

	return head;
}

// --------------------------------------------------------------------------------------------------------------
// 3.5 Morris Traverse

// Morris Traverse in Pre-Order
void morris_pre_order(CU::node* head) {
	if(!head) {
		return ;
	}

	CU::node* p = head;
	CU::node* cur = NULL;
	while(p) {
		cur = p->left;
		if(cur) {
			while(cur->right && cur->right != p) {
				cur = cur->right;
			}
			if(!cur->right) { // or cur->right != p
				CU::VISIT(p);
				cur->right = p;
				p = p->left;
				continue;
			} else { // now cur->right == p
				cur->right = NULL;
				p = p->right;
			}
		} else {
			CU::VISIT(p);
			p = p->right;
		}
	}
}

// Morris Traverse in In-Order
void morris_in_order(CU::node* head) {
	if(!head) {
		return ;
	}

	CU::node* p = head;
	CU::node* cur = NULL;
	while(p) {
		cur = p->left;
		if(cur) {
			while(cur->right && cur->right != p) {
				cur = cur->right;
			}
			if(!cur->right) { // or cur->right != p
				cur->right = p;
				p = p->left;
				continue;
			} else { // now cur->right == p
				CU::VISIT(p);
				cur->right = NULL;
				p = p->right;
			}
		} else {
			CU::VISIT(p);
			p = p->right;
		}
	}
}

// Morris Traverse in Post-Order
// A customized function to reverse a linked list(use tree node 'right' as 'next' pointer)
CU::node* reverse_right_boarder(CU::node* head) {
	if(!head) {
		return NULL;
	}

	CU::node *pre = NULL;
	CU::node *cur = head;
	CU::node *next = cur;
	while(cur) {
		next = cur->right;
		cur->right = pre;
		pre = cur;
		cur = next;
	}

	return pre;
}

// Visit right boarder of a tree node
void visit_right_boarder(CU::node* h) {
	while(h) {
		CU::VISIT(h);
		h = h->right;
	}
}

void print_right_boarder(CU::node* h) {
	CU::node *start = reverse_right_boarder(h);
	visit_right_boarder(start);
	CU::node *end = reverse_right_boarder(start);
	// Just to remove the warning: warning: unused variable 'end' [-Wunused-variable]
	if(!end) {
		CU::VISIT(end);
	}
}

// Morris Traverse in Post-Order Implementation
void morris_post_order(CU::node* head) {
	if(!head) {
		return ;
	}

	CU::node* p = head;
	CU::node* cur = NULL;
	while(p) {
		cur = p->left;
		if(cur) {
			while(cur->right && cur->right != p) {
				cur = cur->right;
			}
			if(!cur->right) { // or cur->right != p
				cur->right = p;
				p = p->left;
				continue;
			} else { // now cur->right == p
				cur->right = NULL;
				print_right_boarder(p->left);
				p = p->right;
			}
		} else {
			p = p->right;
		}
	}

	print_right_boarder(head);
}


// --------------------------------------------------------------------------------------------------------------
// 3.6 Maximum path in a binary tree of a specified value sum
// k is the given sum for the path to find
// Pre-order traverse to resolve
void max_certain_sum_path_in_binary_tree_process(CU::node* head, int level, int sum, const int k, std::map<int, int>& m, int& max_height) {
	if(!head) {
		return ;
	}

	sum += head->value;
	std::map<int, int>::iterator itr = m.find(sum);
	if(itr == m.end()) {
		m.insert(std::make_pair(sum, level));
	}

	itr = m.find(sum - k);
	if(itr != m.end()) {
		max_height = std::max(max_height, level - itr->second);
	}

	max_certain_sum_path_in_binary_tree_process(head->left, level+1, sum, k, m, max_height);
	max_certain_sum_path_in_binary_tree_process(head->right, level+1, sum, k, m, max_height);

	if(level == m.find(sum)->second) {
		m.erase(m.find(sum));
	}
}

int max_certain_sum_path_in_binary_tree(CU::node* head, const int k) {
	int max_path_length = 0;
	std::map<int, int> m;
	m.insert(std::make_pair(0, 0));
	max_certain_sum_path_in_binary_tree_process(head, 1, 0, k, m, max_path_length);

	return max_path_length;
}

// --------------------------------------------------------------------------------------------------------------
// 3.7 Find the biggest BST(sub-tree) in a binary tree

// Meaning of tps
// Position - Meaning
// 0 - Number of BST nodes
// 1 - Min value of this sub tree(could be BST tree or not)
// 2 - Max value of this sub tree(could be BST tree or not)
CU::node* biggest_sub_bst_process(CU::node* head, boost::tuple<int, int, int>& tps) {
	if(!head) {
		tps.get<0>() = 0; // Number of BST nodes
		tps.get<1>() = std::numeric_limits<int>::max(); // Min value of this sub tree(could be BST tree or not)
		tps.get<2>() = std::numeric_limits<int>::min(); // Max value of this sub tree(could be BST tree or not)
		return NULL;
	}

	CU::node* left_bst_head = biggest_sub_bst_process(head->left, tps);
	int left_nodes = tps.get<0>();
	int left_min_value = tps.get<1>();
	int left_max_vlaue = tps.get<2>();

	CU::node* right_bst_head = biggest_sub_bst_process(head->right, tps);
	int right_nodes = tps.get<0>();
	int right_min_value = tps.get<1>();
	int right_max_vlaue = tps.get<2>();

	tps.get<1>() = std::min(head->value, left_min_value);
	tps.get<2>() = std::max(head->value, right_max_vlaue);

	if(left_bst_head == head->left && right_bst_head == head->right && left_max_vlaue < head->value && right_min_value > head->value) {
		tps.get<0>() = left_nodes + right_nodes + 1;
		return head;
	} else {
		tps.get<0>() = std::max(left_nodes, right_nodes);
		return left_nodes > right_nodes ? left_bst_head : right_bst_head;
	}

}

// [TIME_STAMP] Stop at 21:47, 2017/10/03


// [TIME_STAMP] Start at 10:04, 2017/10/04
// --------------------------------------------------------------------------------------------------------------
// 3.8 Find the number of the largest BST topologies in a binary tree
// (1) Use recursive soluation, time complexity is O(N^2)
// (2) Use node 'topo number contribution' method

// Check if node 'n' belongs to a BST tree(head is node 'head')
bool is_bst_node(CU::node* head, CU::node* n) {
	if(!n) {
		return false;
	}
	if(head == n) {
		return true;
	}
	return is_bst_node(n->value > head->value ? head->right : head->left, n);
}

// Recursive resolution
int max_topo_process(CU::node* head, CU::node* n) {
	if(!head) {
		return 0;
	}
	if(!n) {
		return 0;
	}
	if(is_bst_node(head, n)) {
		return max_topo_process(head, n->left) + max_topo_process(head, n->right) + 1;
	} else {
		return 0;
	}
}

int max_topo(CU::node* head) {
	if(!head) {
		return 0;
	}

	return max_topo_process(head, head);
}

int largest_bst_topo_size(CU::node* head) {
	if(!head) {
		return 0;
	}

	int max_num = max_topo(head);
	max_num = std::max(largest_bst_topo_size(head->left), max_num);
	max_num = std::max(largest_bst_topo_size(head->right), max_num);

	return max_num;
}


// Second solution
// Use node 'topo number contribution' method
//
// class contribution_record {
// public:
// 	// ctor
// 	contribution_record() : left_cont(0), right_cont(0) {}
// 	contribution_record(int l, int r) : left_cont(l), right_cont(r) {}
// 	contribution_record(const contribution_record& c) : left_cont(c.left_cont), right_cont(c.right_cont) {}
// 	contribution_record& operator= (const contribution_record& c) {
// 		left_cont = c.left_cont;
// 		right_cont = c.right_cont;
// 		return *this;
// 	}
// 	// member
// 	int left_cont;
// 	int right_cont;
// };

int modify_boarder(CU::node* n, int hvalue, std::map<CU::node*, contribution_record>& m, bool lor) {
	if(!n || m.find(n) == m.end()) {
		return 0;
	}
	std::map<CU::node*, contribution_record>::iterator itr = m.find(n);
	contribution_record r(itr->second);
	int minus = 0;
	if(lor) { // lor is true, means 'n' is the node from left sub-tree of head(head value is 'hvalue'
		if(n->value > hvalue) {
			m.erase(itr);
			return r.left_cont + r.right_cont + 1;
		} else {
			// since lor is true, so the node 'n' is from left sub-tree of head
			// Thus we just investigate the right boarder of its left sub-tree
			minus = modify_boarder(n->right, hvalue, m, true);
			r.right_cont -= minus;
			m[n] = r;
			return minus;
		}
	} else {// lor is false, means 'n' is the node from left sub-tree of head(head value is 'hvalue'
		if(n->value < hvalue) {
			m.erase(itr);
			return r.left_cont + r.right_cont + 1;
		} else {
			// since lor is false, so the node 'n' is from right sub-tree of head
			// Thus we just investigate the left boarder of its left sub-tree
			minus = modify_boarder(n->left, hvalue, m, false);
			r.left_cont -= minus;
			m[n] = r;
			return minus;
		}
	}
}

int largest_bst_topo_size_2nd_process(CU::node* head, std::map<CU::node*, contribution_record>& m) {
	if(!head) {
		return 0;
	}

	int lsize = largest_bst_topo_size_2nd_process(head->left, m);
	int rsize = largest_bst_topo_size_2nd_process(head->right, m);
	modify_boarder(head->left, head->value, m, true);
	modify_boarder(head->right, head->value, m, false);
	typedef std::map<CU::node*, contribution_record>::iterator miterator;
	miterator litr = m.find(head->left);
	miterator ritr = m.find(head->right);
	int lcontri = litr == m.end() ? 0 : litr->second.left_cont + litr->second.right_cont + 1;
	int rcontri = ritr == m.end() ? 0 : ritr->second.left_cont + ritr->second.right_cont + 1;
	m[head] = contribution_record(lcontri, rcontri);
	return std::max(lcontri + rcontri + 1, std::max(lsize, rsize));
}

int largest_bst_topo_size_2nd(CU::node* head) {
	std::map<CU::node*, contribution_record> m;
	return largest_bst_topo_size_2nd_process(head, m);
}

// --------------------------------------------------------------------------------------------------------------
// 3.9 Print a tree by level method and zigzag method

// Traverse by level
void visit_tree_by_level(CU::node* head) {
	std::queue<CU::node*> snq;
	if(head) {
		snq.push(head);
	}
	while(!snq.empty()) {
		CU::node* p = snq.front();
		snq.pop();
		if(p) {
			CU::VISIT(p);
			if(p->left) {
				snq.push(p->left);
			}
			if(p->right) {
				snq.push(p->right);
			}
		}
	}
}

// Traverse by zigzag method
void visit_tree_by_zigzag(CU::node* head) {
	std::deque<CU::node*> sndq;
	if(head) {
		sndq.push_back(head);
	}
	// CU::node* next_level_first = head->left ? head->left : head->right;
	CU::node* next_level_first = NULL;
	bool order = true;// true is pop front
	while(!sndq.empty()) {
		CU::node* p = NULL;
		if(order) {
			p = sndq.front();
			assert(p != NULL);
			sndq.pop_front();
			CU::VISIT(p);
			if(p->left) {
				sndq.push_back(p->left);
				next_level_first = next_level_first ? next_level_first : p->left;
			}
			if(p->right) {
				sndq.push_back(p->right);
				next_level_first = next_level_first ? next_level_first : p->right;
			}
			if(sndq.front() == next_level_first) {
				next_level_first = NULL;
				order = !order;
			}
		} else {
			p = sndq.back();
			assert(p != NULL);
			sndq.pop_back();
			CU::VISIT(p);
			if(p->right) {
				sndq.push_front(p->right);
				next_level_first = next_level_first ? next_level_first : p->right;
			}
			if(p->left) {
				sndq.push_front(p->left);
				next_level_first = next_level_first ? next_level_first : p->left;
			}
			if(sndq.back() == next_level_first) {
				next_level_first = NULL;
				order = !order;
			}
		}
	}
}

// --------------------------------------------------------------------------------------------------------------
// 3.10 Adjust 2 error nodes in a BST(Binary Search Tree)
//    Two methods to adjust error nodes after the 2 error nodes are found
//    (1) swap the node value directly(easy)
//    (2) swap the node pointers(difficult)

// forward declaration
void adjust_two_error_nodes_in_bst_process_1(CU::node* perr1, CU::node* perr2);
void adjust_two_error_nodes_in_bst_process_2(CU::node* perr1, CU::node* perr2);

// main function
void adjust_two_error_nodes_in_bst(CU::node* head) {
	std::stack<CU::node*> stk;
	CU::node* p = head;
	CU::node* pre = NULL;
	CU::node* err1 = NULL;
	CU::node* err2 = NULL;
	while(p || !stk.empty()) {
		while(p) {
			stk.push(p);
			p = p->left;
		}
		p = stk.top();
		stk.pop();
		if(pre && pre->value > p->value) {
			err1 = err1 ? err1 : pre;
			err2 = p;
		}
		pre = p;
		p = p->right;
	}

	// 2 methods, choose one to use
#if 1
	// Method 1 is swap the value directly
	adjust_two_error_nodes_in_bst_process_1(err1, err2);
#else
	// Method 2 is swap the node directly(don't swap the value)
	adjust_two_error_nodes_in_bst_process_2(head, err1, err2);
#endif
}

void adjust_two_error_nodes_in_bst_process_1(CU::node* perr1, CU::node* perr2) {
	// Swap nodes values
	int temp = perr1->value;
	perr1->value = perr2->value;
	perr2->value = temp;
}

void find_error_node_parents(CU::node* head, CU::node* perr1, CU::node* perr2, boost::tuple<CU::node*, CU::node*>& tps) {
	tps.get<0>() = NULL;
	tps.get<1>() = NULL;
	CU::node* p = head;
	std::stack<CU::node*> stk;
	while(p || !stk.empty()) {
		while(p) {
			stk.push(p);
			p = p->left;
		}
		p = stk.top();
		stk.pop();
		if(p->left == perr1) {
			tps.get<0>() = p;
		}
		if(p->right == perr2) {
			tps.get<1>() = p;
		}
		p = p->right;
	}

	// In case one of perr1 and perr2 is head
	// Actually if tps is set at the beginning
	// then there's no need to do this
	// Here just emphasize this to avoid confusion
	if(perr1 == head) {
		tps.get<0>() = NULL;
	}
	if(perr2 == head) {
		tps.get<1>() = NULL;
	}
}

CU::node* adjust_two_error_nodes_pointers(CU::node* head, CU::node* perr1, CU::node* perr2, const boost::tuple<CU::node*, CU::node*>& tps) {
	CU::node* err1parent = tps.get<0>();
	CU::node* err2parent = tps.get<1>();
	CU::node* err1leftchild = perr1->left;
	CU::node* err1rightchild = perr1->right;
	CU::node* err2leftchild = perr2->left;
	CU::node* err2rightchild = perr2->right;

	// Situation analysis
	// err1 is head
	//  |-- err1 and err2 are adjacent --> err2 must be the right child of err1 (1 situation)
	//  |-- err1 and err2 are NOT adjacent --> err2 might be the left/right child of err2parent (2 situations)
	//
	// err2 is head
	//  |-- err1 and err2 are adjacent --> err1 must be the left child of err2 (1 situation)
	//  |-- err1 and err2 are NOT adjacent --> err1 might be the left/right child of err1parent (2 situations)
	//
	// Neither err1 nor err2 is head
	//  |-- err1 and err2 are adjacent
	//  |     |-- err1 is the left child of err2, err2 might be the left/right child of err2parent (2 situations)
	//  |     |-- err2 is the right child of err1, err1 might be the left/right child of err1parent (2 situations)
	//  |-- err1 and err2 are NOT adjacent
	//        |-- err1 might be the left/right child of err1parent, err2 might be the left/right child of err2parent (4 situations)
	//
	// Total situations = 1 + 2 + 1 + 2 + 2 + 2 + 4 = 14

	if(perr1 == head) { // err1 is head
		if(perr1->right == perr2) { // err1 and err2 are adjacent
			assert(err1rightchild == perr2);
			perr2->left = err1leftchild;
			perr2->right = perr1;
			perr1->left = err2leftchild;
			perr2->right = err2rightchild;
		} else { // err1 and err2 are NOT adjacent
			if(err2parent->left == perr2) { // err2 might be the LEFT child of err2parent
				perr2->left = err1leftchild;
				perr2->right = err1rightchild;
				err2parent->left = perr1;
				perr1->left = err2leftchild;
				perr1->right = err2rightchild;
			} else { // err2 might be the RIGHT child of err2parent
				perr2->left = err1leftchild;
				perr2->right = err1rightchild;
				err2parent->right = perr1;
				perr1->left = err2leftchild;
				perr1->right = err2rightchild;
			}
		}
	} else if(perr2 == head) { // err2 is head
		if(perr2->left == perr1) { // err1 and err2 are adjacent
			assert(err2leftchild == perr1);
			perr1->left = perr2;
			perr1->right = err2rightchild;
			perr2->left = err1leftchild;
			perr2->right = err1rightchild;
		} else { // err1 and err2 are NOT adjacent
			if(err1parent->left == perr1) { // err1 might be the LEFT child of err1parent
				perr1->left = err2leftchild;
				perr1->right = err2rightchild;
				err1parent->left = perr2;
				perr2->left = err1leftchild;
				perr2->right = err1rightchild;
			} else { // err1 might be the RIGHT child of err1parent
				perr1->left = err2leftchild;
				perr1->right = err2rightchild;
				err1parent->right = perr2;
				perr2->left = err1leftchild;
				perr2->right = err1rightchild;
			}
		}
	} else { // Neither err1 nor err2 is head
		if(perr2->left == perr1) { // err1 is the left child of err2
			assert(err2leftchild == perr1);
			perr2->left = err1leftchild;
			perr2->right = err1rightchild;
			if(err2parent->left == perr2) { // err2 might be the LEFT child of err2parent
				err2parent->left = perr1;
			} else {  // err2 might be the RIGHT child of err2parent
				err2parent->right = perr1;
			}
			perr1->left = perr2;
			perr1->right = err2rightchild;
		} else if(perr1->right == perr2) { // err2 is the right child of err1
			assert(err1rightchild == perr2);
			perr2->left = err1leftchild;
			perr2->right = perr1;
			if(err1parent->left == perr1) { // err1 might be the LEFT child of err1parent
				err1parent->left = perr2;
			} else { // err1 might be the RIGHT child of err1parent
				err1parent->right = perr2;
			}
			perr1->left = err2leftchild;
			perr1->right = err2rightchild;
		} else { // err1 and err2 are NOT adjacent
			if(err2parent->left == perr2) {
				err2parent->left = perr1;
			} else {
				err2parent->right = perr1;
			}
			perr1->left = err2leftchild;
			perr1->right = err2rightchild;
			if(err1parent->left == perr1) {
				err1parent = perr2;
			} else {
				err1parent = perr2;
			}
			perr2->left = err1leftchild;
			perr2->right = err1rightchild;
		}
	}

	return head;
}

void adjust_two_error_nodes_in_bst_process_2(CU::node* head, CU::node* perr1, CU::node* perr2) {
	boost::tuple<CU::node*, CU::node*> tps;
	tps.get<0>() = NULL;
	tps.get<1>() = NULL;
	find_error_node_parents(head, perr1, perr2, tps);
	adjust_two_error_nodes_pointers(head, perr1, perr2, tps);
}


// --------------------------------------------------------------------------------------------------------------
// 3.11 If tree1 contains the whole topologies of tree2

bool tree_topo_contain_process(CU::node* t1, CU::node* t2) {
	if(!t1 && !t2) {
		return true;
	} else if(t1 && !t2) {
		return true;
	} else if(!t1 && t2) {
		return false;
	} else {
		// now t1 and t2 are both not NULL
		if(t1->value == t2->value) {
			return tree_topo_contain_process(t1->left, t2->left) && tree_topo_contain_process(t1->right, t2->right);
		} else {
			return false;
		}
	}
}

bool tree_topo_contain(CU::node* t1, CU::node* t2) {
	if(tree_topo_contain_process(t1, t2)) {
		return true;
	}

	return tree_topo_contain(t1->left, t2) || tree_topo_contain(t1->right, t2);
}

// --------------------------------------------------------------------------------------------------------------
// 3.12 If tree1 has a sub-tree which is exactly the same topologies as the tree2
// Two methods
// (1) Recursive resolution
// (2) Serialization + KMP

// Method 1
bool tree_topo_compare(CU::node* t1, CU::node* t2) {
	if(!t1 && !t2) {
		return true;
	} else if(t1 && !t2) { // pay attention to this, different from in function tree_topo_contain_process
		return false;
	} else if(!t1 && t2) {
		return false;
	} else {
		if(t1->value == t2->value) {
			return tree_topo_compare(t1->left, t2->left) && tree_topo_compare(t1->right, t2->right);
		} else {
			return false;
		}
	}
}

bool tree_topo_exactly_contain(CU::node* t1, CU::node* t2) {
	if(tree_topo_compare(t1, t2)) {
		return true;
	}

	return tree_topo_exactly_contain(t1->left, t2) || tree_topo_exactly_contain(t1->right, t2);
}

// Method 2, Serialization + KMP
void get_next_array(const std::string& m, std::vector<int>& next_array) {
	next_array.clear();
	if(m.size() <= 0) {
		return ;
	}
	if(m.size() == 1) {
		next_array.push_back(-1);
		return ;
	}
	if(m.size() == 2) {
		next_array.push_back(-1);
		next_array.push_back(0);
		return ;
	}
	next_array.resize(m.size());
	std::size_t i = 2;
	next_array[0] = -1;
	next_array[1] = 0;
	int idx = 0;
	while(i < m.size()) {
		if(m[i - 1] == m[idx]) {
			next_array[i++] = ++idx;
		} else if(idx > 0) {
			idx = next_array[idx];
		} else {
			next_array[i++] = 0;
		}
	}
}

bool kmp_compare(const std::string& s, const std::string& m) {
	std::vector<int> next;
	get_next_array(m, next);
	std::size_t si = 0;
	std::size_t mi = 0;
	const std::size_t ssize = s.size();
	const std::size_t msize = m.size();
	while(si < ssize && mi < msize) {
		if(s[si] == m[mi]) {
			si++;
			mi++;
		} else {
			if(next[mi] == -1) {
				si++;
			} else {
				mi = m[mi];
			}
		}
	}

	// if need to no match start position, use return mi == m.size() ? si - mi : -1;
	return mi == m.size() ? true : false;
}

bool tree_topo_exactly_contain_2(CU::node* t1, CU::node* t2) {
	std::string str1, str2;
	// function binary_tree_serialization_by_preorder_process is implemented in 3.4
	binary_tree_serialization_by_preorder_process(t1, str1);
	binary_tree_serialization_by_preorder_process(t2, str2);
	if(str1.size() < str2.size()) {
		return false;
	}

	return kmp_compare(str2, str2);
}

// --------------------------------------------------------------------------------------------------------------
// 3.13 Is a balanced tree

void is_balanced_tree_process(CU::node* n, bool& balanced, int& height) {
	if(!n) {
		balanced = true;
		height = 0;
		return ;
	}

	is_balanced_tree_process(n->left, balanced, height);
	bool left_balanced = balanced;
	int left_height = height;
	is_balanced_tree_process(n->right, balanced, height);
	bool right_balanced = balanced;
	int right_height = height;

	height = std::max(left_height, right_height) + 1;
	if(!left_balanced || !right_balanced || std::abs(left_height - right_height) > 1) {
		balanced = false;
	} else {
		balanced = true;
	}
}

bool is_balanced_tree(CU::node* head) {
	bool balanced = false;
	int height = 0;
	is_balanced_tree_process(head, balanced, height);
	return balanced;
}

// --------------------------------------------------------------------------------------------------------------
// 3.14 Rebuild a binary tree as per an array generated in post-order traversal of a tree
// Prerequisite: values are unique in the array
// Two steps
// (1) Decide if an array is(or is not) generated in post-order traversal of a tree
// (2) If it is, rebuild the binary tree

// Solution to (1) Decide if an array is(or is not) generated in post-order traversal of a tree
// Use two pointers(indexes) 'less' and 'more'
// 'less' means the last one which is less than the head of this sub-tree(actually is the last element in the array)
// 'more' means the first one which is greater than the head of this sub-tree(actually is the last element in the array)

bool is_bst_post_array_process(const std::vector<int>& ivec, int start, int end) {
	if(start > end) {
		return false;
	}
	if(start == end) {
		return true;
	}
	int less = -1; // use an invalid value to set a flag
	int more = -1;
	for(int i = start; i < end; i++) {
		if(ivec[i] < ivec[end]) {
			less = i;
		} else {
			more = more == -1 ? i : more;
		}
	}

	if(less == -1 || more == -1) {
		return is_bst_post_array_process(ivec, start, end - 1);
	}

	if(less + 1 != more) {
		return false;
	}

	return is_bst_post_array_process(ivec, start, less) && is_bst_post_array_process(ivec, more, end - 1);
}

bool is_bst_post_array(const std::vector<int>& ivec) {
	if(ivec.empty()) {
		return false;
	}

	return is_bst_post_array_process(ivec, 0, ivec.size() - 1);
}

// Solution to (2) If an array is the traversal result of a BST in post order, rebuild it
CU::node* rebuild_bst_from_post_array_process(const std::vector<int>& ivec, int start, int end) {
	if(start > end) {
		return NULL;
	}

	if(start == end) {
		return new CU::node(ivec[start]);
	}

	int less = -1; // use an invalid value to set a flag
	int more = -1;
	for(int i = start; i < end; i++) {
		if(ivec[i] < ivec[end]) {
			less = i;
		} else {
			more = more == -1 ? i : more;
		}
	}

	CU::node* h = new CU::node(ivec[end]);

	if(less == -1 ) { // means 'less' didn't move, which says ivec[start...end-1] are all greater than ivec[end]
		h->right = rebuild_bst_from_post_array_process(ivec, start, end - 1);
	} else if(more == -1) { // means 'more' didn't move, which says ivec[start...end-1] are all less than ivec[end]
		h->left = rebuild_bst_from_post_array_process(ivec, start, end - 1);
	} else {
		h->left = rebuild_bst_from_post_array_process(ivec, start, less);
		h->right = rebuild_bst_from_post_array_process(ivec, more, end - 1);
	}

	return h;
}

CU::node* rebuild_bst_from_post_array(const std::vector<int>& ivec) {
	// First decide if an array is valid for the given conditions
	if(!is_bst_post_array(ivec)) {
		return NULL;
	}

	return rebuild_bst_from_post_array_process(ivec, 0, ivec.size() - 1);
}

// --------------------------------------------------------------------------------------------------------------
// 3.15 Judge if a tree is BST; Judge if a tree is a full binary tree
//  Two problems here, which are
//  (1) Judge if a tree is BST
//  (2) Judge if a tree is a full binary tree

// Solution to (1) Judge if a tree is BST
bool is_bst_tree(CU::node* head) {
	if(!head) {
		return false;
	}

	// In-order traversal
	CU::node* pre = NULL;
	std::stack<CU::node*> stk;
	CU::node* p = head;
	while(p || !stk.empty()) {
		while(p) {
			stk.push(p);
			p = p->left;
		}
		p = stk.top();
		stk.pop();
		if(pre && pre->value > p->value) {
			return false;
		}
		pre = p;
		p = p->right;
	}

	return true;
}

//  Solution to (2) Judge if a tree is a full binary tree
bool is_full_tree(CU::node* head) {
	if(!head) {
		return false;
	}

	// Traversal by level
	std::queue<CU::node*> sq;
	sq.push(head);
	CU::node* p = NULL;
	bool leaf = false;
	while(!sq.empty()) {
		p = sq.front();
		sq.pop();
		if(!p->left && p->right) {
			return false;
		}
		if(leaf && (p->left || p->right)) {
			return false;
		}

		if(p->left && !p->right) {
			// In this case, from next node on, they all should be leaf nodes
			// If not, then return false directly since conditions for full tree will not be satisfied
			leaf = true;
		}
		if(p->left) {
			sq.push(p->left);
		}
		if(p->right) {
			sq.push(p->right);
		}
	}

	return true;
}

// --------------------------------------------------------------------------------------------------------------
// 3.16 Generate a BST from a sorted/ordered array
// Prerequisites: values are unique in the array

CU::node* build_bst_from_sorted_array_process(const std::vector<int>& ivec, int start, int end) {
	if(start > end) {
		return NULL;
	}

	if(start == end) {
		return new CU::node(ivec[end]);
	}

	int mid = (start + end)/2;
	CU::node* h = new CU::node(ivec[mid]);

	h->left = build_bst_from_sorted_array_process(ivec, start, mid - 1);
	h->right = build_bst_from_sorted_array_process(ivec, mid + 1, end);

	return h;
}

CU::node* build_bst_from_sorted_array(const std::vector<int>& ivec) {
	if(ivec.empty()) {
		return NULL;
	}

	return build_bst_from_sorted_array_process(ivec, 0, ivec.size() - 1);
}

// --------------------------------------------------------------------------------------------------------------
// 3.17 Find the successor of a tree node, this tree node has a pointer to its parent

// Given condition
//
// class special_tree_node {
// public:
// 	special_tree_node(int v) : parent(NULL), left(NULL), right(NULL) {}
// public:
// 	special_tree_node* parent;
// 	special_tree_node* left;
// 	special_tree_node* right;
// };

// Solution
special_tree_node* find_successor(special_tree_node* n) {
	if(!n) {
		return NULL;
	}
	if(n->right) {
		// So in this case n has a right sub-tree
		// so the left most node is the successor
		special_tree_node* l = n->right;
		while(l->left) {
			l = l->left;
		}
		return l;
	}

	special_tree_node* p = n->parent;
	special_tree_node* s = n;
	while(p) {
		if(p->left == s) {
			break;
		} else {// p->right == s
			p = p->parent;
			s = s->parent;
		}
	}

	return p;
}
// [TIME_STAMP] Stop at 22:00, 2017/10/04


// [TIME_STAMP] Start at 09:11, 2017/10/05
// --------------------------------------------------------------------------------------------------------------
// 3.18 Find the most recent common ancestor of 2 nodes in a tree
// Two problems
// (1) Query the most recent common ancestor of 2 nodes in a tree for just one time
// (2) Query the most recent common ancestor of 2 nodes in a tree for many times

// Solution to (1) Query the most recent common ancestor of 2 nodes in a tree for just one time
CU::node* most_recent_common_ancestor_process(CU::node* h, CU::node* n1, CU::node* n2, CU::node*& res) {
	if(!h) {
		return NULL;
	}

	if(h == n1 || h == n2) {
		return h;
	}

	CU::node* left = most_recent_common_ancestor_process(h->left, n1, n2, res);
	CU::node* right = most_recent_common_ancestor_process(h->right, n1, n2, res);
	if(!left && !right) {
		return NULL;
	} else if(left && right) {
		return res ? res : h;
	} else {
		// In this case, left or right is NULL
		// which is to say one of left and right is NULL
		return left ? left : right;
	}
}

CU::node* most_recent_common_ancestor(CU::node* h, CU::node* n1, CU::node* n2) {
	CU::node* res = NULL;
	// res is like a global variable
	return most_recent_common_ancestor_process(h, n1, n2, res);
}

// Solution to (2) Query the most recent common ancestor of 2 nodes in a tree for many times


// class most_recent_common_ancestor {
// public:
// 	most_recent_common_ancestor() : m_head(NULL) {}
// 	most_recent_common_ancestor(CU::node* h) : m_head(h) { prepare(); }
// 	~most_recent_common_ancestor() { m_map.clear(); }
// 	void prepare();
// 	void build_parent_map(CU::node* h);
// 	CU::node* execute_query(CU::node* n1, CU::node* n2);
// private:
// 	std::map<CU::node*, CU::node*> m_map;
// 	CU::node* m_head;
// };

void most_recent_common_ancestor::build_parent_map(CU::node* h) {
	if(!h) {
		return ;
	}
	if(h->left) {
		m_map.insert(std::make_pair(h->left, h)); // the parent of 'h->left' is 'h'
	}
	if(h->right) {
		m_map.insert(std::make_pair(h->right, h)); // the parent of 'h->right' is 'h'
	}

	build_parent_map(h->left);
	build_parent_map(h->right);
}

void most_recent_common_ancestor::prepare() {
	m_map.clear();
	if(!m_head) {
		return ;
	}
	m_map.insert(std::pair<CU::node*, CU::node*>(m_head, NULL)); // the parent of the head is NULL

	build_parent_map(m_head);
}

CU::node* most_recent_common_ancestor::execute_query(CU::node* n1, CU::node* n2) {
	if(!n1 || !n2) {
		return NULL;
	}
	// std::map<CU::node*, CU::node*> m;
	std::set<CU::node*> s;

	CU::node* p = n1;
	std::map<CU::node*, CU::node*>::iterator mitr = m_map.find(p);
	while(mitr != m_map.end()) {
		s.insert(p);
		p = mitr->second;
		mitr = m_map.find(p);
	}

	p = n2;
	std::set<CU::node*>::iterator sitr = s.find(p);
	while(sitr == s.end()) {
		mitr = m_map.find(p);
		if(mitr == m_map.end()) {
			// This case indicates p has no father/parent
			return NULL;
		} else {
			// This case indicates p HAS father/parent
			p = mitr->second;
		}
		sitr = s.find(p);
	}

	return *sitr;
}

CU::node* most_recent_common_ancestor_query(CU::node* head, CU::node* n1, CU::node* n2) {
	class most_recent_common_ancestor mrca(head);
	return mrca.execute_query(n1, n2);
}

// --------------------------------------------------------------------------------------------------------------
// 3.19 Tarjan Algorithm and disjoint set
// prerequisites:
// (1) Given a node pair array(query array, std::vector<std::pair<CU::node*, CU::node*> >)
//     Return the most recent common ancestors in the tree as array as per each pair in the array
// (2) Use Tarjan algorithm
// (3) Use disjoint set
// (4) Return result array(std::vector<CU::node*>), each element represents a parent of 2 node
// (5) Time complexity is O(N+M), N is tree total nodes, M is the size of query array

class disjoint_set;

class tarjan_solve;


// --------------------------------------------------------------------------------------------------------------
// 3.20 Maximum path length between 2 nodes in a binary tree

int get_tree_height(CU::node* h) {
	if(!h) {
		return 0;
	}

	return std::max(get_tree_height(h->left), get_tree_height(h->right)) + 1;
}

int max_path_length_between_two_nodes_process(CU::node* h, int& max_height) {
	if(!h) {
		max_height = 0;
		return 0;
	}

	int left_max_path_len = max_path_length_between_two_nodes_process(h->left, max_height);
	int left_tree_height = max_height;
	int right_max_path_len = max_path_length_between_two_nodes_process(h->right, max_height);
	int right_tree_height = max_height;

	max_height = std::max(left_tree_height, right_tree_height) + 1;

	return std::max(max_height, std::max(left_max_path_len, right_max_path_len));
}

int max_path_length_between_two_nodes(CU::node* head) {
	int height = 0;
	return max_path_length_between_two_nodes_process(head, height);
}
// [TIME_STAMP] Stop at 13:42, 2017/10/05



// [TIME_STAMP] Start at 16:45, 2017/10/05
// --------------------------------------------------------------------------------------------------------------
// 3.21 Rebuild a binary tree from arrays of different traversal order
// Three problems
// (1) Rebuild a binary tree from arrays of PRE-order and IN-order
// (2) Rebuild a binary tree from arrays of IN-order and POST-order
// (3) Rebuild a binary tree from arrays of PRE-order and POST-order

// Solution to (1) Rebuild a binary tree from arrays of PRE-order and IN-order
CU::node* rebuild_from_pre_and_in_order_process(const std::vector<int>& pre, const std::vector<int>& in,
										int pre_start, int pre_end, int in_start, int in_end) {
	if(pre_start > pre_end || in_start > in_end) {
		return NULL;
	}

	if(pre_start == pre_end) {
		assert(in_start == in_end);
		return new CU::node(pre[pre_start]);
	}

	CU::node* h = new CU::node(pre.front());
	std::vector<int>::const_iterator itr = std::find(in.begin(), in.end(), pre.front());
	assert(itr != in.end());
	std::size_t index = itr - in.begin();
	h->left = rebuild_from_pre_and_in_order_process(pre, in, pre_start + 1, pre_start + (index + 1), in_start, index - 1);
	h->right = rebuild_from_pre_and_in_order_process(pre, in, pre_start + (index + 1) + 1, pre_end, index + 1, in_end);

	return h;
}

CU::node* rebuild_from_pre_and_in_order(const std::vector<int>& pre, const std::vector<int>& in) {
	if(pre.empty() || in.empty()) {
		return NULL;
	}

	assert(pre.size() == in.size());
	return rebuild_from_pre_and_in_order_process(pre, in, 0, pre.size() - 1, 0, in.size() - 1);
}

// Solution to (2) Rebuild a binary tree from arrays of IN-order and POST-order
CU::node* rebuild_from_in_and_post_order_process(const std::vector<int>& in, const std::vector<int>& post,
										int in_start, int in_end, int post_start, int post_end)  {
	if(in_start > in_end || post_start > post_end) {
		return NULL;
	}

	if(in_start == in_end) {
		assert(post_start == post_end);
		return new CU::node(in[in_start]);
	}

	CU::node* h = new CU::node(post.back());
	std::vector<int>::const_iterator itr = std::find(in.begin(), in.end(), post.back());
	assert(itr != in.end());
	std::size_t index = itr - in.begin();
	h->left = rebuild_from_in_and_post_order_process(in, post, in_start, index - 1, post_start, post_start + index);
	h->right = rebuild_from_in_and_post_order_process(in, post, index + 1, in_end, post_start + index + 1, post_end - 1);

	return h;
}

CU::node* rebuild_from_in_and_post_order(const std::vector<int>& in, const std::vector<int>& post) {
	if(in.empty() || post.empty()) {
		return NULL;
	}

	assert(in.size() == post.size());
	return rebuild_from_in_and_post_order_process(in, post, 0, in.size() - 1, 0, post.size() - 1);
}

// Solution to (3) Rebuild a binary tree from arrays of PRE-order and POST-order
// Caution
//   every node in the tree satisfies the condition below would be recovered from PRE-order and POST-order arrays
// Condition
//   every node should have 2 children, except those leaf nodes

CU::node* rebuild_from_pre_and_post_order_process(const std::vector<int>& pre, const std::vector<int>& post,
										int pre_start, int pre_end, int post_start, int post_end) {
	if(pre_start > pre_end || post_start > post_end) {
		return NULL;
	}

	if(pre_start == pre_end) {
		assert(post_start == post_end);
		return new CU::node(pre[pre_start]);
	}

	CU::node* h = new CU::node(pre.front());
	std::vector<int>::const_iterator itr = std::find(post.begin(), post.end(), *(pre.begin() + pre_start + 1));
	assert(itr != post.end());
	std::size_t index = itr - post.begin();
	h->left = rebuild_from_pre_and_post_order_process(pre, post, pre_start + 1, pre_start + 1 + index, post_start, index);
	h->right = rebuild_from_pre_and_post_order_process(pre, post, pre_start + 1 + index + 1, pre_end, index + 1, post_end);

	return h;
}

CU::node* rebuild_from_pre_and_post_order(const std::vector<int>& pre, const std::vector<int>& post) {
	if(pre.empty() || post.empty()) {
		return NULL;
	}

	assert(pre.size() == post.size());
	return rebuild_from_pre_and_post_order_process(pre, post, 0, pre.size() - 1, 0, post.size() - 1);
}

// --------------------------------------------------------------------------------------------------------------
// 3.22 Generate post-order traversal array directly from pre-order & in-order arrays

//  [In] pre, in
// [Out] post
void generate_post_order_from_pre_and_in_order(const std::vector<int>& pre, const std::vector<int>& in, std::vector<int>& post,
											int pre_start, int pre_end, int in_start, int in_end, int post_start, int post_end) {
	if(pre_start > pre_end || in_start > in_end) {
		return ;
	}

	if(pre_start == pre_end) {
		post[post_end] = pre[pre_start];
		return ;
	}

	std::vector<int>::const_iterator itr = std::find(in.begin(), in.end(), pre.front());
	std::size_t index = itr - in.begin();
	assert(itr != in.end());
	generate_post_order_from_pre_and_in_order(pre, in, post, pre_start + 1, pre_start + index - in_start + 1,
															in_start, index - 1, post_start, post_start + index - in_start - 1);
	generate_post_order_from_pre_and_in_order(pre, in, post, pre_start + index - in_start + 1 + 1, pre_end,
															index + 1, in_end, post_start + index - in_start, post_end - 1);
}

void generate_post_order_array_from_pre_and_in_order_arrays(const std::vector<int>& pre, const std::vector<int>& in) {
	if(pre.empty() || in.empty()) {
		return ;
	}
	if(pre.size() != in.size()) {
		return ;
	}

	std::vector<int> post_vec;
	post_vec.resize(pre.size());
	generate_post_order_from_pre_and_in_order(pre, in, post_vec, 0, pre.size() - 1, 0, in.size() - 1, 0, post_vec.size() - 1);
}

// --------------------------------------------------------------------------------------------------------------
// 3.23 How many possibility is as per given number N to form a binary tree
// Prerequisites
//	(1) N mean array {1, 2, 3, ... , N-1, N} (N>0)
//	(2) array is the traversal result of a tree in in-order
// Solve
//	(1) Get number of possibilities
//	(2) Get all tree head nodes of those possibilities


// Solution to (1) Get number of possibilities
int possible_trees_as_per_given_number_process(const int start, const int end) {
	if(start > end) {
		return 0;
	}
	if(start == end) {
		return 1;
	}
	if(start + 1 == end) {
		return 2;
	}

	int sum = 0;
	for(int i = start; i <= end; i++) {
		// Regard i as head of a tree
		sum += possible_trees_as_per_given_number_process(start, i - 1) * possible_trees_as_per_given_number_process(i + 1, end);
	}

	return sum;
}

int possible_trees_as_per_given_number(const int n) {
	if(n <= 0) {
		return 0;
	}

	if(n == 1) {
		return 1;
	}
	if(n == 2) {
		return 2;
	}
	return possible_trees_as_per_given_number_process(1, n);
}

// Solution to (2) Get all tree head nodes of those possibilities
std::list<CU::node*> get_possible_tree_head_nodes_as_per_given_number_process(const int start, const int end) {
	std::list<CU::node*> l;
	if(start > end) {
		l.push_back(NULL);
		return l;
	}
	if(start == end) {
		l.push_back(new CU::node(start));
		return l;
	}

	for(int i = start; i <= end; i++) {
		// Regard i as head of a tree
		CU::node* h = new CU::node(i);
		std::list<CU::node*> left_node_list = get_possible_tree_head_nodes_as_per_given_number_process(start, i - 1);
		std::list<CU::node*> right_node_list = get_possible_tree_head_nodes_as_per_given_number_process(i + 1, end);
		for(std::list<CU::node*>::iterator i = left_node_list.begin(); i != left_node_list.end(); i++) {
			for(std::list<CU::node*>::iterator j = right_node_list.begin(); j != right_node_list.end(); j++) {
				h->left = *i;
				h->right = *j;
				l.push_back(CU::clone_tree(h));
			}
		}
	}

	return l;
}

// --------------------------------------------------------------------------------------------------------------
// 3.24 Calculate number of nodes in a complete binary tree
// Two methods
// (1) Traversal to count (normal solution)
// (2) Recursive to cout by check left-most nodes of right sub-tree

// Method 1
// [Skip]

// Method 2
int count_node_number(CU::node* n, const int height, const int level) {
	if(!n) {
		return 0;
	}

	CU::node* rsub = n->right;
	int to_level = level + 1; // rsub is on level 'to_level'
	while(rsub) {
		rsub = rsub->left;
		to_level++;
	}
	to_level--;

	// Choose one way to return, each one is fine
#if 0
	if(to_level == height) {
		// In this case, right sub-tree of node 'n' reaches the total height of the whole tree
		return (2 << (height - level + 1)) - 1 + 1/* node n itself */ + count_node_number(n->right, height, level + 1);
	} else {
		return (2 << (to_level - level + 1)) - 1 + 1/* node n itself */ + count_node_number(n->left, height, level + 1);
	}
#else
	return (2 << (to_level - level + 1)) - 1 + 1/* node n itself */ +
			to_level == height ? count_node_number(n->right, height, level + 1) : count_node_number(n->left, height, level + 1);
#endif
}

int node_number_in_complete_binary_tree(CU::node* head) {
	int height = CU::tree_height(head);
	return count_node_number(head, height, 1);
}

// [TIME_STAMP] Stop at 20:43, 2017/10/05


// [TIME_STAMP] Start at XX:XX, 2017/XX/XX
// [TIME_STAMP] Stop at XX:XX, 2017/XX/XX



// [TIME_STAMP] Start at XX:XX, 2017/XX/XX
// [TIME_STAMP] Stop at XX:XX, 2017/XX/XX

} // end-of-namespace C3
