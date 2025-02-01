#include <memory>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;

bool IsBinaryTreeBST(const unique_ptr<BinaryTreeNode<int>>& tree) {
  std::function<bool(const unique_ptr<BinaryTreeNode<int>>&, int, int)> is_bst{};
  is_bst = [&is_bst](const unique_ptr<BinaryTreeNode<int>>& root, int low, int high) {
    if (!root) {
      return true;
    }

    int data = root->data;
    if (data < low || data > high) {
      return false;
    }
    return is_bst(root->left, low, data) &&
           is_bst(root->right, data, high);
  };

  return is_bst(
    tree,
    std::numeric_limits<int>::min(),
    std::numeric_limits<int>::max()
  );
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_a_bst.cc", "is_tree_a_bst.tsv",
                         &IsBinaryTreeBST, DefaultComparator{}, param_names);
}
