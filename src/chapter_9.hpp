/*
 * chapter_9.hpp
 *
 *  Created on: Dec. 30, 2017
 *      Author: Pyrad
 * Description: Header file of chapter 9
 *   Intention: Solutions for problems in Chapter 9 of Code Interview Guide
 */

#ifndef CHAPTER_9_HPP_
#define CHAPTER_9_HPP_

#include <stdio.h>
#include <limits.h>
#include <memory.h>
#include <stdlib.h> // for rand()
#include <math.h> // for sqrt, power

#include <algorithm>
#include <assert.h>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <utility>
#include <vector>
#include <numeric>

// Boost libraries
#include <boost/foreach.hpp>
#include <boost/smart_ptr.hpp>

#include "common_utils.hpp"


namespace C9 {

namespace CU = common_utils;


// [TIME_STAMP] Start at 11:32 2017/12/30

// --------------------------------------------------------------------------------------------------------------
// 9.1 Create a generator for 1~7 based on a random generator for 1~5
// Issue 1
//   Given a a random generator for 1~5, create a generator for 1~7
// Issue 2
//   Given a random generator which creates 0 by possibility 'p',
//   creates 1 by possibility '1-p'(0 < p < 1).
//   Get a random generator for 1~6 by equal possiblities
// Issue 3
//   Given a random generator for 1~M, create a generator for 1~N

// Issue 1
//   Given a a random generator for 1~5, create a generator for 1~7
int rand_1to5() {
	return CU::gen_random_int_1(1, 5);
}


// Solution to issue 1
// 1. Assume 'rdm' creates 1,2,3,4,5 randomly
// 2. So 'rdm - 1' creates 0,1,2,3,4 randomly
// 3. So '(rdm - 1) * 5' creates 0,5,10,15,20 randomly
// 4. So '(rdm - 1) * 5 + rdm - 1' creates 0 ~ 24 randomly
// 5. When creates 21~24, regenerate then random number
// 6. Modular by 7 --> '[(rdm - 1) * 5 + rdm - 1] % 7'
//    So it creates 0,1,2,3,4,5,6 randomly
// 7. Plus 1 --> '[(rdm - 1) * 5 + rdm - 1] % 7 + 1'
int rand_1to7_basedon_1to5() {
	int num = 0;
	do {
		num = (rand_1to5() - 1) * 5 + rand_1to5() - 1;
	} while(num > 20);
	return num % 7 + 1;
}



// Issue 2
//   Given a random generator which creates 0 by possibility 'p',
//   creates 1 by possibility '1-p'(0 < p < 1).
//   Get a random generator for 1~6 by equal possiblities
int rand01p() {
	double p = 0.83;
	return CU::gen_random_double_0to1() < p ? 0 : 1;
}

// Solution
// 1. Assume 'rdm' creates 0, 1 randomly by possiblity 'p' and '1-p'
// 2. So the possibility to create '01' and '10' are the same: p * (1 - p)
// 3. Create a generator based on the possiblity 'p * (1 - p)' to create 0 and 1, suppose its name is 'rdm01'
// 4. 'rdm01 * 2' generates 0, 2 randomly
// 5. 'rdm01 * 2 + rdm01' generates 0,1,2,3 randomly
// 6. '4 * (rdm01 * 2 + rdm01)' generates 0,4,8,12 randomly
// 7. '4 * (rdm01 * 2 + rdm01) + rdm01 * 2 + rdm01' generates 0~15 randomly
// 8. if generates 12~15, then regenerate it so its range is [0,1,..,11]
// 9. Modular 6 --> '[4 * (rdm01 * 2 + rdm01) + rdm01 * 2 + rdm01] % 6'
// 10. Plus 1

int equal_rand_01_basedon_rand01p() {
	int num = 0;
	do {
		num = rand01p();
	} while(num == rand01p());
	return num;
}


int rand_1to6_basedon_rand01p() {
	int (*fptr)();
	fptr = equal_rand_01_basedon_rand01p;
	int num = 0;
	do {
		num = 4 * (fptr() * 2 + fptr()) + fptr() * 2 + fptr();
	} while(num > 11);

	return num % 6 + 1;
}


// Issue 3
//   Given a random generator for 1~M, create a generator for 1~N
int gen_rand_1toM(const int m) {
	return CU::gen_random_int_1(1, m);
}


// Solution
#if 0
int gen_1toN_basedon_1toM(const int m, const int n) {
	int(*fp)(const int m);
	fp = gen_rand_1toM;
	if(m == n) {
		return fp(m);
	} else (m > n) {
		int num = 0;
		do {
			num = fp(m);
		} while(num > n);
		return num;
	} else { // m < n
		// (fp() - 1) * m
	}
}
#endif // 0


// Convert number 'n' to a number based on 'm'
boost::shared_array<int> getMSysNum(const int n, const int m) {
	boost::shared_array<int> res(new int[32]);
	for(int i = 0; i < 32; i++) {
		res[i] = 0;
	}

	int t = n;
	int idx = 31;
	while(t) {
		int r = t % m;
		res[idx--] = r;
		t /= m;
	}

	return res;
}

int getIntFromMSysNum(boost::shared_array<int> n, const int m) {
	int res = 0;

	int start = 0;
	while(n[start] == 0) {
		start++;
	}

	int idx = start;
	while(idx < 32) {
		res = res * m + n[idx];
		idx++;
	}

	return res;
}

boost::shared_array<int> getRandMSysNumLessN(boost::shared_array<int> n, const int m) {
	boost::shared_array<int> res(new int[32]);
	int start = 0;
	while(n[start] == 0) {
		start++;
	}

	int idx = start;
	bool isLess = false;
	while(idx < 32) {
		int numRandom = gen_rand_1toM(m) - 1;
		res[idx] = numRandom;
		if(!isLess) {
			if(numRandom > n[idx]) {
				idx = start;
				continue;
			} else if (numRandom == n[idx]) {
				isLess = false;
			} else { // numRandom < n[idx]
				isLess = true;
			}
		}
		idx++;
	}

	return res;
}

int gen_1toN_basedon_1toM(const int m, const int n) {
	boost::shared_array<int> n_msys = getMSysNum(n, m);
	boost::shared_array<int> rnum = getRandMSysNumLessN(n_msys, m);
	return getIntFromMSysNum(rnum, m);
}


// --------------------------------------------------------------------------------------------------------------
// 9.2 Great Common Divisor
// n = m * q + r

int gcd(int m, int n) {
	while(n) {
		int r = m % n;
		m = n;
		n = r;
	}

	return m;
}


// --------------------------------------------------------------------------------------------------------------
// 9.3 Given integer N, return the number of '0' at the end of 'N!'
// Issue 1: Given integer N, return the number of '0' at the end of 'N!'
// Issue 2: Return the right most position of 1 in the binary number of 'N!'

// Issue 1: Given integer N, return the number of '0' at the end of 'N!'
// Solution
// 10 is the product of factor 2 and 5
// In 1 ~ N, there are more '2' factors than '5' factors
// So the '0' numbers are determined by factor numbers of '5'

// Solution 1 to issue 1
int zero_number_at_end_of_N_factorial(const int n) {
	int res = 0;
	for(int i = 5; i <= n; i += 5) {
		int t = i;
		if(t % 5 == 0) {
			res++;
			t /= 5;
		}
	}

	return res;
}

// Solution 2 to issue 1
// ..., 5, ..., 10, ..., 15, ..., 20, ..., 25, ..., N --> Total 'N/5' has a factor 5
// After divide 5
// ..., 1, ...,  5, ..., 10, ..., 15, ..., 20, ..., [N/5] --> Total '[N/5]/5' has a factor 5
// After divide 5
// ...,    ...,  1, ...,  5, ..., 10, ..., 15, ..., [N/(5^2)] --> Total '[N/(5^2)]/5' has a factor 5
//
// ........................
// Until N/(5^x) == 0

int zero_number_at_end_of_N_factorial_effecient_method(const int n) {
	int res = 0;
	int num = n;
	while(num) {
		res += num / 5;
		num /= 5;
	}

	return res;
}

// Issue 2: Return the right most position of 1 in the binary number of 'N!'
// Similar to issue 1, we have 2 methods
// Method 1
int right_most_position_of_1_in_binary_of_n_factorial(const int n) {
	int res = 0;
	for(int i = 2; i < n; i += 2) {
		int t = i;
		while(t % 2 == 0) {
			res++;
			t = t >> 1;
		}
	}

	return res;
}

// Method 2
int right_most_position_of_1_in_binary_of_n_factorial_effecient_method(const int n) {
	int res = 0;
	int num = n;
	while(num) {
		res += num / 2;
		num = num >> 1;
	}

	return res;
}

// --------------------------------------------------------------------------------------------------------------
// 9.4 Is a point inside a rectangle?

bool _point_inside_rec(double x1, double y1, double x3, double y3, double x, double y) {
	if(x < x1 || x > x3) {
		return false;
	}
	if(x < y1 || x > y3) {
		return false;
	}

	return true;
}

std::pair<double, double> _get_coordinates(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double x, double y) {
	double r = sqrt(pow(x - x4, 2) + pow(y - y4, 2));
	double l = sqrt(pow(x3 - x4, 2) + pow(y3 - y4, 2));

	double sin_1 = (y - y4) / r;
	double cos_1 = (x - x4) / r;
	double sin_2 = (y3 - y4) / l;
	double cos_2 = (x3 - x4) / l;

	double xx = r * (sin_1 * cos_2 - cos_1 * sin_2);
	double yy = r * (cos_1 * cos_2 + sin_1 * sin_2);

	return std::make_pair(xx, yy);
}

bool is_point_inside_rectangle(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double x, double y) {
	std::pair<double, double> xy_cord = _get_coordinates(x1, y2, x2, y3, x3, y3, x4, y4, x, y);
	double xx = xy_cord.first;
	double yy = xy_cord.second;
	return _point_inside_rec(x1, y1, x3, y3, xx, yy);
}



// --------------------------------------------------------------------------------------------------------------
// 9.5 Is a point inside a triangle?
// 2 methods
// (1) Area
// (2) Cross product

// Here use seoncd method to solve this problem
int cross_product(double x1, double y1, double x2, double y2) {
	return x1 * y2 - x2 * y1;
}

bool is_point_inside_triangle(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double x, double y) {
	// Make sure the sequence is anti-clockwise
	if(cross_product(x2 - x1, y2 - y1, x3 - x1, y3 - y1) < 0) {
		double xtemp = x2;
		double ytemp = y2;
		x2 = x3;
		x3 = xtemp;
		y2 = y3;
		y3 = ytemp;
	}

	if(cross_product(x2 - x1, y2 - y1, x - x1, y - y1) < 0) {
		return false;
	}
	if(cross_product(x3 - x2, y3 - x2, x - x2, y - y2) < 0) {
		return false;
	}
	if(cross_product(x1 - x3, y1 - y3, x - x3, y - y3) < 0) {
		return false;
	}

	return true;
}


// --------------------------------------------------------------------------------------------------------------
// 9.6 Paper folding problem
// Get the all crease(up/down) after folding a paper by N times

void _print_paper_folding_creases(const int i, const int n, bool updown) {
	if(i > n) {
		return ;
	}
	_print_paper_folding_creases(i + 1, n, false/*down*/);
	printf("%s\n", updown ? "up" : "down");
	_print_paper_folding_creases(i + 1, n, true/*up*/);
}

void paper_folding_creases(const int n) {
	if(n <= 0) {
		return ;
	}
	if(n == 1) {
		printf("up\n");
		return ;
	}

	_print_paper_folding_creases(1, n, true);
}

// --------------------------------------------------------------------------------------------------------------
// 9.7 Algorithm of Impounding Reservoir

void impoundingReservoir(const int n, const int k) {
	if(k <= 0 || n <= 0 || n < k) {
		return ;
	}

	boost::shared_array<int> reservoir(new int[k]);
	for(int i = 0; i < k; i++) {
		reservoir[i] = i;
	}
	for(int i = k; i < n; i++) {
		if(CU::gen_random_int_1(1, i) <= k) {
			reservoir[CU::gen_random_int_1(1, k)] = i;
		}
	}
}


// --------------------------------------------------------------------------------------------------------------
// 9.8 A hash has method of 'setAll'

class object {
public:
	object() : m_time(0), m_value(0) {}
	object(int v, int t) : m_time(t), m_value(v) {}
	~object() {}
public:
	const int get_time() const { return m_time; }
	const int get_value() const {return m_value;}
	void set_time(int t) { m_time = t;}
	void set_value(int v) {m_value = v;}
private:
	int m_time;
	int m_value;
};

class myhash {
public:
	myhash(): m_time(0), m_reset_time(-1) {}
	~myhash() {m_map.clear();}
public:
	void put(int idx, int value);
	const int get(int idx);
	void setAll();
private:
	int m_time;
	int m_reset_time;
	std::map<int, object> m_map;
};

void myhash::
put(int idx, int value) {
	object obj(value, m_time++);
	m_map[idx] = obj;
}

const int myhash::
get(int idx) {
	if(m_map.find(idx) == m_map.end()) {
		return -1;
	} else {
		const object& obj = m_map[idx];
		if(obj.get_time() > m_reset_time) {
			return 0;
		} else {
			return obj.get_value();
		}
	}
}

void myhash::
setAll() {
	m_reset_time = m_time++;
}

// --------------------------------------------------------------------------------------------------------------
// 9.9 The maximum difference value of leftMax and rightMax
// Issue:
// Divide the array into 2 parts, assume the max value of left part is leftMax
// the max value of right part is rightMax
// Get the maximum difference value of leftMax and rightMax
const int max_diff_leftMax_rightMax(const std::vector<int> ivec) {
	if(ivec.empty() || ivec.size() == 1) {
		return 0;
	}

	int max = ivec[0];
	BOOST_FOREACH(const int v, ivec) {
		max = std::max(max, v);
	}

	return std::abs(std::max(max - ivec.front(), max - ivec.back()));
}
// [TIME_STAMP] Stop at 16:48, 2017/12/30



// [TIME_STAMP] Start at 13:30, 2017/12/31
// --------------------------------------------------------------------------------------------------------------
// 9.10 Design a cache which can change as time goes by
// Requirements
// (1) Once 'set' or 'get' operation occurs for one 'key', regard this 'key'
//     as the most commonly used
// (2) if cache size is greater than K, remove the oldest one

class cache {
	typedef std::pair<std::string, int> cpair;
	// typedef std::deque<cpair> cachelist;
	typedef std::deque<std::string> cachelist;
	typedef std::map<std::string, int> vmap;
	typedef std::map<std::string, cachelist::iterator> pmap;
public:
	cache(const int k) : m_size_limit(k), m_current_size(0) {}
	~cache() {}
	int get(std::string key);
	void set(std::string key, int value);
public:
	const int get_size_limit() const { return m_size_limit; }
	const int get_size() const { return m_current_size; }
private:
	int m_size_limit;
	int m_current_size;
	cachelist m_deque;
	vmap m_map;
	pmap m_pmap;
};

void cache::
set(std::string key, int value) {
	vmap::iterator itr = m_map.find(key);
	if(itr != m_map.end()) {
		cachelist::iterator pitr = m_pmap.find(key)->second;
		m_deque.erase(pitr);
		m_deque.push_front(key);
		m_pmap[key] = m_deque.begin();
		m_map[key] = value;
	} else {
		if(get_size() == get_size_limit()) {
			std::string s(m_deque.back());
			m_map.erase(s);
			m_pmap.erase(s);
			m_deque.pop_back();
			m_deque.push_front(key);
			m_map[key] = value;
			m_pmap[key] = m_deque.begin();
		} else {
			m_deque.push_front(key);
			m_map[key] = value;
			m_pmap[key] = m_deque.begin();
		}
	}
}

int cache::
get(std::string key) {
	vmap::iterator itr = m_map.find(key);
	if(itr == m_map.end()) {
		printf("Key: %s is not found\n", key.c_str());
		return -1;
	} else {
		cachelist::iterator pitr = m_pmap.find(key)->second;
		m_deque.erase(pitr);
		m_deque.push_front(key);
		m_pmap[key] = m_deque.begin();
		return m_map[key];
	}
}


// --------------------------------------------------------------------------------------------------------------
// 9.11 Random Pool
// Request
// (1) insert(key): add this 'key' to this pool, no duplication
// (2) remove(key): delete this 'key'
// (3) getRandom(key): randomly return a key in the structure by equal possibility

class randomPool {
public:
	randomPool(): m_size(0) {}
	~randomPool() {}
public:
	void insert(const std::string& s);
	void remove(const std::string& s);
	const std::string getRandom() const;
private:
	int m_size;
	std::map<std::string, int> m_kvmap;
	std::map<int, std::string> m_vkmap;
};

void randomPool::
insert(const std::string& s) {
	std::map<std::string, int>::iterator itr = m_kvmap.find(s);
	if(itr == m_kvmap.end()) {
		m_size++;
		m_kvmap[s] = m_size;
		m_vkmap[m_size] = s;
	}
}

void randomPool::
remove(const std::string& s) {
	std::map<std::string, int>::iterator itr = m_kvmap.find(s);
	if(itr != m_kvmap.end()) {
		int pos = itr->second;
		std::map<int, std::string>::iterator vklast = m_vkmap.find(m_size);
		std::map<std::string, int>::iterator kvlast = m_kvmap.find(vklast->second);
		kvlast->second = pos;
		m_kvmap.erase(itr);
		std::map<int, std::string>::iterator ii = m_vkmap.find(pos);
		ii->second = kvlast->first;
		m_vkmap.erase(vklast);
		m_size--;
	}
}

const std::string randomPool::
getRandom() const {
	if(m_size == 0) {
		return "";
	}
	if(m_size == 1) {
		return m_kvmap.begin()->first;
	}
	int rnum = CU::gen_random_int_1(1, m_size);
	std::string res(m_vkmap.find(rnum)->second);
	return res;
}


// [TIME_STAMP] Stop 15:47, 2017/12/31




// [TIME_STAMP] Start at 23:20, 2018/01/05

void get_first_unformed_number_0_process(int i, int sum, const std::vector<int>& arr, std::set<int>& ss) {
	const int sz = arr.size();
	if(i == sz) {
		ss.insert(sum);
		return ;
	}
	get_first_unformed_number_0_process(i + 1, sum, arr, ss);
	get_first_unformed_number_0_process(i + 1, sum + arr[i + 1], arr, ss);
}

int get_first_unformed_number_0(const std::vector<int>& arr) {
	std::set<int> sset;
	get_first_unformed_number_0_process(0, 0, arr, sset);

	int sum = 0;
	BOOST_FOREACH(int v, arr) {
		sum += v;
	}
	for(int i = 1; i <= sum; i++) {
		if(sset.find(i) == sset.end()) {
			return i;
		}
	}

	return sum + 1;
}

int get_first_unformed_number(const std::vector<int>& arr) {
	if(arr.empty()) {
		return -1;
	}

	int sum = 0;
	int min = arr[0];
	const int len = arr.size();
	for(int i = 0; i < len; i++) {
		sum += arr[i];
		min = std::min(min, arr[i]);
	}

	std::vector<int> dp(sum + 1, 0);
	for(int i = 0; i < len; i++) {
		for(int j = sum; j >= arr[i]; j--) {
			if(dp[j - arr[i]] + arr[i] > dp[j]) {
				dp[j] = dp[j - arr[i]] + arr[i];
			}
		}
	}

	for(int i = min; i < sum; i++) {
		if(i != dp[i]) {
			return i;
		}
	}

	return sum + 1;
}
// [TIME_STAMP] Stop at 23:44, 2018/01/05


// [TIME_STAMP] Start at 10:01, 2018/01/21
// --------------------------------------------------------------------------------------------------------------
// 9.12 Adjust the appearance probablity of a digit in range [0, x)
//  Assume Math.random() (here use a pseduo function instead) returns a float number in [0, 1) equally,
//  then the probability of occurrence for float number in range [0, x) (0<x<=1) would be 'x'.
//  Given a integer k(k > 0), Write a function to return a float in [0, 1),
//  but the probability of occurrence in [0, x) would be x^k.

double math_random() {
    return CU::gen_random_double_0to1();
}

double randXPowerK(int k) {
    if (k < 1) {
        return -1;
    }
    double res = -1;
    for(int i = 0; i < k; i++) {
        res = std::max(res, math_random());
    }
    return res;
}



// --------------------------------------------------------------------------------------------------------------
// 9.13 Turn a path array into a statistical array
//
// paths:
//   This is a path array, 'path[i] = j' represent that city 'i' is connected to city 'j'
//   If 'path[i] = i', then city 'i' is capital.
// Assume there's only one capital and no city points to itself except the capital
// Question:
//   Get a statistic array nums[..], 'nums[i] = v' represents there are 'v' cities which is
//   'i' distance from capital
// For example
//   index    0, 1, 2, 3, 4, 5, 6, 7, 8, 9
//   paths = [9, 1, 4, 9, 0, 4, 8, 9, 0, 1]
//   The connection would be,
//
//              1
//              |
//         _____9____
//         |    |    |
//         |    |    |
//         0    3    7
//       __|__
//       |    |
//       |    |
//       4    8
//      _|_   |
//     |   |  |
//     2   5  6
//
//   then the nums would be,
//   nums  = [1, 1, 3, 2, 3, 0, 0, 0, 0, 0]


// Solution, 2 steps:
//  1. turn path array to a distance array
//                  index    0, 1,  2,  3,  4,  5,  6,  7,  8,  9
//     For exampel, dist = [-2, 0, -4, -2, -3, -4, -4, -2, -3, -1]
//  2. turn the distance array to statistical array

// 'vdist[i] = j' represents city 'i' is '|j|' distance from capital
// j is negative, though then absolute value of it is the distance
void get_city_dist_array(const std::vector<int>& paths, std::vector<int>& vdist) {
    vdist.clear();
    if(paths.empty()) {
        return ;
    }

    // Copy from original paths
    std::copy(paths.begin(), paths.end(), vdist.begin());
    // Turn the path array to a distance array
    int capital = -1;
    const int vlen = vdist.size();
    for(int i = 0; i < vlen; i++ ) {
    	if(vdist[i] == i) {
    		capital = i;
    		continue;
    	}
    	if(vdist[i] < 0) {
    		continue;
    	}

		int curi = i;
		int nexti = vdist[curi];
		vdist[curi] = -1;
		while(vdist[nexti] > 0 && vdist[nexti] != nexti) {
			int prei = curi;
			curi = nexti;
			nexti = vdist[curi];
			vdist[curi] = prei;
		}
		int dist = vdist[nexti] < 0 ? vdist[nexti] : -1;
		while(vdist[curi] != -1) {
			int prei = vdist[curi];
			vdist[curi] = dist--;
			curi = prei;
		}
		vdist[curi] = dist;
    }
    // Capital
    vdist[capital] = 0;
}

void get_city_count_array(std::vector<int>& vdist) {
	if(vdist.empty()) {
		return ;
	}

	const int length = vdist.size();
	for(int i = 0; i < length; i++) {
		if(vdist[i] >= 0) {
			continue;
		}
		int nexti = std::abs(vdist[i]);
		vdist[i] = 0;
		while(vdist[nexti] < 0) {
			int tmp = vdist[nexti];
			vdist[nexti] = 1;
			nexti = std::abs(tmp);
		}
		vdist[nexti]++;
	}
	vdist[0] = 1;
}

const std::vector<int> get_city_statistical_array(const std::vector<int>& paths) {
	std::vector<int> res;
	if(paths.empty()) {
		return res;
	}

	// Paths -> dist array
	get_city_dist_array(paths, res);
	// dist array -> statistical array
	get_city_count_array(res);

	return res;
}

// --------------------------------------------------------------------------------------------------------------
// 9.14 First unformed sum in a positive array

// Solution(Dynamic Programming):
//   The total sum of this array is SUM = sum(arr[0..N-1])
//   Get a DP array dp[0..SUM-1], length is 'SUM'
//   dp[j] = True/False represents if 'j' can be formed.
// Key:
//   if arr[0..j] can form sum 'k', then arr[0..j,j+1] can form sum 'k + arr[j+1]'

void print_bool_vector(const std::vector<bool>& bv) {
	BOOST_FOREACH(bool v, bv) {
		std::cout << (v ? "* " : "- ");
	}
	std::cout << std::endl;
}

int get_first_unformed_sum(const std::vector<int>& arr) {
	if(arr.empty()) {
		return -1;
	}
	int sum = std::accumulate(arr.begin(), arr.end(), 0);
	int min = *std::min_element(arr.begin(), arr.end());
	const int length = arr.size();
	std::vector<bool> dp(sum + 1, false);
	dp[0] = true;
	print_bool_vector(dp); // Debug use
	for(int i = 0; i < length; i++) {
		for(int j = sum; j >= arr[i]; j--) {
			dp[j] = dp[j - arr[i]] ? true : dp[j];
		}
		print_bool_vector(dp); // Debug use
	}
	for(std::size_t i = min; i != dp.size(); i++) {
		if(!dp[i]) {
			return i;
		}
	}
	return sum + 1;
}

// [TIME_STAMP] Stop at 13:36, 2018/01/21


// [TIME_STAMP] Start at 12:32, 2018/01/27
//
// The problem of sum of a subset in an array
// Given an positive array arr[0...N-1]
// Given an positive integer M
// If any subset in the array's sum can form M?

bool subset_can_form_a_sum(const std::vector<int>& arr, const int asum) {
    // Assume all integers in arr is positive
    // Assume asum is positive
    const int len = arr.size();
    int **dp = CU::get_matrix(len + 1, asum + 1);

    bool res = false;

    // dp[i][j] means the subset of arr[0..i] can form sum 'j' or not
    // 0 <= i <= len, total 'len + 1'
    // 0 <= j <= asum, total 'asum + 1'

    // first row
    // dp[0][j] means the subset of arr[0..0] can form sum 'j'
    // Obviously not, so all of them(dp[0][j], 0<=j<=asum) are '0's
    for(int j = 0; j < asum + 1; j++) {
        dp[0][j] = 0;
    }

    // first column
    // dp[i][0] means the subset of arr[0...i] can form sum '0'
    // Obviously they can.
    for(int i = 0; i < len + 1; i++) {
        dp[i][0] = 1;
    }

    // Pay attention to dp[0][0], obviously it is '1'

    // for the rest
    // (1) if dp[i - 1][j] is '1', then dp[i][j] is '1' too.(Obviously)
    // (2) if dp[i - 1][j] is '0', then investigate dp[i - 1][j - arr[i]]
    //     if dp[i - 1][j - arr[i]] == '1', then after the i-th element included,
    //     the subset of arr[0..i] certainly can form sum 'j', since the subset of
    //     arr[0..i-1] can form 'j-arr[i]', and the i-th element is 'arr[i]'
    //     so it should be '1'
    //     if dp[i - 1][j - arr[i]] == '0', which means there's no subset of arr[0..i-1]
    //     can form sum 'j-arr[i]', so even after i-th element is included,
    //     the sum 'j' can't be formed either.
    for(int i = 1; i < len + 1; i++) {
        for(int j = 0; j < asum + 1; j++) {
            if(dp[i-1][j] == 1) {
                dp[i][j] = 1;
            } else {
                if(j - arr[i] >= 0) {
                    dp[i][j] = dp[i-1][j-arr[i]] == 1 ? 1 : 0;
                } else {
                    dp[i][j] = 0;
                }
            }
        }
    }

    res = dp[len][asum];
    CU::free_matrix(dp, len + 1, asum + 1);

    return res;
} /* func subset_can_form_a_sum*/

// So anther solution for 9.14 would be the following
bool first_unformed_sum(const std::vector<int>& arr) {
    // Assume all integers in arr is positive
    const int len = arr.size();
    const int vmin = *std::min_element(arr.begin(), arr.end());
    const int vmax = std::accumulate(arr.begin(), arr.end(), 0);
    int **dp = CU::get_matrix(len + 1, vmax + 1);

    int res = -1;

    for(int j = 0; j < vmax + 1; j++) {
        dp[0][j] = 0;
    }

    for(int i = 0; i < len + 1; i++) {
        dp[i][0] = 1;
    }

    for(int i = 1; i < len + 1; i++) {
        for(int j = 0; j < vmax + 1; j++) {
            if(dp[i-1][j] == 1) {
                dp[i][j] = 1;
            } else{
                if(j - arr[i] >= 0) {
                    dp[i][j] = dp[i-1][j-arr[i]] == 1 ? 1 : 0;
                } else {
                    dp[i][j] = 0;
                }
            }
        }
    }

    for(int j = vmin; j < vmax + 1; j++) {
        if(dp[len][j] == 0) {
            res = j;
            break;
        }
    }
    if(res == -1) {
        res = vmax + 1;
    }
    CU::free_matrix(dp, len + 1, vmax + 1);

    return res;
} /* func subset_can_form_a_sum*/

// Advanced problem
// Assume integer '1' is in the array
// get the min unformed sum
// ----------------------------------------------------------------------
// Solution:
    // if array[0..i-1] can form sums of [1..range]
    // then after array[i] is included, the total range can be extended.
    // 1. for [0..range], array[0..i-1] can form every element inside
    // 2. for [range + 1, ..., 2 * range], array[0..i-1] together with array[i]
    //    can form every one of them
    //    Anlaysis:
    //    (1) Assume array[i] is 1, then exists the sum of subset(array[0..i-1]) is range, thus
    //              SUM(subset(array[0..i-1])) + array[i] ==> range + 1
    //
    //    (2) Assume array[i] is 2, then exists subset(array[0..i-1]) is range - 1, thus
    //              SUM(subset(array[0..i-1])) + array[i] ==> range + 1
    //        and also exists subset(array[0..i-1]) + array[i] is range, thus
    //              SUM(subset(array[0..i-1])) + array[i] ==> range + 2
    //
    //    (3) Assume array[i] is 3, then exists subset(array[0..i-1]) is range - 2, thus
    //              SUM(subset(array[0..i-1])) + array[i] ==> range + 1
    //        and also exists subset(array[0..i-1]) is range - 1, thus
    //              SUM(subset(array[0..i-1])) + array[i] ==> range + 2
    //        and also exists subset(array[0..i-1]) is range, thus
    //              SUM(subset(array[0..i-1])) + array[i] ==> range + 3
    //
    //        ... ...
    //
    //    (#) Assume array[i] is range, then exists subset(array[0..i-1]) is 1, which is 'range - (range - 1)', thus
    //              SUM(subset(array[0..i-1])) + array[i] ==> range + 1
    //        and also exists subset(array[0..i-1]) is 2, thus
    //              SUM(subset(array[0..i-1])) + array[i] ==> range + 2
    //        ... ...
    //        and also exists subset(array[0..i-1]) is range, thus
    //              SUM(subset(array[0..i-1])) + array[i] ==> range + range
    //    (#) Assume array[i] is range + 1,
    //        then first you could use array[i] alone to form sum 'range + 1'
    //              SUM(array[i]) = range + 1
    //        then exists subset(array[0..i-1]) is 1, thus
    //              SUM(subset(array[0..i-1])) + array[i] ==> range + 2
    //        and also exists subset(array[0..i-1]) is 2, thus
    //              SUM(subset(array[0..i-1])) + array[i] ==> range + 3
    //        ... ...
    //        and also exists subset(array[0..i-1]) is range, thus
    //              SUM(subset(array[0..i-1])) + array[i] ==> range + range + 1
    //    (#) Assume array[i] is range + 2,
    //        then you can not use any one of element in array[0...i-1] and array[i] to form 'range + 2'
    //        So the max value of array[i] should be 'range + 1'
int get_min_unformed_sum_if_1_exists(const std::vector<int>& arr) {
    // Assume all elements in arr is positive
    // Assume integer '1' is in the arr
    int res = -1;
    if(arr.empty()) {
        return res;
    }

    std::vector<int> array(arr);
    // after sorting, array[0] must be 1, because all elements are positive
    std::sort(array.begin(), array.end());
    // when iterating to 'i'-th element, range means [1..range]
    // can be formed by array[0..i-1]
    int range = 0;
    const int len = array.size();
    for(int i = 0; i < len; i++) {
        if(array[i] > range + 1) {
            res = range + 1;
            break;
        } else {
            range += array[i];
        }
    }
    return res == -1 ? range + 1 : res;
} /* func get_min_unformed_sum_if_1_exists */


// --------------------------------------------------------------------------------------------------------------
// 9.15 Use a specified char array, convert a string to Int & int to string
//
// For example, char array is
//    chars [] = {'A', 'B', 'C', 'D', ..., 'Z'}
// then 'A', 'B', ... 'Z', 'AA', 'AB', ..., 'AZ', 'BA', 'BB', ..., 'ZZ', 'AAA', ..., 'ZZZ', 'AAAA', ...
// represent 1, 2, 3, ..., 26, 27, 28, ..., 52, 53, 54, 702, 703, ..., 18278, 18279, ...
// Another example
//    chars [] = {'A', 'B', 'C'}
// then 'A', 'B', 'C', 'AA', 'AB', ..., 'CC', 'AAA', ..., 'CCC', 'AAAA', ...
// represent 1, 2, 3, 4, 5, ..., 12, 13, ..., 39, 40, ...

// Use std::string to mimic char array
const std::string get_string_from_int_using_char_array(const std::string &carray, const int num) {
    if(carray.empty() || num <= 0) {
        return "";
    }

    int cur = 1;
    int n = num;
    int len = 0;
    int base = carray.size();
    // First calculate how many chars width(length) to use for this number to convert
    // Assume the length of carray is 'B', then each char from right to left represents values below
    // ..., B^6, B^5, B^4, B^3, B^2, B, 1
    while(cur <= n) {
        n -= cur;
        len++;
        cur *= base;
    }

    std::string res(len, carray.at(0));
    int idx = 0; // from high end to low end
    int n_cur = 0;
    do {
        cur /= base;
        n_cur = n / cur;
        assert(n_cur >= 1);
        res[idx++] = carray[n_cur - 1];
        n %= cur;
    } while(idx < len);

    return res;
} /* func get_string_from_int_using_char_array */


int char_position_in_char_array(const std::string &carray, const char &c) {
    if(carray.empty() || c > 'z' || c < 'A') {
        return 0;
    }
    int res = -1;
    const int len = carray.size();
    for(int i = 0; i < len; i++) {
        if(c == carray[i]) {
            res = i + 1;
            break;
        }
    }

    return res;
}

const int get_int_from_string_using_char_array(const std::string &carray, const std::string &str) {
    if(carray.empty() || str.empty()) {
        return -1;
    }

    int base = carray.size();
    int len = str.size();
    int curbase = 1;
    int res = 0;
    for(int i = len - 1; i > -1; i--) {
        res += curbase * char_position_in_char_array(carray, str[i]);
        curbase *= base;
    }

    return res;
} /* func get_int_from_string_using_char_array */

// --------------------------------------------------------------------------------------------------------------
// 9.16 How many time does '1' occur from 1 ~ n ?

// A high complextiy solution: check every number for '1'

int one_number(int n) {
    int cnt = 0;
    while(n > 0) {
        cnt = (n % 10 == 1) ? cnt + 1 : cnt;
        n /= 10;
    }

    return cnt;
}

int how_many_ones_in_range1toN(const int n) {
    int res = 0;
    for(int i = 1; i < n + 1; i++) {
        res += one_number(i);
    }

    return res;
}


// --------------------------------------------------------------------------------------------------------------
// 9.17 Equally print M numbers in an array which length is N(N >= M)
// Requirements:
// (1) Don't print duplicated numbers
// (2) Can change original array

void print_m_numbers_in_n_length_array(const std::vector<int> &ivec, const int m) {
    if(ivec.empty() || m <= 0 || (std::size_t)m > ivec.size()) {
        return ;
    }

    std::vector<int> dvec(ivec);
    int count = 0;
    const int len = dvec.size();
    while(count < m) {
        int pos = CU::gen_random_int_1(0, len - count - 1);
        printf("%d ", ivec[pos]);
        // Swap the element in 'pos' to the end
        int tmp = dvec[pos];
        dvec[pos] = dvec[len - count - 1];
        dvec[len - count - 1] = tmp;
        count++;
    }
} /* func print_m_numbers_in_n_length_array */


// --------------------------------------------------------------------------------------------------------------
// 9.18 Check if a number is palindrome

bool check_number_is_palindrome(const int num) {
    int n = std::abs(num);
    int help = 1;
    while(help < n) {
        help *= 10;
    }
    if(help == 1) {
        return true;
    }

    while(n > 0) {
        if(n / help != n % 10) {
            return  false;
        }
        n = (n % help) / 10;
        help /= 10;
    }

    return true;
}

// --------------------------------------------------------------------------------------------------------------
// 9.19 Find the min value in a rotated array which had ascending order before
// Notice, the array has ascending order before rotatation

int min_value_in_rotated_array(const std::vector<int> & arr) {
    if(arr.empty()) {
        return -1;
    }

    const int len = arr.size();
    int low = 0;
    int high = len - 1;
    while(low < high) {
        if(low == high - 1 ) {
            break;
        }

        if(arr[low] < arr[high]) {
            return arr[low];
        }

        // Situation: Now arr[low] >= arr[high]

        int mid = (low + high) / 2;
        if(arr[low] > arr[mid]) { // Situation: if not, then arr[low] <= arr[mid]
            high = mid;
            continue;
        }
        if(arr[mid] > arr[high]) { // Situation: if not, then arr[mid] <= arr[high]
            low = mid;
            continue;
        }
        // According to the situations above
        // Now arr[low] == arr[mid] == arr[high]
        // Starting from low, walking towards 'mid'
        int i = low;
        while(i != mid) {
            if(arr[i] < arr[low]) {
                return arr[i];
            } else if(arr[i] > arr[low]) {
                // this situation means arr[mid] < arr[i] too
                // So the min value(or the cliff-point) is in range [i..mid]
                low = i;
                high = mid;
                break;
            } else {
                i++;
            }
        }
        // If all values are the same in [low..mid]
        // then the min value(or the cliff-pointl) is in range [mid..high]
        if(i == mid) {
            low = mid;
        }
    }

    return std::min(arr[low], arr[high]);

} /* min_value_in_rotated_array */

// [TIME_STAMP] Stop at 17:07, 2018/01/27



// [TIME_STAMP] Start at 13:11, 2018/01/28
// --------------------------------------------------------------------------------------------------------------
// 9.20 Find a number in a rotated(or might not be roated) array
// Notice, the array is original in order and it might be rotated or not
// the array may contain duplicated numbers

// Solution is binary search
// First iterate 'low' to make sure 'arr[low]', 'arr[mid]' and 'arr[high]' are not
//   all the same
//
// then the break-point(where the array is rotated) could be the following situations
//   (1) low <= mid <= high <= break
//   (2) low <= mid <= break <= high
//   (3) low <= break <= mid <= high
//   (4) break <= low <= mid <= high
//
//  if arr[low] != arr[mid]
//    (a) if arr[low] < arr[mid], then (1)(2)(4) statisfy this case
//        thus 1) if arr[low] <= num && num <= arr[mid], then search range [low, mid]
//             2) if arr[low] > num || num > arr[mid], then search range [mid, high]
//    (b) if arr[low] > arr[mid], then (3) statisfy this case
//        thus 1) if arr[mid] <= num && num <= arr[high], then search range [mid, high]
//             2) if arr[mid] > num || num > arr[high], then search range [low, mid]
//  if arr[mid] != arr[high]
//    (a) if arr[mid] < arr[high], then (1)(3)(4) statisfy this case
//        thus 1) if arr[mid] <= num && num <= arr[high], then search range [mid, high]
//             2) if arr[mid] > num || num > arr[high], then search range [low, mid]
//    (b) if arr[mid] > arr[high], then (2) statisfy this case
//        thus 1) if arr[low] <= num && num <= arr[mid], then search range [low, mid]
//             2) if arr[low] > num || num > arr[mid], then search range [mid, high]
int find_number_value_in_rotated_array(const std::vector<int> & arr, const int num) {
    if(arr.empty()) {
        return -1;
    }

    const int len = arr.size();
    int low = 0;
    int high = len - 1;
    int mid = 0;
    int res = -1;

    while(low < high) {
        mid = (low + high) / 2;
        if(arr[mid] == num) {
            res = mid;
            break;
        }

        // First iterate 'low' to make sure 'arr[low]', 'arr[mid]'
        // and 'arr[high]' are not all the same
        if(arr[low] == arr[mid] && arr[mid] == arr[high]) {
            while(low != mid && arr[low] == arr[mid]) {
                low++;
            }
            if(low == mid) {
                low = mid + 1;
                continue;
            }
        }

        if(arr[low] != arr[mid]) {
            if(arr[low] < arr[mid]) {
                if(arr[low] <= num && num <= arr[mid]) {
                    high = mid - 1;
                } else { // arr[low] > num || num > arr[mid]
                    low = mid + 1;
                }
            } else { // arr[low] > arr[mid]
                if(arr[mid] <= num && num <= arr[high]) {
                    low = mid + 1;
                } else { // arr[mid] > num || num > arr[high]
                    high = mid - 1;
                }
            }
        } else { // arr[mid] != arr[high]
            if(arr[mid] < arr[high]) {
                if(arr[mid] <= num && num <= arr[high]) {
                    low = mid + 1;
                } else { // arr[mid] > num || num > arr[high]
                    high = mid - 1;
                }
            }
        }
    } // while-loop

    return res;

} /* fucn find_number_value_in_rotated_array */


// --------------------------------------------------------------------------------------------------------------
// 9.21 Represent a number(32-bit) in English and Chinese
//
//
// Sample
//  English: -2,147,483,648
//    Negative, two billion, one hundred forty seven million, four hundred, eighty three thousand, six hundred, forty eight
//  Chinese: -21,4748,3648, -13,5129,4576
//    FU ER #SHI# YI YI[U], SI #QIAN# QI #BAI# SI #SHI# BA WAN[U], SAN #QIAN# LIU #BAI# SI #SHI# BA
//    FU YI #SHI# SAN YI[U], WU #QIAN# YI #BAI# ER #SHI# JIU WAN[U], SI #QIAN# WU #BAI# QI #SHI# LIU

class numberToLanguageExpression {
public:
    numberToLanguageExpression(int number) : m_num(number) { }
    ~numberToLanguageExpression() { }

public:
    const std::string toEnglishExpression(int num) const;
    const std::string toChineseExpression(int num) const;

protected:
    const std::string toEnglish1to19(int num) const;
    const std::string toEnglish1to99(int num) const;
    const std::string toEnglish1to999(int num) const;
protected:
    const std::string toChinese1to9(int num) const;
    const std::string toChinese1to99(int num, bool hasBAI) const;
    const std::string toChinese1to999(int num) const;
    const std::string toChinese1to9999(int num) const;
    const std::string toChinese1to99999999(int num) const;

private:
    int m_num;
}; /* class numberToLanguageExpression */


const std::string numberToLanguageExpression::
toEnglishExpression(int num) const {
    static std::vector<std::string> ubase = {"Billion", "Million", "Thousand", ""};
    if(num == 0) {
        return "zero";
    }
    std::string res;
    if(num < 0) {
        res = "Negative, ";
    }
    // In case of overflow
    if(num == INT_MIN) {
        res + "Two Billion, ";
        num %= -2000000000; // 2 billion
    }

    num = std::abs(num);
    int high = 1000000000;
    int idx = 0;
    while(num != 0) {
        int cur = num / high;
        num %= high;
        if(cur != 0) {
            res += toEnglish1to999(cur);
            res += ubase[idx] + (num == 0 ? " " : ", ");
        }
        high /= 1000;
        idx++;
    }

    return res;
}

const std::string numberToLanguageExpression::
toChineseExpression(int num) const {
    std::string res;
    if(num == 0) {
        return "zero";
    }
    if(num < 0) {
        res += "#FU# ";
    }
    num = std::abs(num);
    int t = num / 100000000;
    int r = num % 100000000;
    if(t == 0) {
        res += toChinese1to99999999(t);
        return res;
    }
    res += toChinese1to99(t, false) + " *YI* ";
    if(r == 0) {
        return res;
    } else {
        if(r < 10000000) {
            res += " *LING* " + toChinese1to99999999(r);
        } else {
            res += toChinese1to99999999(r);
        }
    }

    return res;
}

const std::string numberToLanguageExpression::
toEnglish1to19(int num) const {
    static std::vector<std::string> nEng1to19 = {"one", "two", "three", "four", "five", "sixe", "seven", "eight", "nine", "ten",
                                "eleven", "tewlve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
    if(num > 19 || num < 1) {
        return "";
    }

    return nEng1to19[num - 1];
}

const std::string numberToLanguageExpression::
toEnglish1to99(int num) const {
    static std::vector<std::string> nEng20to90 = {"twenty", "thirdty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};
    if(num < 1 || num > 99) {
        return "";
    }
    if(num < 20) {
        return toEnglish1to19(num);
    }

    std::string res(nEng20to90[num / 10 - 1]);
    res += " ";
    res += toEnglish1to19(num % 10);

    return res;
}

const std::string numberToLanguageExpression::
toEnglish1to999(int num) const {
    if(num < 1 || num > 999) {
        return "";
    }

    if(num < 100) {
        return toEnglish1to99(num);
    }

    std::string res(toEnglish1to19(num / 100));
    res += " hundred ";
    res += toEnglish1to99(num % 100);
    return res;
}

const std::string numberToLanguageExpression::
toChinese1to9(int num) const {
    static std::vector<std::string> onames = {"YI", "ER", "SAN", "SI", "WU", "LIU", "QI", "BA", "JIU"};
    if(num < 1 || num > 9) {
        return "";
    }

    return onames[num - 1];
}

const std::string numberToLanguageExpression::
toChinese1to99(int num, bool hasBAI) const {
    if(num < 1 || num > 99) {
        return "";
    }
    if(num < 10) {
        return toChinese1to9(num);
    }
    std::string res = toChinese1to9(num / 10);
    if(num / 10 == 1 && (!hasBAI)) {
        res += " *SHI* " + toChinese1to9(num % 10);
    } else {
        res += toChinese1to9(1) + " *SHI* " + toChinese1to9(num % 10);
    }
    return res;
}


const std::string numberToLanguageExpression::
toChinese1to999(int num) const {
    if(num < 1 || num > 999) {
        return "";
    }
    if(num < 100) {
        return toChinese1to99(num, false);
    }
    std::string res;
    res += toChinese1to9(num / 100) + " *BAI*";
    if(num % 100 == 0) {
        return res;
    } else if((num % 100) >= 10) {
        res += toChinese1to99(num % 100, true);
    } else { // num % 100 < 10
        res += " *LING* " + toChinese1to9(num % 100);
    }
    return res;
}

const std::string numberToLanguageExpression::
toChinese1to9999(int num) const {
    if(num < 1 || num > 9999) {
        return "";
    }
    if(num < 1000) {
        return toChinese1to999(num);
    }
    std::string res;
    res += toChinese1to9(num / 1000) + " *QIAN*";
    if(num % 1000 == 0) {
        return res;
    } else if((num % 1000) >= 100) {
        res += toChinese1to999(num % 1000);
    } else { // num % 1000 < 100
        res += " *LING* " + toChinese1to99(num % 1000, false);
    }
    return res;
}

const std::string numberToLanguageExpression::
toChinese1to99999999(int num) const {
    if(num < 1 || num > 99999999) {
        return "";
    }
    std::string res;
    int t = num / 10000;
    int r = num % 10000;
    if(t == 0) {
        res += toChinese1to9999(t);
        return res;
    }
    res += toChinese1to9999(t) + " *WAN* ";
    if(r == 0) {
        return res;
    } else {
        if(r < 1000) {
            res += " *LING* " + toChinese1to999(r);
        } else {
            res += toChinese1to9999(r);
        }
    }

    return res;
}


// --------------------------------------------------------------------------------------------------------------
// 9.22 Candy distribution

// Start from i-th on, value begin to increase
// so, from 'start' to 'res', elements are in descending order
int next_min_index(const std::vector<int> &arr, int start) {
    int res = -1;
    if(arr.empty()) {
        return res;
    }
    const int len = arr.size();
    for(int i = start; i < len - 1; i++) {
        if(arr[i] < arr[i + 1]) { // Notice, it shouldn't reach boundary
            res = i;
            break;
        }
    }

    res = res == -1 ? len - 1 : res;
    return res;
}

// Candies to distribute for the right slope(descending slope)
int right_slope_candies(const std::vector<int> &arr, int begin, int end) {
    assert(end >= begin);
    int num = end - begin + 1;
    // sum of 1 to num
    return (num + 1) * num / 2;
}

int total_candies_to_distribute(const std::vector<int> &arr) {
    if(arr.empty()) {
        return 0;
    }
    int idx = next_min_index(arr, 0);
    int res = right_slope_candies(arr, 0, idx);
    idx++;
    const int len = arr.size();
    int lnum = 1; // From the bottom of a slope, the candy for start one is 1.
    while(idx < len) {
        if(arr[idx - 1] < arr[idx]) {
            lnum++;
            res += lnum;
            idx++;
        } else if(arr[idx - 1] > arr[idx]){
            int next = next_min_index(arr, idx - 1);
            int rcands = right_slope_candies(arr, idx - 1, next);
            next++;
            int rnum = next - idx + 1;
            if(rnum > lnum) {
                res += rcands - lnum;
            } else {
                res += rcands - rnum;
            }
            lnum = 1;
            idx = next;
        } else {
            // for those equall to the one before, assign just 1 candy
            res += 1;
            lnum = 1;
            idx++;
        }
    }

    return res;
} /* func total_candies_to_distribute */

// [TIME_STAMP] Stop at 19:06, 2018/01/28





































// [TIME_STAMP] Start at XX, 2017/XX/XX
// [TIME_STAMP] Stop at XX, 2017/XX/XX

// [TIME_STAMP] Start at XX, 2017/XX/XX
// [TIME_STAMP] Stop at XX, 2017/XX/XX


} // namespace C9

#endif /* CHAPTER_9_HPP_ */

