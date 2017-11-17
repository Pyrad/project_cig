/*
 * chapter_1.hpp
 *
 *  Created on: Oct. 8, 2017
 *      Author: Pyrad
 * Description: Header file of chapter 1 Queue and Stack
 *   Intention: Solutions for problems in Chapter 2[Queue and Stack] of Code Interview Guide
 */

#ifndef CHAPTER_1_HPP_
#define CHAPTER_1_HPP_

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

namespace C1 {

namespace CU = common_utils;


// [TIME_STAMP] Start at 09:51, 2017/10/15
// --------------------------------------------------------------------------------------------------------------
// 1.1 Design a stack which can return min element
//  Requirement,
//  (1) The time complexity of pop, push, get_min is O(1)
//  (2) Can use the stack utility

// Method 1
template<typename T>
class customized_stack {
public:
	customized_stack<T>() {}
	~customized_stack<T>() {}

public:
	void pop();
	void push(const T& v);
	const T& top() const;
	const T& get_min() const;
	bool empty() const;

private:
	std::stack<T> m_stack;
	std::stack<T> m_min_stack;
};

template<typename T>
bool customized_stack<T>::
empty() const {
	return m_stack.empty();
}

template<typename T>
void customized_stack<T>::
pop() {
	m_stack.pop();
	m_min_stack.pop();
}

template<typename T>
const T& customized_stack<T>::
top() const {
	return m_stack.top();
}

template<typename T>
void customized_stack<T>::
push(const T& v) {
	m_stack.push(v);
	if(m_min_stack.empty()) {
		m_min_stack.push(v);
	} else {
		const T& min = m_min_stack.top();
		if(v < min) {
			m_min_stack.push(v);
		} else {
			m_min_stack.push(min);
		}
	}
}

template<typename T>
const T& customized_stack<T>::
get_min() const {
	return m_min_stack.top();
}

// Method 2
template<typename T>
class custom_min_stack {
public:
	custom_min_stack<T>() {}
	~custom_min_stack<T>() {}

public:
	void pop();
	void push(const T& v);
	const T& top() const;
	const T& get_min() const;
	bool empty() const;

private:
	std::stack<T> m_stack;
	std::stack<T> m_min_stack;
};

template<typename T>
bool custom_min_stack<T>::
empty() const {
	return m_stack.empty();
}

template<typename T>
void custom_min_stack<T>::
pop() {
	const T& value = m_stack.top();
	if(value <= m_min_stack.top()) {
		m_min_stack.pop();
	}
	m_stack.pop();
}

template<typename T>
const T& custom_min_stack<T>::
top() const {
	return m_stack.top();
}

template<typename T>
void custom_min_stack<T>::
push(const T& v) {
	m_stack.push(v);
	if(m_min_stack.empty()) {
		m_min_stack.push(v);
	} else {
		const T& min = m_min_stack.top();
		if(v <= min) {
			m_min_stack.push(v);
		}
	}
}

template<typename T>
const T& custom_min_stack<T>::
get_min() const {
	return m_min_stack.top();
}

// --------------------------------------------------------------------------------------------------------------
// 1.2 Construct a queue by two stacks

template<typename T>
class customized_queue {
public:
	customized_queue() {}
	~customized_queue() {}

public:
	void push(const T& v);
	void pop();
	const T& front() const;
	const T& back() const;
	bool empty() const;

private:
	std::stack<T> m_stk1;
	std::stack<T> m_stk2;
};

template<typename T>
void customized_queue<T>::
push(const T& v) {
	m_stk1.push(v);
}

template<typename T>
void customized_queue<T>::
pop() {
	if(m_stk2.empty()) {
		while(!m_stk1.empty()) {
			m_stk2.push(m_stk1.top());
			m_stk1.pop();
		}
	}
	m_stk2.pop();
}

template<typename T>
bool customized_queue<T>::
empty() const {
	return m_stk1.empty() && m_stk2.empty();
}

template<typename T>
const T& customized_queue<T>::
front() const {
	if(m_stk2.empty()) {
		while(!m_stk1.empty()) {
			m_stk2.push(m_stk1.top());
			m_stk1.pop();
		}
	}
	return m_stk2.top();
}

template<typename T>
const T& customized_queue<T>::
back() const {
	if(m_stk1.empty()) {
		while(!m_stk2.empty()) {
			m_stk1.push(m_stk2.top());
			m_stk2.pop();
		}
	}
	return m_stk1.top();
}

// --------------------------------------------------------------------------------------------------------------
// 1.3 Reverse a stack just by using recursive function
// Analysis,
// Step 1, get and remove the last element of a stack(using recursive method)
// Step 2,

template <typename T>
T get_and_remove_last_element(std::stack<T>& stk) {
	T res = stk.top();
	stk.pop();
	if(stk.empty()) {
		return res;
	} else {
		T last = get_and_remove_last_element(stk);
		stk.push(res);
		return last;
	}
}

template <typename T>
void reverse_stack(std::stack<T>& stk) {
	if(stk.empty()) {
		return ;
	}

	T last = get_and_remove_last_element(stk);
	reverse_stack(stk);
	stk.push(last);
}

// --------------------------------------------------------------------------------------------------------------
// 1.4 Cat & Dog Queues

class pet {
public:
	pet() : m_type("") {}
	pet(const std::string& s) : m_type(s) {}
	pet(const pet& p) { m_type = p.m_type; }
	virtual ~pet() {}

public:
	const std::string& get_type() const { return m_type; }

private:
	std::string m_type;
};

class dog : public pet {
public:
	dog() : pet("dog") {}
	dog(const dog& d) : pet(d) {}
};

class cat : public pet {
public:
	cat() : pet("cat") {}
	cat(const cat& c) : pet(c) {}
};

// -- solutions start from here --
class customized_dog : public dog {
public:
	customized_dog() : dog(), m_time_stamp(0) {}
	customized_dog(int t) : dog(), m_time_stamp(t) {}
	customized_dog(const dog& d, int t) : dog(d), m_time_stamp(t) {}
	~customized_dog() { m_time_stamp = 0; }

public:
	const int get_time_stamp() const { return m_time_stamp; }

private:
	int m_time_stamp;
};

class customized_cat : public cat {
public:
	customized_cat() : cat(), m_time_stamp(0) {}
	customized_cat(int t) : cat(), m_time_stamp(t) {}
	customized_cat(const cat& c, int t) : cat(c), m_time_stamp(t) {}
	~customized_cat() { m_time_stamp = 0; }

public:
	const int get_time_stamp() const { return m_time_stamp; }

private:
	int m_time_stamp;
};

class cat_dog_queue {
public:
	cat_dog_queue() : m_counter(0) {}
	~cat_dog_queue() { m_counter = 0; }

public:
	void push(const dog& d);
	void push(const cat& c);
	void pop_all_dogs();
	void pop_all_cats();
	void pop_all();
	bool is_empty() const;
	bool is_dog_empty() const;
	bool is_cat_empty() const;

private:
	int m_counter;
	std::queue<customized_dog> m_dogs;
	std::queue<customized_cat> m_cats;
};

void cat_dog_queue::
push(const dog& d) {
	customized_dog t(d, ++m_counter);
	m_dogs.push(t);
}

void cat_dog_queue::
push(const cat& c) {
	customized_cat t(c, ++m_counter);
	m_cats.push(t);
}

void cat_dog_queue::
pop_all_dogs() {
	while(!m_dogs.empty()) {
		m_dogs.pop();
	}
}

void cat_dog_queue::
pop_all_cats() {
	while(!m_cats.empty()) {
		m_cats.pop();
	}
}

void cat_dog_queue::
pop_all() {
	while(!m_dogs.empty() && !m_cats.empty()) {
		if(m_dogs.front().get_time_stamp() < m_cats.front().get_time_stamp()) {
			m_dogs.pop();
		} else {
			m_cats.pop();
		}
	}
	if(!m_dogs.empty()) {
		pop_all_dogs();
	}
	if(!m_cats.empty()) {
		pop_all_cats();
	}
}

bool cat_dog_queue::
is_empty() const {
	return m_dogs.empty() && m_cats.empty();
}

bool cat_dog_queue::
is_dog_empty() const {
	return m_dogs.empty();
}

bool cat_dog_queue::
is_cat_empty() const {
	return m_cats.empty();
}


// --------------------------------------------------------------------------------------------------------------
// 1.5 Sort a stack by using another stack

template <typename T>
void stack_sort(std::stack<T>& stk) {
	if(stk.empty()) {
		return ;
	}

	std::stack<T> tmp;
	while(!stk.empty()) {
		T value = stk.top();
		stk.pop();
		if(tmp.empty() || tmp.top() >= value) {
			tmp.push(value);
		} else {
			// now tmp is not empty and tmp.top() is greater than value
			while(!tmp.empty()) {
				if(tmp.top() >= value) {
					tmp.push(value);
					break;
				}
				stk.push(tmp.top());
				tmp.pop();
			}
		}
	}

	while(!tmp.empty()) {
		stk.push(tmp.top());
		tmp.pop();
	}
}

// --------------------------------------------------------------------------------------------------------------
// 1.6 Hanoi Tower(condition stricted)
int hanoi_solve_process(int number, const std::string& from, const std::string& help, const std::string& to) {
	if(number == 1) {
		if(from == "middle" || to == "middle") {
			printf("Move 1 from %s to %s\n", from.c_str(), to.c_str());
			return 1;
		} else {
			printf("Move 1 from %s to middle\n", from.c_str());
			printf("Move 1 from middle to %s\n", to.c_str());
			return 2;
		}
	}

	if(from == "middle" || to == "middle") {
		int steps_1 = hanoi_solve_process(number - 1, from, to, help);
		printf("Move %d from %s to %s\n", number, from.c_str(), help.c_str());
		int steps_2 = 1;
		int steps_3 = hanoi_solve_process(number - 1, help, to, from);
		return steps_1 + steps_2 + steps_3;
	} else {
		int steps_1 = hanoi_solve_process(number - 1, from, help, to);
		printf("Move %d from %s to %s\n", number, from.c_str(), "middle");
		int steps_2 = 1;
		int steps_3 = hanoi_solve_process(number - 1, to, help, from);
		printf("Move %d from %s to %s\n", number, "middle", to.c_str());
		int steps_4 = 1;
		int steps_5 = hanoi_solve_process(number - 1, from, help, to);
		return steps_1 + steps_2 + steps_3 + steps_4 + steps_5;
	}

}

void hanoi_solve(int number) {
	if(number < 1) {
		return ;
	}

	hanoi_solve_process(number, "left", "middle", "right");
}


// --------------------------------------------------------------------------------------------------------------
// 1.7 Array of maximum values for a fixed window size in an array
// Original array: arr (size is n)
// window size: w

// Solution: maintain a double queue
std::vector<int> get_max_window(const std::vector<int>& ivec, int w) {
	std::vector<int> res;
	if(ivec.empty() || w < 1 || ivec.size() < (std::size_t)w) {
		return res;
	}

	std::deque<int> maxdeq;
	const int vsize = ivec.size();
	res.resize(vsize - w + 1);
	int index = 0;
	for(int i = 0; i < vsize; i++) {
		while(!maxdeq.empty() && ivec[maxdeq.back()] <= ivec[i]) {
			maxdeq.pop_back();
		}
		maxdeq.push_back(i);
		if(maxdeq.front() == i - w) {
			maxdeq.pop_front();
		}
		if(i >= w - 1) {
			res[index++] = ivec[maxdeq.front()];
		}
	}

	return res;
}

// --------------------------------------------------------------------------------------------------------------
// 1.8 Get a max tree from a certain array(no repeat elements)

void pop_stack_set_map(std::stack<CU::node*>& stk, std::map<CU::node*, CU::node*>& m) {
	CU::node* n = stk.top();
	stk.pop();
	if(stk.empty()) {
		m.insert(std::pair<CU::node*, CU::node*>(n, NULL));
	} else {
		m.insert(std::pair<CU::node*, CU::node*>(n, stk.top()));
	}
}

CU::node* get_max_tree(const std::vector<int>& ivec) {
	if(ivec.empty()) {
		return NULL;
	}

	std::vector<CU::node*> nvec;
	for(std::size_t i = 0; i < ivec.size(); i++) {
		nvec.push_back(new CU::node(ivec[i]));
	}

	std::stack<CU::node*> stk;

	// Get the map for first-greater-than-node at left
	std::map<CU::node*, CU::node*> left_big_map;
	for(std::size_t i = 0; i < nvec.size(); i++) {
		CU::node *cur = nvec[i];
		while(!stk.empty() && cur->value > stk.top()->value) {
			pop_stack_set_map(stk, left_big_map);
		}
		stk.push(cur);
	}
	while(!stk.empty()) {
		pop_stack_set_map(stk, left_big_map);
	}
	// Get the map for first-greater-than-node at right
	std::map<CU::node*, CU::node*> right_big_map;
	for(int i = nvec.size() - 1; i > -1; i--) {
		CU::node *cur = nvec[i];
		while(!stk.empty() && cur->value > stk.top()->value) {
			pop_stack_set_map(stk, right_big_map);
		}
		stk.push(cur);
	}
	while(!stk.empty()) {
		pop_stack_set_map(stk, right_big_map);
	}

	CU::node *head = NULL;
	for(std::size_t i = 0; i < nvec.size(); i++) {
		CU::node *cur = nvec[i];
		assert(left_big_map.find(cur) != left_big_map.end());
		CU::node *left_first_big = left_big_map.find(cur)->second;
		CU::node *right_first_big = right_big_map.find(cur)->second;
		if(!left_first_big && !right_first_big) {
			head = cur;
		} else if(left_first_big) {
			if(!left_first_big->left) {
				left_first_big->left = cur;
			} else {
				left_first_big->right = cur;
			}
		} else if(right_first_big) {
			if(!right_first_big->left) {
				right_first_big->left = cur;
			} else {
				right_first_big->right = cur;
			}
		} else {
			CU::node *parent = left_first_big->value < right_first_big->value ? left_first_big : right_first_big;
			if(!parent->left) {
				parent->left = cur;
			} else {
				parent->left = cur;
			}
		}
	}

	return head;
}



// --------------------------------------------------------------------------------------------------------------
// 1.9 Get maximum rectangle consists of value ones in a matrix
int max_rect_size_from_bottom_up(const std::vector<int>& ivec) {
	int res = 0;
	const int vsize = ivec.size();
	std::stack<int> stk;
	for(int i = 0; i < vsize; i++) {
		if(stk.empty() || ivec[stk.top()] < ivec[i]) {
			stk.push(i);
		} else {
			while(!stk.empty() && ivec[stk.top()] >= ivec[i]) {
				int j = stk.top();
				stk.pop();
				int k = stk.top();
				res = std::max(res, (i - k + 1) * ivec[j]);
			}
			stk.push(i);
		}
	}

	while(!stk.empty()) {
		int j = stk.top();
		stk.pop();
		int k = stk.empty() ? -1 : stk.top();
		res = std::max(res, (vsize - k + 1) * ivec[j]);
	}

	return res;
}

// another way to resolve
int max_rect_size_from_bottom_up_2(const std::vector<int>& ivec) {
	int res = 0;

	// Add a smallest one to the end of 'ivec'
	std::vector<int> local_vec(ivec);
	local_vec.push_back(-1);

	const int vsize = local_vec.size();
	std::stack<int> stk;
	for(int i = 0; i < vsize; i++) {
		if(stk.empty() || ivec[stk.top()] < ivec[i]) {
			stk.push(i);
		} else {
			while(!stk.empty() && ivec[stk.top()] >= ivec[i]) {
				int j = stk.top();
				stk.pop();
				int k = stk.top();
				res = std::max(res, (i - k + 1) * ivec[j]);
			}
			stk.push(i);
		}
	}

	return res;
}

int max_rect_size(int** map, int m/*rows*/, int n/*columns*/) {
	// map is a matrix of size m*n
	// map has only 2 kinds of elements, 0 and 1
	if(!map || m <= 0 || n <= 0) {
		return 0;
	}

	std::vector<int> vec;
	vec.resize(n, 0);
	int res = 0;
	for(int i = 0; i < m; i++) {
		for(int j = 0; j < n; j++) {
			vec[j] = map[i][j] == 0 ? 0 : vec[j] + 1;
			res = std::max(res, max_rect_size_from_bottom_up(vec));
		}
	}

	return res;
}

// --------------------------------------------------------------------------------------------------------------
// 1.10 Total sub arrays satisfying the condition of MaxValue(arr[i..j]) - MinValue(arr[i..j]) <= ACertainValue

int get_total_array_number(const std::vector<int>& ivec, int value) {
	if(ivec.empty()) {
		return 0;
	}

	int res = 0;

	std::deque<int> max_deq;
	std::deque<int> min_deq;

	const int vsize = ivec.size();
	int j = 0;
	for(int i = 0; i < vsize; i++) {
		while(j < vsize) {
			while(!min_deq.empty() && ivec[min_deq.back()] >= ivec[j]) {
				min_deq.pop_back();
			}
			min_deq.push_back(j);
			while(!max_deq.empty() && ivec[max_deq.back()] <= ivec[j]) {
				max_deq.pop_back();
			}
			max_deq.push_back(j);
			if(ivec[max_deq.front()] - ivec[min_deq.front()] > value) {
				break;
			}
			j++;
		}
		if(min_deq.front() == i) {
			min_deq.pop_front();
		}
		if(max_deq.front() == i) {
			max_deq.pop_front();
		}
		res += j - i;
	}

	return res;
}
// [TIME_STAMP] Stop at 21:31, 2017/10/15


} // namespace C1




#endif /* CHAPTER_1_HPP_ */
