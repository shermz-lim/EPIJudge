#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

vector<int> IntersectTwoSortedArrays(const vector<int>& A,
                                     const vector<int>& B) {
  std::vector<int> res{};
  int i = 0;
  int j = 0;
  while (i < A.size() && j < B.size()) {
    int a = A[i];
    int b = B[j];
    if (a < b) {
      i++;
    } else if (a > b) {
      j++;
    } else {
      res.push_back(a);
      while (i < A.size() && A[i] == a) {
        i++;
      }
    }
  }
  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "B"};
  return GenericTestMain(
      args, "intersect_sorted_arrays.cc", "intersect_sorted_arrays.tsv",
      &IntersectTwoSortedArrays, DefaultComparator{}, param_names);
}
