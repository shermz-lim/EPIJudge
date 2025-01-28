#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
bool IsBalanced(const unique_ptr<BinaryTreeNode<int>>& tree) {
  using NodePtr_t = const unique_ptr<BinaryTreeNode<int>>&;

  std::function<int(NodePtr_t)> height_or_balanced{};
  height_or_balanced = [&height_or_balanced](NodePtr_t root) -> int {
    if (!root) {
      return 0;
    }

    int left_horb = height_or_balanced(root->left);
    if (left_horb < 0) {
      return -1;
    }

    int right_horb = height_or_balanced(root->right);
    if (right_horb < 0) {
      return -1;
    }

    return abs(left_horb - right_horb) > 1
      ? -1 // not balanced, return -1
      : std::max(left_horb, right_horb) + 1; // return height
  };

  return height_or_balanced(tree) >= 0;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_balanced.cc", "is_tree_balanced.tsv",
                         &IsBalanced, DefaultComparator{}, param_names);
}
