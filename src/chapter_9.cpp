/*
 * chapter_9.cpp
 *
 *  Created on: Dec. 30, 2017
 *      Author: Pyrad
 * Description: Header file of chapter 9
 *   Intention: Solutions for problems in Chapter 9 of Code Interview Guide
 */


#include "chapter_9.hpp"
#include "chapter_9_test.hpp"

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
	return CU::gen_random_int(1, 5);
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
	return CU::gen_random_int(1, m);
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
		if(CU::gen_random_int(1, i) <= k) {
			reservoir[CU::gen_random_int(1, k)] = i;
		}
	}
}


// --------------------------------------------------------------------------------------------------------------
// 9.8 A hash has method of 'setAll'

// class object {
// public:
// 	object() : m_time(0), m_value(0) {}
// 	object(int v, int t) : m_time(t), m_value(v) {}
// 	~object() {}
// public:
// 	const int get_time() const { return m_time; }
// 	const int get_value() const {return m_value;}
// 	void set_time(int t) { m_time = t;}
// 	void set_value(int v) {m_value = v;}
// private:
// 	int m_time;
// 	int m_value;
// };
// 
// class myhash {
// public:
// 	myhash(): m_time(0), m_reset_time(-1) {}
// 	~myhash() {m_map.clear();}
// public:
// 	void put(int idx, int value);
// 	const int get(int idx);
// 	void setAll();
// private:
// 	int m_time;
// 	int m_reset_time;
// 	std::map<int, object> m_map;
// };
// 
// void myhash::
// put(int idx, int value) {
// 	object obj(value, m_time++);
// 	m_map[idx] = obj;
// }
// 
// const int myhash::
// get(int idx) {
// 	if(m_map.find(idx) == m_map.end()) {
// 		return -1;
// 	} else {
// 		const object& obj = m_map[idx];
// 		if(obj.get_time() > m_reset_time) {
// 			return 0;
// 		} else {
// 			return obj.get_value();
// 		}
// 	}
// }
// 
// void myhash::
// setAll() {
// 	m_reset_time = m_time++;
// }

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

// class cache {
// 	typedef std::pair<std::string, int> cpair;
// 	// typedef std::deque<cpair> cachelist;
// 	typedef std::deque<std::string> cachelist;
// 	typedef std::map<std::string, int> vmap;
// 	typedef std::map<std::string, cachelist::iterator> pmap;
// public:
// 	cache(const int k) : m_size_limit(k), m_current_size(0) {}
// 	~cache() {}
// 	int get(std::string key);
// 	void set(std::string key, int value);
// public:
// 	const int get_size_limit() const { return m_size_limit; }
// 	const int get_size() const { return m_current_size; }
// private:
// 	int m_size_limit;
// 	int m_current_size;
// 	cachelist m_deque;
// 	vmap m_map;
// 	pmap m_pmap;
// };
// 
// void cache::
// set(std::string key, int value) {
// 	vmap::iterator itr = m_map.find(key);
// 	if(itr != m_map.end()) {
// 		cachelist::iterator pitr = m_pmap.find(key)->second;
// 		m_deque.erase(pitr);
// 		m_deque.push_front(key);
// 		m_pmap[key] = m_deque.begin();
// 		m_map[key] = value;
// 	} else {
// 		if(get_size() == get_size_limit()) {
// 			std::string s(m_deque.back());
// 			m_map.erase(s);
// 			m_pmap.erase(s);
// 			m_deque.pop_back();
// 			m_deque.push_front(key);
// 			m_map[key] = value;
// 			m_pmap[key] = m_deque.begin();
// 		} else {
// 			m_deque.push_front(key);
// 			m_map[key] = value;
// 			m_pmap[key] = m_deque.begin();
// 		}
// 	}
// }
// 
// int cache::
// get(std::string key) {
// 	vmap::iterator itr = m_map.find(key);
// 	if(itr == m_map.end()) {
// 		printf("Key: %s is not found\n", key.c_str());
// 		return -1;
// 	} else {
// 		cachelist::iterator pitr = m_pmap.find(key)->second;
// 		m_deque.erase(pitr);
// 		m_deque.push_front(key);
// 		m_pmap[key] = m_deque.begin();
// 		return m_map[key];
// 	}
// }


// --------------------------------------------------------------------------------------------------------------
// 9.11 Random Pool
// Request
// (1) insert(key): add this 'key' to this pool, no duplication
// (2) remove(key): delete this 'key'
// (3) getRandom(key): randomly return a key in the structure by equal possibility

// class randomPool {
// public:
// 	randomPool(): m_size(0) {}
// 	~randomPool() {}
// public:
// 	void insert(const std::string& s);
// 	void remove(const std::string& s);
// 	const std::string getRandom() const;
// private:
// 	int m_size;
// 	std::map<std::string, int> m_kvmap;
// 	std::map<int, std::string> m_vkmap;
// };
// 
// void randomPool::
// insert(const std::string& s) {
// 	std::map<std::string, int>::iterator itr = m_kvmap.find(s);
// 	if(itr == m_kvmap.end()) {
// 		m_size++;
// 		m_kvmap[s] = m_size;
// 		m_vkmap[m_size] = s;
// 	}
// }
// 
// void randomPool::
// remove(const std::string& s) {
// 	std::map<std::string, int>::iterator itr = m_kvmap.find(s);
// 	if(itr != m_kvmap.end()) {
// 		int pos = itr->second;
// 		std::map<int, std::string>::iterator vklast = m_vkmap.find(m_size);
// 		std::map<std::string, int>::iterator kvlast = m_kvmap.find(vklast->second);
// 		kvlast->second = pos;
// 		m_kvmap.erase(itr);
// 		std::map<int, std::string>::iterator ii = m_vkmap.find(pos);
// 		ii->second = kvlast->first;
// 		m_vkmap.erase(vklast);
// 		m_size--;
// 	}
// }
// 
// const std::string randomPool::
// getRandom() const {
// 	if(m_size == 0) {
// 		return "";
// 	}
// 	if(m_size == 1) {
// 		return m_kvmap.begin()->first;
// 	}
// 	int rnum = CU::gen_random_int(1, m_size);
// 	std::string res(m_vkmap.find(rnum)->second);
// 	return res;
// }


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
        int pos = CU::gen_random_int(0, len - count - 1);
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

// class numberToLanguageExpression {
// public:
//     numberToLanguageExpression(int number) : m_num(number) { }
//     ~numberToLanguageExpression() { }
// 
// public:
//     const std::string toEnglishExpression(int num) const;
//     const std::string toChineseExpression(int num) const;
// 
// protected:
//     const std::string toEnglish1to19(int num) const;
//     const std::string toEnglish1to99(int num) const;
//     const std::string toEnglish1to999(int num) const;
// protected:
//     const std::string toChinese1to9(int num) const;
//     const std::string toChinese1to99(int num, bool hasBAI) const;
//     const std::string toChinese1to999(int num) const;
//     const std::string toChinese1to9999(int num) const;
//     const std::string toChinese1to99999999(int num) const;
// 
// private:
//     int m_num;
// }; /* class numberToLanguageExpression */
// 
// 
// const std::string numberToLanguageExpression::
// toEnglishExpression(int num) const {
//     static std::vector<std::string> ubase = {"Billion", "Million", "Thousand", ""};
//     if(num == 0) {
//         return "zero";
//     }
//     std::string res;
//     if(num < 0) {
//         res = "Negative, ";
//     }
//     // In case of overflow
//     if(num == INT_MIN) {
//         res + "Two Billion, ";
//         num %= -2000000000; // 2 billion
//     }
// 
//     num = std::abs(num);
//     int high = 1000000000;
//     int idx = 0;
//     while(num != 0) {
//         int cur = num / high;
//         num %= high;
//         if(cur != 0) {
//             res += toEnglish1to999(cur);
//             res += ubase[idx] + (num == 0 ? " " : ", ");
//         }
//         high /= 1000;
//         idx++;
//     }
// 
//     return res;
// }
// 
// const std::string numberToLanguageExpression::
// toChineseExpression(int num) const {
//     std::string res;
//     if(num == 0) {
//         return "zero";
//     }
//     if(num < 0) {
//         res += "#FU# ";
//     }
//     num = std::abs(num);
//     int t = num / 100000000;
//     int r = num % 100000000;
//     if(t == 0) {
//         res += toChinese1to99999999(t);
//         return res;
//     }
//     res += toChinese1to99(t, false) + " *YI* ";
//     if(r == 0) {
//         return res;
//     } else {
//         if(r < 10000000) {
//             res += " *LING* " + toChinese1to99999999(r);
//         } else {
//             res += toChinese1to99999999(r);
//         }
//     }
// 
//     return res;
// }
// 
// const std::string numberToLanguageExpression::
// toEnglish1to19(int num) const {
//     static std::vector<std::string> nEng1to19 = {"one", "two", "three", "four", "five", "sixe", "seven", "eight", "nine", "ten",
//                                 "eleven", "tewlve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
//     if(num > 19 || num < 1) {
//         return "";
//     }
// 
//     return nEng1to19[num - 1];
// }
// 
// const std::string numberToLanguageExpression::
// toEnglish1to99(int num) const {
//     static std::vector<std::string> nEng20to90 = {"twenty", "thirdty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};
//     if(num < 1 || num > 99) {
//         return "";
//     }
//     if(num < 20) {
//         return toEnglish1to19(num);
//     }
// 
//     std::string res(nEng20to90[num / 10 - 1]);
//     res += " ";
//     res += toEnglish1to19(num % 10);
// 
//     return res;
// }
// 
// const std::string numberToLanguageExpression::
// toEnglish1to999(int num) const {
//     if(num < 1 || num > 999) {
//         return "";
//     }
// 
//     if(num < 100) {
//         return toEnglish1to99(num);
//     }
// 
//     std::string res(toEnglish1to19(num / 100));
//     res += " hundred ";
//     res += toEnglish1to99(num % 100);
//     return res;
// }
// 
// const std::string numberToLanguageExpression::
// toChinese1to9(int num) const {
//     static std::vector<std::string> onames = {"YI", "ER", "SAN", "SI", "WU", "LIU", "QI", "BA", "JIU"};
//     if(num < 1 || num > 9) {
//         return "";
//     }
// 
//     return onames[num - 1];
// }
// 
// const std::string numberToLanguageExpression::
// toChinese1to99(int num, bool hasBAI) const {
//     if(num < 1 || num > 99) {
//         return "";
//     }
//     if(num < 10) {
//         return toChinese1to9(num);
//     }
//     std::string res = toChinese1to9(num / 10);
//     if(num / 10 == 1 && (!hasBAI)) {
//         res += " *SHI* " + toChinese1to9(num % 10);
//     } else {
//         res += toChinese1to9(1) + " *SHI* " + toChinese1to9(num % 10);
//     }
//     return res;
// }
// 
// 
// const std::string numberToLanguageExpression::
// toChinese1to999(int num) const {
//     if(num < 1 || num > 999) {
//         return "";
//     }
//     if(num < 100) {
//         return toChinese1to99(num, false);
//     }
//     std::string res;
//     res += toChinese1to9(num / 100) + " *BAI*";
//     if(num % 100 == 0) {
//         return res;
//     } else if((num % 100) >= 10) {
//         res += toChinese1to99(num % 100, true);
//     } else { // num % 100 < 10
//         res += " *LING* " + toChinese1to9(num % 100);
//     }
//     return res;
// }
// 
// const std::string numberToLanguageExpression::
// toChinese1to9999(int num) const {
//     if(num < 1 || num > 9999) {
//         return "";
//     }
//     if(num < 1000) {
//         return toChinese1to999(num);
//     }
//     std::string res;
//     res += toChinese1to9(num / 1000) + " *QIAN*";
//     if(num % 1000 == 0) {
//         return res;
//     } else if((num % 1000) >= 100) {
//         res += toChinese1to999(num % 1000);
//     } else { // num % 1000 < 100
//         res += " *LING* " + toChinese1to99(num % 1000, false);
//     }
//     return res;
// }
// 
// const std::string numberToLanguageExpression::
// toChinese1to99999999(int num) const {
//     if(num < 1 || num > 99999999) {
//         return "";
//     }
//     std::string res;
//     int t = num / 10000;
//     int r = num % 10000;
//     if(t == 0) {
//         res += toChinese1to9999(t);
//         return res;
//     }
//     res += toChinese1to9999(t) + " *WAN* ";
//     if(r == 0) {
//         return res;
//     } else {
//         if(r < 1000) {
//             res += " *LING* " + toChinese1to999(r);
//         } else {
//             res += toChinese1to9999(r);
//         }
//     }
// 
//     return res;
// }


// --------------------------------------------------------------------------------------------------------------
// 9.22 Candy distribution
// (1) Basic problem
// (2) Advanced problem

// (1) Basic problem
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

// arr[0..N-1] is the score array
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
            // Calculate candies for ascending slope in this while loop
            lnum++;
            res += lnum;
            idx++;
        } else if(arr[idx - 1] > arr[idx]) {
            int next = next_min_index(arr, idx - 1);
            int rcands = right_slope_candies(arr, idx - 1, next);
            next++;
            // now 'lnum' is the total length of previous left slope(ascending order)
            // and 'rnum' is the total length of right slope(descending order)
            int rnum = next - idx + 1;
            if(rnum > lnum) {
                res += rcands - lnum;
            } else {
                res += rcands - rnum;
            }
            lnum = 1;
            idx = next;
        } else {
            // for those equal to the one before, assign just 1 candy
            res += 1;
            lnum = 1;
            idx++;
        }
    }

    return res;
} /* func total_candies_to_distribute */

// [TIME_STAMP] Stop at 19:06, 2018/01/28



// [TIME_STAMP] Start at 12:34, 2018/02/04

// (2) Advanced problem
// For those whose scores are equal must get equal candies.

// get the last index of right slope(descending order slope)
int next_min_index_2(const std::vector<int> &arr, int start) {
    int res = -1;
    const int len = arr.size();
    for(int i = start; i < len; i++) {
        if(arr[i] <= arr[i + 1]) {
            res = i;
            break;
        }
    }

    return res == -1 ? len - 1 : res;
}

// Candies to distribute for the right slope(descending slope)
// Equal scores get equal candies
std::pair<int, int> right_slope_candies_and_base(const std::vector<int> &arr, int begin, int end) {
    int base = 1;
    int cands = 1; // start from the last one
    for(int i = end - 1; i >= begin; i--) {
        if(arr[i] == arr[i + 1]) {
            cands += base;
        } else {
            cands += ++base;
        }
    }

    // cands --> total candies for the right slope
    // base  --> the candies for the top, calculated based on the right slope
    return std::make_pair(cands, base);
}

// arr[0..N-1] is the score array
int total_candies_to_distribute_2(const std::vector<int> &arr) {
    if(arr.empty()) {
        return 0;
    }
    const int len = arr.size();
    int idx = next_min_index_2(arr, 0);
    std::pair<int, int> data(right_slope_candies_and_base(arr, 0, idx));
    idx++;
    int res = data.first;
    int lnum = 1;
    int next = 0;
    int same = 1;

    while(idx < len) {
        if(arr[idx - 1] < arr[idx]) {
            lnum++;
            res += lnum;
            idx++;
        } else if(arr[idx - 1] > arr[idx]) {
            next = next_min_index_2(arr, idx - 1);
            data = right_slope_candies_and_base(arr, idx - 1, next);
            if(data.second <= lnum) {
                // left slope is longer than the right slope
                res += data.first - data.second;
            } else {
                // left slope is shorter than the right slope
                res += data.second * same - lnum * same + data.first - data.second;
            }
            idx = ++next;
            lnum = 1;
            same = 1;
        } else {
            // arr[idx - 1] == arr[idx]
            res += lnum;
            same++;
            idx++;
        }
    } // while-loop

    return res;
}



// --------------------------------------------------------------------------------------------------------------
// 9.23 Design a system to print messages recieved following a rule
// Rule
// 1. Message stream generates '2', system recieves '2' but don't print, since '1' hasn't appear yet
// 2. Message stream generates '1', system recieves '1' and prints '1, 2'
// 3. Message stream generates '4', system recieves '4' but don't print, since '3' hasn't appear yet
// 4. Message stream generates '5', system recieves '5' but don't print, since '3' hasn't appear yet
// 5. Message stream generates '7', system recieves '7' but don't print, since '3' hasn't appear yet
// 6. Message stream generates '3', system recieves '3' and prints '3, 4, 5'
// 7. Message stream generates '9', system recieves '9' but don't print, since '6' hasn't appear yet
// 8. Message stream generates '8', system recieves '8' but don't print, since '6' hasn't appear yet
// 9. Message stream generates '6', system recieves '8' and prints '6, 7, 8, 9'
//
// That is to say, if a message stream generates 1~N(integers)
// Recieve system recieves but doesn't print in the recieved order
// If last time 'i' is printed, then if 'i+1' appears, print 'i+1' and the all the successive integers
// following recieved.

// class MessageBoxSystem {
// public:
//     MessageBoxSystem() = default;
//     ~MessageBoxSystem() {
//         for(auto i : recyle) {
//             if(i != nullptr) {
//                 delete i;
//                 i = nullptr;
//             }
//         }
//     }
// 
// public:
//     void recieve(int num);
//     void print();
// 
// private:
//     std::unordered_map<int, CU::lnode*> headMap;
//     std::unordered_map<int, CU::lnode*> tailMap;
//     std::unordered_set<int> nset;
//     std::forward_list<CU::lnode*> recyle;
//     int lastPrint;
// }; /* class MessageBoxSystem */
// 
// 
// void MessageBoxSystem::
// recieve(int num) {
//     if(nset.find(num) != nset.end()) {
//         // num must be unique
//         return ;
//     } else {
//         nset.insert(num);
//     }
// 
//     CU::lnode *pnode = new CU::lnode(num);
//     // In case of memory leak
//     recyle.push_front(pnode);
//     headMap[num] = pnode;
//     tailMap[num] = pnode;
// 
//     auto i = tailMap.find(num - 1);
//     if(i != tailMap.end()) {
//         i->second->next = pnode;
//         tailMap.erase(i); // or use tailMap.erase(num - 1)
//         auto e = headMap.find(num);
//         headMap.erase(e);
//     }
// 
//     auto j = headMap.find(num + 1);
//     if(j != headMap.end()) {
//         pnode->next = j->second;
//         headMap.erase(j); // or use headMap.erase(num + 1)
//         auto e = tailMap.find(num);
//         tailMap.erase(e);
//     }
// 
// } /* member func MessageBoxSystem::recieve */
// 
// void MessageBoxSystem::
// print() {
//     // Check if to print
//     auto k = headMap.find(lastPrint + 1);
//     if(k == headMap.end()) {
//         return ;
//     }
// 
//     // next to print is "lastPrint + 1"
//     lastPrint++;
//     // Now from 'lastPrint' on, the list will be printed
//     headMap.erase(lastPrint);
// 
//     CU::lnode *p = k->second;
//     while(!p) {
//         std::cout << "Value is: " << p->value << "\n";
//         p = p->next;
//         lastPrint++;
//     }
// 
//     // Now 'p' is nullptr
//     lastPrint--;
//     tailMap.erase(lastPrint);
// } /* member func MessageBoxSystem::print */



// --------------------------------------------------------------------------------------------------------------
// 9.24 Design a heap which don't need to extend the space
// Actually it is to say use tree structure other than array(consecutive space) to design a heap
// Requirements:
//  1. Can generate a min_root_heap or max_root_heap
//  2. get_head() -> return the root of the heap
//  3. get_size() -> return the size of the heap
//  4. add(x) -> add a new element into the heap
//  5. pop_head() -> pop the root of the heap and then auto adjust the heap


// class heap_node {
// public:
//     heap_node(int n) : left(nullptr), right(nullptr), parent(nullptr), value(n) { }
//     ~heap_node() { left = right = parent = nullptr; }
// 
// public:
//     heap_node *left;
//     heap_node *right;
//     heap_node *parent;
//     int value;
// }; /* class heap_node */
// 
// class customized_compare {
// public:
//     customized_compare(bool b): m_comp(b) { }
//     customized_compare(const customized_compare &cc): m_comp(cc.m_comp) { }
//     customized_compare(const customized_compare *cc): m_comp(cc->m_comp) { }
//     ~customized_compare() { m_comp = false; }
// 
// public:
//     inline bool compare(heap_node* n1, heap_node *n2) {
//         return m_comp ? n1->value < n2->value : n1->value > n2->value;
//     }
// 
// public:
//     // True -> min heap
//     // False -> max heap
//     bool m_comp;
// }; /* class customized_compare */
// 
// class customized_heap {
// public:
//     customized_heap(const customized_compare &cc) : m_head(nullptr), m_last(nullptr), m_size(0), m_comp(cc) { }
//     ~customized_heap() {
//         clear_all_nodes();
//         m_head = m_last = nullptr;
//         m_size = 0;
//         m_comp = true;
//     }
// 
// public:
//     inline heap_node* get_head() { return m_head; }
//     inline const int get_size() const { return m_size; }
//     void add(int n);
//     int pop_head();
// 
// public:
//     inline bool empty() { return get_size() == 0; }
//     heap_node* get_node(int n) {
//         heap_node *p = new heap_node(n);
//         m_recyle.push_front(p);
//         return p;
//     }
//     int get_head_value() {
//         return m_head ? 0 : m_head->value;
//     }
// 
// private:
//     void clear_all_nodes() {
//         for(auto i : m_recyle) {
//             if(i != nullptr) {
//                 delete i;
//                 i = nullptr;
//             }
//         }
//         m_recyle.clear();
//     }
//     void adjust_heap_from_tail();
//     void adjust_heap_from_head();
//     void swap_adjacent_two_nodes(heap_node *n, heap_node *nparent);
//     heap_node* popLastNodeAndUpdateLastNode();
// 
// private:
//     heap_node *m_head;
//     heap_node *m_last; // the right most node of the last row in the heap
//     int m_size;
//     customized_compare m_comp; // True - min heap, False - max heap
// 
// private:
//     std::forward_list<heap_node*> m_recyle;
// }; /* class customized_heap */
// 
// 
// void customized_heap::
// add(int n) {
//     heap_node *pnode = get_node(n);
//     if(empty()) {
//         m_head = m_last = pnode;
//         m_size++;
//         return ;
//     }
// 
//     heap_node *p = m_last;
//     heap_node *pp = p->parent;
//     while(pp != nullptr && pp->left != p) {
//         p = pp;
//         pp = p->parent;
//     }
// 
//     if(pp == nullptr) {
//         // case 1: m_last is the last one of at bottom(now tree is a full-binary-tree)
//         m_last = pnode;
//         heap_node *res = m_head;
//         while(res->left != nullptr) {
//             res = res->left;
//         }
//         res->left = pnode;
//         pnode->parent = res;
//         pnode = m_last;
//     } else if(pp->right == nullptr) {
//         // case 2: parent has no right child
//         pp->right = pnode;
//         pnode->parent = pp;
//         pnode = m_last;
//     } else {
//         // case 3: parent does have right child
//         // get the left most of its right sub-tree
//         heap_node *res = pp->right;
//         while(res->left) {
//             res = res->left;
//         }
//         res->left = pnode;
//         pnode->parent = res;
//         pnode = m_last;
//     }
// 
//     m_size++;
//     adjust_heap_from_tail();
// 
// } /* member func customized_heap::add */
// 
// 
// void customized_heap::
// adjust_heap_from_tail() {
//     heap_node *p = m_last;
//     heap_node *pp = m_last->parent;
//     heap_node *lp = nullptr;
//     if(pp != nullptr && !m_comp.compare(p, pp)) {
//         lp = pp;
//     }
// 
//     while(pp != nullptr && !m_comp.compare(p, pp)) {
//         // Notice arguments order, 'pp' is parent of 'p'
//         swap_adjacent_two_nodes(p, pp);
//         pp = p->parent;
//         // no need to change 'p' since its pointer remain unchanged
//     }
// 
//     // the head of the heap has changed
//     if(m_head->parent != nullptr) {
//         m_head = m_head->parent;
//     }
// 
//     if(m_last->left || m_last->right){
//         m_last = lp;
//     }
// } /* member func customized_heap::adjust_heap_from_tail */
// 
// void customized_heap::
// swap_adjacent_two_nodes(heap_node *n, heap_node *parent) {
//     if(!n || !parent) {
//         return ;
//     }
// 
//     heap_node *parentParent = parent->parent;
//     heap_node *parentLeft= parent->left;
//     heap_node *parentRight = parent->right;
//     heap_node *nodeLeft = n->left;
//     heap_node *nodeRight = n->right;
// 
//     // Just in case parent is head of the heap
//     if(parentParent) {
//         if(parent == parentParent->left) {
//             parentParent->left = n;
//         } else{
//             parentParent->right = n;
//         }
//     }
//     n->parent = parentParent;
// 
//     if(n == parentRight) {
//         if(parentLeft) {
//             parentLeft->parent = n;
//         }
//         parent->parent = n;
//         n->left = parentLeft;
//         n->right = parent;
//         if(nodeLeft) {
//             nodeLeft->parent = parent;
//             parent->left = nodeLeft;
//         } else {
//             parent->left = nullptr;
//         }
//         if(nodeRight){
//             nodeRight->parent = parent;
//             parent->right = nodeRight;
//         } else {
//             parent->right = nullptr;
//         }
//     } else { // n == parentLeft
//         if(parentRight) {
//             parentRight->parent = n;
//         }
//         parent->parent = n;
//         n->left = parent;
//         n->right = parentRight;
//         if(nodeLeft) {
//             nodeLeft->parent = parent;
//             parent->left = nodeLeft;
//         } else {
//             parent->left = nullptr;
//         }
//         if(nodeRight){
//             nodeRight->parent = parent;
//             parent->right = nodeRight;
//         } else {
//             parent->right = nullptr;
//         }
//     }
// 
// } /* member func customized_heap::swap_adjacent_two_nodes */
// 
// 
// int customized_heap::
// pop_head() {
//     if(empty()) {
//         printf("Heap is empty!\n");
//         return -1;
//     }
// 
//     int res = m_head->value;
//     if(get_size() == 1) {
//         m_head = nullptr;
//         m_last = nullptr;
//         m_size = 0;
//         return res;
//     }
// 
//     heap_node *node = popLastNodeAndUpdateLastNode();
//     if(m_head->left) {
//         m_head->left->parent = node;
//     }
//     if(m_head->right) {
//         m_head->right->parent = node;
//     }
//     node->left = m_head->left;
//     node->right = m_head->right;
//     node->parent = nullptr;
// 
//     adjust_heap_from_head();
// 
//     return res;
// 
// } /* member func customized_heap::pop_head */
// 
// heap_node* customized_heap::
// popLastNodeAndUpdateLastNode() {
//     if(empty()) {
//         return nullptr;
//     }
// 
//     heap_node *res = m_last;
// 
//     heap_node *p = m_last;
//     heap_node *pp = p->parent;
//     while(pp != nullptr && pp->right != p) {
//         p = pp;
//         pp = p->parent;
//     }
// 
//     if(pp == nullptr) {
//         // case 1: m_last is the first one at the bottom(now tree is a full-binary-tree)
//         heap_node *l = m_head;
//         while(l->right != nullptr) {
//             l = l->right;
//         }
//         m_last = l;
//         heap_node *rp = res->parent;
//         if(res == rp->left) {
//             rp->left = nullptr;
//         } else {
//             rp->right = nullptr;
//         }
//         res->parent = nullptr;
//     } else {
//         heap_node *l = pp->left;
//         while(l->right) {
//             l = l->right;
//         }
//         m_last = l;
//         heap_node *rp = res->parent;
//         if(res == rp->left) {
//             rp->left = nullptr;
//         } else {
//             rp->right = nullptr;
//         }
//         res->parent = nullptr;
//     }
// 
//     m_size--;
//     return res;
// 
// } /* member func customized_heap::popLastNodeAndUpdateLastNode */
// 
// void customized_heap::
// adjust_heap_from_head() {
//     heap_node *p = m_head;
//     heap_node *left = p->left;
//     heap_node *right = p->right;
//     heap_node *most = p;
//     while(left) {
//         if(left && !m_comp.compare(left, p)) {
//             most = left;
//         }
//         if(right && !m_comp.compare(right, p)) {
//             most = right;
//         }
//         if(most == p) {
//             break;
//         }
//         // Notice arguments order, 'pp' is parent of 'p'
//         swap_adjacent_two_nodes(most, p);
//         left = p->left;
//         right = p->right;
//         most = p;
//     }
// 
//     if(p->parent == m_last) {
//         m_last = p;
//     }
// 
//     while(p->parent) {
//         p = p->parent;
//     }
//     m_head = p;
// 
// } /* member func customized_heap::adjust_heap_from_head */
// 
// 
// 
// // --------------------------------------------------------------------------------------------------------------
// // 9.25 Get the median of a data stream at any time
// // Notice, use the heap structure
// // use the heap constructing by binary tree instead of array
// // Use the solution of 9.24
// 
// class median_holder {
// public:
//     median_holder();
//     ~median_holder();
// 
// public:
//     void add_number_from_data_stream(int n);
//     int get_median_in_data_stream();
// 
// private:
//     std::shared_ptr<customized_heap> m_min_heap;// Store the max half of all recieved till now
//     std::shared_ptr<customized_heap> m_max_heap;// Store the min half of all recieved till now
// 
// }; /* class median_holder */
// 
// median_holder::
// ~median_holder()
// {
// }
// 
// median_holder::
// median_holder() :
//     m_min_heap(new customized_heap(customized_compare(true))),
//     m_max_heap(new customized_heap(customized_compare(false)))
// {
// } /* ctor of class median_holder */
// 
// void median_holder::
// add_number_from_data_stream(int n) {
//     if(m_max_heap->empty()) {
//         m_min_heap->add(n);
//     }
// 
//     if(m_max_heap->get_head_value() >= n) {
//         m_max_heap->add(n);
//     } else {
//         if(m_min_heap->empty()) {
//             m_min_heap->add(n);
//         }
//         if(m_min_heap->get_head_value() > n) {
//             m_max_heap->add(n);
//         } else {
//             m_min_heap->add(n);
//         }
//     }
// 
//     if(m_max_heap->get_size() == m_min_heap->get_size() + 2) {
//         m_min_heap->add(m_max_heap->pop_head());
//     }
//     if(m_min_heap->get_size() == m_max_heap->get_size() + 2) {
//         m_max_heap->add(m_min_heap->pop_head());
//     }
// 
// } /* member func median_holder::add_number_from_data_stream */
// 
// int median_holder::
// get_median_in_data_stream() {
//     const int maxSize = m_max_heap->get_size();
//     const int minSize = m_min_heap->get_size();
//     if(maxSize == 0 && minSize == 0) {
//         std::printf("No data recieved yet\n");
//         return -1;
//     }
// 
//     if(maxSize > minSize) {
//         return m_max_heap->get_head_value();
//     } else if(maxSize < minSize) {
//         return m_min_heap->get_head_value();
//     } else {
//         return (m_max_heap->get_head_value() + m_min_heap->get_head_value()) / 2;
//     }
// 
// } /* member func median_holder::get_median_in_data_stream */


// [TIME_STAMP] Stop at 18:02, 2018/02/04


// [TIME_STAMP] Start at 13:11, 2018/02/10


// --------------------------------------------------------------------------------------------------------------
// 9.26 Get the median(former one) from two sorted arrays of a same size
//
// Because the sum of two arrarys' size is even, so get the two median number and return the less one
int get_former_median_of_two_size_equal_sorted_arraies(const std::vector<int> &arr1, const std::vector<int> &arr2) {
    int res = -1;
    if(arr1.size() != arr2.size() || arr1.empty()) {
        return res;
    }

    if(arr1.size() == 1) {
        return arr1.front() > arr2.front() ? arr1.front() : arr2.front();
    }

    int start1 = 0;
    int end1 = arr1.size() - 1;
    int start2 = 0;
    int end2 = arr2.size() - 2;

    int mid1 = 0;
    int mid2 = 0;

    while(start1 < end1) {
        mid1 = (start1 + end1) / 2;
        mid2 = (start2 + end2) / 2;
        if(arr1[mid1] == arr2[mid2]) {
            return arr1[mid1]; // or return arr2[mid2]
        } else if(arr1[mid1] > arr2[mid2]) {
            if((end1 - start1 + 1) % 2 != 0) { // odd size
                end1 = mid1;
                start2 = mid2;
            } else { // even size
                end1 = mid1;
                start2 = mid2 + 1;
            }
        } else { // arr1[mid1] < arr2[mid2]
            if((end1 - start1 + 1) % 2 != 0) { // odd size
                start1 = mid1;
                end2 = mid2;
            } else { // even size
                start1 = mid1 + 1;
                end2 = mid2;
            }
        }
    }

    return std::min(arr1[start1], arr2[start2]);
} /* func get_former_median_of_two_size_equal_sorted_arrays */


// --------------------------------------------------------------------------------------------------------------
// 9.27 Get K-th element in two sorted arrarys of a same size

int _helpGetFormerMedian(const std::vector<int> &arr1, const std::vector<int> &arr2, int s1, int e1, int s2, int e2) {
    int res = -1;
    if(arr1.size() != arr2.size() || arr1.empty()) {
        return res;
    }

    if(arr1.size() == 1) {
        return arr1.front() > arr2.front() ? arr1.front() : arr2.front();
    }

    int mid1 = 0;
    int mid2 = 0;

    while(s1 < e1) {
        mid1 = (s1 + e1) / 2;
        mid2 = (s2 + e2) / 2;
        if(arr1[mid1] == arr2[mid2]) {
            return arr1[mid1]; // or return arr2[mid2]
        } else if(arr1[mid1] > arr2[mid2]) {
            if((e1 - s1 + 1) % 2 != 0) { // odd size
                e1 = mid1;
                s2 = mid2;
            } else { // even size
                e1 = mid1;
                s2 = mid2 + 1;
            }
        } else { // arr1[mid1] < arr2[mid2]
            if((e1 - s1 + 1) % 2 != 0) { // odd size
                s1 = mid1;
                e2 = mid2;
            } else { // even size
                s1 = mid1 + 1;
                e2 = mid2;
            }
        }
    }

    return std::min(arr1[s1], arr2[s2]);
} /* func _helpGetFormerMedian */

int get_kth_element_in_two_sorted_arrays(const std::vector<int> &arr1, const std::vector<int> &arr2, const int k) {
    // arr1 and arr2 must not be empty
    // arr1 and arr2 can be of different size
    if(arr1.empty() || arr2.empty()) {
        return -1;
    }

    // short & long length
    const int slen = std::min(arr1.size(), arr2.size());
    const int llen = std::max(arr1.size(), arr2.size());
    if(k <= 0 || k > slen + llen) {
        return -1;
    }

    // long array and short array
    const std::vector<int> &a1 = slen == (int)arr1.size() ? arr1 : arr2;
    const std::vector<int> &a2 = llen == (int)arr1.size() ? arr1 : arr2;


    if(k <= slen) {
        return _helpGetFormerMedian(a1, a2, 0, k - 1, 0, k - 1);
    } else if(k > llen) { // don't forget now k <= slen + llen
        if(a1[k - llen - 1] > a2[llen - 1]) {
            return a1[k - llen - 1];
        }
        if(a2[k - slen - 1] > a1[slen - 1]) {
            return a2[k - slen - 1];
        }
        return _helpGetFormerMedian(a1, a2, k - llen, slen - 1, k - slen, llen - 1);
    } else { // (k > slen && k <= llen)
        if(a2[k - slen - 1] > a1[slen - 1]) {
            return a2[k - slen - 1];
        }
        return _helpGetFormerMedian(a1, a2, 0, slen - 1, k - slen, k - 1);
    }
} /* func get_kth_element_in_two_size_equal_sorted_arrays */


// --------------------------------------------------------------------------------------------------------------
// 9.28 The TOP-K sum of two number from two arrarys separately
// Notice, the 2 arrarys could be different sizes
// The two number must come from 2 arrarys separately
// K sum number will be returned

// class heapNode {
// public:
//     int m_row;
//     int m_col;
//     int m_value;
// public:
//     heapNode& operator=(const heapNode &n) {
//         m_row = n.m_row;
//         m_col = n.m_col;
//         m_value = n.m_value;
//         return *this;
//     }
//     bool operator==(const heapNode &n) const {
//         if(m_row != n.m_row) {
//             return false;
//         }
//         if(m_col != n.m_col) {
//             return false;
//         }
//         if(m_value != n.m_value) {
//             return false;
//         }
//         return true;
//     }
// public:
//     heapNode() : m_row(-1), m_col(-1), m_value(-1) { }
//     heapNode(int r, int c, int v) : m_row(r), m_col(c), m_value(v) { }
// }; /* heapNode */

class heapNode;

// size is the current heap size
void heapInsert(std::vector<heapNode*> &h, int size, int row, int col, int value) {
    if(h.empty()) {
        return ;
    }
    h[size] = new heapNode(row, col, value);
    // filter up
    int idx = size;
    int parent = (idx - 1) / 2;
    while(idx >= 0) {
        if(h[idx]->m_value > h[parent]->m_value) {
            heapNode *p = h[idx];
            h[idx] = h[parent];
            h[parent] = p;
        } else {
            break;
        }
        idx = parent;
        parent = (idx - 1) / 2;
    }
}

void filterDown(std::vector<heapNode*> &h, int idx, int size) {
    int left = idx * 2 + 1;
    int right = idx * 2 + 2;
    int largest = idx;
    while(left < size) {
        if(h[largest]->m_value < h[left]->m_value) {
            largest = left;
        }
        if(right < size && h[largest]->m_value < h[right]->m_value) {
            largest = right;
        }
        if(largest == idx) {
            break;
        }
        heapNode *p = h[largest];
        h[largest] = h[idx];
        h[idx] = p;
        idx = largest;
        left = idx * 2 + 1;
        right = idx * 2 + 2;
    }
}

heapNode* popHead(std::vector<heapNode*> &h, int size) {
    heapNode *p = h[0];
    h[0] = h[size - 1];
    h[size - 1] = NULL;
    // filter down from 0-th item
    filterDown(h, 0, size - 1);

    return p;
}

bool inHeapNodeCollection(const std::forward_list<heapNode*> &l, int r, int c) {
    for(auto pp : l) {
        if(pp->m_row == r && pp->m_col == c) {
            return false;
        }
    }
    return true;
}

std::vector<int> top_k_sum_from_two_arrays(const std::vector<int> &arr1, const std::vector<int> &arr2, const int k) {
    std::vector<int> res;
    if(arr1.empty() || arr2.empty()) {
        return res;
    }
    const int m = arr1.size();
    const int n = arr2.size();
    if(k < 1 || k > m * n) {
        return res;
    }

    std::vector<heapNode*> heap(k + 1, NULL);
    int heapsize = 0;
    int headR = m - 1;
    int headC = n - 1;
    std::set<heapNode*> coll;// recycle
    std::forward_list<heapNode*> sset;
    heapInsert(heap, heapsize++, headR, headC, arr1[headR] + arr2[headC]);
    while(res.size() != (std::size_t)k) {
        heapNode *p = popHead(heap, heapsize--);
        res.push_back(p->m_value);
        coll.insert(p);
        headR = p->m_row;
        headC = p->m_col;
        if(headR != 0 && !inHeapNodeCollection(sset, headR - 1, headC)) {
            heapInsert(heap, heapsize++, headR - 1, headC, arr1[headR - 1] + arr2[headC]);
            sset.push_front(heap[heapsize - 1]); // a new node was inserted into index 'heapsize - 1'
        }
        if(headC != 0 && !inHeapNodeCollection(sset, headR, headC - 1)) {
            heapInsert(heap, heapsize++, headR, headC - 1, arr1[headR] + arr2[headC - 1]);
            sset.push_front(heap[heapsize - 1]); // a new node was inserted into index 'heapsize - 1'
        }
    }

    // Clean up
    for(auto &p : heap) {
        if(p != nullptr) {
            delete p;
            p = nullptr;
        }
    }
    for(auto p : coll) {
        if(p != nullptr) {
            delete p;
            p = nullptr;
        }
    }

    return res;
} /* top_k_sum_from_two_arrays */


// --------------------------------------------------------------------------------------------------------------
// 9.29 Print k strings whose times appeared rank in top k
// Including 2 issues
//  (1)
//  (2) Design a TopKRecord structure, which will print top k strings
//      at any time

// Solution to issue (1)

// Word Times Node
// also available for solution to issue(2)
// class wtnode {
// public:
//     wtnode() : m_str(std::string()), m_times(0) { }
//     wtnode(const std::string &str, int t) : m_str(str), m_times(t) { };
// 
// public:
//     std::string m_str;
//     int m_times;
// 
// };

// Filter up for min root heap
void heap_insert(std::vector<wtnode*> &h, int pos, wtnode *n) {
    const int sz = h.size();
    assert(sz > pos);
    assert(pos >= 0);
    h[pos] = n;
    int parent = (pos - 1) / 2;
    while(parent >= 0) {
        if(h[pos]->m_times < h[parent]->m_times) {
            wtnode *tmp = h[parent];
            h[parent] = h[pos];
            h[pos] = tmp;
            pos = parent;
            parent = (pos - 1) / 2;
        } else {
            break;
        }
    }
}

void heapify(std::vector<wtnode*> &h, int sz) {
    assert(!h.empty());
    int i = 0;
    int left = i * 2 + 1;
    int right = i * 2 + 2;
    while(left < sz) {
        int j = i;
        if(h[left]->m_times < h[j]->m_times) {
            j = left;
        }
        if(right < sz && h[right]->m_times < h[j]->m_times) {
            j = right;
        }
        if(j == i) {
            break;
        }

        wtnode *tmp = h[i];
        h[i] = h[j];
        h[j] = tmp;

        i = j;
        left = i * 2 + 1;
        right = i * 2 + 2;
    }
}

bool cmpFunc(wtnode *pa, wtnode *pb) {
    return pa->m_times < pb->m_times;
}

std::vector<std::string> get_top_k_times_strings(const std::vector<std::string> &vstr, int k) {
    std::vector<std::string> res;
    const int len = vstr.size();
    if(k < 1 || k > len) {
        return res;
    }

    std::map<std::string, int> smap;
    for(const auto &s : vstr) {
        if(smap.find(s) == smap.end()) {
            smap[s] = 1;
        } else {
            smap[s]++;
        }
    }

    int cnt = 0;
    // min root heap
    std::vector<wtnode*> heap(k, nullptr);
    for(const auto &p : smap) {
        if(cnt < k) {
            wtnode *n = new wtnode(p.first, p.second);
            heap_insert(heap, cnt, n);
            cnt++;
        } else {
            if(p.second > heap.front()->m_times) {
                wtnode *n = new wtnode(p.first, p.second);
                wtnode *d = heap.front();
                heap[0] = nullptr;
                if(d) { delete d; }
                heap[0] = n;
                heapify(heap, heap.size());
            }
        }
    }

    // Print in order
    std::sort(heap.begin(), heap.end(), cmpFunc);

    res.clear();
    for(int i = 0; i < k; i++) {
        res.emplace_back(heap[i]->m_str);
    }

    // clean up
    for(int i = 0; i < k; i++) {
        wtnode *p = heap[i];
        heap[i] = nullptr;
        delete p;
    }

    return res;
}

// [TIME_STAMP] Stop at 17:24, 2018/02/10


// [TIME_STAMP] Start at 16:15, 2018/02/25
//
// Solution to issue (2)

// class TopKRecord {
// public:
//     TopKRecord(int k) : m_ksize(k), m_cnt(0) {
//         m_heap = std::vector<wtnode*>(m_ksize, nullptr);
//     }
// 
// public:
//     void addString(const std::string &s);
//     void printTopK();
// 
// private:
//     int heapInsert(std::vector<wtnode*> &h, int pos, wtnode *n); // Insert a node at pos
//     int heapify(std::vector<wtnode*> &h, int sz, int pos); // from pos filter down
// 
// private:
//     int m_ksize;
//     int m_cnt;
//     std::map<std::string, int> m_smap; // string & times map
//     std::map<std::string, int> m_pmap; // string & position in m_heap
//     std::vector<wtnode*> m_heap; // min root heap
// }; // class TopKRecord
// 
// 
// // Filter up, return position in heap after insertion
// int TopKRecord::
// heapInsert(std::vector<wtnode*> &h, int pos, wtnode *n) {
//     const int sz = h.size();
//     assert(sz > pos);
//     assert(pos >= 0);
//     h[pos] = n;
//     int parent = (pos - 1) / 2;
//     while(parent >= 0) {
//         if(h[pos]->m_times < h[parent]->m_times) {
//             wtnode *tmp = h[parent];
//             h[parent] = h[pos];
//             h[pos] = tmp;
//             pos = parent;
//             parent = (pos - 1) / 2;
//         } else {
//             break;
//         }
//     }
// 
//     return pos;
// }
// 
// int TopKRecord::
// heapify(std::vector<wtnode*> &h, int sz, int pos) {
//     assert(!h.empty());
//     int i = pos;
//     int left = i * 2 + 1;
//     int right = i * 2 + 2;
//     while(left < sz) {
//         int j = i;
//         if(h[left]->m_times < h[j]->m_times) {
//             j = left;
//         }
//         if(right < sz && h[right]->m_times < h[j]->m_times) {
//             j = right;
//         }
//         if(j == i) {
//             break;
//         }
//         // Swap pointers
//         wtnode *tmp = h[i];
//         h[i] = h[j];
//         h[j] = tmp;
//         // Prepare for next loop
//         i = j;
//         left = i * 2 + 1;
//         right = i * 2 + 2;
//     }
// 
//     return i;
// }
// 
// void TopKRecord::
// addString(const std::string &s) {
//     std::map<std::string, int>::iterator i = m_smap.find(s);
//     if(i == m_smap.end()) {
//         m_smap[s] = 1;
//         if(m_cnt < m_ksize) {
//             wtnode *p = new wtnode(s, 1);
//             int pos = heapInsert(m_heap, m_cnt, p);
//             m_pmap[s] = pos;
//             m_cnt++;
//         }
//     } else {
//         i->second++; // or m_smap[s]++;
//         std::map<std::string, int>::iterator j = m_pmap.find(s);
//         if(j != m_pmap.end()) { // Already in heap
//             int pos = heapify(m_heap, m_cnt, j->second);
//             m_pmap[s] = pos;
//         } else { // not in heap
//             if(m_cnt < m_ksize) {
//                 wtnode *p = new wtnode(s, 1);
//                 int pos = heapInsert(m_heap, m_cnt, p);
//                 m_pmap[s] = pos;
//                 m_cnt++;
//             } else {
//                 wtnode *p = m_heap.front();
//                 if(p->m_times < i->second) {
//                     m_heap[0] = nullptr;
//                     m_pmap.erase(p->m_str);
//                     delete p;
//                     m_heap[0] = new wtnode(i->first/*'s'*/, i->second);
//                     int pos = heapify(m_heap, m_cnt, 0);
//                     m_pmap[s] = pos;
//                 }
//             }
//         }
//     }
// }
// 
// 
// void TopKRecord::
// printTopK() {
//     if(m_cnt == 0) {
//         printf("Warning: No strings inserted yet\n");
//         return ;
//     }
// 
//     for(int i = 0; i < m_cnt; i++) {
//         // std::cout << "No. " << i + 1 << ", String: " << m_heap[i]->m_str << ", Times: " << m_heap[i]->m_times << "\n";
//         printf("No. %d, String: %s, Times: %d\n", i + 1, m_heap[i]->m_str.c_str(), m_heap[i]->m_times);
//     }
// }

// [TIME_STAMP] Stop at 17:28, 2018/02/25


// [TIME_STAMP] Start at 11:37, 2018/03/04
// --------------------------------------------------------------------------------------------------------------
// 9.30 Algorithm Manacher - Get the longest palindrome(substring) of a string

const std::string convert_to_istring(const std::string &s) {
    std::string res;
    if(s.empty()) {
        return res;
    }

    res.push_back('#');
    for(const char c : s) {
        res.push_back(c);
        res.push_back('#');
    }

    return res;
}


// pArr[..] - pArr is an array, the size of it is same as istring(converted intermediate string)
//            represent the radius of max palindrome is center is 'i'
// pR       - Position, one after the all max radius palindrome before current
//            Position in the loop
//            Initial value is -1
// index    - The center of palindrome when pR is updated
//            If pR remain unchanged, index remain unchanged
//            So index is corresponded to pR



int max_palindrome_size(const std::string &str) {
    int res = 0;
    if(str.empty()) {
        return res;
    }

    std::string s = convert_to_istring(str);
    const int len = s.size();

    std::vector<int> pArr(len, 0);
    int pR = -1;
    int index = 0;

    int max = std::numeric_limits<int>::min();

    for(int i = 0; i < len; i++) {
        if(pR - 1 < i) {
            int u = i;
            int l = i;
            while(u < len && l > -1) {
                if(s[u + 1] == s[l - 1]) {
                    u++;
                    l--;
                    continue;
                } else {
                    break;
                }
            }
            pArr[i] = u - i; // or 'i - l'
            if(pR < u + 1) {
                pR = u + 1;
                index = i;
            }
        } else { // pR - 1 >= i, i.e. i is inside 'pR - 1'
            if(i + pArr[2 * index - 1] > pR - 1) {
                pArr[i] = pR - i;
            } else if(i + pArr[2 * index - 1] < pR - 1) {
                pArr[i] = pArr[2 * index - 1];
            } else { // i + pArr[2 * index - 1] == pR - 1
                int u = pR - 1;
                int l = i - pArr[2 * index - 1];
                while(u < len && l > -1) {
                    if(s[u + 1] == s[l - 1]) {
                        u++;
                        l--;
                        continue;
                    } else {
                        break;
                    }
                }
                pArr[i] = u - i; // or 'i - l'
                if(pR < u + 1) {
                    pR = u + 1;
                    index = i;
                }
            }
        }
        max = std::max(pArr[i], max);
    }

    res = max;
    return res;
}


// --------------------------------------------------------------------------------------------------------------
// 9.31 KMP Algorithm

const std::vector<int> get_next_array(const std::string &m) {
    const int len = m.size();
    std::vector<int> next(len, 0);

    if(len == 0) {
        return next;
    }
    if(len == 1) {
        next[0] = -1;
        return next;
    }
    if(len == 2) {
        next[0] = -1;
        next[1] = 0;
        return next;
    }

    int pos = 2;
    int cn = 0;
    while(pos < len) {
        if(m[pos - 1] == m[cn]) {
            next[pos++] = ++cn;
        } else if(cn > 0) {
            cn = next[cn];
        } else {
            next[pos++] = 0;// now cn should be 0
        }
    }

    return next;
}

// Find first position of 'm' in string 's'
// If not found, return -1
int kmp(const std::string &s, const std::string &m) {
    int mi = 0;
    int si = 0;
    int mlen = m.size();
    int slen = s.size();

    std::vector<int> next(get_next_array(m));
    while(si < slen && mi < mlen) {
        if(s[si] == m[mi]) {
            si++;
            mi++;
        } else if(next[mi] <= 0) {
            si++;
            mi = 0;
        } else {
            mi = next[mi];
        }
    }

    // Can also be:
    // return mi == mlen ? si - mi : -1;
    return mi == mlen ? si - mlen : -1;
}


// --------------------------------------------------------------------------------------------------------------
// 9.32 Issue of throwing chess pieces

// Solution 1:
//  P(N, K) means min throwing times under worst circumstances if floor is N high and
//          number of chess pieces is K
//  P(0, K) if floor number is 0, it means no floor, so no need to throw chess piece
//          Obviously its value is 0
//  P(N, 1) if there's only one chess piece(K=1), then has to throw N times, obviously

int _chessFloorProcess1(int nLevel, int kChess) {
    if(nLevel == 0) {
        return 0;
    }
    if(kChess == 1) {
        return nLevel;
    }
    int min = std::numeric_limits<int>::max();
    for(int i = 1; i < nLevel; i++) {
        int t = std::max(_chessFloorProcess1(i - 1, kChess - 1) + 1, _chessFloorProcess1(nLevel - i, kChess) + 1);
        min = std::min(min, t);
    }

    return min;
}

int chessFloorProcess1(int nLevel, int kChess)  {
    if(nLevel < 1 || kChess < 1) {
        return 0;
    }
    return _chessFloorProcess1(nLevel, kChess);
}

// solution 2: DP solution
// dp[0][j] - 0
// dp[i][1] - i
// dp[i][j] = MIN( MAX(dp[p - 1][j - 1], dp[i - p][j]) ), 1 <= p <= i

int chessFloorProcess2(int nLevel, int kChess) {
    int res = 0;
    if(nLevel < 1 || kChess < 1) {
        return res;
    }
    if(kChess == 1) {
        return nLevel;
    }

    int **dp = CU::get_matrix(nLevel + 1, kChess + 1);
    for(int k = 1; k < kChess + 1; k++) {
        dp[0][k] = 0;
    }
    for(int i = 1; i < nLevel + 1; i++) {
        dp[i][1] = i;
    }

    for(int j = 2; j < kChess + 1; j++) {
        for(int i = 1; i < nLevel + 1; i++) {
            int min = std::numeric_limits<int>::max();
            for(int t = 1; t <= i; t++) {
                min = std::min(std::max(dp[t - 1][j - 1], dp[i - t][j]), min);
            }
            dp[i][j] = min + 1;
        }
    }
    res = dp[nLevel][kChess];

    CU::free_matrix(dp, nLevel, kChess);
    return res;
}



// --------------------------------------------------------------------------------------------------------------
// 9.33 Artisan-Painter Issue
// Description:
//  Given an array(arr), each element is positive and represents the time to finish a painting
//  besides, given the number of artisan painters(num), and each painter could only finish adjacent
//  paintings(in the array)
// Issue:
//  Get the min time to finish all the paintings

// Solution:
// Assume dp[i][j] represents the time to finish 'j' + 1 paintings(arr[0..j]) with 'i' artisan painters
// So,
// (1) 1..i-1 pinters for arr[0],    painter i for arr[1..j] -> MAX{ dp[i-1][0], SUM(arr[1..j]) } -> T(1)
// (2) 1..i-1 pinters for arr[0..1], painter i for arr[2..j] -> MAX{ dp[i-1][1], SUM(arr[2..j]) } -> T(2)
// (3) 1..i-1 pinters for arr[0..2], painter i for arr[3..j] -> MAX{ dp[i-1][2], SUM(arr[3..j]) } -> T(3)
// ... ...
// (k) 1..i-1 pinters for arr[0..k], painter i for arr[k+1..j] -> MAX{ dp[i-1][k], SUM(arr[k+1..j]) } -> T(k)
// ... ...
// (j) 1..i-1 pinters for arr[0..j-1], painter i for arr[j] -> MAX{ dp[i-1][j-1], SUM(arr[j]) } -> T(j)
//
// So last,
// MinTime = MIN{T(n)}, 1 <= n <= j

int artisanPainterIssue(const std::vector<int> &ivec, const int num) {
    if(ivec.empty() || num < 1) {
        return -1;
    }

    int res = 0;
    const int n = ivec.size();
    int **dp = CU::get_matrix(num, n);
    // Second row
    dp[1][0] = ivec[0];
    for(int j = 1; j < n + 1; j++) {
        dp[1][j] = dp[1][j - 1] + ivec[j];
    }
    // First column
    for(int i = 1; i < num; i++) {
        dp[i][1] = ivec[0];
    }

    std::vector<int> sum(n, 0);
    sum[0] = ivec[0];
    for(int k = 0; k < n; k++) {
        sum[k] = sum[k - 1] + ivec[k];
    }

    for(int i = 2; i < num; i++) {
        for(int j = 1; j < n; i++) {
            int min = std::numeric_limits<int>::max();
            int tmp = sum[j];
            for(int k = 0; k < j; k++) {
                tmp -= ivec[k];
                min = std::min(min, std::max(dp[i - 1][j - 1], tmp));
            }
            dp[i][j] = min;
        }
    }
    res = dp[num - 1][n - 1];

    CU::free_matrix(dp, num, n);
    return res;
}

// [TIME_STAMP] Stop at 17:11, 2018/03/04


// [TIME_STAMP] Start at 15:49, 2018/03/10
// --------------------------------------------------------------------------------------------------------------
// 9.34 Where to build post offices
// Description:
// Given an array(int), each element represents the coordinate in the line(1-Dimension) of resident, and
// given a number(num), select 'num' resident location to build post offices and make sure the total distance
// of residential location to nearest post office is minimum, the return the total distance as result
// Notice that the post office could only be built on the location of residents


// Solution
// First, consider the following issue: assume 0 <= i <= j <= N(N is the length of the array),
// if to choose only on residential place to build one post office, what is the min total distance?
// Because 0 <= i <= N and 0 <= j <= N and 0 <= i <= j <= N, so the results would be a half matrix
// Assume w[i][j] represent the min total distance of building only one postoffice in range [i,...,j]
// then only those above diagnal is required (since i<=j)
// Obviously, the centeral point(resident) of the array is best place to build the postoffice
//
// Situation (1):
//  If length of arr[i..j - 1] is odd(it indicates 'i' and 'j-1' are either both odd or both even),
//  then the place(residential coordinate) to build is arr[(i + j - 1)/2], and (i+j-1)/2 is the central
//  point. Assume the result is w[i][j-1].
//  Thus in this case, the length of arr[i..j] is even, so it has 2 central points, and the first one is
//  arr[(i+j)/2], and the second one is arr[(i+j+1)/2], choose either one and the final result(min total
//  distance) is the same.
//  Since (i+j)/2 is the same as (i+j-1)/2, so it is the same central point of arr[i..j-1] mentioned above,
//  So here we choose arr[(i+j)/2].
//  Thus compared to w[i][j-1], w[i][j] is just contributed by the last residential point arr[j], and its
//  distance to postoffice is arr[j] - arr[(i+j)/2], so it comes to a conclusion:
//  w[i][j] = w[i][j-1] + arr[j] - arr[(i+1)/2]
//
// Situation (2):
//  If length of arr[i..j-1] is even, it has 2 central residential point, i.e. arr[(i+j-1)/2] and arr[(i+j)/2]
//  here we choose the second one to build postoffice(reason see the following)
//  So similar to situation (1), then the length of arr[i..j] is odd, it has only 1 central point, which is
//  arr[(i+j)/2], so the additional distance contributed by arr[j] is arr[j] - arr[(i+j)/2]
//  And now arr[(i+j)/2] is the same residential point in arr[i..j-1], so it comes to a conclusion:
//  w[i][j] = w[i][j-1] + arr[j] - arr[(i+1)/2]
//
// Thus considering the 2 situations above, we have
//  w[i][j] = w[i][j-1] + arr[j] - arr[(i+1)/2]
//
// Notice we don't have to resolve those below diagonal(where i>j), and when i==j, w[i][j] is 0
//
// Till now, we have matrix 'w'
// Use dynamic programming method, dp[a][b] means the min total distance to build 'a' postoffices
// in [0..b] residentials
//
// Leave dp[0][0..N-1] alone since they have no meaning
// Obviously dp[1][0..N-1] can be directly got from matrix w
//
//
// For the rest:
//   dp[i][j]
//   0 <= i <= num
//   0 <= j <= N - 1
//   i <= j
//
//   i-1 responsible for [0...j-1], i responsible for [j...j]
//   i-1 responsible for [0...j-2], i responsible for [j-1...j]
//   i-1 responsible for [0...j-3], i responsible for [j-2...j]
//   ...
//   i-1 responsible for [0...i-2], i responsible for [i-1...j]
//
//   i-1 responsible for [0..k], i responsible for [k+1..j], i-2 <= k <= j-1
//   i.e. dp[i-1][k] + w[k+1][j], i-2 <= k <= j-1





int min_distance_from_residents_to_postoffices(const std::vector<int> &arr, const int num) {
    int res = -1;
    if(arr.empty() || num <= 0) {
        return res;
    }
    const int N = arr.size();
    if(num == N) {
        return 0;
    }
    if(num > N) {
        return res;
    }


    // First get matrix 'w'
    int **w = CU::get_matrix(N, N);

    // Set all values in w to 0
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            w[i][j] = 0;
        }
    }

    // Set diagnal to 0
    // Since now all the values are 0
    // So this step can be skipped

    // Compute values above diagonal
    for(int i = 0; i < N; i++) {
        for(int j = i + 1; j < N; j++) {
            w[i][j] = w[i][j-1] + arr[j] - arr[(i+j)/2];
        }
    }

    int **dp = CU::get_matrix(num + 1, N);

    // Set all values in dp to 0
    for(int i = 0; i < num + 1; i++) {
        for(int j = 0; j < N; j++) {
            dp[i][j] = 0;
        }
    }

    // dp[1][0..N-1]
    for(int j = 0; j < N; j++) {
        dp[1][j] = w[0][j];
    }

    // diagonal dp[i+1][i], 0 <= i <= num - 1
    // dp[i+1][i] means building 'i+1' postoffices for [0,...,i], 0 <= i <= num - 1
    // Obviously they are all 0
    for(int k = 0; k < num; k++) {
        dp[k+1][k] = 0;
    }

    // Rest
    for(int i = 2; i <= num; i++) {
        for(int j = i; j < N; j++) {
            int min = std::numeric_limits<int>::max();
            for(int k = j - 1; k >= i - 2; k--) {
                min = std::min(min, dp[i-1][k] + w[k+1][j]);
            }
            dp[i][j] = min;
        }
    }
    res = dp[num][N-1];

    CU::free_matrix(w, N, N);
    CU::free_matrix(dp, num+1, N);

    return res;
}
// [TIME_STAMP] Stop at 17:40, 2018/03/10


} // namespace C9

namespace C9 {


void test_9_XX() {
	int a[9] = {9, 3, 1, 2, 5, 3, 4, 8, 7};
	std::vector<int> arr(a, a + 9);
	int res = get_first_unformed_number(arr);
	printf("RES: %d\n", res);

	res = get_first_unformed_number_0(arr);
	printf("RES: %d\n", res);

	res = get_first_unformed_sum(arr);
	printf("RES: %d\n", res);
}


}; // namespace C8
