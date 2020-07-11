#include <cmath>

#include "normal.hpp"

namespace NORMAL {

namespace CU = common_utils;

CU::node* create_random_binary_tree(int height, int minlimit, int maxlimit) {
    using node = CU::node;

    if (height <= 0) {
        return nullptr;
    }

    int node_num = pow(2, height) - 1;

    node **p = new node*[node_num];
    node *head = new node(CU::gen_random_int_1(minlimit, maxlimit));
    p[0] = head;

    for (int i = 1; i < node_num; ++i) {
        int s = CU::gen_random_int_1(minlimit, maxlimit);
        if (s % 2 == 0) {
            continue;
        }

        int parent = (i - 1) / 2;
        node *cur = new node(CU::gen_random_int_1(minlimit, maxlimit));
        p[i] = cur;

        if (p[parent]) {
            if( i % 2 == 0) {
                p[parent]->right = cur;
            } else {
                p[parent]->left = cur;
            }
        }
    }

    delete [] p;

    return head;
}

void run_all() {

}

} // End of namespace NORMAL
