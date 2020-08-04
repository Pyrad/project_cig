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

    std::function<void(node*)> f = [](node* h) {if (h) { printf("%d ", h->value); }};
    auto delptr = std::bind(CU::release_tree, _1, 99);

    // Write to folder of "./temp"
    const std::string tmpdir("temp");
    // CU::get_dir will print message if not to create it (only in case it doesn't exist)
    if (!CU::get_dir(tmpdir)) {
        return ;
    }

    const std::string fprefix("graphvizFile");
    const std::string fsuffix(".dot");

    for (int i = 0; i < TEST_TIMES; ++i) {
        printf("Tree %d: ", i);
        std::shared_ptr<node> sp(CU::create_random_binary_tree(5, -50, 50), delptr);
        CU::pre_order(sp.get(), f);
        printf("\nTree %d done\n", i);

        const std::string fname(tmpdir + "/" + fprefix + "." + std::to_string(i) + fsuffix);
        std::fstream fs(fname.c_str(), std::fstream::out);
        if (!fs.is_open()) {
            printf("%s Failed to open file for writing: %s\n",
                    CU::ColorTermString::warning().c_str(),
                    fname.c_str());
            return ;
        }

        printf("%s Write to file: %s ...", CU::ColorTermString::info().c_str(), fname.c_str());
        CU::write_binary_tree_to_graphviz(sp.get(), fs);
        printf("Done");
        fs.close();
    }

} // end of test_3_6()

} // namespace C3TEST
