/*
 * chapter_2.hpp
 *
 *  Created on: Oct. 5, 2017
 *      Author: Pyrad
 * Description: Header file of chapter 2 Linked List
 *   Intention: Solutions for problems in Chapter 2[Linked List] of Code Interview Guide
 */

#ifndef CHAPTER_2_HPP_
#define CHAPTER_2_HPP_

// Boost libraries
#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_io.hpp>
#include <boost/scoped_ptr.hpp>

#include <stdio.h>
#include <math.h>

#include <iostream>
#include <stack>
#include <sstream>
#include <vector>
#include <queue>
#include <deque>
#include <cstring>
#include <map>
#include <set>

#include "common_utils.hpp"

namespace C2 {

namespace CU = common_utils;


// [TIME_STAMP] Start at 09:23, 2017/10/07
// --------------------------------------------------------------------------------------------------------------
// 2.1 Print common part of two ordered linked list

void print_two_common_part_of_two_ordered_linked_list(CU::lnode* head1, CU::lnode* head2);


// --------------------------------------------------------------------------------------------------------------
// 2.2 Remove the K-th from the end of a linked list or a double linked list
// Two problems
// (1) Remove the K-th from the end of a linked list
// (2) Remove the K-th from the end of a double linked list
// After removed, return the head node of the list


// Solution to (1) Remove the K-th from the end of a linked list
CU::lnode* remove_reciprocal_k_node_from_end(CU::lnode* head, const int k);

// Solution to (2) Remove the K-th from the end of a double linked list
CU::dlnode* remove_reciprocal_k_node_from_end(CU::dlnode* head, const int k);

// --------------------------------------------------------------------------------------------------------------
// 2.3 Remove a node in a linked list, which is located
//     (1) in the middle
//     (2) in a/b position of whole list length

CU::lnode* remove_middle_node(CU::lnode* head);

CU::lnode* remove_A_Bth_node(CU::lnode* head, const int a, const int b);

// --------------------------------------------------------------------------------------------------------------
// 2.4 Reversion of a linked list or a double linked list
// Two problems
// (1) Reverse a linked list
// (2) Reverse a double linked list

CU::lnode* reverse_linked_list(CU::lnode* head);

CU::dlnode* reverse_double_linked_list(CU::dlnode* head);

// --------------------------------------------------------------------------------------------------------------
// 2.5 Reverse part of a linked list
// Given integer 'from' and 'to', reverse list between them

CU::lnode* reverse_list_from_to(CU::lnode* head, const int from, const int to);

// [TIME_STAMP] Stop at 11:22, 2017/10/07



// [TIME_STAMP] Start at 13:48, 2017/10/07
// --------------------------------------------------------------------------------------------------------------
// 2.6 Josephus Ring Problem

// Solution
// According to recursion formula, R(n) = [R(n-1) + m] % n
// We could directly resolve the problem
// See analysis in cig_notes.docx

int josephus_resolve(int n, int m);

int josephu_problem(int n, int m);


// --------------------------------------------------------------------------------------------------------------
// 2.7 Judge if a linked list is palindrome

bool is_palindrome_list(CU::lnode* head);

// --------------------------------------------------------------------------------------------------------------
// 2.8 Adjust a linked list to be separated by a pivot value
//  (1) Nodes whose values are less than the pivot are at front
//  (2) Nodes whose values are equal to the pivot are in the middle
//  (3) Nodes whose values are greater than the pivot are at back

CU::lnode* adjust_list_to_three_parts(CU::lnode* head, const int pivot);


// --------------------------------------------------------------------------------------------------------------
// 2.9 Copy a linked list whose every node has a random pointer to a node in the list

class rnode {
public:
	rnode(int v) : value(v), next(NULL), random(NULL) {}

public:
	int value;
	rnode *next;
	rnode* random;
};

rnode* copy_list_with_random_pointers(rnode* head);


// --------------------------------------------------------------------------------------------------------------
// 2.10 Get the sum of two linked list(add two linked list together)
// Prerequisite: Each node's value should be in range from 0 to 9

CU::lnode* add_two_list(CU::lnode *p, CU::lnode *q);


// --------------------------------------------------------------------------------------------------------------
// 2.11 If two linked list intersect with each other

bool has_loop(CU::lnode *head);

CU::lnode* first_node_in_loop(CU::lnode *head);

// if NULL is returned, it means h1 and h2 have no intersection
// otherwise the first intersecting node is returned
CU::lnode* intersect_node(CU::lnode *h1, CU::lnode *h2);

// --------------------------------------------------------------------------------------------------------------
// 2.12 Reverse every K nodes in a linked list

CU::lnode* reverse_by_every_k_nodes(CU::lnode *head, int k);

// --------------------------------------------------------------------------------------------------------------
// 2.13 Remove duplicated nodes in a un-ordered linked list

// Use std::set
CU::lnode* remove_duplicated_nodes(CU::lnode *head);

// Remove directly without help of std::set
CU::lnode* remove_duplicated_nodes_2(CU::lnode *head);

// --------------------------------------------------------------------------------------------------------------
// 2.14 Remove a certain duplicated nodes in a list
// Given an integer, remove all nodes whose values equal to that value in the list

CU::lnode* remove_certain_duplicated_nodes(CU::lnode *head, const int value);


// --------------------------------------------------------------------------------------------------------------
// 2.15 Convert a BST to an ordered double linked list
// Use in-order traversal(non-recursive)

CU::dlnode* convert_bst_to_ordered_double_list(CU::node *head);

// [TIME_STAMP] Stop at 20:12, 2017/10/07



// [TIME_STAMP] Start at 10:37, 2017/10/08
// --------------------------------------------------------------------------------------------------------------
// 2.16 Selection sort of a linked list
// Given an unordered linked list, implement the selection sort


// Remove the minimum node(value) in a list and return the head after removal
std::pair<CU::lnode*, CU::lnode*> remove_min_node(CU::lnode *head);

CU::lnode* list_selection_sort(CU::lnode *head);


// --------------------------------------------------------------------------------------------------------------
// 2.17 A weird way to remove a node in a linked list

// the head of a linked list won't be given, remove a specified node
void remove_node_weird_way(CU::lnode* n);

// --------------------------------------------------------------------------------------------------------------
// 2.18 Insert a new node(value) into a ordered loop linked list
// Given a head of a loop list(asceding order), insert a node(value) into the correct position of it

CU::lnode* insert_node_to_loop_ordered_list(CU::lnode *head, int k);

// --------------------------------------------------------------------------------------------------------------
// 2.19 Merge two ordered link list
CU::lnode* merge_two_ordered_list(CU::lnode *h1, CU::lnode *h2);

// --------------------------------------------------------------------------------------------------------------
// 2.20 Make a stagger list from a list's left part and right part
CU::lnode* stagger_list(CU::lnode *head);
// [TIME_STAMP] Stop at 12:27, 2017/10/08



}// namespace C2



#endif /* CHAPTER_2_HPP_ */















