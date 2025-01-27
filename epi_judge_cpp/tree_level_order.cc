#include <memory>
#include <vector>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;

vector<vector<int>> BinaryTreeDepthOrder(
    const unique_ptr<BinaryTreeNode<int>>& tree) {
  vector<vector<int>> res{};

  std::queue<const BinaryTreeNode<int>*> curr_lvl{};
  curr_lvl.push(tree.get());
  curr_lvl.push(nullptr);

  while (curr_lvl.front()) {
    vector<int> lvl_res{};
    while (curr_lvl.front()) {
      const auto& node = *curr_lvl.front();
      curr_lvl.pop();

      lvl_res.push_back(node.data);
      if (node.left) {
        curr_lvl.push(node.left.get());
      }
      if (node.right) {
        curr_lvl.push(node.right.get());
      }
    }

    curr_lvl.pop();
    curr_lvl.push(nullptr);
    res.push_back(std::move(lvl_res));
  }

  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_level_order.cc", "tree_level_order.tsv",
                         &BinaryTreeDepthOrder, DefaultComparator{},
                         param_names);
}
