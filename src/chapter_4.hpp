/*
 * chapter_4.hpp
 *
 *  Created on: Sept. 19, 2017
 *      Author: Pyrad
 * Description: Header file of chapter 4 Dynamic Planning
 *   Intention: Solutions for problems in Chapter 4[Dynamic Planning] of Code Interview Guide
 */

#ifndef CHAPTER_4_HPP_
#define CHAPTER_4_HPP_

#include <stdio.h>
#include <algorithm>
#include <assert.h>
#include <string>
#include <iostream>
#include <vector>
#include <map>

#include "common_utils.hpp"

namespace C4 {

// [TIME_STAMP] Start at 20:00, 2017/09/19

// --------------------------------------------------------------------------------------------------------------
// 4.1 Fibonacci issue
//     Stages issue
//     Cows and their descendant issue

//------------Fibonacci--------------------
// Recursive resolution
int fibonacci(int n);

// Dynamic planning resolution
int fibonacci_dp(int n);

//------------Stages--------------------
// Recursive resolution
int stages(int n);

// Dynamic planning resolution
int stages_dp(int n);

//------------Cows & descendants-------------------
// Recursive resolution
int cows_descendants(int n);

// Dynamic planning resolution
int cows_desendants_dp(int n);

// --------------------------------------------------------------------------------------------------------------
// 4.2 Minimum route length in matrix from top left to bottom right
// Allocate a matrix same as input matrix
int min_route_len_in_matrix(int **m, int row, int col);

// Just allocate an array(space saving)
int min_route_len_in_matrix_space_saving(int **m, int row, int col);

// [TIME_STAMP] Stop at 22:51, 2017/09/19



// [TIME_STAMP] Start at 20:48, 2017/09/20


// --------------------------------------------------------------------------------------------------------------
// 4.3 Money Exchange
// (1) Minimum number of sheets for money exchange(NO sheet limits for each nominal value)
// (2) Minimum number of sheets for money exchange(HAS sheet limits for each nominal value)

int mini_exchange(const std::vector<int>& ivec, const int aim);

int mini_exchange_space_saving(const std::vector<int>& ivec, const int aim);

// [TIME_STAMP] Stop at 22:50, 2017/09/20



// [TIME_STAMP] Start at 20:06, 2017/09/21

int mini_exchange_sheets_limit(const std::vector<int>& ivec, const int aim);


int mini_exchange_sheets_limit_space_saving(const std::vector<int>& ivec, int aim);


// --------------------------------------------------------------------------------------------------------------
// 4.4 Money Exchange
// The total ways to exchange money 'aim' by using several sheets of values(an array)
// Each value in the array can be used several times

int exchange_ways_1(const std::vector<int>& ivec, int aim);

int exchange_ways_2(const std::vector<int>& ivec, int aim);




// --------------------------------------------------------------------------------------------------------------
// 4.5 Max subsequence of ascending order
// Given an array, get the max subsequence of it in the ascending order
// The array's order doesn't have to be in ascending/descending order

// solution
// allocate an array 'dp', which size is same as the input array
// dp[i] means the max len of the subsequence in ascending order which MUST use the array[i] as the last one of the subsequence
// That is to say dp[i] means the max len of the subsequence in ascending order which MUST end by array[i]
// So first step is to get 'dp', then the second step is to get subsequence using 'dp'

void max_subseq_ascend_len(const std::vector<int>& arr, std::vector<int>& dp);

// [In] arr
// [In] dp
// [Out] subseq
void get_max_sub_ascend(const std::vector<int>& arr, const std::vector<int>& dp, std::vector<int>& subseq);


// [TIME_STAMP] Stop at 22:45, 2017/09/21



// [TIME_STAMP] Start at 10:02, 2017/09/23

// --------------------------------------------------------------------------------------------------------------
// 4.6 Hanoi Tower Problem
// (1) Print the trace of the optimal movements
// (2) Judge if an array is the one of those optimal movements

// Recursive solution
void hanoi(int n, const std::string& from, const std::string& help, const std::string& to);
void hanoi_solve(int n);

// enum WHICH_PILLAR {UNKNOW = 0, FROM, MID, TO};
int step(const std::vector<int>& arr, const int i, int from, int mid, int to);
int step_judge(const std::vector<int>& arr);

// --------------------------------------------------------------------------------------------------------------
// 4.7 Longest Common Sequence of 2 Strings
// Not only max length but also this common sequence

// out_dp is a matrix and it is for output
void longest_common_sequence_dp_matrix(const std::string& str1, const std::string& str2, int **out_dp);

std::string longest_common_sequence(const std::string& str1, const std::string& str2);

// --------------------------------------------------------------------------------------------------------------
// 4.8 Longest Common Sub String of 2 Strings

void longest_common_substring_dp_matrix(const std::string& str1, const std::string& str2, int **out_dp);

std::string longest_common_substring(const std::string& str1, const std::string& str2);

// --------------------------------------------------------------------------------------------------------------
// 4.9 Minimum Cost of Editting

int min_edit_cost(const std::string& str1, const std::string& str2, const int ic, const int dc, const int rc);

int min_edit_cost_space_saving(const std::string& str1, const std::string& str2, const int ic, const int dc, const int rc);

// --------------------------------------------------------------------------------------------------------------
// 4.10 Is a string staggered by 2 strings

bool is_stagger_string(const std::string& str1, const std::string& str2, const std::string& aim);

bool is_stagger_string_space_saving(const std::string& str1, const std::string& str2, const std::string& aim);

// --------------------------------------------------------------------------------------------------------------
// 4.11 Game of Dungeons and Dragons

int dungeons_and_dragons(const int **map, const int row, const int col);

int dungeons_and_dragons_space_saving(const int **map, const int row, const int col);

// --------------------------------------------------------------------------------------------------------------
// 4.12 How many ways to convert a string(all digits) to a character string

int convert_number_string_to_char_string_process(const std::string& digit_string, const int i);
int convert_number_string_to_char_string(const std::string& s);

// Use dynamic planning to resolve the problem
int convert_number_string_to_char_string_dp_solution_method(const std::string& s);

// --------------------------------------------------------------------------------------------------------------
// 4.13 Number of Expectations for An Expression

bool is_valid_expression(const std::string& expr);

int desired_expections_process(const std::string& expr, bool desired, const int start, const int end);

int desired_expections(const std::string& expr, bool desired);

// --------------------------------------------------------------------------------------------------------------
// 4.14 Game of Poker
//

// For arr[i..j], if take firstly, what is the final score
int first_take(const std::vector<int>& arr, const int start, const int end);
// For arr[i..j], if take secondly, what is the final score
int second_take(const std::vector<int>& arr, const int start, const int end);

int first_take(const std::vector<int>& arr, const int start, const int end);

int second_take(const std::vector<int>& arr, const int start, const int end);

int winner_score(const std::vector<int>& arr);

// DP solution for the 'Game of Poker issue'

int winner_score_dp_solution(const std::vector<int>& arr);

// [TIME_STAMP] Stop at 20:16, 2017/09/23


// [TIME_STAMP] Start at 10:24, 2017/09/24

// --------------------------------------------------------------------------------------------------------------
// 4.15 Jump Game

int min_times_jump_to_the_end(const std::vector<int>& arr);


// --------------------------------------------------------------------------------------------------------------
// 4.16 Longest Consecutive Subsequence

int longest_consecutive_subsequence(const std::vector<int>& arr);

// --------------------------------------------------------------------------------------------------------------
// 4.17 N Queens Problem

bool is_place_valid(const int i, const int j, const std::vector<int>& arr);

int n_queens(const int n, const int row, std::vector<int>& arr);

int n_queens_solution(const int n);

// [TIME_STAMP] Stop at 12:50, 2017/09/24


} // end-of-namespace C4


#endif /* CHAPTER_4_HPP_ */





































