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
int hanoi_solve_process(int number, const std::string& from, const std::string& help, const std::string& to);

void hanoi_solve(int number);


// --------------------------------------------------------------------------------------------------------------
// 1.7 Array of maximum values for a fixed window size in an array
// Original array: arr (size is n)
// window size: w

// Solution: maintain a double queue
std::vector<int> get_max_window(const std::vector<int>& ivec, int w);

// --------------------------------------------------------------------------------------------------------------
// 1.8 Get a max tree from a certain array(no repeat elements)

void pop_stack_set_map(std::stack<CU::node*>& stk, std::map<CU::node*, CU::node*>& m);

CU::node* get_max_tree(const std::vector<int>& ivec);


// --------------------------------------------------------------------------------------------------------------
// 1.9 Get maximum rectangle consists of value ones in a matrix
int max_rect_size_from_bottom_up(const std::vector<int>& ivec);

// another way to resolve
int max_rect_size_from_bottom_up_2(const std::vector<int>& ivec);

int max_rect_size(int** map, int m/*rows*/, int n/*columns*/);

// --------------------------------------------------------------------------------------------------------------
// 1.10 Total sub arrays satisfying the condition of MaxValue(arr[i..j]) - MinValue(arr[i..j]) <= ACertainValue
int get_total_array_number(const std::vector<int>& ivec, int value);
// [TIME_STAMP] Stop at 21:31, 2017/10/15


} // namespace C1




#endif /* CHAPTER_1_HPP_ */
