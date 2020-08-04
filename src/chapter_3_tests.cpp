/*
 * chapter_3_tests.cpp
 *
 *  Created on: Agu. 4th, 2020
 *      Author: Pyrad
 * Description: Source file of the tests for the chapter 3 Binary Tree
 *   Intention: Test functions for problems in Chapter 3[Binary Tree] of Code Interview Guide
 */


#include "chapter_3_tests.hpp"

#include <cstdio>
#include <memory>
#include <functional>

#include <boost/filesystem.hpp>

namespace C3TEST {

namespace CU = common_utils;

void test_3_all() {
    test_3_6();
}

void test_3_6() {
    namespace BF = boost::filesystem;
    using node = CU::node;
    constexpr int TEST_TIMES = 10;
    using namespace std::placeholders;

    auto delptr = std::bind(CU::release_tree, _1, 99);
    std::function<void(node*)> f = [](node* h) {if (h) { printf("%d ", h->value); }};
    for (int i = 0; i < TEST_TIMES; ++i) {
        printf("Tree %d: ", i);
        std::shared_ptr<node> sp(CU::create_random_binary_tree(5, -50, 50), delptr);
        CU::pre_order(sp.get(), f);
    }
    // CU::node* phead = CU::create_random_binary_tree(5, -50, 50);
    // CU::release_tree(phead);
}

} // namespace C3TEST
