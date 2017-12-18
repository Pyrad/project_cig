/*
 * chapter_8.hpp
 *
 *  Created on: Oct. 3, 2017
 *      Author: Pyrad
 * Description: Header file of chapter 8 Array and Matrix Problems
 *   Intention: Solutions for problems in Chapter 8[Array and Matrix Problems] of Code Interview Guide
 */

#ifndef CHAPTER_8_HPP_
#define CHAPTER_8_HPP_

#include <stdio.h>
#include <limits.h>
#include <memory.h>

#include <algorithm>
#include <assert.h>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <utility>



#include "common_utils.hpp"


namespace C8 {

// [TIME_STAMP] Start at 14:15 2017/12/09

// --------------------------------------------------------------------------------------------------------------
// 8.1 Print a matrix in order of clockwise

void print_matrix_clockwise(int **mtx, const int m, const int n) {
	if(!mtx || m <= 0 || n <= 0) {
		return ;
	}

	int x1 = 0;
	int y1 = 0;
	int x2 = m - 1;
	int y2 = n - 1;
	while(x1 <= x2 && y1 <= y2) {
		if(x1 == x2) {
			for(int j = y1; j <= y2; j++) {
				printf("%d ", mtx[x1][j]);
			}
		} else if(y1 == y2) {
			for(int i = x1; i <= x2; i++) {
				printf("%d ", mtx[i][y1]);
			}
		} else {
			// top side
			for(int j = y1; j < y2; j++) {
				printf("%d ", mtx[x1][j]);
			}
			// right side
			for(int i = x1; i < x2; i++) {
				printf("%d ", mtx[i][y2]);
			}
			// bottom side
			for(int j = y2; j > y1; j--) {
				printf("%d ", mtx[x2][j]);
			}
			// left side
			for(int i = x2; i > x1; i--) {
				printf("%d ", mtx[i][y1]);
			}
		}
		x1++, y1++;
		x2--, y2--;
	}
}


// --------------------------------------------------------------------------------------------------------------
// 8.2 Rotate a square matrix for 90 degrees

// Rotate by clockwise order
void rotate_square_matrix_90_degree(int **mtx, const int sz) {
	if(!mtx || sz <= 0) {
		return ;
	}

	int m = 0;
	int n = sz - 1;
	while(m < n) {
		for(int i = 0; i < n; i++) {
			int tmp = mtx[m][m + i];
			mtx[m][m + i] = mtx[n - i][m];
			mtx[n - i][m] = mtx[n][n - i];
			mtx[n][n - i] = mtx[m + i][n];
			mtx[m + i][n] = tmp;
		}
		m++;
		n--;
	}
}

// --------------------------------------------------------------------------------------------------------------
// 8.3 Print a matrix in zigzag order


void print_matrix_in_zigzag_order(int **mtx, const int m, const int n) {
	if(!mtx || m <= 0 || n <= 0) {
		return ;
	}

	int tR = 0;
	int tC = 0;
	int dR = 0;
	int dC = 0;
	bool updown = true;

	while(tR <= m - 1 && dC <= n - 1) {
		if(updown) {
			int i = dR;
			int j = dC;
			while(i >= tR) {
				printf("%d ", mtx[i][j]);
				i--;
				j++;
			}
		} else {
			int i = tR;
			int j = tC;
			while(i <= dR) {
				printf("%d ", mtx[i][j]);
			}
			i++;
			j--;
		}

		if(tC == n - 1) {
			tR++;
		} else {
			tC++;
		}

		if(dR == m - 1) {
			dC++;
		} else {
			dR++;
		}

		updown = !updown;
	}
}

// --------------------------------------------------------------------------------------------------------------
// 8.4 Find K minimum number in an unordered array
// Can use 2 different kinds of algorithms
// (1) Heap algorithm
// (2) BFPRT algorithm

// (1) Heap algorithm
void filter_up(std::vector<int>& vec, int pos);
void filter_down(std::vector<int>& vec, const int pos, const int slimit);

std::vector<int> find_k_min_in_unordered_array(const std::vector<int>& ivec, const int k) {
	std::vector<int> m;

	if(ivec.empty() || k <= 0) {
		return m;
	}

	// Big-root heap
	const int len = ivec.size();
	for(int i = 0; i < len; i++) {
		if((int)m.size() != k) {
			m.push_back(ivec[i]);
			filter_up(m, i);
		} else {
			if(ivec[i] < m[0]) { // here, m[0] is m.front()
				m[0] = ivec[i];
				filter_down(m, 0, k - 1);
			}
		}
	}

	return m;
}

void filter_up(std::vector<int>& vec, int pos) {
	int father = (pos - 1) / 2;
	while(father > 0) {
		if(vec[pos] > vec[father]) {
			int tmp = vec[pos];
			vec[pos] = vec[father];
			vec[father] = tmp;
		} else {
			break;
		}
		pos = father;
		father = (pos - 1) / 2;
	}
}

void filter_down(std::vector<int>& vec, const int pos, const int slimit) {
	int i = pos;
	int left = i * 2 + 1;
	int right = i * 2 + 2;
	while(left < slimit) {
		int max = i;
		if(vec[left] > vec[i]) {
			max = left;
		}
		if(right < slimit && vec[right] > vec[max]) {
			max = right;
		}
		if(max == i) {
			break;
		}
		int tmp = vec[max];
		vec[max] = vec[i];
		vec[i] = tmp;
		i = max;
		left = 2 * i + 1;
		right = 2 * i + 2;
	}
}

// (2) BFPRT algorithm
// Skip since it is to sophisticated...

// --------------------------------------------------------------------------------------------------------------
// 8.5 The size of the shortest sub-array which needs to be sorted

const int shortest_subarray_need_to_sort(const std::vector<int>& ivec) {
	if(ivec.empty() || ivec.size() == 1) {
		return 0;
	}

	const int len = ivec.size();

	int index1 = -1;
	int min = ivec[len - 1];
	for(int i = len - 2; i > -1; i--) {
		index1 = ivec[i] > min ? i : index1;
		min = std::min(min, ivec[i]);
	}
	if(index1 == -1) {
		return 0;
	}

	int index2 = -1;
	int max = ivec[0];
	for(int i = 1; i < len; i++) {
		index1 = ivec[i] < max ? i : index1;
		max = std::max(max, ivec[i]);
	}
	if(index2 == -1) {
		return 0;
	}

	return index2 - index1 + 1;
}

// [TIME_STAMP] Stop 16:52, 2017/12/09






// [TIME_STAMP] Start at 20:07 2017/12/09

// --------------------------------------------------------------------------------------------------------------
// 8.6 Find a number which appears more than N/K times in an array(length is N)
// (1) Find a number which appears more than N/2 times in an array(length is N)
// (2) Find a number which appears more than N/K times in an array(length is N)

// (1) Find a number which appears more than N/2 times in an array(length is N)
// Space complexity - O(1), time complexity - O(N)

int more_than_half_size_integer(const std::vector<int>& ivec) {
	if(ivec.empty()) {
		printf("Array is empty\n");
		return 0;
	}

	int times = 0;
	int candidate = 0;
	const int len = ivec.size();
	for(int i = 0; i < len; i++) {
		if(times == 0) {
			candidate = ivec[i];
			times = 1;
		} else if(ivec[i] != candidate) {
			times++;
		}  else {
			times--;
		}
	}

	// Count if 'candidate' realy has more than 'len/2'
	times = 0;
	for(int i = 0; i < len; i++) {
		if(ivec[i] == candidate) {
			times++;
		}
	}

	if(times > len/2) {
		return candidate;
	}

	printf("There's no number has more than %d\n", len / 2);
	return 0;
}

// (2) Find a number which appears more than N/K times in an array(length is N)
// Space complexity - O(K), time complexity - O(N*K)

void minus_one_and_remove_if_zero(std::map<int, int>& m) {
	if(m.empty()) {
		return ;
	}

	std::map<int, int>::iterator itr = m.begin();
	while(itr != m.end()) {
		std::map<int, int>::iterator i = itr;
		itr++;
		if(i->second == 1) {
			m.erase(i);
		} else {
			i->second--;
		}
	}
}

void more_than_N_of_K_size_integers(const std::vector<int>& ivec, const int k) {
	if(k < 2) {
		printf("Specified number K=%d is invalid\n", k);
		return ;
	}

	std::map<int, int> m;
	const int len = ivec.size();
	for(int i = 0; i < len; i++) {
		std::map<int, int>::iterator itr = m.find(ivec[i]);
		if(itr != m.end()) {
			itr->second++;
		} else {
			if((int)m.size() < k - 1) {
				m[ivec[i]] = 1;
			} else {
				minus_one_and_remove_if_zero(m);
			}
		}
	}

	std::map<int, int> nkcount;
	for(int i = 0; i < len; i++) {
		const int num = ivec[i];
		if(m.find(num) != m.end()) {
			if(nkcount.find(num) == nkcount.end()) {
				nkcount[num] = 1;
			} else {
				nkcount[num]++;
			}
		}
	}

	std::list<std::pair<int, int> > l;
	for(std::map<int, int>::iterator itr = nkcount.begin(); itr != nkcount.end(); itr++) {
		if(itr->second > len / k) {
			l.push_back(std::make_pair(itr->first, itr->second));
			printf("Element %d, times=%d\n", itr->first, itr->second);
		}
	}

}

// --------------------------------------------------------------------------------------------------------------
// 8.7 Find a number in a matrix whose rows and columns have been all sorted already

// The rows are all in ascending order
// The columns are all in ascending order

bool find_number_in_matrix_rows_columns_sorted(int **mtx, const int m, const int n, const int k) {
	if(!mtx || m <= 0 || n <= 0) {
		return false;
	}

	for(int j = n - 1; j > -1; j--) {
		if(mtx[0][j] == k) {
			return true;
		}
		if(mtx[0][j] < k) {
			for(int i = 0; i < m; i++) {
				if(mtx[i][j] == k) {
					return true;
				}
			}
			return false;
		}
	}

	return false;
}

// --------------------------------------------------------------------------------------------------------------
// 8.8 Find the max size of consolidated sub array in an unordered array

// Define a consolidated array
// Array [5, 3, 4, 6, 2] after sorted is [2, 3, 4, 5, 6]
// Each adjacent two elements are consecutive
// then it is called 'consolidated'

// Solution KEY
// if MAX(array[0..N-1]) - MIN(array[0..N-1]) + 1= LENGTH(array[0..N-1])
// then it is the so-called consolidated array

int max_size_consolidate_subarray(const std::vector<int>& ivec) {
	int res = INT_MIN;
	if(ivec.empty()) {
		return res;
	}

	const int len = ivec.size();
	std::set<int> duplicated_elements;

	for(int i = 0; i < len; i++) {
		int max = INT_MIN;
		int min = INT_MAX;
		for(int j = i; j < len; j++) {
			if(duplicated_elements.find(ivec[i]) != duplicated_elements.end()) {
				break;
			}
			duplicated_elements.insert(ivec[i]);
			max = std::max(max, ivec[i]);
			min = std::min(min, ivec[i]);

			// Judgement if consolidated array
			if(max - min == j - i) {
				res = std::max(res, j - i + 1);
			}
		}
		duplicated_elements.clear();
	}

	return res;
}

// --------------------------------------------------------------------------------------------------------------
// 8.9 Print all two-tuples or triad of a certain value specified in a sorted array
// (1) Print all two-tuples of a certain value specified in a sorted array
// (2) Print all triad of a certain value specified in a sorted array
// Notice, don't print duplicated ones

// (1) Print all two-tuples of a certain value specified in a sorted array
void two_tuples_certain_value_in_sorted_array(const std::vector<int>& ivec, const int k) {
	if(ivec.size() < 2) {
		return ;
	}

	const int len = ivec.size();
	int left = 0;
	int right = len - 1;

	while(left < right) {
		if(ivec[left] + ivec[right] > k) {
			right--;
		} else if(ivec[left] + ivec[right] < k) {
			left++;
		} else {
			if(left == 0 || ivec[left - 1] != ivec[left]) { // In case of duplicated two-tuples
				printf("(%d + %d) = %d\n", ivec[left], ivec[right], k);
				left++;
				right--;
			}
		}
	}
}

// (2) Print all triad of a certain value specified in a sorted array
void triad_certain_value_in_sorted_array(const std::vector<int>& ivec, const int k) {
	if(ivec.size() < 3) {
		return ;
	}

	const int len = ivec.size();

	for(int t = 0; t < len; t++) {
		if(t == 0 || ivec[t - 1] != ivec[t]) {
			int left = t + 1;
			int right = len - 1;
			while(left < right) {
				if(ivec[left] + ivec[right] > k - ivec[t]) {
					right--;
				} else if(ivec[left] + ivec[right] < k - ivec[t]) {
					left++;
				} else {
					if(left + 1 == right || ivec[left - 1] != ivec[left]) { // In case of duplicated two-tuples
						printf("(%d + %d + %d) = %d\n", ivec[t], ivec[left], ivec[right], k);
						left++;
						right++;
					}
				}
			}
		}
	}
}

// [TIME_STAMP] Stop 22:29, 2017/12/09



// [TIME_STAMP] Start at 11:39, 2017/12/10

// --------------------------------------------------------------------------------------------------------------
// 8.10 The max size of a sub-array of which the sum is a certain value specified
// The orginal array is unordered, and all elements are positive integers

int max_subarray_of_certain_sum(const std::vector<int>& arr, const int k) {
	int res = 0;

	if(arr.empty() || k <= 0) {
		return res;
	}

	int left = 0;
	int right = 0;
	int sum = arr[0];
	const int len = arr.size();

	while(right < len) {
		if(sum < k) {
			right++;
			if(right == len) {
				break;
			}
			sum += arr[right];
		} else if(sum > k) {
			sum -= arr[left];
			left++;
		} else { // sum == k
			res = std::max(res, right - left + 1);
			sum -= arr[left];
			left++;
		}
	}

	return res;
}
// [TIME_STAMP] Stop 12:04, 2017/12/10


// [TIME_STAMP] Start at 20:54 2017/10/03
// --------------------------------------------------------------------------------------------------------------
// 8.11 The longest sub-array in an unordered array of a certain sum
// Notice, the elements in the original array can be negative, positive or zero.
// Solution,
// Assume S(i) = Sum[0...i], so if K=S(i)-S(j), then Sum[j+1,...,i] = K, that's what we want

int longest_subarray_of_a_certain_sum(const std::vector<int>& ivec, const int k) {
	if(ivec.empty() || k <= 0) {
		return 0;
	}
	int max_len = 0;
	int sum = 0;
	std::map<int, int> m;
	m.insert(std::make_pair(0, -1)); // important
	const int len = ivec.size();
	for(int i = 0; i < len; i++) {
		sum += ivec[i];
		std::map<int, int>::iterator itr = m.find(sum);
		if(itr == m.end()) {
			m.insert(std::make_pair(sum, i));
		}
		itr = m.find(sum - k);
		if(itr != m.end()) {
			max_len = std::max(max_len, i - itr->second);
		}
	}

	return max_len;
}
// [TIME_STAMP] Stop XX:XX, 2017/10/03



// [TIME_STAMP] Start at 12:13 2017/12/10
// --------------------------------------------------------------------------------------------------------------
// 8.12 The max size of a sub-array of which the sum is less than or equal to a certain value specified
// Notice, the elements in the original array can be negative, positive or zero.
// The origianl array is unordered

int find_left_most(int *arr, const int length, int v);

int longest_subarray_sum_less_than_or_equal_to_a_certain_sum(const std::vector<int>& ivec, const int k) {
	int res = 0;
	if(ivec.empty() || k <= 0) {
		return res;
	}

	const int len = ivec.size();
	// Second get greater-than-left-sum array
	int *g = new int[len + 1];// Size is one more than ivec.size()
	g[0] = 0;
	int sum = 0;
	for(int i = 0; i < len; i++) {
		sum += ivec[i];
		g[i + 1] = std::max(sum, g[i]);
	}

	int pre = 0;
	sum = 0;
	for(int i = 0; i < len; i++) {
		sum += ivec[i];
		pre = find_left_most(g, len + 1, sum - k);
		if(pre != -1) {
			res = std::max(res, i - pre + 1);
		}
	}

	delete [] g;
	return res;
}

// Binary search
int find_left_most(int *arr, const int length, int v) {
	if(!arr) {
		return -1;
	}

	int left_most_pos = -1;

	int left = 0;
	int right = length - 1;
	while(left < right) {
		int mid = (left + right) / 2;
		if(arr[mid] >= v) { // sum is already greater than or equal to 'v'
			right = mid - 1;
			left_most_pos = mid;
		} else {
			left = mid + 1;
		}
	}

	return left_most_pos;
}

// --------------------------------------------------------------------------------------------------------------
// 8.13 Get the sum of less-than-i-sum
// Assume array = {1, 3, 5, 2, 4, 6}
// i   ---   array[i]   ---   less-than-i-sum
// 0   ---       1      ---         0                 => 0
// 1   ---       3      ---         1                 => 1
// 2   ---       5      ---         1 + 3             => 4
// 3   ---       2      ---         1                 => 1
// 4   ---       4      ---         1 + 3 + 2         => 6
// 5   ---       6      ---         1 + 3 + 5 + 2 + 4 => 15
//------------------------------------------------------------------
// So the sum of less-than-i-sum is: 0 + 1 + 4 + 1 + 6 + 15 = 27

// Use merge sort
int _merge(std::vector<int>& arr, int left, int mid, int right);
int _merge_sort(std::vector<int>& arr, int l, int r);
int merge_sort(std::vector<int>& arr);
int get_array_small_sum(std::vector<int>& arr);

int _merge(std::vector<int>& arr, int left, int mid, int right) {
	std::vector<int> h;
	h.resize(arr.size(), 0);
	int i = left;
	int j = mid + 1;
	int k = 0;
	int smallSum = 0;
	while(i <= mid && j <= right) {
		if(arr[i] <= arr[j]) {
			smallSum += arr[i] * (right - j + 1);
			h[k++] = arr[i++];
		} else {
			h[k++] = arr[j++];
		}
	}

	while(i <= mid) {
		h[k++] = arr[i++];
	}
	while(j <= right) {
		h[k++] = arr[j++];
	}
	i = left;
	k = 0;
	while(i <= right) {
		arr[i++] = h[k++];
	}
	return smallSum;
}

int _merge_sort(std::vector<int>& arr, int l, int r) {
	int ssum = 0;
	if(l >= r) {
		return ssum;
	}
	int mid = (l + r) / 2;
	ssum += _merge_sort(arr, l, mid);
	ssum += _merge_sort(arr, mid + 1, r);
	ssum += _merge(arr, l, mid, r);

	return ssum;
}

int merge_sort(std::vector<int>& arr) {
	return _merge_sort(arr, 0, arr.size() - 1);
}

int get_array_small_sum(std::vector<int>& arr) {
	if(arr.size() < 2) {
		return 0;
	}
	return merge_sort(arr);
}

// --------------------------------------------------------------------------------------------------------------
// 8.14 Natural number sorting
// Assume all elements are different
// Assume elements are 1~N, the length of array is N
void natural_number_sorting(std::vector<int>& ivec) {
	if(ivec.size() < 2) {
		return ;
	}
	const int len = ivec.size();
	for(int i = 0; i < len; i++) {
		while(ivec[i] != i + 1) {
			int a = ivec[i];
			int t = ivec[a - 1];
			ivec[a - 1] = ivec[i];
			ivec[i] = t;
		}
	}
}

// --------------------------------------------------------------------------------------------------------------
// 8.15 Elements of even indexes are even, elements of odd indexes are odd
// All elements in the array are integers

void even_index_even_odd_index_odd(std::vector<int>& ivec) {
	if(ivec.size() < 2) {
		return ;
	}

	int pEven = 0;
	int pOdd = 1;
	const int len = ivec.size();
	while(pEven < len && pOdd < len) {
		if(ivec[len - 1] % 2 == 0) {
			int t = ivec[pEven];
			ivec[pEven] = ivec[len - 1];
			ivec[len - 1] = t;
			pEven += 2;
		} else {
			int t = ivec[pOdd];
			ivec[pOdd] = ivec[len - 1];
			ivec[len - 1] = t;
			pOdd += 2;
		}
	}
}

// --------------------------------------------------------------------------------------------------------------
// 8.16 The max sum of a sub-array in the array

int max_sum_subarray(const std::vector<int>& ivec) {
	int res = 0;
	int sum = 0;
	const int len = ivec.size();
	for(int i = 0; i < len; i++) {
		if(sum + ivec[0] < 0) {
			sum = 0;
		} else {
			sum += ivec[0];
		}
		res = std::max(res, sum);
	}
	return res;
}

// --------------------------------------------------------------------------------------------------------------
// 8.17 The max sum of a sub-matrix in the matrix

int get_max_sum_subarray(const int *arr, const int cols);

int max_sum_submatrix(const int **mtx, const int rows, const int cols) {
	int res = 0;
	int *a = new int[cols];
	for(int i = 0; i < rows; i++) {
		memset(a, 0, sizeof(int) * cols); // memset is included in memory.h
		for(int j = i; j < rows; j++) {
			for(int c = 0; c < cols; c++) {
				a[c] += mtx[j][c];
			}
			res = std::max(res, get_max_sum_subarray(a, cols));
		}
	}

	delete [] a;
	return res;
}

int get_max_sum_subarray(const int *arr, const int cols) {
	int res = 0;
	int sum = 0;
	for(int i = 0; i < cols; i++) {
		if(sum + arr[0] < 0) {
			sum = 0;
		} else {
			sum += arr[0];
		}
		res = std::max(res, sum);
	}
	return res;
}

// --------------------------------------------------------------------------------------------------------------
// 8.18 Find a local minimum number in an array
// If array size is 1, then arr[0] is the local min
// else
// (1) arr[0] < arr[1], arr[0] is a local min
// (2) arr[N-1] < arr[N-2], arr[N-1] is a local min
// (3) arr[i] < arr[i+1] && arr[i] < arr[i-1], arr[i] is a local min
// Find any one local min is enough

int find_a_local_min(const std::vector<int>& ivec) {
	if(ivec.size() < 1) {
		printf("Local min doesn't exist\n");
		return -1;
	}
	if(ivec.size() == 1 || ivec[0] < ivec[1]) {
		return ivec.front();
	}
	const int len = ivec.size();
	if(ivec[len - 1] < ivec[len - 2]) {
		return ivec.back();
	}

	int left = 1; // the 2nd element position
	int right = len - 2; // the last but one
	while(left < right) {
		int mid = (left + right) / 2;
		if(ivec[mid] > ivec[mid - 1]) {
			right = mid - 1;
		} else if(ivec[mid] > ivec[mid + 1]) {
			left = mid + 1;
		} else { // Now ivec[mid] <= ivec[mid-1] && ivec[mid] <= ivec[mid + 1]
			return ivec[mid];
		}
	}

	return left; // at this time, left equals to right, so can also be 'return right'
}

// --------------------------------------------------------------------------------------------------------------
// 8.19 Max accumulated product of subarray
// The elements in this array are double type

// DP method
// dpmax[i] means the max accumulated product subarray of array[0..i]
// dpmin[i] means the min accumulated product subarray of array[0..i]

// The possibilities of dpmax[i] and dpmin[i]:
// (1) dpmax[i-1] * arr[i]
// (2) dpmin[i-1] * arr[i]
// (3) Or just arr[i]
// So
// dpmax[i] = MAX(dpmax[i-1] * arr[i], dpmin[i-1] * arr[i], arr[i])
// dpmin[i] = MIN(dpmax[i-1] * arr[i], dpmin[i-1] * arr[i], arr[i])


double max_accumulated_product_subarray(const std::vector<double>& ivec) {
	if(ivec.empty()) {
		return 0;
	}
	if(ivec.size() == 1) {
		return ivec.front();
	}

	double res = 0;
	const int len = ivec.size();
	double *dpmax = new double[len];
	double *dpmin = new double[len];

	double a = 0;
	double b = 0;

	dpmax[0] = ivec[0];
	dpmin[0] = ivec[0];

	for(int i = 1; i < len; i++) {
		a = dpmax[i - 1] * ivec[i];
		b = dpmin[i - 1] * ivec[i];
		dpmax[i] = std::max(std::max(a, b), ivec[i]);
		dpmin[i] = std::min(std::min(a, b), ivec[i]);
	}
	res = dpmax[len - 1];

	delete dpmax;
	delete dpmin;
	return res;
}

// [TIME_STAMP] Stop 16:15, 2017/12/10



// [TIME_STAMP] Start at 22:07, 2017/12/18
// --------------------------------------------------------------------------------------------------------------
// 8.20 Get K max values from N sorted arrays
// Notice that arrays may have different length, but all of them are sorted and in ascending order

class _heapNode {
public:
	_heapNode(const int& v, const int& from, const int& pos) : m_value(v), m_from_array(from), m_pos(pos) {}
	~_heapNode() {}
public:
	int m_value;
	int m_from_array;
	int m_pos;
};


void _heap_filter_up(_heapNode** h, int hsize, int pos) {
	_heapNode* n = h[pos];
	int parent = (pos - 1) / 2;
	while(parent > 0) {
		_heapNode* p = h[parent];
		if(n->m_value <= p->m_value) {
			break;
		}
		_heapNode* tmp = h[pos];
		h[pos] = h[parent];
		h[parent] = tmp;
		pos = parent;
		parent = (pos - 1) / 2;
	}
}

void _heap_filter_down(_heapNode** h, int hsize, int pos) {
	int left = pos * 2 + 1;
	int right = pos * 2 + 2;
	// _heapNode* p = h[pos];
	int mindex = pos;
	while(left < hsize) {
		if(h[left]->m_value > h[mindex]->m_value) {
			mindex = left;
		}
		if(right < hsize && h[right]->m_value > h[mindex]->m_value) {
			mindex = right;
		}
		if(mindex == pos) {
			break;
		}
		_heapNode* tmp = h[pos];
		h[pos] = h[mindex];
		h[mindex] = tmp;

		pos = mindex;
		left = pos * 2 + 1;
		right = pos * 2 + 2;
	}
}

const std::list<int> get_k_max_from_n_sorted_arrays(std::vector<std::vector<int> >& vecs, const int k) {
	std::list<int> res;

	// Error & unexpected situations check
	if(vecs.empty()) {
		return res;
	}

	typedef std::vector<std::vector<int> > varray;
	int total_cnt = 0;
	for(varray::iterator itr = vecs.begin(); itr != vecs.end(); itr++) {
		if(itr->empty()) {
			return res;
		}
		total_cnt += itr->size();
	}

	if(total_cnt < k) {
		return res;
	}

	const int vsize = vecs.size();
	_heapNode** heap = new _heapNode*[vsize];
	memset(heap, 0, sizeof(_heapNode*) * vsize); // initialize
	int hsize = 0;
	for(int i = 0; i < vsize; i++) {
		if(!vecs[i].empty()) {
			int v = vecs[i].back();
			int pos = vecs[i].size() - 1;
			vecs[i].pop_back();
			_heapNode* nd = new _heapNode(v, i, pos);
			heap[hsize++] = nd;
			_heap_filter_up(heap, hsize, hsize - 1);
		}
	}

	for(int i = 0; i < k; i++) {
		_heapNode* n = heap[0];
		assert(n != NULL);
		res.push_back(n->m_value);
		if(n->m_pos == 0) {
			delete heap[0];
			heap[0] = heap[hsize - 1];
			heap[hsize - 1] = NULL;
			_heap_filter_down(heap, hsize--, 0);
		} else {
			const int from = n->m_from_array;
			_heapNode* nn = new _heapNode(vecs[from].back(), from, vecs[from].size() - 1);
			delete n;
			n = NULL;
			heap[0] = nn;
			_heap_filter_down(heap, hsize, 0); // No need to decrease 'hisze' since no size change
		}
	}

	for(int j = 0; j < vsize; j++) {
		if(heap[j]) {
			delete heap[j];
			heap[j] = NULL;
		}
	}
	delete [] heap;

	return res;
}

// [TIME_STAMP] Stop 23:16, 2017/12/18












} // namespace C8



#endif /* CHAPTER_8_HPP_ */
