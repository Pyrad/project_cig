#include <cmath>
#include <cassert>

#include "normal.hpp"

#include <map>
#include <unordered_map>
#include <fstream>

namespace NORMAL {

void run_all() {
    test_write_binary_tree_to_graphviz();
}

void write_binary_tree_to_graphviz(CU::node *head, std::ostream &fs) {
    if (!head) {
        return ;
    }

    std::unordered_map<const CU::node*, int> m;
    int ncnt = 0;

    // auto visit_record = [&m, &ncnt](const CU::node *h, std::unordered_map<const CU::node*, int> &m) {
    auto visit_record = [&m, &ncnt](const CU::node *h) {
        // printf("visit_record executed!\n");
        if (m.find(h) == m.end()) {
            m.insert(std::make_pair(h, ncnt++));
            // printf("Added: %p (value=%d) as node number %d\n", h, h->value, ncnt - 1);
        }
    };

    // using namespace std::placeholders;
    // auto func = std::bind(visit_record, _1, m);
    // CU::pre_order(head, func);
    CU::pre_order(head, visit_record);

    // printf("Map has size %lu\n", m.size());
    
    if (!m.empty()) {
        fs << "graph g {\n";
    }

    for (const auto &kv : m) {
        const CU::node *pleft = kv.first->left;
        const CU::node *pright = kv.first->right;
        int numleft = -1;
        int numright = -1;
        if (pleft) {
            const auto itr = m.find(pleft);
            assert(itr != m.end());
            numleft = itr->second;
            assert(numleft >= 0);
        }
        if (pright) {
            const auto itr = m.find(pright);
            assert(itr != m.end());
            numright = itr->second;
            assert(numright >= 0);
        }

        const int numcur = kv.second;
        if (numleft > 0) {
            // printf("N%d--N%d;\n", numcur, numleft);
            fs << "N" << numcur << "--N" << numleft << ";\n";
        }
        if (numright > 0) {
            // printf("N%d--N%d;\n", numcur, numright);
            fs << "N" << numcur << "--N" << numright << ";\n";
        }
    }

    // Write node information
    for (const auto &kv : m) {
        // printf("N%d[label=\"%d\"];\n", kv.second, kv.first->value);
        fs << "N" << kv.second << "[label=\"" << kv.first->value << "\"];\n";
    }

    if (!m.empty()) {
        fs << "}\n";
    }
}

void test_write_binary_tree_to_graphviz() {
    CU::node* phead = CU::create_random_binary_tree_full(5, 0, 50);
    std::function<void(CU::node*)> f = [](CU::node* h) {if (h) { printf("%d ", h->value); }};
    CU::pre_order(phead, f);
    printf("\n");
    std::fstream fs("./temp/graphtest.dot", std::fstream::out);
    // write_binary_tree_to_graphviz(phead);
    write_binary_tree_to_graphviz(phead, fs);
    fs.close();
    CU::release_tree(phead);

}

} // End of namespace NORMAL
