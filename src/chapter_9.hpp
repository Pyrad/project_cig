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
















































// [TIME_STAMP] Start at XX, 2017/XX/XX
// [TIME_STAMP] Stop at XX, 2017/XX/XX

// [TIME_STAMP] Start at XX, 2017/XX/XX
// [TIME_STAMP] Stop at XX, 2017/XX/XX


} // namespace C9

#endif /* CHAPTER_9_HPP_ */
