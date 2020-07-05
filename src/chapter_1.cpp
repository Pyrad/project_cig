/*
 * chapter_1.hpp
 *
 *  Created on: Oct. 8, 2017
 *      Author: Pyrad
 * Description: Source file of chapter 1 Queue and Stack
 *   Intention: Solutions for problems in Chapter 2[Queue and Stack] of Code Interview Guide
 */



#include "chapter_1.hpp"

namespace C1 {

namespace CU = common_utils;


// --------------------------------------------------------------------------------------------------------------
// 1.1 ~ 1.6 is implemented in HPP

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
