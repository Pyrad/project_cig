//============================================================================
// Name        : project_cig.cpp
// Author      : Pyrad
// Version     :
// Copyright   : Pyrad
// Description : Project for Code Interview Guide
//============================================================================

#include <iostream>
#include <stdio.h>
#include <limits.h>
// using namespace std;


#include "chapter_5_tests.hpp"
#include "chapter_9_test.hpp"


#include "smart_pointer_test.hpp"

#define TEST_CHAPTER_1 0
#define TEST_CHAPTER_2 0
#define TEST_CHAPTER_3 0
#define TEST_CHAPTER_4 0
#define TEST_CHAPTER_5 0
#define TEST_CHAPTER_6 0
#define TEST_CHAPTER_7 0
#define TEST_CHAPTER_8 0
#define TEST_CHAPTER_9 0

#define TEST_OTHERS 0

int main() {
	std::cout << "Greetings" << std::endl; // prints Greetings

#if TEST_CHAPTER_5
	// Tests in chapter 5
	C5::test_5_all();
#endif // TEST_CHAPTER_5

#if TEST_OTHERS
	// Other Tests
	smart_pointer_test::run_smart_pointer_test();
#endif // TEST_OTHERS

#if TEST_CHAPTER_9
	// Tests in chapter 9
	C9::test_9_XX();
#endif // TEST_CHAPTER_9

	return 0;
}
