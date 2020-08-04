#include <cmath>
#include <cassert>

#include "normal.hpp"

#include <map>
#include <unordered_map>
#include <fstream>

#include <boost/filesystem.hpp>

namespace NORMAL {

namespace CU = common_utils;

void run_all() {
    // test_write_binary_tree_to_graphviz();
}

void test_write_binary_tree_to_graphviz() {
    using node = CU::node;
    namespace BF = boost::filesystem;
    // node* phead = create_random_binary_tree_full(5, 0, 50);
    node* phead = CU::create_random_binary_tree(5, -50, 50);
    std::function<void(node*)> f = [](node* h) {if (h) { printf("%d ", h->value); }};
    CU::pre_order(phead, f);
    printf("\n");
    std::string dirname("temp");
    BF::path dpath(dirname.c_str());
    if (BF::is_directory(dpath)) {
        std::string infoPrefix(CU::ColorTermString::info());
        // printf("%s is a directory\n", dirname.c_str());
        printf("%s %s is a directory\n", infoPrefix.c_str(), dirname.c_str());
    } else {
        std::string warningPrefix(CU::ColorTermString::warning());
        // printf("%s is not a directory or doesn't exist\n", dirname.c_str());
        printf("%s %s is not a directory or doesn't exist\n", warningPrefix.c_str(), dirname.c_str());
        printf("Try to create directory: %s ...", dirname.c_str());
        if (BF::create_directory(dpath)) {
            printf("Succeed\n");
        } else {
            printf("Failed\n");
            return ;
        }
    }
    std::fstream fs("./temp/graphtest.dot", std::fstream::out);
    if (!fs.is_open()) {
        printf("Error to open file for writing: ./temp/graphtest.dot\n");
        return ;
    }
    // write_binary_tree_to_graphviz(phead);
    CU::write_binary_tree_to_graphviz(phead, fs);
    fs.close();
    CU::release_tree(phead);
}

} // End of namespace NORMAL

