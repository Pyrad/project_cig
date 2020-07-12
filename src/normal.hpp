#pragma once

#include <cstdlib>
// #include <fstream>

#include "common_utils.hpp"

namespace NORMAL {

namespace CU = common_utils;

void write_binary_tree_to_graphviz(CU::node* head, std::ostream &fs= std::cout);
void test_write_binary_tree_to_graphviz();

void run_all();

} // End of namespace NORMAL
