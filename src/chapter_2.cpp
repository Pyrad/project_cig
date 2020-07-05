/*
 * chapter_2.cpp
 *
 *  Created on: Oct. 5, 2017
 *      Author: Pyrad
 * Description: Source file of chapter 2 Linked List
 *   Intention: Solutions for problems in Chapter 2[Linked List] of Code Interview Guide
 */

#include "chapter_2.hpp"


namespace C2 {

namespace CU = common_utils;


// [TIME_STAMP] Start at 09:23, 2017/10/07
// --------------------------------------------------------------------------------------------------------------
// 2.1 Print common part of two ordered linked list

void print_two_common_part_of_two_ordered_linked_list(CU::lnode* head1, CU::lnode* head2) {
	if(!head1 || !head2) {
		return ;
	}

	CU::lnode* p1 = head1;
	CU::lnode* p2 = head2;

	while(p1 && p2) {
		if(p1->value < p2->value) {
			p1 = p1->next;
		} else if(p1->value > p2->value) {
			p2 = p2->next;
		} else {
			// In this case p1->value == p2->value
			printf("%d\n", p1->value);// or printf("%d\n", p2->value);
			p1 = p1->next;
			p2 = p2->next;
		}
	}

}


// --------------------------------------------------------------------------------------------------------------
// 2.2 Remove the K-th from the end of a linked list or a double linked list
// Two problems
// (1) Remove the K-th from the end of a linked list
// (2) Remove the K-th from the end of a double linked list
// After removed, return the head node of the list


// Solution to (1) Remove the K-th from the end of a linked list
CU::lnode* remove_reciprocal_k_node_from_end(CU::lnode* head, const int k) {
	if(!head || k <= 0) {
		return head;
	}

	CU::lnode* p1 = head;
	CU::lnode* p2 = head;

	int kth = k;
	while(kth--) {
		if(!p1 && kth != 0) {
			printf("The list length is less than %d\n", k);
			return head;
		}
		p1 = p1->next;
	}

	if(!p1) {
		// In this case kth node from the end is head itself
		// So directly return second node from the head node
		p2 = head->next;
		head->next = NULL;
		return p2;
	}

	// Now the list length is greater than k
	while(p1->next) {
		p1 = p1->next;
		p2 = p2->next;
	}

	CU::lnode* temp = p2->next;
	p2->next = p2->next->next;
	temp->next = NULL;

	return head;
}

// Solution to (2) Remove the K-th from the end of a double linked list
CU::dlnode* remove_reciprocal_k_node_from_end(CU::dlnode* head, const int k) {
	if(!head || k <= 0) {
		return head;
	}

	CU::dlnode* p1 = head;
	CU::dlnode* p2 = head;

	int kth = k;
	while(kth--) {
		if(!p1 && kth != 0) {
			printf("The list length is less than %d\n", k);
			return head;
		}
		p1 = p1->next;
	}

	if(!p1) {
		// In this case kth node from the end is head itself
		// So directly return second node from the head node
		p2 = head->next;
		p2->pre = NULL;
		head->next = NULL;
		return p2;
	}

	// Now the list length is greater than k
	while(p1->next) {
		p1 = p1->next;
		p2 = p2->next;
	}

	CU::dlnode* temp = p2->next;
	p2->next = p2->next->next;
	temp->next->pre = p2;
	temp->pre = NULL;
	temp->next = NULL;

	return head;
}

// --------------------------------------------------------------------------------------------------------------
// 2.3 Remove a node in a linked list, which is located
//     (1) in the middle
//     (2) in a/b position of whole list length

CU::lnode* remove_middle_node(CU::lnode* head) {
	// length < 2
	if(!head || !head->next) {
		return head;
	}

	// If only 2 nodes
	if(!head->next->next) {
		CU::lnode* p = head->next;
		head->next = NULL;
		return p;
	}

	CU::lnode* p1 = head->next->next;
	CU::lnode* p2 = head;
	while(p1->next && p1->next->next) {
		p1 = p1->next->next;
		p2 = p2->next;
	}

	CU::lnode* p = p2->next;
	p2->next = p2->next->next;
	p->next = NULL;

	return head;
}

CU::lnode* remove_A_Bth_node(CU::lnode* head, const int a, const int b) {
	if(!head || b == 0 || a == 0) {
		return head;
	}

	int len = 1;
	CU::lnode* p = head;
	while(p) {
		len++;
		p = p->next;
	}

	// Get minimum integar greater than a/b
	int pos = (int)ceil((double)a * len / b);

	// Use solution to 2.2
	remove_reciprocal_k_node_from_end(head, len - pos);

	return head;
}

// --------------------------------------------------------------------------------------------------------------
// 2.4 Reversion of a linked list or a double linked list
// Two problems
// (1) Reverse a linked list
// (2) Reverse a double linked list

CU::lnode* reverse_linked_list(CU::lnode* head) {
	if(!head) {
		return head;
	}

	CU::lnode* pre = NULL;
	CU::lnode* next = head;
	CU::lnode* cur = head;

	while(cur) {
		next = cur->next;
		cur->next = pre;
		pre = cur;
		cur = next;
	}

	return pre;
}

CU::dlnode* reverse_double_linked_list(CU::dlnode* head) {
	if(!head) {
		return head;
	}

	CU::dlnode* pre = NULL;
	CU::dlnode* next = head;
	CU::dlnode* cur = head;

	while(cur) {
		next = cur->next;
		cur->pre = next;
		cur->next = pre;
		pre = cur;
		cur = next;
	}

	return pre;
}

// --------------------------------------------------------------------------------------------------------------
// 2.5 Reverse part of a linked list
// Given integer 'from' and 'to', reverse list between them

CU::lnode* reverse_list_from_to(CU::lnode* head, const int from, const int to) {
	if(!head || from > to || from <= 0 || to <= 0) {
		return head;
	}

	// the node before 'from'-th node
	CU::lnode *before_from = NULL;
	// the node after 'to'-th node
	CU::lnode* after_to = NULL;
	// the 'to'-th node
	CU::lnode* to_node = NULL;
	// the 'from'-th node
	CU::lnode* from_node = NULL;

	// Get before_from
	if(from != 1) {
		before_from = head;
		int k = 1;
		while(k != from - 1) {
			before_from = before_from->next;
		}
		from_node = before_from->next;
	} else {
		// In this case, from is 1, and the head to return should be 'to'-th node after reversion
		before_from = NULL;
		from_node = head;
	}

	// Get after_to
	int i = 1;
	after_to = head;
	while(i++ != to) {
		after_to = after_to->next;
	}
	to_node = after_to;
	after_to = after_to->next;

	CU::lnode* pre = before_from;
	CU::lnode* next = before_from ? before_from->next : head;
	CU::lnode* cur = next;
	while(cur != after_to) {
		next = cur->next;
		cur->next = pre;
		pre = cur;
		cur = next;
	}

	if(!before_from && !after_to) {
		return pre;
	} else if(!before_from && after_to) {
		head->next = after_to;
		return pre;
	} else if(before_from && !after_to) {
		before_from->next = to_node;
		from_node->next = after_to;
		return head;
	} else { // before_from && after_to
		before_from->next = to_node;
		from_node->next = after_to;
		return head;
	}
}

// [TIME_STAMP] Stop at 11:22, 2017/10/07



// [TIME_STAMP] Start at 13:48, 2017/10/07
// --------------------------------------------------------------------------------------------------------------
// 2.6 Josephus Ring Problem

// Solution
// According to recursion formula, R(n) = [R(n-1) + m] % n
// We could directly resolve the problem
// See analysis in cig_notes.docx

int josephus_resolve(int n, int m) {
	if(n <= 0 || m <= 0) {
		return -1;
	}

	if(n == 1) {
		return 0;
	}

	std::vector<int> ivec;
	ivec.resize(n);
	ivec[0] = 0;

	for(int i = 1; i < n; i++) {
		ivec[i] = (ivec[i-1] + m) % n;
	}

	return ivec[n-1];
}

int josephu_problem(int n, int m) {
	// index is the index of 0,1,2,...,n-2,n-1
	// If error, -1 is returned
	int index = josephus_resolve(n, m);
	if(index < 0) {
		return -1;
	} else {
		return index + 1;
	}
}


// --------------------------------------------------------------------------------------------------------------
// 2.7 Judge if a linked list is palindrome

bool is_palindrome_list(CU::lnode* head) {
	if(!head || head->next) {
		return true;
	}

	if(!head->next->next) {
		return head->value == head->next->value;
	}

	// now list has at leat 3 nodes
	CU::lnode *p1 = head->next->next;
	CU::lnode *p2 = head;
	while(p1->next && p1->next->next) {
		p1 = p1->next->next;
		p2 = p2->next;
	}

	CU::lnode *left_last = NULL;
	CU::lnode *right_first = NULL;

	left_last = p2->next;
	right_first = p2->next->next;

	left_last->next = NULL;
	CU::lnode *new_head = CU::reverse(right_first);
	CU::lnode *p = new_head;
	p1 = head;
	while(p1 && p) {
		if(p1->value == p->value) {
			return false;
		}
	}

	return true;
}

// --------------------------------------------------------------------------------------------------------------
// 2.8 Adjust a linked list to be separated by a pivot value
//  (1) Nodes whose values are less than the pivot are at front
//  (2) Nodes whose values are equal to the pivot are in the middle
//  (3) Nodes whose values are greater than the pivot are at back

CU::lnode* adjust_list_to_three_parts(CU::lnode* head, const int pivot) {
	if(!head || head->next) {
		return head;
	}

	CU::lnode *pleft = NULL;
	CU::lnode *pmiddle = NULL;
	CU::lnode *pright = NULL;

	CU::lnode *pleft_end = NULL;
	CU::lnode *pmiddle_end = NULL;
	CU::lnode *pright_end = NULL;

	CU::lnode *p = head;
	while(p) {
		if(p->value < pivot) {
			if(pleft) {
				pleft = p;
			} else {
				pleft_end->next = p;
			}
			pleft_end = p;
		} else if(p->value > pivot) {
			if(pright) {
				pright = p;
			} else {
				pright_end->next = p;
			}
			pright_end = p;
		} else {
			if(pmiddle) {
				pmiddle = p;
			} else {
				pmiddle_end->next = p;
			}
			pmiddle_end = p;
		}
	}

	// merge three parts together
	if(pleft_end) {
		pleft_end->next = pmiddle;
	}
	if(pmiddle_end) {
		pmiddle_end->next = pright;
	}

	return pleft ? pleft : pmiddle ? pmiddle : pright;
}


// --------------------------------------------------------------------------------------------------------------
// 2.9 Copy a linked list whose every node has a random pointer to a node in the list

rnode* copy_list_with_random_pointers(rnode* head) {
	if(!head) {
		return NULL;
	}

	rnode *h = NULL;
	rnode *l = h;
	rnode *p = head;

	// Copy normally
	while(p) {
		rnode* t = new rnode(p->value);
		if(!h) {
			h = t;
		} else {
			l->next = t;
		}
		l = t;
		p = p->next;
	}

	// Merge newly copied list and the original into one
	p = head;
	l = h;
	while(p) {
		rnode *p_next = p->next;
		rnode *l_next = l->next;
		p->next = l;
		l->next = p_next;
		p = p_next;
		l = l_next;
	}

	// Copy random pointers
	p = head;
	while(p) {
		p->next = p->random->next;
		p = p->next->next;
	}

	// Tear the merged list apart
	h = NULL;
	l = NULL;
	p = head;
	while(p) {
		if(!h) {
			h = p->next;
		} else {
			l->next = p->next;
		}
		l = p->next;
	}

	return h;
}


// --------------------------------------------------------------------------------------------------------------
// 2.10 Get the sum of two linked list(add two linked list together)
// Prerequisite: Each node's value should be in range from 0 to 9

CU::lnode* add_two_list(CU::lnode *p, CU::lnode *q) {
	if(!p || !q) {
		return p ? p : q;
	}

	CU::lnode *h1 = CU::reverse(p);
	CU::lnode *h2 = CU::reverse(q);
	CU::lnode *h1backup = h1;
	CU::lnode *h2backup = h2;

	CU::lnode *last = NULL;
	CU::lnode *first = NULL;
	int carry = 0;

	while(h1 && h2) {
		int res = h1->value + h2->value + carry;
		CU::lnode *n = new CU::lnode(res % 10);
		if(!last) {
			last = n;
		} else {
			n->next = first;
		}
		first = n;
		h1 = h1->next;
		h2 = h2->next;
	}

	// after while loop, at least one of h1 and h2 should be NULL
	h1 = h1 ? h1 : h2;
	while(h1) {
		int res = h1->value + carry;
		CU::lnode *n = new CU::lnode(res % 10);
		if(!last) {
			last = n;
		} else {
			n->next = first;
		}
		first = n;
		h1 = h1->next;
	}

	CU::reverse(h1backup);
	CU::reverse(h2backup);

	return first;
}


// --------------------------------------------------------------------------------------------------------------
// 2.11 If two linked list intersect with each other

bool has_loop(CU::lnode *head) {
	if(!head || !head->next || !head->next->next) {
		return false;
	}

	CU::lnode *slow = head;
	CU::lnode *fast = head->next->next;
	while(fast->next && fast->next->next) {
		if(slow == fast) {
			return true;
		}
		fast = fast->next->next;
		slow = slow->next;
	}
	return false;
}

CU::lnode* first_node_in_loop(CU::lnode *head) {
	if(!head || !head->next || !head->next->next) {
		return NULL;
	}

	CU::lnode *slow = head;
	CU::lnode *fast = head->next->next;
	while(fast->next && fast->next->next) {
		if(slow == fast) {
			break;
		}
		fast = fast->next->next;
		slow = slow->next;
	}
	if(fast != slow) {
		// This case means list has no loop
		return NULL;
	}

	fast = head;
	while(fast != slow) {
		fast = fast->next;
		slow = slow->next;
	}

	return fast; // or return slow
}

// if NULL is returned, it means h1 and h2 have no intersection
// otherwise the first intersecting node is returned
CU::lnode* intersect_node(CU::lnode *h1, CU::lnode *h2) {
	if(!h1 || !h2) {
		return NULL;
	}

	bool h1_has_loop = has_loop(h1);
	bool h2_has_loop = has_loop(h2);
	if((h1_has_loop && !h2_has_loop) || (!h1_has_loop && h2_has_loop)) {
		// in this case h1 and h2 can't intersect
		return NULL;
	}

	// Cases left are h1 and h2 both have loop(s) or not
	// First analyze the situation where h1 and h2 are both NULL
	if(!h1_has_loop && !h2_has_loop) {
		int len1 = CU::list_length(h1);
		int len2 = CU::list_length(h2);
		int delta = std::abs(len1 - len2);
		CU::lnode *p1 = len1 > len2 ? h1 : h2;
		CU::lnode *p2 = len1 > len2 ? h2 : h1;
		while(delta > 0) {
			delta--;
			p1 = p1->next;
		}
		while(p1 && p2 && p1 != p2) {
			p1 = p1->next;
			p2 = p2->next;
		}

		return p1;
	}

	CU::lnode *h1_first_in_loop = first_node_in_loop(h1);
	CU::lnode *h2_first_in_loop = first_node_in_loop(h2);
	if(h1_first_in_loop != h2_first_in_loop) {
		return h1_first_in_loop; // or return h2_first_in_loop
	}

	// Now because h1_first_in_loop == h2_first_in_loop
	// it doesn't matter assign h1_first_in_loop or h2_first_in_loop to 'common_first_in_loop'
	CU::lnode *c = h1_first_in_loop;
	// Calculate length from 'h1' to 'c'
	CU::lnode *p = h1;
	int len = 0;
	while(p && p != c) {
		len++;
		p = p->next;
	}
	// Subtract length from 'h2' to 'c' from len
	p = h2;
	while(p && p != c) {
		len--;
		p = p->next;
	}

	// Move 'p' first by 'len' steps
	// Caution, now the 'len' is a delta value
	p = len > 0 ? h1 : h2;
	while(len > 0) {
		len--;
		p = p->next;
	}
	CU::lnode *q = len > 0 ? h2 : h1;
	assert(p);
	assert(q);
	while(p && q && p != q) {
		p = p->next;
		q = q->next;
	}
	// now p and q are the node of intersection
	return p;
}


// --------------------------------------------------------------------------------------------------------------
// 2.12 Reverse every K nodes in a linked list

CU::lnode* reverse_by_every_k_nodes(CU::lnode *head, int k) {
	if(!head || k <= 0) {
		return head;
	}

	if(k == 1) {
		return CU::reverse(head);
	}

	CU::lnode *ret_head = NULL;

	CU::lnode *left = NULL;
	CU::lnode *right = NULL;


	CU::lnode *p = head;
	while(p) {
		right = p;
		int cnt = k;
		while(p && cnt != 0) {
			cnt--;
			p = p->next;
			right = p;
		}
		if(cnt == 0) {
			// Reverse these k nodes
			CU::lnode *pre = left;
			CU::lnode *next = left ? left->next : head;
			CU::lnode *cur = next;
			while(cur != right) {
				next = cur->next;
				cur->next = pre;
				pre = cur;
				cur = next;
			}
			if(!ret_head) {
				ret_head = pre;
				head->next = right;
				left = head;
			} else {
				left->next->next = right;
				CU::lnode *temp = left->next;
				left->next = pre;
				left = temp;
			}
		} else {
			break;
		}
	}

	return ret_head;
}

// --------------------------------------------------------------------------------------------------------------
// 2.13 Remove duplicated nodes in a un-ordered linked list

// Use std::set
CU::lnode* remove_duplicated_nodes(CU::lnode *head) {
	if(!head || head->next) {
		return head;
	}

	std::set<int> s;
	s.insert(head->value);
	CU::lnode *pre = head;
	CU::lnode *p = head->next;
	while(p) {
		if(s.find(p->value) == s.end()) {
			s.insert(p->value);
			pre = p;
		} else {
			// now 'p' is a duplicated node
			pre->next = p->next;
		}
		p = p->next;
	}

	return head;
}

// Remove directly without help of std::set
CU::lnode* remove_duplicated_nodes_2(CU::lnode *head) {
	if(!head || head->next) {
		return head;
	}

	CU::lnode *p = head;
	while(p) {
		CU::lnode *start = p;
		int value = p->value;
		while(p->next) {
			if(value == p->next->value) {
				p->next = p->next->next;
			} else {
				p = p->next;
			}
		}
		p = start->next;
	}

	return head;
}

// --------------------------------------------------------------------------------------------------------------
// 2.14 Remove a certain duplicated nodes in a list
// Given an integer, remove all nodes whose values equal to that value in the list

CU::lnode* remove_certain_duplicated_nodes(CU::lnode *head, const int value) {
	if(!head) {
		return head;
	}

	CU::lnode *p = head;
	while(p->next) {
		if(value == p->next->value) {
			p->next = p->next->next;
		} else {
			p = p->next;
		}
	}

	return head->value == value ? head->next : head;
}


// --------------------------------------------------------------------------------------------------------------
// 2.15 Convert a BST to an ordered double linked list
// Use in-order traversal(non-recursive)

CU::dlnode* convert_bst_to_ordered_double_list(CU::node *head) {
	if(!head) {
		return NULL;
	}

	std::stack<CU::node*> stk;
	CU::node *p = head;
	CU::dlnode *pre = NULL;
	CU::dlnode *h = NULL;
	while(p || stk.empty()) {
		while(p) {
			stk.push(p);
			p = p->left;
		}
		p = stk.top();
		stk.pop();
		CU::dlnode *t = new CU::dlnode(p->value);
		if(pre) {
			pre->next = t;
			t->pre = pre;
			pre = t;
		} else {
			pre = t;
			h = t;
		}
		p = p->right;
	}

	return h;
}

// [TIME_STAMP] Stop at 20:12, 2017/10/07



// [TIME_STAMP] Start at 10:37, 2017/10/08
// --------------------------------------------------------------------------------------------------------------
// 2.16 Selection sort of a linked list
// Given an unordered linked list, implement the selection sort


// Remove the minimum node(value) in a list and return the head after removal
std::pair<CU::lnode*, CU::lnode*> remove_min_node(CU::lnode *head) {

	typedef std::pair<CU::lnode*, CU::lnode*> nodepair;
	if(!head) {
		return nodepair(NULL, NULL);
	}

	if(!head->next) {
		return nodepair(NULL, head);
	}

	// int mvalue = head->value;
	CU::lnode *pre = NULL;
	CU::lnode *p = head;
	CU::lnode *min_pre = NULL;
	CU::lnode *min = head;

	while(p) {
		if(p->value < min->value) {
			min = p;
			min_pre = pre;
		}
		pre = p;
		p = p->next;
	}

	if(!min_pre) {
		// In this case, min is the head
		p = min->next;
		min->next = NULL;
		return nodepair(p/*new head*/, min/*removed node*/);
	} else {
		p = min->next;
		min->next = NULL;
		min_pre = p;
		return nodepair(head, min);
	}
}

CU::lnode* list_selection_sort(CU::lnode *head) {
	if(!head || !head->next) {
		return head;
	}

	CU::lnode *h = NULL;
	CU::lnode *last = NULL;
	CU::lnode *p = head;

	typedef std::pair<CU::lnode*, CU::lnode*> nodepair;
	while(p) {
		nodepair t(remove_min_node(head));
		p = t.first;
		h = h ? h : p;
		if(last) {
			last->next = t.second;
			last = last->next;
		} else {
			last = t.second;
		}
	}

	return h;
}


// --------------------------------------------------------------------------------------------------------------
// 2.17 A weird way to remove a node in a linked list

// the head of a linked list won't be given, remove a specified node
void remove_node_weird_way(CU::lnode* n) {
	if(!n) {
		return ;
	}

	if(!n->next) {
		// Defect:
		// if n is the last node, it can't be removed
		return ;
	}

	CU::lnode *p = n->next;

	n->next = n->next->next;
	p->next = NULL;

	return ;
}

// --------------------------------------------------------------------------------------------------------------
// 2.18 Insert a new node(value) into a ordered loop linked list
// Given a head of a loop list(asceding order), insert a node(value) into the correct position of it

CU::lnode* insert_node_to_loop_ordered_list(CU::lnode *head, int k) {
	if(!head) {
		return head;
	}

	if(head->next == head) {
		head->next = new CU::lnode(k);
		head->next->next = head;
		return head;
	}

	if(k < head->value) {
		CU::lnode *t = head->next;
		head->next = new CU::lnode(k);
		head->next->next = t;
		return head;
	}

	CU::lnode *p = head;
	while(p->next != head){
		if(p->next->value > k) {
			CU::lnode *t = p->next;
			p->next = new CU::lnode(k);
			p->next->next = t;
			return head;
		}
		p = p->next;
	}

	// Now k is the biggest value of the whole list
	p->next = new CU::lnode(k);
	p->next->next = head;
	return head;
}

// --------------------------------------------------------------------------------------------------------------
// 2.19 Merge two ordered link list
CU::lnode* merge_two_ordered_list(CU::lnode *h1, CU::lnode *h2) {
	if(!h1 || !h2) {
		return h1 ? h1 : h2;
	}

	// now h1 and h2 both have node(s)
	CU::lnode *h = NULL; // the head of the list after merge
	CU::lnode *last = NULL; // last node in the merged list
	while(h1 && h2) {
		if(h1 < h2) {
			h = h ? h : h1;
			if(last) {
				last->next = h1;
				last = last->next;
			} else {
				last = h1;
			}
			h1 = h1->next;
		} else {
			h = h ? h : h2;
			if(last) {
				last->next = h2;
				last = last->next;
			} else {
				last = h2;
			}
			h2 = h2->next;
		}
	}

	last->next = h1 ? h1 : h2;
	return h;
}

// --------------------------------------------------------------------------------------------------------------
// 2.20 Make a stagger list from a list's left part and right part
CU::lnode* stagger_list(CU::lnode *head) {
	if(!head || !head->next || !head->next->next) {
		return head;
	}

	CU::lnode *p1 = head;
	CU::lnode *p2 = head->next->next;
	while(p2->next && p2->next->next) {
		p1 = p1->next;
		p2 = p2->next->next;
	}

	CU::lnode *right = NULL;// head of the right half part
	CU::lnode *left = head; // head of the left half part
	CU::lnode *h = NULL; // new head to return
	CU::lnode *last = NULL;

	if(!p2->next) {
		// In this case the length of the list is odd number
		right = p1->next;
		p1->next = NULL;
	} else {
		assert(p2->next->next == NULL);
		// In this case the length of the list is even number
		right = p1->next->next;
		p1->next->next = NULL;
	}

	while(left && right) {
		h = h ? h : left;
		last = last ? last : h;
		last->next = left;
		last->next->next = right;
		last = right;
		left = left->next;
		right = right->next;
	}

	last->next = left ? left : right;
	return h;
}
// [TIME_STAMP] Stop at 12:27, 2017/10/08



}// namespace C2
