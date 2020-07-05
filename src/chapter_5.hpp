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
#include <boost/lexical_cast.hpp>

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
#include <algorithm>

#include "common_utils.hpp"

namespace C5 {

namespace CU = common_utils;




// [TIME_STAMP] Start at 12:31, 2017/11/26

// --------------------------------------------------------------------------------------------------------------
// 5.1 Judge if two words are anagrams

bool if_two_words_are_anagrams(const std::string& str1, const std::string& str2);


// --------------------------------------------------------------------------------------------------------------
// 5.2 Get total sum of digits(as characters) in a string
int total_digits_sum_in_string(const std::string& str);

// --------------------------------------------------------------------------------------------------------------
// 5.3 Remove successive K characters of '0' in a string

const std::string remove_k_0_in_string(const std::string& str, int k);


// --------------------------------------------------------------------------------------------------------------
// 5.4 If 2 words are rotated words

bool is_rotated_word(const std::string& str1, const std::string& str2);

// --------------------------------------------------------------------------------------------------------------
// 5.5 Convert a string to integer if it is valid

bool check_is_string_valid_integer(const std::string& str);

const int convert_string_to_integer(const std::string& str);

// --------------------------------------------------------------------------------------------------------------
// 5.6 Replace repeated strings in a string

const std::string replace_repeated_strings(std::string& str, const std::string& from, const std::string& to);


// --------------------------------------------------------------------------------------------------------------
// 5.7 Character statistics in a string

const std::string string_successive_char_statistics(const std::string& str);

const std::string find_char_in_string_statistics_by_order(const std::string& str, const int kth);

// [TIME_STAMP] Stop at 18:02, 2017/11/26



// [TIME_STAMP] Start at 19:32, 2017/11/27

// --------------------------------------------------------------------------------------------------------------
// 5.8 If any char in a string appear only once
//	(1) Use a map, O(N)
//	(2) Don't use map, O(NlogN)

// (1) Use a map, O(N)
bool if_any_char_appear_only_once(const std::string& str);

// (2) Don't use map, use heap sort, O(NlogN)

void swap(char* a, char* b);

void filter_up(char* chars, const int csize, int k);

void filter_down(char* chars, const int csize, int k);

bool if_repeat_char_in_array(const char* chars, const int size);

bool if_any_char_appear_only_once_use_heap_sort(const std::string& str);


// --------------------------------------------------------------------------------------------------------------
// 5.9 Find the left most position in an ordered string array(array of some strings) which may contain null character

const int left_most_position_in_string_array(const std::vector<std::string>& svec, const std::string& str);

// [TIME_STAMP] Stop at 22:54 2017/11/27


// [TIME_STAMP] Start at 20:25, 2017/11/28

// --------------------------------------------------------------------------------------------------------------
// 5.10 Adjust string and replace with specified characters
// There's a char array. The right part are all '\0' and left part doesn't contain '\0'
// Replace the space character in the left part and adjust the string

// (1) Replace all space characters
void adjust_and_replace(char* chars, const int size, const std::string& str);

// (2) Move all star charactes to the front of the char array
void move_all_star_chars_to_front(char* chars, const int size);


// --------------------------------------------------------------------------------------------------------------
// 5.11 Reverse all the words in a string
// No requirements for the empty chars and punctuations

void reverse_char_array(char* chars, int start, int end);

void reverse_all_words_in_string(const std::string& str);

// --------------------------------------------------------------------------------------------------------------
// 5.12 The minimum distance of 2 strings in a string array(array of strings)
// (1) Query only once
// (2) Query many times

// (1) Query only once
int min_dist_two_strings_in_string_array(const std::vector<std::string>& svec, const std::string& str1, const std::string& str2);

// (2) Query many times
class records_relation {
public:
	records_relation(const std::vector<std::string>& strs) { init(strs); }
	~records_relation() { m_records.clear(); }
public:
	void query_min_distance(const std::vector<std::pair<std::string, std::string> >& strs, std::vector<int>& res);
	int query_min_distance(const std::string& str1, const std::string& str2);
private:
	void init(const std::vector<std::string>& strs);
	void update(const std::string& str, std::map<std::string, int>& idxmap, int cur_index);
private:
	std::map<std::string, std::map<std::string, int> > m_records;
};

void records_relation::
update(const std::string& str, std::map<std::string, int>& idxmap, int cur_index) {
	if(m_records.find(str) == m_records.end()) {
		std::map<std::string, int> m;
		m_records.insert(std::make_pair(str, m));
	}
	// typedef std::pair<std::string, std::map<std::string, int> > vpair;
	std::map<std::string, std::map<std::string, int> >::iterator itr(m_records.find(str));
	typedef std::pair<std::string, int> mpair;
	BOOST_FOREACH(const mpair& kv, idxmap) {
		const std::string& s = kv.first;
		int pos = kv.second;
		if(s != str) {
			if(m_records.find(s)== m_records.end()) {
				std::map<std::string, int> m;
				m_records.insert(std::make_pair(s, m));
			}
			std::map<std::string, std::map<std::string, int> >::iterator ii(m_records.find(s));
			int cur_dist = cur_index - pos;
			std::map<std::string, int>::iterator j = itr->second.find(s);
			if(j != itr->second.end()) {
				int min_dist = j->second;
				if(cur_dist < min_dist) {
					(itr->second)[s] = cur_dist;
					(ii->second)[str] = cur_dist;
				}
			} else {
				(itr->second)[s] = cur_dist;
				(ii->second)[str] = cur_dist;
			}
		}
	}
}

void records_relation::
init(const std::vector<std::string>& strs) {
	std::map<std::string, int> nearest_index_map;
	const int len = strs.size();
	for(int i = 0; i < len; i++) {
		const std::string& s = strs[i];
		update(s, nearest_index_map, i);
		nearest_index_map[s] = i; // update each string's latest index
	}
}

int records_relation::
query_min_distance(const std::string& str1, const std::string& str2) {
	if(str1.empty() || str2.empty()) {
		return -1;
	}

	if(str1 == str2) {
		return 0;
	}

	std::map<std::string, std::map<std::string, int> >::iterator itr(m_records.find(str1));
	if(itr != m_records.end()) {
		std::map<std::string, int>::iterator ii(itr->second.find(str2));
		if(ii != itr->second.end()) {
			return ii->second;
		}
	}

	return -1;
}

void records_relation::
query_min_distance(const std::vector<std::pair<std::string, std::string> >& strs, std::vector<int>& res) {
	typedef std::pair<std::string, std::string> spair;
	res.clear();
	BOOST_FOREACH(const spair& sp, strs) {
		res.push_back(query_min_distance(sp.first, sp.second));
	}
}
// [TIME_STAMP] Stop at 22:23, 2017/11/28



// [TIME_STAMP] Start at 21:49, 2017/12/02
// --------------------------------------------------------------------------------------------------------------
// 5.13 Add minimum characters to make a string as palindrome
// First get the minimum number
// Secondly, get a result string(any one of possible results)

// Use DP(Dyanmic Programming) method
int min_char_number_added_for_string_to_be_palindrome(const std::string& str, int** dp_matrix = NULL);

std::string get_palindrome_adding_min_chars(const std::string& str);

// --------------------------------------------------------------------------------------------------------------
// 5.14 String of parentheses
// (1) Judge if it is a valid string of parentheses
// (2) Get the max length of valid sub-string of parentheses string

// (1) Judge if it is a valid string of parentheses
bool is_valid_parentheses_string(const std::string& str);

// (2) Get the max length of valid sub-string of parentheses string
// DP method
// dp[i], 0 <= i <= length(str)
// dp[i] represents the max length of valid parentheses sub-string for str[0..i](str[i] as the last one char of this substring)
int max_length_of_valid_parentheses_substring(const std::string& str);

// --------------------------------------------------------------------------------------------------------------
// 5.15 Get the value of a formula string
// Assume the formula string is valid
// Operator contains only +, -, * and / four types

void add_num(std::deque<std::string>& deq, int num);

int get_num(std::deque<std::string>& deq);

std::pair<int, int> get_formula_string_value(const std::string& str, const int start);

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
int total_string_number_one_before_zero(const int n);

// Or use space saving DP method
int total_string_number_one_before_zero_space_saving(const int n);

// --------------------------------------------------------------------------------------------------------------
// 5.17 Concatenate a string array(vector) to get a final string which has min dict value

bool scompare_f(const std::string& s1, const std::string& s2);

const std::string concatenate_strings_min_dict_value(const std::vector<std::string>& svec);

// --------------------------------------------------------------------------------------------------------------
// 5.18 Find the longest substring without replication of characters

// DP method to resolve
// pre - This substring without duplication and ends with str[i-1](last char is str[i-1]), starting from position: pre + 1
//       i.e. substring is str[pre+1...i-1] has no duplication

const int max_substring_without_duplication(const std::string& str);


// --------------------------------------------------------------------------------------------------------------
// 5.19 Get the new type of character specified at position K in a string consists of new types of chars
// Assume the string consists of correct chars of new types
// Valid char type:
//	(1) 1 char or 2 chars
//	(2) a single lower case; upper case + lower case; upper case + upper case

const std::string new_type_char_at_position(const std::string& str, const int k);

// --------------------------------------------------------------------------------------------------------------
// 5.20 The shortest substring in string A, which contains all chars in string B
// The order of all the chars of string B in A is not required

int shortest_substring_containing_another_string(const std::string& str1, const std::string str2);


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

int palindrome_partition(const std::string& str);

// --------------------------------------------------------------------------------------------------------------
// 5.22 String match
// Skipped


// [TIME_STAMP] Stop at 18:02, 2017/12/03





// [TIME_STAMP] Start at 21:17 2017/12/04
// --------------------------------------------------------------------------------------------------------------
// 5.23 Lexicographic tree
// Assume all chars are: a~z

class TrieNode {
public:
	TrieNode();
	~TrieNode() { if(m_map) delete [] m_map; }

public:
	int m_share_cnt;
	int m_end;
	TrieNode* *m_map;
};

TrieNode::
TrieNode() : m_share_cnt(0), m_end(0), m_map(NULL) {
	m_map = new TrieNode*[26]; // assumption that all chars are a~z
	memset(m_map, 0, sizeof(int) * 26);
}

class Trie {
public:
	Trie() {
		// Actually m_root has:
		// 0 m_share_cnt, since it represents no char
		// 0 m_end, since no word ends at it
		// Several pointers pointing to different TrieNodes
		m_root = get_trie_node();
	}
	~Trie() { free_all_nodes(); }

public:
	void insert(const std::string& str);
	void remove(const std::string& str);
	bool search(const std::string& str);
	int prefix_number(const std::string& pre);

private:
	TrieNode* get_trie_node() {
		TrieNode *n = new TrieNode;
		m_collect.push_back(n);
		return n;
	}
	void free_all_nodes() {
		for(std::list<TrieNode*>::iterator itr = m_collect.begin(); itr != m_collect.end(); itr++) {
			TrieNode *p = *itr;
			if(p) {
				delete p;
				p = NULL;
			}
		}
		m_collect.clear();
	}

private:
	std::list<TrieNode*> m_collect;

private:
	TrieNode* m_root;
};


void Trie::
insert(const std::string& str) {
	if(str.empty()) {
		return ;
	}

	TrieNode *node = m_root;
	BOOST_FOREACH(const char& c, str) {
		int idx = c - 'a';
		if(!node->m_map[idx]) {
			TrieNode *nd = get_trie_node();
			node->m_map[idx] = nd;
		}
		node = node->m_map[idx];
		node->m_share_cnt++;
	}
	node->m_end++;
}

void Trie::
remove(const std::string& str) {
	if(str.empty() || !search(str) || !m_root) {
		return ;
	}

	TrieNode *node = m_root;
	BOOST_FOREACH(const char& c, str) {
		int idx = c - 'a';
		TrieNode *nd = node->m_map[idx];
		assert(nd); // Since search(str) == true
		if(nd->m_share_cnt--) {
			node->m_map[idx] = NULL;
			return ;
		}
		node = nd;
	}
	node->m_end--;
}

bool Trie::
search(const std::string& str) {
	if(str.empty() || !m_root) {
		return false;
	}

	TrieNode *node = m_root;
	BOOST_FOREACH(const char& c, str) {
		int idx = c - 'a';
		if(!node->m_map[idx]) {
			return false;
		}
		node = node->m_map[idx];
	}

	return node->m_end > 0;
}

int Trie::
prefix_number(const std::string& pre) {
	if(pre.empty() || !m_root) {
		return false;
	}

	TrieNode *node = m_root;
	BOOST_FOREACH(const char& c, pre) {
		int idx = c - 'a';
		if(!node->m_map[idx]) {
			return 0;
		}
		node = node->m_map[idx];
	}

	return node->m_share_cnt;
}

// [TIME_STAMP] Stop at 22:40, 2017/12/04



// [TIME_STAMP] Start at XX:XX, 2017/XX/XX
// [TIME_STAMP] Stop at XX:XX, 2017/XX/XX

// [TIME_STAMP] Start at XX:XX, 2017/XX/XX
// [TIME_STAMP] Stop at XX:XX, 2017/XX/XX




} // namespace C5


#endif /* CHAPTER_5_HPP_ */
