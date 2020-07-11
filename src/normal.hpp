#pragma once

#include <cstdlib>

#include "common_utils.hpp"

namespace NORMAL {

common_utils::node* create_random_binary_tree(int height, int minlimit=0, int maxlimit=RAND_MAX);

void run_all();

} // End of namespace NORMAL
