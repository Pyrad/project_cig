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
#include <algorithm>
#include <assert.h>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <utility>


#include "common_utils.hpp"


namespace C8 {

// [TIME_STAMP] Start at 20:54 2017/10/03

// --------------------------------------------------------------------------------------------------------------
// 8.11 The longest sub-array in an unordered array of a certain sum
// Solution,
// Assume S(i) = Sum[0...i], so if K=S(i)-S(j), then Sum[j+1,...,i] = K, that's what we want

int longest_subarray_of_a_certain_sum(const std::vector<int>& ivec, const int k) {
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

} // namespace C8



#endif /* CHAPTER_8_HPP_ */
