/*
 * chapter_5.hpp
 *
 *  Created on: Oct. 15, 2017
 *      Author: Pyrad
 * Description: Source file of chapter 5 String Problems
 *   Intention: Solutions for problems in Chapter 5[String Problems] of Code Interview Guide
 */



#include "chapter_5.hpp"
#include "chapter_5_tests.hpp"

#include <stdio.h>

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

// (2) Query many times
// class records_relation {
// public:
// 	records_relation(const std::vector<std::string>& strs) { init(strs); }
// 	~records_relation() { m_records.clear(); }
// public:
// 	void query_min_distance(const std::vector<std::pair<std::string, std::string> >& strs, std::vector<int>& res);
// 	int query_min_distance(const std::string& str1, const std::string& str2);
// private:
// 	void init(const std::vector<std::string>& strs);
// 	void update(const std::string& str, std::map<std::string, int>& idxmap, int cur_index);
// private:
// 	std::map<std::string, std::map<std::string, int> > m_records;
// };
// 
// void records_relation::
// update(const std::string& str, std::map<std::string, int>& idxmap, int cur_index) {
// 	if(m_records.find(str) == m_records.end()) {
// 		std::map<std::string, int> m;
// 		m_records.insert(std::make_pair(str, m));
// 	}
// 	// typedef std::pair<std::string, std::map<std::string, int> > vpair;
// 	std::map<std::string, std::map<std::string, int> >::iterator itr(m_records.find(str));
// 	typedef std::pair<std::string, int> mpair;
// 	BOOST_FOREACH(const mpair& kv, idxmap) {
// 		const std::string& s = kv.first;
// 		int pos = kv.second;
// 		if(s != str) {
// 			if(m_records.find(s)== m_records.end()) {
// 				std::map<std::string, int> m;
// 				m_records.insert(std::make_pair(s, m));
// 			}
// 			std::map<std::string, std::map<std::string, int> >::iterator ii(m_records.find(s));
// 			int cur_dist = cur_index - pos;
// 			std::map<std::string, int>::iterator j = itr->second.find(s);
// 			if(j != itr->second.end()) {
// 				int min_dist = j->second;
// 				if(cur_dist < min_dist) {
// 					(itr->second)[s] = cur_dist;
// 					(ii->second)[str] = cur_dist;
// 				}
// 			} else {
// 				(itr->second)[s] = cur_dist;
// 				(ii->second)[str] = cur_dist;
// 			}
// 		}
// 	}
// }
// 
// void records_relation::
// init(const std::vector<std::string>& strs) {
// 	std::map<std::string, int> nearest_index_map;
// 	const int len = strs.size();
// 	for(int i = 0; i < len; i++) {
// 		const std::string& s = strs[i];
// 		update(s, nearest_index_map, i);
// 		nearest_index_map[s] = i; // update each string's latest index
// 	}
// }
// 
// int records_relation::
// query_min_distance(const std::string& str1, const std::string& str2) {
// 	if(str1.empty() || str2.empty()) {
// 		return -1;
// 	}
// 
// 	if(str1 == str2) {
// 		return 0;
// 	}
// 
// 	std::map<std::string, std::map<std::string, int> >::iterator itr(m_records.find(str1));
// 	if(itr != m_records.end()) {
// 		std::map<std::string, int>::iterator ii(itr->second.find(str2));
// 		if(ii != itr->second.end()) {
// 			return ii->second;
// 		}
// 	}
// 
// 	return -1;
// }
// 
// void records_relation::
// query_min_distance(const std::vector<std::pair<std::string, std::string> >& strs, std::vector<int>& res) {
// 	typedef std::pair<std::string, std::string> spair;
// 	res.clear();
// 	BOOST_FOREACH(const spair& sp, strs) {
// 		res.push_back(query_min_distance(sp.first, sp.second));
// 	}
// }
// [TIME_STAMP] Stop at 22:23, 2017/11/28



// [TIME_STAMP] Start at 21:49, 2017/12/02
// --------------------------------------------------------------------------------------------------------------
// 5.13 Add minimum characters to make a string as palindrome
// First get the minimum number
// Secondly, get a result string(any one of possible results)

// Use DP(Dyanmic Programming) method
int min_char_number_added_for_string_to_be_palindrome(const std::string& str, int** dp_matrix/*default: NULL*/) {
	if(str.empty() || str.size() == 1 || (str.size() == 2 && str[0] == str[1])) {
		return 0;
	}

	int res = 0;
	const int len = str.size();
	int **dp = CU::get_matrix(len, len);

	// dp[i][j] means add how many chars to str[i..j] to make it as a palindrome
	for(int j = 0; j < len; j++) {
		dp[j][j] = 0;
		for(int i = j - 1; i > -1; i--) {
			if(i == j - 1) {
				dp[i][j] = str[i] == str[j] ? 0 : 1;
			} else {
				if(str[i] == str[j]) {
					dp[i][j] = dp[i + 1][j - 1];
				} else {
					dp[i][j] = std::min(dp[i + 1][j], dp[i][j - 1]) + 1;
				}
			}
		}
	}

	if(dp_matrix) {
		CU::copy_matrix(dp, dp_matrix, len, len);
	}

	res = dp[0][len - 1];

	CU::free_matrix(dp, len, len);
	return res;
}

std::string get_palindrome_adding_min_chars(const std::string& str) {
	if(str.empty() || str.size() == 1 || (str.size() == 2 && str[0] == str[1])) {
		return str;
	}

	const int len = str.size();
	int** dp = CU::get_matrix(len, len);

	int min_chars = min_char_number_added_for_string_to_be_palindrome(str, dp);
	int tlength = min_chars + len;

	std::string res(tlength, '\0');
	int left = 0;
	int right = tlength - 1;
	for(int i = 0, j = len - 1; i <= j; ) {
		if(str[i] == str[j]) {
			res[left++] = str[i++];
			res[right--] = str[j--];
		} else {
			if(dp[i + 1][j] < dp[i][j - 1]) {
				res[left++] = str[i];
				res[right--] = str[i++];
			} else {
				res[left++] = str[j];
				res[right--] = str[j--];
			}
		}
	}

	return res;
}

// --------------------------------------------------------------------------------------------------------------
// 5.14 String of parentheses
// (1) Judge if it is a valid string of parentheses
// (2) Get the max length of valid sub-string of parentheses string

// (1) Judge if it is a valid string of parentheses
bool is_valid_parentheses_string(const std::string& str) {
	if(str.empty() || str.size() % 2 != 0) {
		return false;
	}

	const int len = str.size();
	int cnt = 0;
	for(int i = 0; i < len; i++) {
		if(str[i] == '(') {
			cnt++;
		} else if(str[i] == ')') {
			cnt--;
			if(cnt < 0) {
				return false;
			}
		} else { // str[i] != '(' && str[i] != ')'
			return false;
		}
	}

	return cnt == 0;
}

// (2) Get the max length of valid sub-string of parentheses string
// DP method
// dp[i], 0 <= i <= length(str)
// dp[i] represents the max length of valid parentheses sub-string for str[0..i](str[i] as the last one char of this substring)
int max_length_of_valid_parentheses_substring(const std::string& str) {
	int res = 0;

	if(str.empty()) {
		return res;
	}

	const int len = str.size();
	int *dp = new int[len];
	memset(dp, 0, sizeof(int) * len);
	dp[0] = 0;
	int pos = 0;

	for(int i = 1; i < len; i++) {
		assert(str[i] == '(' || str[i] == ')');
		if(str[i] == '(') {
			dp[i] = 0;
		} else { // str[i] == ')'
			// max_len = dp[i - 1]
			// => pos - pre + 1= max_len + 1 + 1
			// => pre = pos - max_len - 1
			int pre = i - dp[i - 1] - 1;
			if(pre >= 0 && str[pre] == '(') {
				dp[i] = dp[i - 1] + 2;
				if(pre > 0 && str[pre - 1] == ')') {
					dp[i] += dp[pre - 1];
				}
			}
			if(dp[i] > res) {
				pos = i;
			}
			res = std::max(res, dp[i]);
		}
	}

	printf("Original string is: %s\n", str.c_str());
	printf("Max valid parentheses sub-string length is: %d\n", res);
	printf("Last char position of this sub-string is %d (starting from 0)\n", pos);
	printf("Result string is %s\n", std::string(str.begin() + pos + 1 - res, str.begin() + pos + 1).c_str());

	delete [] dp;
	return res;
}

// --------------------------------------------------------------------------------------------------------------
// 5.15 Get the value of a formula string
// Assume the formula string is valid
// Operator contains only +, -, * and / four types

void add_num(std::deque<std::string>& deq, int num) {
	if(!deq.empty()) {
		const std::string& s = deq.back();
		if(s == "+" || s == "-") {
			; // do nothing
		} else { // s == "*" || s == "/"
			std::string ss(deq.back());
			deq.pop_back();
			std::string sn(deq.back());
			deq.pop_back();
			int snn = boost::lexical_cast<int>(sn);
			num = (ss == "*") ? snn * num : snn / num;
		}
	}
	deq.push_back(boost::lexical_cast<std::string>(num));
}

int get_num(std::deque<std::string>& deq) {
	bool add_minus = true;
	int sum = 0;
	while(!deq.empty()) {
		const std::string& s = deq.front();
		if(s == "+") {
			add_minus = true;
		} else if(s == "-") {
			add_minus = false;
		} else {
			sum = add_minus ? sum + boost::lexical_cast<int>(s) : sum - boost::lexical_cast<int>(s);
		}
		deq.pop_front();
	}

	return sum;
}

std::pair<int, int> get_formula_string_value(const std::string& str, const int start) {
	std::pair<int, int> res;
	if(str.empty()) {
		printf("Empty string\n");
		return res;
	}

	const int len = str.size();
	int pre_num = 0;
	std::deque<std::string> deq;
	int i = start;
	while(i < len) {
		if(str[i] == ')') {
			break;
		}
		int v = str[i] - '0';
		if(v >= 0 && v <= 9) {
			pre_num = pre_num * 10 + v;
			i++;
		} else if(str[i] != '(') { // Operators: + - * /
			add_num(deq, pre_num);
			deq.push_back(std::string(1, str[i]));
			pre_num = 0;
			i++;
		} else { // str[i] == '('
			res = get_formula_string_value(str, i + 1);
			pre_num = res.first;
			i = res.second + 1;
		}
	}

	add_num(deq, pre_num);
	res.first = get_num(deq);
	res.second = i;

	return res;
}

// [TIME_STAMP] Stop at 00:08, 2017/12/02


// [TIME_STAMP] Start at 13:29, 2017/12/03
// --------------------------------------------------------------------------------------------------------------
// 5.16 Number of strings which must have 1 before 0(1 is on the left of 0) for its binary value
// Speicify an integer N, there are 2^N strings consist of 0 and 1.
// Get the number of those strings which 1 must be in front of each 0

// DP method
// dp[i] means in condition that str[0..i-1] is determined(and str[i-1] == '1') and statisfies the conditions
// how many strings statisfy the condition
// i.e. the number of strings consist of str[i...N-1]
// So the result to get is dp[1], since str[0] must be 1
// dp[N] = 1
// dp[N-1] = 2
// dp[N-2] = 3
int total_string_number_one_before_zero(const int n) {
	if(n < 0) {
		return 0;
	}
	if(n == 1 || n == 2) {
		return n;
	}
	int *dp = new int[n + 1];
	dp[n] = 1;
	dp[n - 1] = 2;
	for(int i = n - 2; i > -1; i--) {
		dp[i] = dp[i + 1] + dp[i + 2];
	}

	return dp[1];
}

// Or use space saving DP method
int total_string_number_one_before_zero_space_saving(const int n) {
	int next = 2;
	int nnext = 1;
	int res = 0;
	// get dp[1] not dp[0]
	for(int i = 1; i < n - 1; i++) {
		res = next + nnext;
		nnext = next;
		next = res;
	}

	return res;
}

// --------------------------------------------------------------------------------------------------------------
// 5.17 Concatenate a string array(vector) to get a final string which has min dict value

bool scompare_f(const std::string& s1, const std::string& s2) {
	return s1 + s2 < s2 + s2;
}

const std::string concatenate_strings_min_dict_value(const std::vector<std::string>& svec) {
	std::string res;
	std::vector<std::string> sv(svec);
	std::sort(sv.begin(), sv.end(), scompare_f);
	BOOST_FOREACH(const std::string& s, sv) {
		res.append(s);
	}

	return res;
}

// --------------------------------------------------------------------------------------------------------------
// 5.18 Find the longest substring without replication of characters

// DP method to resolve
// pre - This substring without duplication and ends with str[i-1](last char is str[i-1]), starting from position: pre + 1
//       i.e. substring is str[pre+1...i-1] has no duplication

const int max_substring_without_duplication(const std::string& str) {
	if(str.empty() || str.size() == 1) {
		return str.size();
	}

	int pre = -1;
	int res = 0;
	std::map<char, int> imap; // the char and its latest index/position
	const int len = str.size();
	for(int i = 0; i < len; i++) {
		const char& c = str[i];
		std::map<char, int>::iterator ii(imap.find(c));
		if(ii != imap.end()) {
			int last = ii->second;
			if(last <= pre) {
				res = std::max(res, i - pre);
			} else {
				res = std::max(res, i - last);
				pre = last;
			}
			imap[c] = i;
		} else {
			// str[pre+1..i-1] + str[i]
			imap[c] = i;
			res = std::max(res, i - pre);
		}
	}

	return res;
}


// --------------------------------------------------------------------------------------------------------------
// 5.19 Get the new type of character specified at position K in a string consists of new types of chars
// Assume the string consists of correct chars of new types
// Valid char type:
//	(1) 1 char or 2 chars
//	(2) a single lower case; upper case + lower case; upper case + upper case

const std::string new_type_char_at_position(const std::string& str, const int k) {
	if(str.empty() || k < 0 || k >= (int)str.size()) {
		return "";
	}

	std::string res;
	int upper_case_count = 0;
	for(int i = k - 1; i > -1; i--) {
		if(str[i] >= 'a' && str[i] <= 'z') {
			break;
		}
		upper_case_count++;
	}

	if(upper_case_count % 2 == 0) {
		if(str[k] >= 'a' && str[k] <= 'z') {
			return std::string(1, str[k]);
		} else { // upper cases
			return std::string(str.begin() + k, str.begin() + k + 1 + 1); // [first, last)
		}
	} else {
		return std::string(str.begin() + k - 1, str.begin() + k + 1); // [first, last)
	}

	return res;
}

// --------------------------------------------------------------------------------------------------------------
// 5.20 The shortest substring in string A, which contains all chars in string B
// The order of all the chars of string B in A is not required

int shortest_substring_containing_another_string(const std::string& str1, const std::string str2) {
	if(str1.empty() || str2.empty() || str1.size() < str2.size()) {
		return 0;
	}

	int res = INT_MAX;

	int left = 0;
	int right = 0;
	std::map<char, int> smap;
	BOOST_FOREACH(const char& c, str2) {
		if(smap.find(c) != smap.end()) {
			smap[c]++;
		} else {
			smap[c] = 1;
		}
	}

	const int len = str1.size();
	int count = str2.size();
	while(right < len + 1) { // Just let the last one to be calculated, so use 'len+1' instead of 'len'
		if(count == 0) {
#if 0
			// debug use
			printf("All chars in str2 are found\n");
			typedef std::pair<char, int> cpair;
			BOOST_FOREACH(const cpair& cp, smap) {
				printf("(%c, %d)\n", cp.first, cp.second);
			}
#endif // 0
			while(1) {
				const char& c = str1[left];
				if(smap.find(c) != smap.end()) {
					// int debug_cur_num = smap[c];
					smap[c]++;
					if(smap[c] > 0) {
						count = 1;
						res = std::min(res, right - left + 1 - 1); // Caution: now 'right' has already moved to the next unhandled char
						left++;
						break;
					}
				}
				left++;
			}
		}

		// Just let the last one to be calculated
		if(right >= len) {
			break;
		}
		if(smap.find(str1[right]) != smap.end()) {
			if(smap[str1[right]] > 0) {
				count--;
			}
			smap[str1[right]]--;
		}
		right++;
	}

	return res == INT_MAX ? 0 : res;
}


// --------------------------------------------------------------------------------------------------------------
// 5.21 Palindrome partitioning
// Get minimum times to partition a string to make all partitions are palindrome
// DP method
// dp[i] means how many time to partition a string str[i...N-1], N is length(str)
// dp[0] is what we want
// For each j (i <= j <= N-1), if str[i..j] is palindrome, then dp[i] could be dp[j+1] + 1
//		which means partition str[i..j] and str[j+1...N-1], and do partition in str[j+1...N-1]
// Traverse j from i to N-1 (i <= j <= N-1) and get min value
//		dp[i] = MIN{dp[j+1] + 1 && str[i..j] is palindrome}, i <= j <= N-1

int palindrome_partition(const std::string& str) {
	if(str.empty() || str.size() == 1 || (str.size() == 2 && str[0] == str[1])) {
		return 0;
	}

	int res = 0;

	const int len = str.size();
	int *dp = new int[len + 1];
	memset(dp, 0, sizeof(int) * len);
	dp[len] = -1;
	// dp[len - 1] = 0;
	// dp[len - 2] = str[len - 1] == str[len - 2] ? 0 : 1;

	// p[i][j] means if str[i..j] is palindrome(true) or not(false)
	int **p = CU::get_matrix(len, len);
	for(int k = 0; k < len; k++) {
		memset(p[k], 0, sizeof(int) * len);
	}

	for(int i = len - 1; i > -1; i--) {
		dp[i] = INT_MAX;
		for(int j = i; j < len; j++) {
			if(j == i || (j - i == 1 && str[i] == str[j]) || (str[i] == str[j] && p[i+1][j-1]) ) {
				p[i][j] = 1;
				dp[i] = std::min(dp[i], dp[j+1] + 1); // Since here j+1 might be 'len' long, so dp has to be size of 'len+1'
			}
		}
	}

	res = dp[0];
	delete [] dp;
	CU::free_matrix(p, len, len);

	return res;
}

// --------------------------------------------------------------------------------------------------------------
// 5.22 String match
// Skipped


// [TIME_STAMP] Stop at 18:02, 2017/12/03





// [TIME_STAMP] Start at 21:17 2017/12/04
// --------------------------------------------------------------------------------------------------------------
// 5.23 Lexicographic tree
// Assume all chars are: a~z

// class TrieNode {
// public:
// 	TrieNode();
// 	~TrieNode() { if(m_map) delete [] m_map; }
// 
// public:
// 	int m_share_cnt;
// 	int m_end;
// 	TrieNode* *m_map;
// };
// 
// TrieNode::
// TrieNode() : m_share_cnt(0), m_end(0), m_map(NULL) {
// 	m_map = new TrieNode*[26]; // assumption that all chars are a~z
// 	memset(m_map, 0, sizeof(int) * 26);
// }
// 
// class Trie {
// public:
// 	Trie() {
// 		// Actually m_root has:
// 		// 0 m_share_cnt, since it represents no char
// 		// 0 m_end, since no word ends at it
// 		// Several pointers pointing to different TrieNodes
// 		m_root = get_trie_node();
// 	}
// 	~Trie() { free_all_nodes(); }
// 
// public:
// 	void insert(const std::string& str);
// 	void remove(const std::string& str);
// 	bool search(const std::string& str);
// 	int prefix_number(const std::string& pre);
// 
// private:
// 	TrieNode* get_trie_node() {
// 		TrieNode *n = new TrieNode;
// 		m_collect.push_back(n);
// 		return n;
// 	}
// 	void free_all_nodes() {
// 		for(std::list<TrieNode*>::iterator itr = m_collect.begin(); itr != m_collect.end(); itr++) {
// 			TrieNode *p = *itr;
// 			if(p) {
// 				delete p;
// 				p = NULL;
// 			}
// 		}
// 		m_collect.clear();
// 	}
// 
// private:
// 	std::list<TrieNode*> m_collect;
// 
// private:
// 	TrieNode* m_root;
// };
// 
// 
// void Trie::
// insert(const std::string& str) {
// 	if(str.empty()) {
// 		return ;
// 	}
// 
// 	TrieNode *node = m_root;
// 	BOOST_FOREACH(const char& c, str) {
// 		int idx = c - 'a';
// 		if(!node->m_map[idx]) {
// 			TrieNode *nd = get_trie_node();
// 			node->m_map[idx] = nd;
// 		}
// 		node = node->m_map[idx];
// 		node->m_share_cnt++;
// 	}
// 	node->m_end++;
// }
// 
// void Trie::
// remove(const std::string& str) {
// 	if(str.empty() || !search(str) || !m_root) {
// 		return ;
// 	}
// 
// 	TrieNode *node = m_root;
// 	BOOST_FOREACH(const char& c, str) {
// 		int idx = c - 'a';
// 		TrieNode *nd = node->m_map[idx];
// 		assert(nd); // Since search(str) == true
// 		if(nd->m_share_cnt--) {
// 			node->m_map[idx] = NULL;
// 			return ;
// 		}
// 		node = nd;
// 	}
// 	node->m_end--;
// }
// 
// bool Trie::
// search(const std::string& str) {
// 	if(str.empty() || !m_root) {
// 		return false;
// 	}
// 
// 	TrieNode *node = m_root;
// 	BOOST_FOREACH(const char& c, str) {
// 		int idx = c - 'a';
// 		if(!node->m_map[idx]) {
// 			return false;
// 		}
// 		node = node->m_map[idx];
// 	}
// 
// 	return node->m_end > 0;
// }
// 
// int Trie::
// prefix_number(const std::string& pre) {
// 	if(pre.empty() || !m_root) {
// 		return false;
// 	}
// 
// 	TrieNode *node = m_root;
// 	BOOST_FOREACH(const char& c, pre) {
// 		int idx = c - 'a';
// 		if(!node->m_map[idx]) {
// 			return 0;
// 		}
// 		node = node->m_map[idx];
// 	}
// 
// 	return node->m_share_cnt;
// }

// [TIME_STAMP] Stop at 22:40, 2017/12/04



// [TIME_STAMP] Start at XX:XX, 2017/XX/XX
// [TIME_STAMP] Stop at XX:XX, 2017/XX/XX

// [TIME_STAMP] Start at XX:XX, 2017/XX/XX
// [TIME_STAMP] Stop at XX:XX, 2017/XX/XX

} // namespace C5








namespace C5 {

// [TIME_STAMP] Start at 12:31, 2017/11/26

// --------------------------------------------------------------------------------------------------------------
// 5.1 Judge if two words are anagrams
void test_5_1() {
	const std::string str1("ambulence");
	const std::string str2("banana");
	printf("If %s and %s are anagrams: %s\n", str1.c_str(), str2.c_str(), if_two_words_are_anagrams(str1, str2) ? "Yes" : "No");
}

void test_5_2() {
	const std::string str1("A1CD2E33");
	const std::string str2("A-1BC--12");
	const std::string str3("A-1B--2C--D6E");
	printf("Sum of string %s is: %d\n", str1.c_str(), total_digits_sum_in_string(str1));
	printf("Sum of string %s is: %d\n", str2.c_str(), total_digits_sum_in_string(str2));
	printf("Sum of string %s is: %d\n", str3.c_str(), total_digits_sum_in_string(str3));
}


void test_5_3() {
	const std::string str("A0B00C000D0000E00000");
	printf("Remove 1 '0' in %s: %s\n", str.c_str(), remove_k_0_in_string(str, 1).c_str());
	printf("Remove 2 '0' in %s: %s\n", str.c_str(), remove_k_0_in_string(str, 2).c_str());
	printf("Remove 3 '0' in %s: %s\n", str.c_str(), remove_k_0_in_string(str, 3).c_str());
	printf("Remove 4 '0' in %s: %s\n", str.c_str(), remove_k_0_in_string(str, 4).c_str());
	printf("Remove 5 '0' in %s: %s\n", str.c_str(), remove_k_0_in_string(str, 5).c_str());
}

void test_5_4() {
	const std::string str1("ambulance");
	const std::string str2("lanceambu");
	printf("'%s' is or not rotated from '%s': %s\n", str1.c_str(), str2.c_str(), is_rotated_word(str1, str2) ? "Yes" : "No");
}

void test_5_5() {
	std::string str1("12abcabca4");
	std::string str2("12abccabcababc4");
	std::string str3("12abcababc4");

	const std::string from("abc");
	const std::string to("xyz");

	std::cout << str1 << " => " << replace_repeated_strings(str1, from, to) << std::endl;
	std::cout << str2 << " => " << replace_repeated_strings(str2, from, to) << std::endl;
	std::cout << str3 << " => " << replace_repeated_strings(str3, from, to) << std::endl;

	// printf("%s\n", str.c_str()); if str contains '\0', won't work

}

void test_5_7_1() {
	// a_1_b_1_d_1_a_2_b_2_c_2_d_3_e_1_f_2_g_1
	std::string str1("abdaabbccdddeffg");
	std::cout << string_successive_char_statistics(str1) << std::endl;

	std::string str2("a");
	std::cout << string_successive_char_statistics(str2) << std::endl;

	std::string str3("aa");
	std::cout << string_successive_char_statistics(str3) << std::endl;

	std::string str4("ab");
	std::cout << string_successive_char_statistics(str4) << std::endl;
}

void test_5_7_2() {
	// a_1_b_1_d_1_a_2_b_2_c_2_d_3_e_1_f_2_g_1
	// abdaabbccdddeffg
	std::string str("a_1_b_1_d_1_a_2_b_2_c_2_d_3_e_1_f_2_g_1");
	// std::cout << "Position " << 14 << " = >" << find_char_in_string_statistics_by_order(str, 14) << std::endl;
	for(std::size_t pos = 1; pos < 20; pos++) {
		// printf("current position: %d, pos);
		std::cout << "Position " << pos << " = >" << find_char_in_string_statistics_by_order(str, pos) << std::endl;
	}

}

void test_5_8() {
	const int num = 4;
	std::string test_strings[4] = {"ambulance", "zxzxyayaefefpqqp", "next", "woman"};
	for(int i = 0; i < num; i++) {
		printf("String '%s' has repeated chars: %s\n", test_strings[i].c_str(),  if_any_char_appear_only_once_use_heap_sort(test_strings[i]) ? "Yes" : "No");
	}
}

void test_5_9() {

}


void test_5_10_1() {
	const int SIZE = 30;
	char chars1[SIZE] = {'a', ' ', 'b', ' ', 'c', ' ', 'd', ' ', 'e', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
	adjust_and_replace(chars1, SIZE, "XYZ");
	CU::print_char_array(chars1, SIZE);
}

void test_5_10_2() {
	const int SIZE = 30;
	char chars2[SIZE] = {'a', '*', 'b', '*', 'c', '*', 'd', '*', 'e', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
	move_all_star_chars_to_front(chars2, SIZE);
	CU::print_char_array(chars2, SIZE);
}


void test_5_11() {
	std::string str("Nice to meet you!");
	reverse_all_words_in_string(str);

	str = std::string("Today   is    a   good day, isn't    it?");
	reverse_all_words_in_string(str);
}

void test_5_12_1() {
	const int SIZE = 30;
	const std::string ss[] = {"spam", "ham", "eggs", "bread", "toast", "apple", "garlic", "watermelon", "butter", "oil", \
								"milk", "banana", "oil", "suggar", "garlic", "onion", "pepper", "salt", "tomato", "oil", \
								"pork", "beef", "lamb", "potato", "leek", "carrot", "garlic", "celery", "carp", "bean"};
	const std::string item1("oil");
	const std::string item2("garlic");
	const std::string item3("eggs");
	const std::string item4("potato");

	const int ITEM_SIZE = 6;
	const std::string items[ITEM_SIZE] = {"oil", "garlic", "eggs", "potato", "noodle", "lobster"};

	std::vector<std::string> svec(CU::convert_to_string_vector(ss, SIZE));

	for(int i = 0; i < ITEM_SIZE; i++) {
		for(int j = i + 1; j < ITEM_SIZE; j++) {
			int mdist = min_dist_two_strings_in_string_array(svec, items[i], items[j]);
			printf("The minimum distance between '%s' and '%s' is: %d\n", items[i].c_str(), items[j].c_str(), mdist);
		}
	}
}

void test_5_12_2() {
	const int SIZE = 30;
	const std::string ss[] = {"spam", "ham", "eggs", "bread", "toast", "apple", "garlic", "watermelon", "butter", "oil", \
								"milk", "banana", "oil", "suggar", "garlic", "onion", "pepper", "salt", "tomato", "oil", \
								"pork", "beef", "lamb", "potato", "leek", "carrot", "garlic", "celery", "carp", "bean"};
	const std::string item1("oil");
	const std::string item2("garlic");
	const std::string item3("eggs");
	const std::string item4("potato");

	const int ITEM_SIZE = 6;
	const std::string items[ITEM_SIZE] = {"oil", "garlic", "eggs", "potato", "noodle", "lobster"};

	std::vector<std::string> svec(CU::convert_to_string_vector(ss, SIZE));
	std::vector<std::pair<std::string, std::string> > qvec;
	for(int i = 0; i < ITEM_SIZE; i++) {
		for(int j = i + 1; j < ITEM_SIZE; j++) {
			qvec.push_back(std::make_pair(items[i], items[j]));
		}
	}
	std::vector<int> results;

	records_relation rds(svec);
	rds.query_min_distance(qvec, results);
	printf("\n");
	CU::print_int_vector(results);
}

void test_5_13() {
	std::string test_string("good");
	std::string pstring(get_palindrome_adding_min_chars(test_string));

	printf("Original string: \t%s\n", test_string.c_str());
	printf("Palindrome string: \t%s\n", pstring.c_str());

	test_string = "ambulance";
	pstring = get_palindrome_adding_min_chars(test_string);
	printf("Original string: \t%s\n", test_string.c_str());
	printf("Palindrome string: \t%s\n", pstring.c_str());

	printf("\n");
}

void test_5_14() {
	std::string test_string("(())(())()()((()()))");
	int max_valid_substring_length = max_length_of_valid_parentheses_substring(test_string);
	if(max_valid_substring_length < 0) {
		printf("Error!\n");
	}

	test_string = "(())(())()()(((())";
	max_valid_substring_length = max_length_of_valid_parentheses_substring(test_string);
	if(max_valid_substring_length < 0) {
		printf("Error!\n");
	}

	test_string = "())(())()()(((())";
	max_valid_substring_length = max_length_of_valid_parentheses_substring(test_string);
	if(max_valid_substring_length < 0) {
		printf("Error!\n");
	}
}

void test_5_15() {
	std::string test_string("9*(3+2)-1");
	std::pair<int, int> res(get_formula_string_value(test_string, 0));
	printf("The result of '%s' is: %d\n", test_string.c_str(), res.first);

	test_string = "30+1+2*9";
	res = get_formula_string_value(test_string, 0);
	printf("The result of '%s' is: %d\n", test_string.c_str(), res.first);

	test_string = "30+(1+2)*9";
	res = get_formula_string_value(test_string, 0);
	printf("The result of '%s' is: %d\n", test_string.c_str(), res.first);

	test_string = "30+(2-1)*9";
	res = get_formula_string_value(test_string, 0);
	printf("The result of '%s' is: %d\n", test_string.c_str(), res.first);
}

void test_5_16() {
	int test_num = 10;
	printf("(n=%d)Total string number satisfying 1 at the left of 0: %d\n", test_num, total_string_number_one_before_zero(test_num));
	printf("(n=%d)Total string number satisfying 1 at the left of 0: %d\n", test_num, total_string_number_one_before_zero_space_saving(test_num));

	 test_num = 3;
	 printf("(n=%d)Total string number satisfying 1 at the left of 0: %d\n", test_num, total_string_number_one_before_zero(test_num));
	 printf("(n=%d)Total string number satisfying 1 at the left of 0: %d\n", test_num, total_string_number_one_before_zero_space_saving(test_num));
}

void test_5_17() {
	const int SIZE = 2;
	const std::string ss1[] = {"abc", "de"};
	const std::string ss2[] = {"b", "ba"};

	std::vector<std::string> svec1(CU::convert_to_string_vector(ss1, SIZE));
	printf("ss1 after concatenation: %s\n", concatenate_strings_min_dict_value(svec1).c_str());

	std::vector<std::string> svec2(CU::convert_to_string_vector(ss2, SIZE));
	printf("ss2 after concatenation: %s\n", concatenate_strings_min_dict_value(svec2).c_str());
}


void test_5_18() {
	std::string test_string("abcd");
	printf("The max length of substring without duplication for string %s is: %d\n", test_string.c_str(), max_substring_without_duplication(test_string));

	test_string = "aabcb";
	printf("The max length of substring without duplication for string %s is: %d\n", test_string.c_str(), max_substring_without_duplication(test_string));

}

void test_5_19() {
	std::string test_string("aaABCDEcBCg");
	int k = 7;
	printf("String is '%s', new type char at position %d is: %s\n", test_string.c_str(), k, new_type_char_at_position(test_string, k).c_str());

	k = 4;
	printf("String is '%s', new type char at position %d is: %s\n", test_string.c_str(), k, new_type_char_at_position(test_string, k).c_str());

	k = 10;
	printf("String is '%s', new type char at position %d is: %s\n", test_string.c_str(), k, new_type_char_at_position(test_string, k).c_str());
}

void test_5_20() {
	std::string str1("abcde");
	std::string str2("ac");
	printf("Shorteset length of substring in str1('%s') containing all chars in str2('%s') is: %d\n", str1.c_str(), str2.c_str(), shortest_substring_containing_another_string(str1, str2));

	str1 = "12345";
	str2 = "344";
	printf("Shorteset length of substring in str1('%s') containing all chars in str2('%s') is: %d\n", str1.c_str(), str2.c_str(), shortest_substring_containing_another_string(str1, str2));


	str1 = "acbfhcdefgfh";
	str2 = "cf";
	printf("Shorteset length of substring in str1('%s') containing all chars in str2('%s') is: %d\n", str1.c_str(), str2.c_str(), shortest_substring_containing_another_string(str1, str2));

	str1 = "cccacmkgdfeeeckf";
	str2 = "cf";
	printf("Shorteset length of substring in str1('%s') containing all chars in str2('%s') is: %d\n", str1.c_str(), str2.c_str(), shortest_substring_containing_another_string(str1, str2));

}

void test_5_21() {
	std::string test_string("ABA");
	printf("The min palindrome-paritioning times for string '%s' is: %d\n", test_string.c_str(), palindrome_partition(test_string));

	test_string = "ACDCDCDAD";
	printf("The min palindrome-paritioning times for string '%s' is: %d\n", test_string.c_str(), palindrome_partition(test_string));
}

void test_5_23() {
	Trie* a_trie = new Trie;

	a_trie->insert("abc");
	a_trie->insert("abcd");
	a_trie->insert("abd");
	a_trie->insert("b");
	a_trie->insert("bcd");
	a_trie->insert("efg");
	a_trie->insert("hik");

	std::string str("abc");
	printf("If '%s' exists in the trie: %s\n", str.c_str(), a_trie->search(str) ? "Yes" : "No");
	str = "k";
	printf("If '%s' exists in the trie: %s\n", str.c_str(), a_trie->search(str) ? "Yes" : "No");
	str = "hig";
	printf("If '%s' exists in the trie: %s\n", str.c_str(), a_trie->search(str) ? "Yes" : "No");
	str = "efg";
	printf("If '%s' exists in the trie: %s\n", str.c_str(), a_trie->search(str) ? "Yes" : "No");

	printf("Remove '%s' from trie...\n", str.c_str());
	a_trie->remove(str);
	printf("If '%s' exists in the trie: %s\n", str.c_str(), a_trie->search(str) ? "Yes" : "No");

	delete a_trie;
}

void test_5_all() {
	test_5_1();
	test_5_2();
	test_5_3();
	test_5_4();
	test_5_5();
	// test_5_6();
	test_5_7_1();
	test_5_7_2();
	test_5_8();
	test_5_9();
	test_5_10_1();
	test_5_10_1();
	test_5_11();
	test_5_12_1();
	test_5_12_2();
	test_5_13();
	test_5_14();
	test_5_15();
	test_5_16();
	test_5_17();
	test_5_18();
	test_5_19();
	test_5_20();
	test_5_21();
	// test_5_22();
	test_5_23();
}


// [TIME_STAMP] Stop at

} // namespace C5








































