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
    test_write_binary_tree_to_graphviz();
}

void test_write_binary_tree_to_graphviz() {
    using node = CU::node;
    namespace BF = boost::filesystem;
    // node* phead = create_random_binary_tree_full(5, 0, 50);
    node* phead = CU::create_random_binary_tree(5, 0, 50);
    std::function<void(node*)> f = [](node* h) {if (h) { printf("%d ", h->value); }};
    CU::pre_order(phead, f);
    printf("\n");
    std::string dirname("temp");
    BF::path dpath(dirname.c_str());
    if (BF::is_directory(dpath)) {
        printf("%s is a directory\n", dirname.c_str());
    } else {
        printf("%s is not a directory or doesn't exist\n", dirname.c_str());
    }
    std::fstream fs("./temp/graphtest.dot", std::fstream::out);
    if (!fs.is_open()) {
        printf("Error to open file for writing: ./temp/graphtest.dot");
        return ;
    }
    // write_binary_tree_to_graphviz(phead);
    CU::write_binary_tree_to_graphviz(phead, fs);
    fs.close();
    CU::release_tree(phead);
}

} // End of namespace NORMAL

