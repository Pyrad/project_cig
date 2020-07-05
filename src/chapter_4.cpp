/*
 * chapter_4.hpp
 *
 *  Created on: Oct. 5, 2017
 *      Author: Pyrad
 * Description: Source file of chapter 4 Dynamic Planning
 *   Intention: Solutions for problems in Chapter 4[Dynamic Planning] of Code Interview Guide
 */


#include "chapter_4.hpp"

namespace common_utils {
	int** get_matrix(int row, int col);
	void free_matrix(int **m, int row, int col);
}

namespace C4 {

// [TIME_STAMP] Start at 20:00, 2017/09/19

// --------------------------------------------------------------------------------------------------------------
// 4.1 Fibonacci issue
//     Stages issue
//     Cows and their descendant issue

//------------Fibonacci--------------------
// Recursive resolution
int fibonacci(int n) {
	if(n < 1) {
		return 0;
	}

	if(n == 1 || n == 2) {
		return 1;
	}

	return fibonacci(n - 1) + fibonacci(n - 1);
}

// Dynamic planning resolution
int fibonacci_dp(int n) {
	if(n <= 0) {
		return 0;
	}

	if(n == 1 || n == 2) {
		return 1;
	}

	int tmp = 1;
	int pre = 1;
	int cur = 0;
	for(int i = 2; i < n; i++) {
		cur = pre + tmp;
		tmp = pre;
		pre = cur;
	}

	return cur;
}

//------------Stages--------------------
// Recursive resolution
int stages(int n) {
	if(n <= 0) {
		return 0;
	}

	if(n <= 2) {
		return n;
	}

	return stages(n - 1) + stages(n -2);
}

// Dynamic planning resolution
int stages_dp(int n) {
	if(n <= 0) {
		return 0;
	}

	if(n <=2 ) {
		return n;
	}

	int ppre = 1;
	int pre = 2;
	int cur = 0;
	for(int i = 2; i < n; i++) {
		cur = ppre + pre;
		ppre = pre;
		pre = cur;
	}

	return cur;
}

//------------Cows & descendants-------------------
// Recursive resolution
int cows_descendants(int n) {
	if(n <= 0) {
		return 0;
	}

	if(n <= 3) {
		return n;
	}

	return cows_descendants(n - 1) + cows_descendants(n - 3);
}

// Dynamic planning resolution
int cows_desendants_dp(int n) {
	if(n <= 0) {
		return 0;
	}

	if(n <= 3) {
		return n;
	}

	int pppre = 1;
	int ppre = 2;
	int pre = 3;
	int cur = 0;

	for(int i = 3; i < n; i++) {
		cur = pre + pppre;
		pppre = ppre;
		ppre = pre;
		pre = cur;
	}

	return cur;
}

// --------------------------------------------------------------------------------------------------------------
// 4.2 Minimum route length in matrix from top left to bottom right
// Allocate a matrix same as input matrix
int min_route_len_in_matrix(int **m, int row, int col) {
	if(!m) {
		return -1;
	}

	if(row < 2 || col < 2) {
		printf("Error row and column\n");
		return -1;
	}
	int res = -1;

	int **dp = common_utils::get_matrix(row, col);
	if(!dp) {
		return -1;
	}

	dp[0][0] = m[0][0];
	// First row
	for(int j = 1; j < col; j++) {
		dp[0][j] = dp[0][j - 1] + m[0][j];
	}
	// First column
	for(int i = 1; i < row; i++) {
		dp[i][0] = dp[i - 1][0] + m[i][0];
	}

	for(int i = 1; i < row; i++) {
		for(int j = 1; j < col; j++) {
			dp[i][j] = std::min(dp[i - 1][j], dp[i][j - 1]) + m[i][j];
		}
	}
	res = dp[row - 1][col - 1];
	common_utils::free_matrix(dp, row, col);

	return res;
}

// Just allocate an array(space saving)
int min_route_len_in_matrix_space_saving(int **m, int row, int col) {
	if(!m) {
		return -1;
	}

	if(row < 2 || col < 2) {
		printf("Error row and column\n");
		return -1;
	}
	int res = -1;

	int array_len = std::min(row, col);
	bool is_row_len = array_len == row;
	int *dp = new int[array_len];
	dp[0] = m[0][0];
	for(int i = 1; i < array_len; i++) {
		if(is_row_len) {
			dp[i] = dp[i - 1] + m[i][0];
		} else {
			dp[i] = dp[i - 1] + m[0][i];
		}
	}

	int n = is_row_len ? col : row;
	for(int i = 1; i < n; i++) {
		dp[0] += is_row_len ? m[0][i] : m[i][0];
		for(int j = 1; j < array_len; j++) {
			if(is_row_len) {
				dp[j] = std::min(dp[j], dp[j - 1]) + m[j][i];
			} else {
				dp[j] = std::min(dp[j], dp[j - 1]) + m[i][j];
			}
		}
	}

	res = dp[array_len - 1];

	delete [] dp;

	return res;
}

// [TIME_STAMP] Stop at 22:51, 2017/09/19



// [TIME_STAMP] Start at 20:48, 2017/09/20


// --------------------------------------------------------------------------------------------------------------
// 4.3 Money Exchange
// (1) Minimum number of sheets for money exchange(NO sheet limits for each nominal value)
// (2) Minimum number of sheets for money exchange(HAS sheet limits for each nominal value)

int mini_exchange(const std::vector<int>& ivec, const int aim) {
	int res = -1;

	if(ivec.empty()) {
		return res;
	}

	const int m = ivec.size();
	// Allocate a matrix, rows is 'n', columns is aim + 1
	// dp[i][j] means the minimum number of sheets by using ivec[0..i] to consist of money 'j'
	int **dp = common_utils::get_matrix(m, aim + 1);

	// first row
	for(int k = 0; k < aim + 1; k++) {
		if( k % ivec[0] == 0) {
			dp[0][k] = k / ivec[0];
		} else {
			dp[0][k] = -1; // negative means it can't be consisted of
		}
	}

	/*
	 * Some analysis
	dp[i][j]

	Use only 0...i-1 to consist of aim 'j', dp[i-1][j]
	Use 0...i-1 and 1 sheet of array[i] to consist of aim 'j', dp[i-1][j-array[i]] + 1
	Use 0...i-1 and 2 sheet of array[i] to consist of aim 'j', dp[i-1][j-2*array[i]] + 2
	Use 0...i-1 and 3 sheet of array[i] to consist of aim 'j', dp[i-1][j-3*array[i]] + 3
	...
	Use 0...i-1 and k sheet of array[i] to consist of aim 'j', dp[i-1][j-k*array[i]] + k
	(j-k*array[i] >= 0, k >=0)
	...

	So, min_sheets = min{ dp[i-1][j], dp[i-1][j-k*array[i]] + k}, (j-k*array[i] >= 0, k >=1)

	Use 0...i-1 and (t+1) sheet of array[i] to consist of aim 'j', dp[i-1][j-(t+1)*array[i]] + (t+1)
	(j-(t+1)*array[i] >= 0, (t+1) >=1),
	Which also is,
	Use 0...i-1 and (t+1) sheet of array[i] to consist of aim 'j', dp[i-1][j-t*array[i] - array[i]] + t + 1
	(j-(t+1)*array[i] >= 0, t >= 0)
	i.e.
	Use only 0...i-1 to consist of aim 'j-array[i]', dp[i-1][j-array[i]]
	Use 0...i-1 and 1 sheet of array[i] to consist of aim 'j-array[i]', dp[i-1][j-array[i] - array[i]] + 1
	Use 0...i-1 and 2 sheet of array[i] to consist of aim 'j', dp[i-1][j- array[i]-2*array[i]] + 2
	Use 0...i-1 and 3 sheet of array[i] to consist of aim 'j', dp[i-1][j- array[i]-3*array[i]] + 3
	...
	Use 0...i-1 and k sheet of array[i] to consist of aim 'j', dp[i-1][j- array[i]-t*array[i]] + t
	(j-t*array[i] >= 0, t >=0)
	So indeed this is dp[i][j-array[i]], which is to say,
	dp[i-1][j-t*array[i] - array[i]] + t+1 (j-(t+1)*array[i] >= 0, t >= 0), equals,
	dp[i][j-array[i]].
	Finally,
	dp[i][j] = min_sheets = min{ dp[i-1][j], dp[i][j-array[i]] + 1}
	 */

	// from 2nd row to the last row
	int temp = -1;
	for(int k = 1; k < m; k++) {
		dp[k][0] = 0;
		for(int h = 1; h < aim + 1; h++) {
			temp = -1;
			if(h - ivec[k] >= 0 && dp[k][h - ivec[k]] != - 1) {
				temp = dp[k][h-ivec[k]] + 1;
			}
			if(temp != -1 && dp[k - 1][h] != -1) {
				dp[k][h] = std::min(dp[k - 1][h], temp);
			} else if( temp != -1) {
				dp[k][h] = temp;
			} else if( dp[k - 1][h] != -1 ) {
				dp[k][h] = dp[k - 1][h];
			} else {
				dp[k][h] = -1;
			}
		}
	}

	res = dp[m - 1][aim]; // if -1, means can't be exchanged
	common_utils::free_matrix(dp, m, aim + 1);

	return res;
}

int mini_exchange_space_saving(const std::vector<int>& ivec, const int aim) {
	int res = -1;

	if(ivec.empty()) {
		return res;
	}

	const int m = ivec.size();
	std::vector<int> pre_dp;
	pre_dp.resize(m);

	std::vector<int> dp;
	dp.resize(m);

	dp[0] = 0;

	// First row
	for(int k = 0; k < aim + 1; k++) {
		if( k % ivec[0] == 0) {
			dp[k] = k / ivec[0];
		} else {
			dp[k] = -1; // negative means it can't be consisted of
		}
	}
	pre_dp.swap(dp);

	// from 2nd row to the last row (which is m-1)
	for(int i = 1; i < m; i++) {
		dp[0] = 0;
		for(int j = 1; j < aim + 1; j++) {
			if(j - ivec[i] < 0) {
				// dp[j] = dp[j];
				continue;
			} else {
				if(pre_dp[j] != -1 && pre_dp[j - ivec[i]] != -1) {
					dp[j] = std::min(pre_dp[j], pre_dp[j - ivec[i]]);
				} else if(pre_dp[j] != -1) {
					dp[j] = pre_dp[j];
				} else if(pre_dp[j - ivec[i]] != -1) {
					dp[j] = pre_dp[j - ivec[i]];
				} else {
					dp[j]  = -1;
				}
			}
		}
		pre_dp.clear();
		pre_dp.swap(dp);
	}

	res = pre_dp[aim];

	return res;
}

// [TIME_STAMP] Stop at 22:50, 2017/09/20



// [TIME_STAMP] Start at 20:06, 2017/09/21

int mini_exchange_sheets_limit(const std::vector<int>& ivec, const int aim) {
	int res = -1;

	if(ivec.empty()) {
		return res;
	}

	const int m = ivec.size();
	// dp[i][j] means the minimum number of sheets by using ivec[0..i] to consist of money 'j'
	int **dp = common_utils::get_matrix(m, aim + 1);

	// First row
	dp[0][0] = 0;
	for(int i = 1; i < aim + 1; i++) {
		if(ivec[0] == i) {
			dp[0][i] = 1; // Because ivec[0] only has one sheet for its value
		} else {
			dp[0][i] = -1; // Because others can't be consisted of by ivec[0] alone
		}
	}

	// From 2nd row to the last row, which is m - 1
	// dp[i][j] could be
	//  (1) Don't use ivec[i], use only ivec[0...i-1] to consist of 'j', so dp[i][j] = dp[i-1][j]
	//  (2) Use ivec[i], as a result use and only use ivec[0..i-1] to consist of 'j-ivec[i]', so dp[i][j] = dp[i-1][j-ivec[i]]
	//      But if j - ivec[i] < 0, then it means we're not able to use ivec[0..i-1] to consist of 'j-ivec[i]'
	for(int i = 1; i < m; i++) {
		dp[i][0] = 0; // First column is always 0, since no need to consist of 0
		for(int j = 1; j < aim + 1; j++) {
			if(j - ivec[i] < 0) {
				dp[i][j] = dp[i - 1][j]; // no matter if dp[i - 1][j] is -1
			} else {
				if(dp[i-1][j] != -1 && dp[i-1][j-ivec[i]] != -1) {
					dp[i][j] = std::min(dp[i-1][j], dp[i-1][j-ivec[i]]);
				} else if(dp[i-1][j] != -1) {
					dp[i][j] = dp[i-1][j];
				} else if(dp[i-1][j-ivec[i]] != -1) {
					dp[i][j] = dp[i-1][j-ivec[i]];
				} else {
					dp[i][j] = -1;
				}
			}
		}
	}

	res = dp[m - 1][aim];

	common_utils::free_matrix(dp, m, aim + 1);

	return res;
}


int mini_exchange_sheets_limit_space_saving(const std::vector<int>& ivec, int aim) {
	int res = -1;

	if(ivec.empty()) {
		return res;
	}

	const int m = ivec.size();
	std::vector<int> pre_dp;
	pre_dp.resize(m);

	std::vector<int> dp;
	dp.resize(m);

	dp[0] = 0;

	// First row
	for(int i = 0; i < aim + 1; i++) {
		if(ivec[0] == i) {
			dp[i] = 1;
		} else {
			dp[i] = -1;
		}
	}
	pre_dp.swap(dp);

	for(int i = 1; i < m; i++) {
		dp[0] = 0;
		for(int j = 1; j < aim + 1; j++) {
			if(j - ivec[i] < 0) {
				dp[j] = pre_dp[j]; // no matter if pre_dp[j] is -1 or not
			} else {
				if(pre_dp[j] != -1 && pre_dp[j - ivec[i]] != -1) {
					dp[j] = std::min(pre_dp[j], pre_dp[j-ivec[i]]);
				} else if(pre_dp[j] != -1) {
					dp[j] = pre_dp[j];
				} else if(pre_dp[j - ivec[i]] != -1) {
					dp[j] = pre_dp[j - ivec[i]];
				} else {
					dp[j] = -1;
				}
			}
		}
		pre_dp.clear();
		pre_dp.swap(dp);
	}

	res = pre_dp[aim];

	return res;
}


// --------------------------------------------------------------------------------------------------------------
// 4.4 Money Exchange
// The total ways to exchange money 'aim' by using several sheets of values(an array)
// Each value in the array can be used several times

int exchange_ways_1(const std::vector<int>& ivec, int aim) {
	int res = 0;

	if(ivec.empty()) {
		return res;
	}

	// allocate a matrix, row number is ivec.size(), and column number is aim + 1
	const int m = ivec.size();
	int **dp = common_utils::get_matrix(m, aim + 1);

	// dp[i][j] means how many ways could be used to consist of 'j' by ivec[0..i]

	// first column
	for(int k = 0; k < m; k++) {
		dp[k][0] = 1; // since target value is 0, so no need to use any ivec[0...k]
	}

	// first row
	for(int k = 0; k < aim + 1; k++) {
		if(k % ivec[0] == 0) {
			dp[0][k] = 1; // only those k could be divided by ivec[0] can be consisted of
		} else {
			dp[0][k] = 0;
		}
	}

	/*
	 * dp[i][j]
	 * 	(1) use just ivec[0..i-1] to consist of 'j' and 0 sheet ivec[i]
	 * 	(2) use just ivec[0..i-1] to consist of 'j -     ivec[i]' and 1 sheet ivec[i]
	 * 	(3) use just ivec[0..i-1] to consist of 'j - 2 * ivec[i]' and 2 sheets ivec[i]
	 * 	...
	 * 	(k) use just ivec[0..i-1] to consist of 'j - k * ivec[i]' and k sheets ivec[i], here j - k * ivec[i] >= 0
	 * 	...
	 *
	 *
	 * 	finally, dp[i][j] = sum of dp[i-1][j - k * ivec[i] ], here k >= 0 && j - k * ivec[i] >= 0
	 */

	for(int i = 1; i < m; i++) {
		// no need to set first column as it has been set already previously
		for(int j = 1; j < aim + 1; j++) {
			int num = 0;
			for(int k = 0; j - k * ivec[i] >= 0; k++) {
				num += dp[i-1][j-k*ivec[i]];
			}
			dp[i][j] = num;
		}
	}

	res = dp[m-1][aim];

	common_utils::free_matrix(dp, m, aim + 1);

	return res;
}

int exchange_ways_2(const std::vector<int>& ivec, int aim) {
	int res = 0;

	if(ivec.empty()) {
		return res;
	}

	// allocate a matrix, row number is ivec.size(), and column number is aim + 1
	const int m = ivec.size();
	int **dp = common_utils::get_matrix(m, aim + 1);

	// dp[i][j] means how many ways could be used to consist of 'j' by ivec[0..i]

	// first column
	for(int k = 0; k < m; k++) {
		dp[k][0] = 1; // since target value is 0, so no need to use any ivec[0...k]
	}

	// first row
	for(int k = 0; k < aim + 1; k++) {
		if(k % ivec[0] == 0) {
			dp[0][k] = 1; // only those k could be divided by ivec[0] can be consisted of
		} else {
			dp[0][k] = 0;
		}
	}

	/*
	 * dp[i][j]
	 * 	(1) use just ivec[0..i-1] to consist of 'j' and 0 sheet ivec[i]
	 * 	(2) use just ivec[0..i-1] to consist of 'j -     ivec[i]' and 1 sheet ivec[i]
	 * 	(3) use just ivec[0..i-1] to consist of 'j - 2 * ivec[i]' and 2 sheets ivec[i]
	 * 	...
	 * 	(k) use just ivec[0..i-1] to consist of 'j - k * ivec[i]' and k sheets ivec[i], here j - k * ivec[i] >= 0
	 * 	...
	 *
	 *  finally, dp[i][j] = sum of dp[i-1][j - k * ivec[i] ], here k >= 0 && j - k * ivec[i] >= 0
	 * 	But indeed, (2), (3), (4), ..., (k), ... is dp[i][j-ivec[i]], actually replace 'j' with 'j-ivec[i]' we get
	 * 	dp[i][j-ivec[i]] = sum of dp[i-1][j - ivec[i] - k * ivec[i] ], here k >= 0 && j - ivec[i] - k * ivec[i] >= 0
	 * 	i.e.
	 * 	dp[i][j-ivec[i]] = sum of dp[i-1][j - (k+1)* ivec[i] ], here k >= 0 && j - (k+1) * ivec[i] >= 0
	 * 	i.e.
	 * 	dp[i][j-ivec[i]] = sum of dp[i-1][j - t * ivec[i] ], here t >= 1 && j - t * ivec[i] >= 0,
	 * 	which is exactly (2), (3), (4), ..., (k), ...
	 *
	 * 	So finally dp[i][j] = dp[i-1][j] + dp[i][j-ivec[i]]
	 */

	for(int i = 1; i < m; i++) {
		// no need to set first column as it has been set already previously
		for(int j = 1; j < aim + 1; j++) {
			dp[i][j] = dp[i-1][j];
			if(j-ivec[i] >= 0) {
				dp[i][j] += dp[i][j-ivec[i]];
			}
		}
	}

	res = dp[m-1][aim];

	common_utils::free_matrix(dp, m, aim + 1);

	return res;
}




// --------------------------------------------------------------------------------------------------------------
// 4.5 Max subsequence of ascending order
// Given an array, get the max subsequence of it in the ascending order
// The array's order doesn't have to be in ascending/descending order

// solution
// allocate an array 'dp', which size is same as the input array
// dp[i] means the max len of the subsequence in ascending order which MUST use the array[i] as the last one of the subsequence
// That is to say dp[i] means the max len of the subsequence in ascending order which MUST end by array[i]
// So first step is to get 'dp', then the second step is to get subsequence using 'dp'

void max_subseq_ascend_len(const std::vector<int>& arr, std::vector<int>& dp) {

	if(arr.empty()) {
		return ;
	}

	const int m = arr.size();

	dp.resize(m);

	dp[0] = 1; // This is obvious...

	for(int i = 1; i < m; i++) {
		int mlen = 1;
		for(int k = 0; k < i; k++) {
			if(arr[k] <= arr[i]) { // If strictly ascending order, it should be 'arr[k] < arr[i]'
				mlen = std::max(dp[k] + 1, mlen);
			}
		}
		dp[i] = mlen;
	}

}

// [In] arr
// [In] dp
// [Out] subseq
void get_max_sub_ascend(const std::vector<int>& arr, const std::vector<int>& dp, std::vector<int>& subseq) {
	if(arr.empty() || dp.empty() || arr.size() != dp.size()) {
		return ;
	}

	// First find which one is the tail of the max subsequence
	int max_len = 0;
	int index = 0;
	for(std::size_t i = 0; i < dp.size(); i++) {
		if(dp[i] > max_len) {
			max_len = dp[i];
			index = i;
		}
	}

	subseq.resize(max_len);
	subseq[max_len - 1] = arr[index];
	max_len--;
	for(int i = index; i >= 0; i--) {
		if(arr[i] < arr[index] && dp[i] == max_len) {
			subseq[max_len - 1] = arr[i];
			index = i;
			max_len--;
		}
	}

}


// [TIME_STAMP] Stop at 22:45, 2017/09/21



// [TIME_STAMP] Start at 10:02, 2017/09/23

// --------------------------------------------------------------------------------------------------------------
// 4.6 Hanoi Tower Problem
// (1) Print the trace of the optimal movements
// (2) Judge if an array is the one of those optimal movements

// Recursive solution
void hanoi(int n, const std::string& from, const std::string& help, const std::string& to) {
	if(n <= 0) {
		return;
	}
	if(n == 1) {
		std::cout << "Move " << n << " from " << from << " to " << to << std::endl;
		return ;
	}
	// Move top 'n-1' plate from 'from' to 'help' with the help of 'to'
	hanoi(n-1, from, to, help);
	// Move the last one, which is 'n' from 'from' to 'to' directly with help of 'help'
	hanoi(1, from, help, to);
	// Move the 'n-1' plates from 'help' to 'to' with the help of 'from'
	hanoi(n-1, help, to, from);
}
void hanoi_solve(int n) {
	if(n <= 0) {
		return;
	}
	hanoi(n, "left", "middle", "right");
}

enum WHICH_PILLAR {UNKNOW = 0, FROM, MID, TO};
int step(const std::vector<int>& arr, const int i, int from, int mid, int to) {
	if(i < 0 ) {
		return 0;
	}
	if(arr[i] != from && arr[i] != to) {
		return -1;
	}
	if(arr[i] == from) {
		return step(arr, i - 1, from, to, mid);
	} else {
		int rest = step(arr, i - 1, mid, from, to);
		if(rest == -1) {
			return -1;
		}
		return rest + (1 << i);
	}
}
int step_judge(const std::vector<int>& arr) {
	if(arr.empty()) {
		return -1;
	}

	int res = step(arr, arr.size() - 1, FROM, MID, TO);

	return res;
}

// --------------------------------------------------------------------------------------------------------------
// 4.7 Longest Common Sequence of 2 Strings
// Not only max length but also this common sequence

// out_dp is a matrix and it is for output
void longest_common_sequence_dp_matrix(const std::string& str1, const std::string& str2, int **out_dp) {
	if(str1.empty() || str2.empty()) {
		return ;
	}

	int **dp = common_utils::get_matrix(str1.size() - 1, str2.size() - 1);
	// First row
	for(std::size_t i = 0; i < str2.size(); i++) {
		if(str1[0] == str2[i]) {
			dp[0][i] = 1;
			// from 'i' to the end, the longest common sequence length are all 1.
			while(i < str2.size()) {
				i++;
				dp[0][i] = 1;
			}
			break;
		} else {
			dp[0][i] = 0;
		}
	}

	// First column
	for(std::size_t j = 0; j < str1.size(); j++) {
		if(str1[0] == str1[j]) {
			dp[0][j] = 1;
			// from 'j' to the end, the longest common sequence length are all 1.
			while(j < str1.size()) {
				j++;
				dp[0][j] = 1;
			}
			break;
		} else {
			dp[0][j] = 0;
		}
	}

	// dp[i][j] means the longest common sequence of str1[0..i] and str2[0..j]
	// Possibilities
	// (1) if str1[i] != str2[j], then 2 possibilities,
	//     dp[i-1][j], maybe from the longest common sequence of str1[0..i-1] and str2[0..j]
	//     dp[i][j-1], maybe from the longest common sequence of str1[0..i] and str2[0..j-1]
	// (2) if str1[i] == str2[j], then
	//     dp[i-1][j-1] + 1

	for(std::size_t i = 1; i < str2.size(); i++) {
		for(std::size_t j = 1; j < str1.size(); j++) {
			dp[i][j] = 0;
			if(str1[i] == str2[j]) {
				dp[i][j] = std::max(dp[i][j], dp[i-1][j-1] + 1);
			}
			dp[i][j] = std::max(dp[i][j], dp[i-1][j]);
			dp[i][j] = std::max(dp[i][j], dp[i][j-1]);
		}
	}

	// Copy 'dp' to 'out_dp'
	common_utils::copy_matrix(dp, out_dp, str1.size(), str2.size());

	// free dp, because it has been copied to out_dp
	common_utils::free_matrix(dp, str1.size(), str2.size());

	return ;
}

std::string longest_common_sequence(const std::string& str1, const std::string& str2) {
	std::string res;
	if(str1.empty() || str2.empty()) {
		return res;
	}
	const int len1 = str1.size();
	const int len2 = str2.size();
	int ** dp = common_utils::get_matrix(len1, len2);
	longest_common_sequence_dp_matrix(str1, str2, dp);
	int max_len = dp[len1 - 1][len2 - 2];
	res.resize(max_len);
	int index = max_len - 1;
	int i = len1 - 1;
	int j = len2 - 1;
	while(index >= 0) {
		if(i > 0 && dp[i][j] == dp[i-1][j]) {
			i--;
		} else if(j > 0 && dp[i][j] == dp[i][j-1]) {
			j--;
		} else { // dp[i][j] == dp[i-1][j-1]
			res[index--] = str1[i];// or res[index--] = str2[j], because in this caes str1[i] == str2[j]
			i--;
			j--;
		}
	}

	return res;
}

// --------------------------------------------------------------------------------------------------------------
// 4.8 Longest Common Sub String of 2 Strings

void longest_common_substring_dp_matrix(const std::string& str1, const std::string& str2, int **out_dp) {
	if(!out_dp || str1.empty() || str2.empty()) {
		return;
	}

	int **dp = common_utils::get_matrix(str1.size(), str2.size());

	// dp[i][j] means the max length of common substring of str1[0..i] and str2[0..j]
	// And this common substring must end with str1[i] and str2[j], which is to say at this time str1[i] == str2[j]

	dp[0][0] = str1[0] == str2[0] ? 1 : 0;
	// first row
	for(std::size_t j = 1; j < str2.size(); j++) {
		dp[0][j] = (str1[0] == str2[j] ? 1 : 0);
	}
	// first column
	for(std::size_t i = 1; i < str1.size(); i++) {
		dp[i][0] = (str2[0] == str1[i] ? 1 : 0);
	}

	for(std::size_t i = 1; i < str1.size(); i++) {
		for(std::size_t j = 1; j < str2.size(); j++) {
			dp[i][j] = (str1[i] == str2[j] ? dp[i-1][j-1] + 1 : 0);
		}
	}

	common_utils::copy_matrix(dp, out_dp, str1.size(), str2.size());

	common_utils::free_matrix(dp, str1.size(), str2.size());

}

std::string longest_common_substring(const std::string& str1, const std::string& str2) {
	std::string res;
	if(str1.empty() || str2.empty()) {
		return res;
	}

	const int len1 = str1.size();
	const int len2 = str2.size();
	int **dp = common_utils::get_matrix(len1, len2);

	int max_len = 0;
	int index = 0;// index for str1
	// Get the max value in matrix, which is the max substring length of str1 and str2
	for(int i = 0; i < len1; i++) {
		for(int j = 0; j < len2; j++) {
			if(dp[i][j] > max_len) {
				max_len = dp[i][j];
				index = i;
			}
		}
	}

	res = str1.substr(index - max_len + 1, max_len);

	return res;
}

// --------------------------------------------------------------------------------------------------------------
// 4.9 Minimum Cost of Editting

int min_edit_cost(const std::string& str1, const std::string& str2, const int ic, const int dc, const int rc) {
	// str1 and str2 are allowed to be empty strings
	int return_value = 0;

	if(str1.empty() && str2.empty()) {
		return return_value;
	}

	const int m = str1.size();
	const int n = str2.size();
	int **dp = common_utils::get_matrix(m + 1, n + 1);

	// dp[0][*] means how to convert empty char '' to str2
	// dp[*][0] means how to convert str1 to empty char ''
	// dp[i][j] means cost how much to change 'str1' to 'str2'
	dp[0][0] = 0;
	// first row
	for(int j = 1; j < n + 1; j++) {
		// str1[0] means an empty char
		dp[0][j] = ic * j;
	}
	// firt column
	for(int i = 1; i < m + 1; i++) {
		// str2[0[ means an empty char
		dp[i][0] = rc * i;
	}

	for(int i = 1; i < m + 1; i++) {
		for(int j = 1; j < n + 1; j++) {
			if(str1[i] == str2[j]) {
				dp[i][j] = dp[i-1][j-1];// For str[0..i], convert str1[0..i-1] to str2[0..j-1] is enough because str1[i] == str2[j]
			} else {
				dp[i][j] = dp[i-1][j-1] + rc; // For str[0..i], convert str1[0..i-1] to str2[0..j-1], then replace str1[i] with str2[j]
			}
			dp[i][j] = std::min(dp[i][j], dp[i][j-1] + ic);
			dp[i][j] = std::min(dp[i][j], dp[i-1][j] + dc);
		}
	}

	return_value = dp[m][n]; // Notice that matrix is (m+1)x(n+1)

	common_utils::free_matrix(dp, m+1, n+1);

	return return_value;
}

int min_edit_cost_space_saving(const std::string& str1, const std::string& str2, const int ic, const int dc, const int rc) {
	int return_value = 0;

	std::vector<int> dp;
	const int m = str1.size();
	const int n = str2.size();
	dp.resize(n + 1); // reserve the length of str2's size plus 1(which is for empty char intention)

	dp[0] = 0;
	// first row, means str1[0] is an empty char
	for(int j = 1; j < n + 1; j++) {
		dp[j] = ic * j;
	}

	int pre_left = 0;
	for(int i = 1; i < m + 1; i++) {
		pre_left = dp[0];
		dp[0] = dc * i;
		for(int j = 1; j < n + 1; j++) {
			int temp = dp[j];
			if(str1[i] == str2[j]) {
				dp[j] = pre_left;
			} else {
				dp[j] = pre_left + rc;
			}
			dp[j] = std::min(dp[j], temp + dc);
			dp[j] = std::min(dp[j], dp[j-1] + ic);
			pre_left = dp[j];
		}
	}

	return_value = dp[n];

	return return_value;

}

// --------------------------------------------------------------------------------------------------------------
// 4.10 Is a string staggered by 2 strings

bool is_stagger_string(const std::string& str1, const std::string& str2, const std::string& aim) {
	bool ret_val = false;

	if(aim.size() != str1.size() + str2.size()) {
		return ret_val;
	}

	// dp[i][j] means if aim[0..i+j-1](length is 'i+j') can be consisted of str1[0..i-1](length is 'i') and str2[0..j-1](length is 'j')
	// 1 - yes
	// 0 - no
	const int m = str1.size();
	const int n = str2.size();

	int **dp = common_utils::get_matrix(m + 1, n + 1);
	dp[0][0] = 1;
	// first row
	for(int j = 1; j < n + 1; j++) {
		dp[0][j] = (dp[0][j-1] == 1) && (aim[j] == str2[j]);
	}
	// first column
	for(int i = 1; i < m + 1; i++) {
		dp[i][0] = (dp[i-1][0] == 1) && (aim[i] == str1[i]);
	}

	// dp[i][j] has 2 possibilities
	// (1) str1[0..i-2] and str2[0..j-1] consist of aim[0..i+j-2], and str1[i-1] == aim[i+j-1], which is
	//     dp[i-1][j] == 1 && str1[i] == aim[i+j-1]
	// (2) str1[0..i-1] and str2[0..j-2] consist of aim[0..i+j-2], and str2[j-1] == aim[i+j-1], which is
	//     dp[i][j-1] == 1 && str2[j] == aim[i+j-1]
	for(int i = 1; i < m + 1; i++) {
		for(int j = 1; j < n + 1; j++) {
			if(dp[i-1][j] == 1 && str1[i-1] == aim[i+j-1]) {
				dp[i][j] = 1;
			} else if(dp[i][j-1] == 1 && str2[j-1] == aim[i+j-1]) {
				dp[i][j] = 1;
			} else {
				dp[i][j] = 0;
			}
		}
	}

	ret_val = dp[m][n];

	common_utils::free_matrix(dp, m+1, n+1);

	return ret_val;
}

bool is_stagger_string_space_saving(const std::string& str1, const std::string& str2, const std::string& aim) {
	bool ret_val = false;

	if(aim.size() != str1.size() + str2.size()) {
		return ret_val;
	}
	const int m = str1.size();
	const int n = str2.size();

	// first row
	std::vector<int> dp;
	dp.resize(n+1);
	dp[0] = 1;
	// first row
	for(int j = 1; j < n + 1; j++) {
		dp[j] = (dp[j-1] == 1) && (aim[j] == str2[j]);
	}

	// from 2nd row to the bottom row
	for(int i = 1; i < m + 1; i++) {
		dp[0] = (dp[0] == 1 && str1[i] == aim[i]) ? 1 : 0;
		for(int j = 1; j < n + 1; j++) {
			if(dp[j] == 1 && str1[i-1] == aim[i+j-1]) {
				dp[j] = 1;
			} else if(dp[j-1] == 1 && str2[j-1] == aim[i+j-1]) {
				dp[j] = 1;
			} else {
				dp[j] = 0;
			}
		}
	}

	ret_val = dp[n];

	return ret_val;
}

// --------------------------------------------------------------------------------------------------------------
// 4.11 Game of Dungeons and Dragons

int dungeons_and_dragons(const int **map, const int row, const int col) {
	int ret_val = -1;

	int **dp = common_utils::get_matrix(row, col);

	dp[row-1][col-1] = map[row-1][col-1] > 0 ? 1 : 1 - map[row-1][col-1];

	// last row(bottom row)
	for(int j = col - 2; j >= 0; j--) {
		dp[row-1][j] = dp[row-1][j+1] - map[row-1][j]; // Statisfying condition 'dp[row-1][j] + map[row-1][j] = dp[row-1][j+1]'
		dp[row-1][j] = std::max(dp[row-1][j], 1); // Because in local must have >= 1 blood
	}

	// last column(right most column)
	for(int i = row - 2; i >= 0; i--) {
		dp[i][col-1] = dp[i+1][col-1] - map[i][col-1]; // Statisfying condition 'dp[i][col-1] + map[i][col-1] = dp[row-1][j+1]'
	}

	// from second last row(bottom) to the first row
	for(int i = row - 2; i >= 0; i--) {
		for(int j = col - 2; j >= 0; j--) {
			int walk_down = dp[i+1][j] - map[i][j];
			walk_down = std::max(walk_down, 1);

			int walk_right = dp[i][j+1] - map[i][j];
			walk_right = std::max(walk_right, 1);

			dp[i][j] = std::min(walk_down, walk_right);
		}
	}

	ret_val = dp[0][0];

	common_utils::free_matrix(dp, row, col);

	return ret_val;
}

int dungeons_and_dragons_space_saving(const int **map, const int row, const int col) {
	int ret_val = -1;

	std::vector<int> dp;
	dp.resize(col);

	dp[col-1] = map[row-1][col-1] > 0 ? 1 : 1 - map[row-1][col-1];

	// last row(bottom row)
	for(int j = col - 2; j >= 0; j--) {
		dp[j] = dp[j+1] - map[row-1][j]; // Statisfying condition 'dp[row-1][j] + map[row-1][j] = dp[row-1][j+1]'
		dp[j] = std::max(dp[j], 1); // Because in local must have >= 1 blood
	}

	// from 2nd last row to the top(first row)
	for(int i = row - 2; i >= 0; i--) {
		dp[col - 1] = dp[col - 1] - map[i][col - 1];
		dp[col - 1] = std::max(dp[col - 1], 1);
		for(int j = col - 2; j >= 0; j--) {
			int walk_down = dp[j] - map[i][j];
			walk_down = std::max(walk_down, 1);

			int walk_right = dp[j+1] - map[i][j];
			walk_right = std::max(walk_right, 1);

			dp[j] = std::min(walk_down, walk_right);
		}
	}

	ret_val = dp[0];

	return ret_val;
}

// --------------------------------------------------------------------------------------------------------------
// 4.12 How many ways to convert a string(all digits) to a character string

int convert_number_string_to_char_string_process(const std::string& digit_string, const int i) {
	const int n = digit_string.size();
	if(i == n) {
		return 1;
	}

	if(digit_string[i] == '0') {
		return 0;
	}

	// until now, digit_string[i] won't be '0'
	int res = convert_number_string_to_char_string_process(digit_string, i+1);
	int v = (digit_string[i] - '0') * 10 + (digit_string[i+1] - '0');
	if( v >= 1 && v <= 26) {
		res += convert_number_string_to_char_string_process(digit_string, i+2);
	}

	return res;
}
int convert_number_string_to_char_string(const std::string& s) {
	if(s.empty()) {
		return 0;
	}
	if(s.size() == 1) {
		if(s == "0") {
			return 0;
		} else {
			return 1;
		}
	}

	return convert_number_string_to_char_string_process(s, 0);
}

// Use dynamic planning to resolve the problem
int convert_number_string_to_char_string_dp_solution_method(const std::string& s) {
	if(s.empty()) {
		return 0;
	}

	const int len = s.size();
	// 'current' is similar to dp[i], which means given s[0..i-1](already converted), s[i..len-1] can be converted in how many ways
	// 'current' initial value is dp[len - 1]
	int current = s[len - 1] == '0' ? 0 : 1;
	// 'next' is similar to dp[i+1]
	// 'next' initial value is dp[len], which actually means s[0..len-1](already converted), no string left to convert, so only 1 way
	int next = 1;
	for(int i = len - 2; i >= 0; i--) {
		if(s[i] == '0') {
			next = current;
			current = 0;
		} else {
			int temp = current;
			int v = (s[i] - '0') * 10 + (s[i+1] - '0');
			if(v >= 1 && v <= 26) {
				current += next;
			}
			next = temp;
		}
	}

	return current;
}

// --------------------------------------------------------------------------------------------------------------
// 4.13 Number of Expectations for An Expression

bool is_valid_expression(const std::string& expr) {
	if(expr.empty() || expr.size() % 2 == 0) {
		return false;
	}

	for(std::size_t i = 0; i < expr.size(); i += 2) {
		if(expr[i] != '0' && expr[i] != '1') {
			return false;
		}
	}

	for(std::size_t i = 1; i < expr.size(); i += 2) {
		if(expr[i] != '&' && expr[i] != '|' && expr[i] != '^') {
			return false;
		}
	}

	return true;
}

int desired_expections_process(const std::string& expr, bool desired, const int start, const int end) {
	if(start == end) {
		if(desired) {
			return expr[start] == '1' ? 1 : 0;
		} else {
			return expr[start] == '0' ? 1 : 0;
		}
	}

	int res = 0;
	for(int i = start + 1; i < end; i += 2) {
		if(desired) {
			switch(expr[i]) {
				case '&': {
					res += desired_expections_process(expr, true, start, i - 1) * desired_expections_process(expr, true, i + 1, end);
					break;
				} case '|' : {
					res += desired_expections_process(expr, true, start, i - 1) * desired_expections_process(expr, true, i + 1, end);
					res += desired_expections_process(expr, true, start, i - 1) * desired_expections_process(expr, false, i + 1, end);
					res += desired_expections_process(expr, false, start, i - 1) * desired_expections_process(expr, true, i + 1, end);
					break;
				} case '^' : {
					res += desired_expections_process(expr, true, start, i - 1) * desired_expections_process(expr, false, i + 1, end);
					res += desired_expections_process(expr, false, start, i - 1) * desired_expections_process(expr, true, i + 1, end);
					break;
				} default : {
					break;
				}
			}
		} else {
			switch(expr[i]) {
				case '&': {
					res += desired_expections_process(expr, false, start, i - 1) * desired_expections_process(expr, false, i + 1, end);
					res += desired_expections_process(expr, true, start, i - 1) * desired_expections_process(expr, false, i + 1, end);
					res += desired_expections_process(expr, false, start, i - 1) * desired_expections_process(expr, true, i + 1, end);
					break;
				} case '|' : {
					res += desired_expections_process(expr, false, start, i - 1) * desired_expections_process(expr, false, i + 1, end);
					break;
				} case '^' : {
					res += desired_expections_process(expr, true, start, i - 1) * desired_expections_process(expr, true, i + 1, end);
					res += desired_expections_process(expr, false, start, i - 1) * desired_expections_process(expr, false, i + 1, end);
					break;
				} default : {
					break;
				}
			}
		}
	}

	return res;

}

int desired_expections(const std::string& expr, bool desired) {
	int res = 0;

	if(!is_valid_expression(expr)) {
		return res;
	}

	res = desired_expections_process(expr, desired, 0, expr.size() - 1);

	return res;
}

// --------------------------------------------------------------------------------------------------------------
// 4.14 Game of Poker
//

// For arr[i..j], if take firstly, what is the final score
int first_take(const std::vector<int>& arr, const int start, const int end);
// For arr[i..j], if take secondly, what is the final score
int second_take(const std::vector<int>& arr, const int start, const int end);

int first_take(const std::vector<int>& arr, const int start, const int end) {
	if(start == end) {
		return arr[start];
	} else {
		return std::max(arr[start] + second_take(arr, start+1, end), arr[end] + second_take(arr, start, end - 1));
	}
}

int second_take(const std::vector<int>& arr, const int start, const int end) {
	if(start == end) {
		return arr[start];
	} else {
		return std::max(first_take(arr, start + 1, end), first_take(arr, start, end - 1));
	}
}

int winner_score(const std::vector<int>& arr) {
	if(arr.empty()) {
		return 0;
	}

	return std::max(first_take(arr, 0, arr.size()), second_take(arr, 0, arr.size()));
}

// DP solution for the 'Game of Poker issue'

int winner_score_dp_solution(const std::vector<int>& arr) {
	int res = 0;

	const int len = arr.size();
	// Matrix for the first take
	// f_dp[i][j] means what score is if you first take from arr[i..j]
	int **f_dp = common_utils::get_matrix(len, len);
	// Matrix for the second take
	// f_dp[i][j] means what score is if you second take from arr[i..j]
	int **s_dp = common_utils::get_matrix(len, len);

	// Assign all values in the matrix as 0
	for(int i = 0; i < len; i++) {
		for(int j = 0; j < len; j++) {
			f_dp[i][j] = 0;
			s_dp[i][j] = 0;
		}
	}

	// Assign values to diagonal
	for(int i = 0; i < len; i++) {
		f_dp[i][i] = arr[i]; // this is obvious since facing arr[i..i](only arr[i]), you first take you'll get arr[i]
		s_dp[i][i] = 0; // this is obvious since facing arr[i..i](only arr[i]), you second take you'll get nothing(because first person has taken it)
	}

	for(int col = 1; col < len; col++) {
		for(int row = 0, k = col; k < len; k++, row++) {
			f_dp[row][k] = std::max(arr[row] + s_dp[row+1][k], arr[k-1] + s_dp[row][k-1]);
			s_dp[row][k] = std::max(f_dp[row+1][k], f_dp[row][k-1]);
		}
	}

	// Decide facing arr[0..len-1], first take will win or second take will win
	res = std::max(f_dp[0][len-1], s_dp[0][len-1]);

	common_utils::free_matrix(f_dp, len, len);
	common_utils::free_matrix(s_dp, len, len);

	return res;
}

// [TIME_STAMP] Stop at 20:16, 2017/09/23


// [TIME_STAMP] Start at 10:24, 2017/09/24

// --------------------------------------------------------------------------------------------------------------
// 4.15 Jump Game

int min_times_jump_to_the_end(const std::vector<int>& arr) {
	// how many times has jumped
	int jump_cnt = 0;
	// How far it can reach by jumping 'times' times
	std::size_t most = 0;
	// How far it can reach by jumping 'times + 1' times, which is one more jump
	std::size_t one_more_most = 0;

	for(std::size_t i = 0; i < arr.size(); i++) {
		if(i > most) {
			// Now jump 'jump_cnt' times cannot reach 'i' position
			// has to jump one more time
			jump_cnt++;
			most = one_more_most;
		}
		// Now as position 'i' is reachable(since till now i <= cur)
		// Suppose how far it can reach if jump one more time from position 'i'
		one_more_most = std::max(one_more_most, i + arr[i]);
	}

	return jump_cnt;
}


// --------------------------------------------------------------------------------------------------------------
// 4.16 Longest Consecutive Subsequence

int longest_consecutive_subsequence(const std::vector<int>& arr) {
	int res = 0;

	// pair - first is value in arr
	//        second is the forward/backword length
	std::map<int, int> m;
	for(std::size_t i = 0; i < arr.size(); i++) {
		if(m.find(arr[i]) == m.end()) {
			m[arr[i]] = 1;

			// Backword
			std::map<int, int>::iterator itr = m.find(arr[i] - 1);
			if( itr != m.end()) {
				int p1 = itr->first;
				int len1 = itr->second;
				int x1 = p1 - len1 + 1;
				m[x1] = len1 +1;
				m[arr[i]] = len1 + 1;
			}

			// Forward
			itr = m.find(arr[i] + 1);
			if( itr != m.end()) {
				int x2 = itr->first;
				int len2 = itr->second;
				int p2 = x2 + len2 - 1;
				int x1 = p2 - (len2 + m[arr[i]]) + 1;
				m[p2] = len2 + m[arr[i]];
				m[x1] = len2 + m[arr[i]];
			}
		}
	}

	for(std::map<int, int>::iterator itr = m.begin(); itr != m.end(); itr++) {
		if(itr->second > res) {
			res = itr->second;
		}
		// Or just 'res = std::max(res, itr->second)'
	}

	return res;
}

// --------------------------------------------------------------------------------------------------------------
// 4.17 N Queens Problem

bool is_place_valid(const int i, const int j, const std::vector<int>& arr) {

	for(int k = 0; k < i; k++) {
		if(arr[k] == j || i - k == std::abs(j - arr[k])) {
			return false;
		}
	}

	return true;
}

int n_queens(const int n, const int row, std::vector<int>& arr) {

	int res = 0;

	for(int col = 0; col < n; col++) {
		if(is_place_valid(row, col, arr)) {
			arr[row] = col;
			res += n_queens(n, row+1, arr);
		}
	}

	return res;
}

int n_queens_solution(const int n) {
	if(n < 2) {
		return n;
	}

	std::vector<int> arr;
	arr.resize(n);

	return n_queens(n, 0, arr);
}

// [TIME_STAMP] Stop at 12:50, 2017/09/24


} // end-of-namespace C4
