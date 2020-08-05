/*
 * chapter_3_tests.cpp
 *
 *  Created on: Agu. 4th, 2020
 *      Author: Pyrad
 * Description: Source file of the tests for the chapter 3 Binary Tree
 *   Intention: Test functions for problems in Chapter 3[Binary Tree] of Code Interview Guide
 */


#include "chapter_3.hpp"
#include "chapter_3_tests.hpp"

#include <cstdio>
#include <memory>
#include <functional>

#include <boost/filesystem.hpp>

namespace C3TEST {

namespace CU = common_utils;

void test_3_all() {
    test_3_4();
    // test_3_6();
}

void test_3_4() {
    using node = CU::node;

    // const std::string tstr(binary_tree_serialization_by_preorder(phead));

    // deserialization
    //-9 
    std::string serialstr_0("-9!#!#!");
    //43 -27 -41 -36 24 50 13 -25 
    // std::string serialstr_1("43!-27!-41!-36!#!#!24!50!#!#!13!#!#!#!-25!#!#!");
    std::string serialstr_1("43!-27!0!10!#!#!4!6!#!#!13!#!#!#!-25!#!#!");
    //-46 1 12 47 10 -40 50 50 21 -30 17 -39 
    std::string serialstr_2("-46!1!12!#!#!47!#!10!#!-40!#!#!50!50!#!#!21!-30!17!#!#!#!-39!#!#!");
    //25 -5 -31 
    std::string serialstr_3("25!-5!#!-31!#!#!#!");
    //34 -21 0 -6 -14 -46 -27 
    std::string serialstr_4("34!-21!#!0!-6!-14!#!#!-46!#!#!#!-27!#!#!");
    //-27 15 31 6 -50 -30 -13 -32 
    std::string serialstr_5("-27!15!31!#!#!#!6!#!-50!-30!-13!#!#!-32!#!#!#!");
    //20 
    std::string serialstr_6("20!#!#!");
    //-43 43 
    std::string serialstr_7("-43!43!#!#!#!");
    //1 -47 6 9 -20 35 20 -47 39 
    std::string serialstr_8("1!-47!6!#!9!-20!#!#!35!#!#!20!-47!39!#!#!#!#!#!");
    //-49 
    std::string serialstr_9("-49!#!#!");

    std::vector<std::string> strs{serialstr_0, serialstr_1, serialstr_2,
                                serialstr_3, serialstr_4, serialstr_5,
                                serialstr_6, serialstr_7, serialstr_8,
                                serialstr_9};

    std::function<void(node*)> f = [](node* h) {if (h) { printf("%d ", h->value); }};
    int i = 0;
    const std::string fprefix("graphvizFile");
    const std::string fsuffix(".dot");

    // Write to folder of "./temp"
    const std::string tmpdir("temp");
    // CU::get_dir will print message if not to create it (only in case it doesn't exist)
    if (!CU::get_dir(tmpdir)) {
        return ;
    }

    for (auto s : strs) {
        CU::node *phead = C3::deserialization_to_create_binary_tree_process(s);
        printf("Tree %d: ", i);
        CU::pre_order(phead, f);
        printf("\n");

        const std::string fname(tmpdir + "/" + fprefix + "." + std::to_string(i) + fsuffix);
        std::fstream fs(fname.c_str(), std::fstream::out);
        if (!fs.is_open()) {
            printf("%s Failed to open file for writing: %s\n",
                    CU::ColorTermString::warning().c_str(),
                    fname.c_str());
            return ;
        }

        if (i == 1) {
            int maxpath = C3::max_certain_sum_path_in_binary_tree(phead, 10);
            printf("Max path is: %d\n", maxpath);
        }

        printf("%s Write to file: %s ...", CU::ColorTermString::info().c_str(), fname.c_str());
        CU::write_binary_tree_to_graphviz(phead, fs);
        printf("Done");
        fs.close();

        CU::release_tree(phead);
        ++i;
    }

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
        printf("\n");

        const std::string treestr(C3::binary_tree_serialization_by_preorder(sp.get()));
        printf("Serialization: %s\n", treestr.c_str());

        printf("Tree %d done\n", i);

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
