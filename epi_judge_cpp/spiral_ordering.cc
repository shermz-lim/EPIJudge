#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
vector<int> MatrixInSpiralOrder(const vector<vector<int>>& square_matrix) {
  vector<int> res{};
  for (
    int low = 0, high = square_matrix.size() - 1;
    low <= high;
    low++, high--
  ) {
    if (low == high) {
      res.push_back(square_matrix[low][low]);
      break;
    }

    for (int c = low; c < high; ++c) {
      res.push_back(square_matrix[low][c]);
    }
    for (int r = low; r < high; ++r) {
      res.push_back(square_matrix[r][high]);
    }
    for (int c = high; c > low; --c) {
      res.push_back(square_matrix[high][c]);
    }
    for (int r = high; r > low; --r) {
      res.push_back(square_matrix[r][low]);
    }
  }
  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"square_matrix"};
  return GenericTestMain(args, "spiral_ordering.cc", "spiral_ordering.tsv",
                         &MatrixInSpiralOrder, DefaultComparator{},
                         param_names);
}
