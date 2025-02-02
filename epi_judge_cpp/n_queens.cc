#include <algorithm>
#include <iterator>
#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

namespace {

bool valid_placement(const std::vector<int>& placements, int candidate) {
  // given queens at (i, placements[i]) for i from 0 to placements.size(),
  // check whether we can put queen at (placements.size(), candidate)
  for (int i = 0; i < placements.size(); i++) {
    int row_dist = abs(placements.size() - i);
    int col_dist = abs(candidate - placements[i]);
    if (row_dist == col_dist) {
      return false;
    }
  }
  return true;
}

void generate_placement(
  std::unordered_set<int>& candidate_cols,
  std::vector<int>& placements,
  vector<vector<int>>& all_valid_placements
) {
  if (candidate_cols.empty()) {
    // base case
    all_valid_placements.emplace_back(placements);
    return;
  }

  std::vector<int> candidates{candidate_cols.begin(), candidate_cols.end()};
  for (int candidate : candidates) {
    if (valid_placement(placements, candidate)) {
      // try placing queen at col candidate
      candidate_cols.erase(candidate);
      placements.emplace_back(candidate);
      generate_placement(candidate_cols, placements, all_valid_placements);
      placements.pop_back();
      candidate_cols.insert(candidate);
    }
  }
}

}

vector<vector<int>> NQueens(int n) {
  std::unordered_set<int> candidate_cols{};
  for (int i = 0; i < n; ++i) {
    candidate_cols.insert(i);
  }
  std::vector<int> placements{};
  std::vector<std::vector<int>> all_valid_placements{};

  generate_placement(candidate_cols, placements, all_valid_placements);

  return all_valid_placements;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "n_queens.cc", "n_queens.tsv", &NQueens,
                         UnorderedComparator{}, param_names);
}
