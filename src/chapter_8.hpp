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

// Boost libraries
#include <boost/foreach.hpp>

#include "common_utils.hpp"


namespace C8 {

namespace CU = common_utils;


// [TIME_STAMP] Start at 14:15 2017/12/09

// --------------------------------------------------------------------------------------------------------------
// 8.1 Print a matrix in order of clockwise

void print_matrix_clockwise(int **mtx, const int m, const int n);


// --------------------------------------------------------------------------------------------------------------
// 8.2 Rotate a square matrix for 90 degrees

// Rotate by clockwise order
void rotate_square_matrix_90_degree(int **mtx, const int sz);

// --------------------------------------------------------------------------------------------------------------
// 8.3 Print a matrix in zigzag order


void print_matrix_in_zigzag_order(int **mtx, const int m, const int n);

// --------------------------------------------------------------------------------------------------------------
// 8.4 Find K minimum number in an unordered array
// Can use 2 different kinds of algorithms
// (1) Heap algorithm
// (2) BFPRT algorithm

// (1) Heap algorithm
void filter_up(std::vector<int>& vec, int pos);
void filter_down(std::vector<int>& vec, const int pos, const int slimit);

std::vector<int> find_k_min_in_unordered_array(const std::vector<int>& ivec, const int k);

void filter_up(std::vector<int>& vec, int pos);

void filter_down(std::vector<int>& vec, const int pos, const int slimit);

// (2) BFPRT algorithm
// Skip since it is to sophisticated...

// --------------------------------------------------------------------------------------------------------------
// 8.5 The size of the shortest sub-array which needs to be sorted

const int shortest_subarray_need_to_sort(const std::vector<int>& ivec);

// [TIME_STAMP] Stop 16:52, 2017/12/09






// [TIME_STAMP] Start at 20:07 2017/12/09

// --------------------------------------------------------------------------------------------------------------
// 8.6 Find a number which appears more than N/K times in an array(length is N)
// (1) Find a number which appears more than N/2 times in an array(length is N)
// (2) Find a number which appears more than N/K times in an array(length is N)

// (1) Find a number which appears more than N/2 times in an array(length is N)
// Space complexity - O(1), time complexity - O(N)

int more_than_half_size_integer(const std::vector<int>& ivec);

// (2) Find a number which appears more than N/K times in an array(length is N)
// Space complexity - O(K), time complexity - O(N*K)

void minus_one_and_remove_if_zero(std::map<int, int>& m);

void more_than_N_of_K_size_integers(const std::vector<int>& ivec, const int k);

// --------------------------------------------------------------------------------------------------------------
// 8.7 Find a number in a matrix whose rows and columns have been all sorted already

// The rows are all in ascending order
// The columns are all in ascending order

bool find_number_in_matrix_rows_columns_sorted(int **mtx, const int m, const int n, const int k);

// --------------------------------------------------------------------------------------------------------------
// 8.8 Find the max size of consolidated sub array in an unordered array

// Define a consolidated array
// Array [5, 3, 4, 6, 2] after sorted is [2, 3, 4, 5, 6]
// Each adjacent two elements are consecutive
// then it is called 'consolidated'

// Solution KEY
// if MAX(array[0..N-1]) - MIN(array[0..N-1]) + 1= LENGTH(array[0..N-1])
// then it is the so-called consolidated array

int max_size_consolidate_subarray(const std::vector<int>& ivec);

// --------------------------------------------------------------------------------------------------------------
// 8.9 Print all two-tuples or triad of a certain value specified in a sorted array
// (1) Print all two-tuples of a certain value specified in a sorted array
// (2) Print all triad of a certain value specified in a sorted array
// Notice, don't print duplicated ones

// (1) Print all two-tuples of a certain value specified in a sorted array
void two_tuples_certain_value_in_sorted_array(const std::vector<int>& ivec, const int k);

// (2) Print all triad of a certain value specified in a sorted array
void triad_certain_value_in_sorted_array(const std::vector<int>& ivec, const int k);

// [TIME_STAMP] Stop 22:29, 2017/12/09



// [TIME_STAMP] Start at 11:39, 2017/12/10

// --------------------------------------------------------------------------------------------------------------
// 8.10 The max size of a sub-array of which the sum is a certain value specified
// The orginal array is unordered, and all elements are positive integers

int max_subarray_of_certain_sum(const std::vector<int>& arr, const int k);
// [TIME_STAMP] Stop 12:04, 2017/12/10


// [TIME_STAMP] Start at 20:54 2017/10/03
// --------------------------------------------------------------------------------------------------------------
// 8.11 The longest sub-array in an unordered array of a certain sum
// Notice, the elements in the original array can be negative, positive or zero.
// Solution,
// Assume S(i) = Sum[0...i], so if K=S(i)-S(j), then Sum[j+1,...,i] = K, that's what we want

int longest_subarray_of_a_certain_sum(const std::vector<int>& ivec, const int k);
// [TIME_STAMP] Stop XX:XX, 2017/10/03



// [TIME_STAMP] Start at 12:13 2017/12/10
// --------------------------------------------------------------------------------------------------------------
// 8.12 The max size of a sub-array of which the sum is less than or equal to a certain value specified
// Notice, the elements in the original array can be negative, positive or zero.
// The origianl array is unordered

int find_left_most(int *arr, const int length, int v);

int longest_subarray_sum_less_than_or_equal_to_a_certain_sum(const std::vector<int>& ivec, const int k);

// Binary search
int find_left_most(int *arr, const int length, int v);

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

int _merge(std::vector<int>& arr, int left, int mid, int right);

int _merge_sort(std::vector<int>& arr, int l, int r);

int merge_sort(std::vector<int>& arr);

int get_array_small_sum(std::vector<int>& arr);

// --------------------------------------------------------------------------------------------------------------
// 8.14 Natural number sorting
// Assume all elements are different
// Assume elements are 1~N, the length of array is N
void natural_number_sorting(std::vector<int>& ivec);

// --------------------------------------------------------------------------------------------------------------
// 8.15 Elements of even indexes are even, elements of odd indexes are odd
// All elements in the array are integers

void even_index_even_odd_index_odd(std::vector<int>& ivec);

// --------------------------------------------------------------------------------------------------------------
// 8.16 The max sum of a sub-array in the array

int max_sum_subarray(const std::vector<int>& ivec);

// --------------------------------------------------------------------------------------------------------------
// 8.17 The max sum of a sub-matrix in the matrix

int get_max_sum_subarray(const int *arr, const int cols);

int max_sum_submatrix(const int **mtx, const int rows, const int cols);

int get_max_sum_subarray(const int *arr, const int cols);

// --------------------------------------------------------------------------------------------------------------
// 8.18 Find a local minimum number in an array
// If array size is 1, then arr[0] is the local min
// else
// (1) arr[0] < arr[1], arr[0] is a local min
// (2) arr[N-1] < arr[N-2], arr[N-1] is a local min
// (3) arr[i] < arr[i+1] && arr[i] < arr[i-1], arr[i] is a local min
// Find any one local min is enough

int find_a_local_min(const std::vector<int>& ivec);

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


double max_accumulated_product_subarray(const std::vector<double>& ivec);

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


void _heap_filter_up(_heapNode** h, int hsize, int pos);

void _heap_filter_down(_heapNode** h, int hsize, int pos);

const std::list<int> get_k_max_from_n_sorted_arrays(std::vector<std::vector<int> >& vecs, const int k);

// [TIME_STAMP] Stop 23:16, 2017/12/18





// [TIME_STAMP] Start at 15:34, 2017/12/24
// --------------------------------------------------------------------------------------------------------------
// 8.21 The max square of which the boarders  are consist of '1' in a square matrix
// (1) Values in matrix are '0' or '1'
// (2) the square's boarders are consist of '1'
// (3) Get the boarder length


// Solution
// (1) Separately check NxN positions
// (2) For each position, check if it is the upper-left point of a valid square
// Notice, use pre-processed RIGHT matrix and DOWN matrix
// RIGHT[i][j] means start from (i,j), there're how many successive 1s to the right at most
//  DOWN[i][j] means start from (i,j), there're how many successive 1s down to the bottom at most

const int max_square_boarders_are_1_value_in_matrix(int **m, const int slen);

// --------------------------------------------------------------------------------------------------------------
// 8.22 Accumulated multiply array except itself
// Given an array, return the multiply array, the multiply excepts the element itself for each element
// For example, arr=[2,3,1,4], return [12, 8, 24, 6]
// Which are,
// 12 = 3 * 1 * 4
//  8 = 2 * 1 * 4
// 24 = 2 * 3 * 4
//  6 = 2 * 3 * 1

// First method
const std::vector<int> accumulated_multiply_array(const std::vector<int>& ivec);

// Second method
const std::vector<int> accumulated_multiply_array_2(const std::vector<int>& ivec);

// --------------------------------------------------------------------------------------------------------------
// 8.23 Partition an ordered array, partition an array containing 3 kinds of values
// Issue 1
// Adjust an ordered array
// (1) make the left part as ascending order without repetition
// (2) move the repeated elements to the right part(no matter what the order is)
// Issue 2
// An array contains 3 kinds of values(0, 1 and 2)
// Sort this array
// Issue 2 mutation 1
// An array has 3 kinds of balls(red, blue and yellow)
// sort this array as the order of "red at left, blue in the middle and yellow at right"
// Issue 2 mutation 2
// An array has 3 kinds of values(>k, ==k and <k)
// sort this array as the order of "<k at left, ==k in the middle and >k at right"

// Issue 1
// Unique left part of an ordered array
void unique_array_left_part(std::vector<int>& ivec);


// Issue 2 and its mutation
void partition_an_array(std::vector<int>& ivec);

// or index could also be this
void partition_an_array_2(std::vector<int>& ivec);


// --------------------------------------------------------------------------------------------------------------
// 8.24 Get the min path from top-left to bottom-right of a matrix
// matrix[i][j] == 1 --> means road is connected
// matrix[i][j] == 0 --> means road is not connected

const int min_path_matrix_topleft_to_bottomright(int **m, const int row, const int col);

// --------------------------------------------------------------------------------------------------------------
// 8.25 Find the min positive integer which doesn't appear in an unordered array
// Example
// arr = [-1, 2, 3, 4]
// arr = [1, 2, 3, 4]

const int min_positive_integer_missing(const std::vector<int>& ivec);

// --------------------------------------------------------------------------------------------------------------
// 8.26 The max different of two adjacent elements in an array after sorting

int get_bucket_num(long num, long len, long min, long max);

const int max_diff_two_adjacent_array_after_sorting(const std::vector<int>& ivec);

// [TIME_STAMP] Stop at 22:15, 2017/12/24



} // namespace C8



#endif /* CHAPTER_8_HPP_ */
