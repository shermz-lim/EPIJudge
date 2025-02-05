#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
// Check if a partially filled matrix has any conflicts.
bool IsValidSudoku(const vector<vector<int>>& partial_assignment) {
  const vector<vector<int>>& A = partial_assignment;

  std::array<std::bitset<10>, 9> row_count{};
  std::array<std::bitset<10>, 9> col_count{};
  std::array<std::bitset<10>, 9> subgrid_count{};
  for (int r = 0; r < 9; ++r) {
    for (int c = 0; c < 9; ++c) {
      int val = A[r][c];
      if (val > 0) {
        if (row_count[r][val]) {
          return false;
        }
        row_count[r][val] = true;

        if (col_count[c][val]) {
          return false;
        }
        col_count[c][val] = true;

        int subgrid = ((r / 3) * 3) + (c / 3);
        if (subgrid_count[subgrid][val]) {
          return false;
        }
        subgrid_count[subgrid][val] = true;
      }
    }
  }

  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"partial_assignment"};
  return GenericTestMain(args, "is_valid_sudoku.cc", "is_valid_sudoku.tsv",
                         &IsValidSudoku, DefaultComparator{}, param_names);
}
