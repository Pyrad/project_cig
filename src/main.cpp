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
#include "common_utils.hpp"

#include "normal.hpp"

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

#if 0
    const std::string s("-3,3,-9,1,0,2,1,#,#,1,6,#,#,#,#");

    namespace CU = common_utils;
    CU::node* ptree = CU::construct_tree_from_full_tree_array(s);
    if (ptree) {
        CU::pre_order(ptree);
        CU::release_tree(ptree);
        ptree = nullptr;
    } else {
        std::cout << "no need to release tree\n";
    }

    // CU::node* phead = NORMAL::create_random_binary_tree(5, 0, 50);
    CU::node* phead = CU::create_random_binary_tree_full(5, 0, 50);
    std::function<void(CU::node*)> f = [](CU::node* h) {if (h) { printf("%d ", h->value); }};
    CU::pre_order(phead, f);
    printf("\n");
    CU::release_tree(phead);
#endif // 0

    NORMAL::run_all();

	return 0;
}
