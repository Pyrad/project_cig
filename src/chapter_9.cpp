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


void test_9_XX() {
	int a[9] = {9, 3, 1, 2, 5, 3, 4, 8, 7};
	std::vector<int> arr(a, a + 9);
	int res = get_first_unformed_number(arr);
	printf("RES: %d\n", res);

	res = get_first_unformed_number_0(arr);
	printf("RES: %d\n", res);
}


}; // namespace C8
