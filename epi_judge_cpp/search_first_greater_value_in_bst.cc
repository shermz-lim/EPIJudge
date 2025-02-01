#include <memory>

#include "bst_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;

BstNode<int>* FindFirstGreaterThanK(const unique_ptr<BstNode<int>>& tree,
                                    int k) {
  BstNode<int>* curr_node = tree.get();
  BstNode<int>* best_candidate = nullptr;
  while (curr_node) {
    if (k < curr_node->data) {
      best_candidate = curr_node;
      curr_node = curr_node->left.get();
    } else {
      curr_node = curr_node->right.get();
    }
  }
  return best_candidate;
}
int FindFirstGreaterThanKWrapper(const unique_ptr<BstNode<int>>& tree, int k) {
  auto result = FindFirstGreaterThanK(tree, k);
  return result ? result->data : -1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree", "k"};
  return GenericTestMain(args, "search_first_greater_value_in_bst.cc",
                         "search_first_greater_value_in_bst.tsv",
                         &FindFirstGreaterThanKWrapper, DefaultComparator{},
                         param_names);
}
