#include <string>
#include <vector>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;

int LevenshteinDistance(const string& A, const string& B) {
  int len_A = A.size();
  int len_B = B.size();

  std::vector<std::vector<int>> min_edits(
    len_A + 1, std::vector<int>(len_B + 1, 0)
  );
  // fill in base cases
  for (int a = 0; a <= len_A; ++a) {
    // edit A[a..(len_A-1)] to empty B
    min_edits[a][len_B] = len_A - a;
  }
  for (int b = 0; b <= len_B; ++b) {
    // edit B[b..(len_B-1)] to empty A
    min_edits[len_A][b] = len_B - b;
  }

  for (int a = len_A - 1; a >= 0; a--) {
    for (int b = len_B - 1; b >= 0; b--) {
      if (A[a] == B[b]) {
        min_edits[a][b] = min_edits[a + 1][b + 1];
      } else {
        min_edits[a][b] = 1 + std::min(
          min_edits[a + 1][b + 1],
          std::min(
            min_edits[a + 1][b],
            min_edits[a][b + 1]
          )
        );
      }
    }
  }
  return min_edits[0][0];
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "B"};
  return GenericTestMain(args, "levenshtein_distance.cc",
                         "levenshtein_distance.tsv", &LevenshteinDistance,
                         DefaultComparator{}, param_names);
}
