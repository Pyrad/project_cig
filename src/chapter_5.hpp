/*
 * chapter_5.hpp
 *
 *  Created on: Oct. 15, 2017
 *      Author: Pyrad
 * Description: Header file of chapter 5 String Problems
 *   Intention: Solutions for problems in Chapter 5[String Problems] of Code Interview Guide
 */

#ifndef CHAPTER_5_HPP_
#define CHAPTER_5_HPP_


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

namespace C5 {

namespace CU = common_utils;




// [TIME_STAMP] Start at 12:31, 2017/11/26

// --------------------------------------------------------------------------------------------------------------
// 5.1 Judge if two words are anagrams

bool if_two_words_are_anagrams(const std::string& str1, const std::string& str2) {
	if(str1.size() != str2.size()) {
		return false;
	}

	// Assume they are ASCII codes
	std::vector<int> char_map;
	// a map, the index represents ASCII value of a char
	// array value represents its number
	char_map.resize(256, 0); // 256 ASCII chars
	const std::size_t len = str1.size();
	assert(len == str2.size());
	for(std::size_t i = 0; i < len; i++) {
		int idx = str1[i] - '0';
		char_map[idx]++;
	}

	for(std::size_t i = 0; i < len; i++) {
		int idx = str2[i] - '0';
		char_map[idx]--;
		if(char_map[idx] < 0) {
			return false;
		}
	}

	return true;
}


// --------------------------------------------------------------------------------------------------------------
// 5.2 Get total sum of digits(as characters) in a string
int total_digits_sum_in_string(const std::string& str) {
	int res = 0;

	bool sign = true; // true - positive, false - negative
	int sum = 0;

	std::size_t len = str.size();
	for(std::size_t i = 0; i < len; i++) {
		char c = str[i];
		if(c - '0' >= 0 && c - '0' <= 9) {
			sum = sum * 10;
			int cur = c - '0';
			if(sign) {
				sum += cur;
			} else {
				sum -= cur;
			}
		} else {
			res += sum;
			sum = 0;
			if(c == '-') {
				if(i > 0 && str[i - 1] == '-') {
					sign = !sign;
				} else {
					sign = false;
				}
			} else {
				sign = true;
			}
		}
	}

	res += sum;
	return res;
}

// --------------------------------------------------------------------------------------------------------------
// 5.3 Remove successive K characters of '0' in a string

const std::string remove_k_0_in_string(const std::string& str, int k) {
	std::string res;

	std::size_t len = str.size();
	for(std::size_t i = 0; i < len; i++) {
		if(str[i] != '0') {
			res += str[i];
		} else {
			int num = 0;
			while(i < len) {
				if(str[i] != '0') {
					break;
				}
				i++;
				num++;
			}
			if(num != k) {
				res.append(std::string(num, '0'));
			}
			if(i < len) {
				res += str[i];
			}
		}
	}

	return res;
}


// --------------------------------------------------------------------------------------------------------------
// 5.4 If 2 words are rotated words

bool is_rotated_word(const std::string& str1, const std::string& str2) {
	if(str1.size() != str2.size()) {
		return false;
	}

	std::string str(str1 + str2);
	return (str.find(str1) != std::string::npos);
}

// --------------------------------------------------------------------------------------------------------------
// 5.5 Convert a string to integer if it is valid

bool check_is_string_valid_integer(const std::string& str) {
	if(str.empty()) {
		return false;
	}

	if(str[0] == '0' && str.size() > 1) {
		return false;
	}
	if(str[0] == '-' && (str[1] < '0' || str[1] > '9')) {
		return false;
	}
	if(str[0] == '-' && (str.size() == 1 || str[1] == '0')) {
		return false;
	}

	std::size_t len = str.size();
	for(std::size_t i = 0; i < len; i++) {
		if(str[i] < '0' || str[i] > '9') {
			return false;
		}
	}

	return true;
}

const int convert_string_to_integer(const std::string& str) {
	int res = 0;
	if(check_is_string_valid_integer(str)) {
		return 0;
	}

	bool sign = str[0] == '-' ? false : true;
	int minq = INT_MIN / 10;
	int minr = INT_MIN % 10;

	std::size_t len = str.size();
	for(std::size_t i = 0; i < len; i++) {
		int cur = str[i] - '0';
		if( res < minq) {
			return 0;
		}
		if( res == minq && -minr < cur) {
			return 0;
		}
		res = res * 10 - cur;
	}

	if(res == INT_MIN) {
		return 0;
	}

	return sign ? -res : res;
}

// --------------------------------------------------------------------------------------------------------------
// 5.6 Replace repeated strings in a string

const std::string replace_repeated_strings(std::string& str, const std::string& from, const std::string& to) {
	/*
	std::size_t len = str.size();
	std::size_t idx = 0;
	int start = -1;
	for(std::size_t i = 0; i < len; i++) {
		if(str[i] == from[idx]) {
			start = start == -1 ? i : start;
			if(idx == from.size() - 1) {
				int cnt = from.size();
				while(cnt-- > 0) {
					str[start] = '\0';
					start++;
				}
				start = -1;
				idx = 0;
			} else {
				idx++;
			}
		} else {
			start = -1;
			idx = 0;
			if(str[i] == from[idx]) { // idx now is 0
				start = i;
				idx++;
			}
		}
	}
	*/

	std::size_t len = str.size();
	std::size_t match = 0;
	for(std::size_t i = 0; i < len; i++) {
		if(str[i] == from[match]) {
			match++;
			if(match == from.size()) {
				int cnt = from.size();
				int idx = i;
				while(cnt-- > 0) {
					str[idx--] = '\0';
				}
				match = 0;
			}
		} else {
			match = 0;
			if(str[i] == from[match]) {
				match++;
			}
		}
	}

	std::string res("");
	for(std::size_t i = 0; i < len; i++) {
		if(str[i] != '\0') {
			res += str[i];
		} else {
			while(i + 1< len && str[i + 1] == '\0') {
				i++;
			}
			res += to;
		}
	}

	return res;
}


// --------------------------------------------------------------------------------------------------------------
// 5.7 Character statistics in a string

const std::string string_successive_char_statistics(const std::string& str) {
	if(str.empty()) {
		return "";
	}
	if(str.size() == 1) {
		return str + "_1";
	}

	std::size_t len = str.size();
	int cnt = 1;
	std::stringstream ss;
	for(std::size_t i = 1; i < len; i++) {
		if(str[i] != str[i - 1]) {
			ss << str[i - 1] << "_" << cnt << "_";
			cnt = 1;
		} else {
			cnt++;
		}
	}
	ss << str[len - 1] << "_" << cnt;

	return ss.str();
}

const std::string find_char_in_string_statistics_by_order(const std::string& str, const int kth) {
	if(str.empty() || kth <= 0 || (int)str.size() < kth) {
		return "";
	}

	std::size_t len = str.size();
	bool flag = true;
	char c = '\0';
	int acc = 0;
	int res = 0;
	for(std::size_t i = 0; i < len; i++) {
		if(str[i] == '_') {
			if(!flag) {
				res += acc;
				if(res >= kth) {
					std::stringstream ss;
					ss << c;
					return ss.str();
				}
				acc = 0;
			}
			flag = !flag;
		} else {
			int cur = str[i] - '0';
			if(cur < 0 || cur > 9) {
				c = str[i];
			} else {
				acc = acc * 10 + cur;
			}
		}
	}

	res += acc;
	if(res >= kth) {
		std::stringstream ss;
		ss << c;
		return ss.str();
	} else {
		return "";
	}
}

// [TIME_STAMP] Stop at 18:02, 2017/11/26



// [TIME_STAMP] Start at 19:32, 2017/11/27

// --------------------------------------------------------------------------------------------------------------
// 5.8 If any char in a string appear only once
//	(1) Use a map, O(N)
//	(2) Don't use map, O(NlogN)

// (1) Use a map, O(N)
bool if_any_char_appear_only_once(const std::string& str) {
	if(str.empty()) {
		return false;
	}

	std::vector<int> value_map;
	value_map.resize(256, 0);

	std::size_t len = str.size();
	for(std::size_t i = 0; i < len; i++) {
		int idx = str[i] - '0';
		if(value_map[idx] != 0) {
			return false;
		}
		value_map[idx]++;
	}

	return true;
}

// (2) Don't use map, use heap sort, O(NlogN)

void swap(char* a, char* b) {
	char c = *a;
	*a = *b;
	*b = c;
}

void filter_up(char* chars, const int csize, int k) {
	while(k > 0) { // or k != 0
		int parent = (k - 1) / 2;
		if(chars[parent] - chars[k] < 0) {
			char c = chars[parent];
			chars[parent] = chars[k];
			chars[k] = c;
			k = parent;
		} else {
			break;
		}
	}
}

void filter_down(char* chars, const int csize, int k) {
	int left = k * 2 + 1;
	int right = k * 2 + 2;
	int largest = k;
	while(left < csize) {
		if(chars[left] > chars[k]) {
			largest = left;
		}
		if(right < csize && chars[largest] < chars[right]) {
			largest = right;
		}
		if(k == largest) {
			break;
		}
		char tmp = chars[k];
		chars[k] = chars[largest];
		chars[largest] = tmp;
		k = largest;
		left = k * 2 + 1;
		right = k * 2 + 2;
	}
}

bool if_repeat_char_in_array(const char* chars, const int size) {
	assert(size > 0);
	for(int i = 1; i < size; i++) {
		if(chars[i] == chars[i - 1]) {
			return true;
		}
	}

	return false;
}

bool if_any_char_appear_only_once_use_heap_sort(const std::string& str) {
	const std::size_t num = str.size();

	// Copy the string to a char array
	char* chars = new char[num];
	memset(chars, 0, sizeof(char) * num);
	for(std::size_t i = 0; i < num; i++) {
		chars[i] = str[i];
	}

	/*
	printf("Before sort:\n");
	CU::print_char_array(chars, num);
	*/

	// Make a heap
	for(std::size_t i = 1; i < num; i++) {
		filter_up(chars, num, i);
	}

	// heat sort
	for(int i = num - 1; i > 0; i--) {
		swap(&chars[i], &chars[0]);
		filter_down(chars, i, 0);
	}

	/*
	printf("After sort:\n");
	CU::print_char_array(chars, num);
	*/

	bool res = if_repeat_char_in_array(chars, num);

	delete chars;
	return res;
}


// --------------------------------------------------------------------------------------------------------------
// 5.9 Find the left most position in an ordered string array(array of some strings) which may contain null character

const int left_most_position_in_string_array(const std::vector<std::string>& svec, const std::string& str) {
	if(svec.empty() || str.empty()) {
		return -1;
	}

	int left = 0;
	int right = svec.size() - 1;
	int position = -1;
	while(left <= right) {
		int mid = (left + right) / 2;
		if(svec[mid].empty()) {
			int p = mid - 1;
			while(p >= left && svec[p].empty()) {
				p--;
			}
			if(p < left) {
				left = mid + 1;
			} else {
				if(svec[p] < str) {
					left = p + 1;
				} else if(svec[p] > str) {
					right = p - 1;
				} else { // svec[p] == str
					position = p;
					right = p - 1;
				}
			}
		} else {
			if(svec[mid] > str) {
				right = mid - 1;
			} else if(svec[mid] < str) {
				left = mid - 1;
			} else { // svec[mid] == str
				position = mid;
				right = mid - 1;
			}
		}

	}

	return position;
}

// [TIME_STAMP] Stop at 22:54 2017/11/27


// [TIME_STAMP] Start at 20:25, 2017/11/28

// --------------------------------------------------------------------------------------------------------------
// 5.10 Adjust string and replace with specified characters
// There's a char array. The right part are all '\0' and left part doesn't contain '\0'
// Replace the space character in the left part and adjust the string

// (1) Replace all space characters
void adjust_and_replace(char* chars, const int size, const std::string& str) {
	if(!chars || size <= 0) {
		return ;
	}

	int space_count = 0;
	int i = 0;
	while(chars[i] != '\0') {
		assert(i < size);
		if(chars[i] == ' ') {
			space_count++;
		}
		i++;
	}

	int before_length = i;
	int after_length = i - space_count + str.size() * space_count;
	int k = after_length - 1;
	for(int j = before_length - 1; j > -1; j--) {
		if(chars[j] == ' ') {
			int len = str.size();
			while(len-- > 0) {
				chars[k--] = str[len];
			}
		} else {
			chars[k--] = chars[j];
		}
	}
}

// (2) Move all star charactes to the front of the char array
void move_all_star_chars_to_front(char* chars, const int size) {
	if(!chars || size <= 0) {
		return ;
	}
	int i = 0;
	while(chars[i] != '\0') {
		assert(i < size);
		i++;
	}

	int len = i;
	int j = len - 1;
	for(i = len - 1; i > -1; i--) {
		if(chars[i] != '*') {
			chars[j--] = chars[i];
		}
	}

	assert(j >= 0);
	while(j > -1) {
		chars[j--] = '*';
	}
}


// --------------------------------------------------------------------------------------------------------------
// 5.11 Reverse all the words in a string
// No requirements for the empty chars and punctuations

void reverse_char_array(char* chars, int start, int end) {
	if(!chars || start > end) {
		printf("Error when reversing a word(char array)\n");
		return ;
	}

	while(start < end) {
		char tmp = chars[start];
		chars[start] = chars[end];
		chars[end] = tmp;
		start++;
		end--;
	}
}

void reverse_all_words_in_string(const std::string& str) {
	if(str.empty()) {
		return ;
	}

	// const int size = str.size();
	int length = 0;
	char* chars = CU::convert_to_chars(str, length);

	// First reverse the whole string
	reverse_char_array(chars, 0, length - 1);

	int start = -1;
	int end = -1;
	for(int i = 0; i < length; i++) {
		if(chars[i] != ' ') {
			start = i == 0 || chars[i - 1] == ' ' ? i : start;
			end = i == length - 1 || chars[i + 1] == ' ' ? i : end;
		}
		if(start != -1 && end != -1) {
			reverse_char_array(chars, start, end);
			start = -1;
			end = -1;
		}
	}
	printf("After reverse:\n");
	CU::print_char_array(chars, length, false);

	delete [] chars;
}

// --------------------------------------------------------------------------------------------------------------
// 5.12 The minimum distance of 2 strings in a string array(array of strings)
// (1) Query only once
// (2) Query many times

// (1) Query only once
int min_dist_two_strings_in_string_array(const std::vector<std::string>& svec, const std::string& str1, const std::string& str2) {
	if(svec.empty()) {
		return -1;
	}
	if(str1 == str2) {
		return 0;
	}

	int last1 = -1;
	int last2 = -1;
	int min_dist = INT_MAX;
	int size = svec.size();
	for(int i = 0; i < size; i++) {
		if(svec[i] == str1) {
			last1 = i;
			if(last2 != -1) {
				min_dist = std::min(min_dist, last1 - last2);
			}
		}
		if(svec[i] == str2) {
			last2 = i;
			if(last1 != -1) {
				min_dist = std::min(min_dist, last2 - last1);
			}
		}
	}

	if(last1 == -1 || last2 == -1) {
		return -1;
	} else {
		return min_dist;
	}
}




// [TIME_STAMP] Stop at 22:23, 2017/11/28







// [TIME_STAMP] Start at XX:XX, 2017/XX/XX
// [TIME_STAMP] Stop at XX:XX, 2017/XX/XX

// [TIME_STAMP] Start at XX:XX, 2017/XX/XX
// [TIME_STAMP] Stop at XX:XX, 2017/XX/XX

// [TIME_STAMP] Start at XX:XX, 2017/XX/XX
// [TIME_STAMP] Stop at XX:XX, 2017/XX/XX






























































} // namespace C5


#endif /* CHAPTER_5_HPP_ */
