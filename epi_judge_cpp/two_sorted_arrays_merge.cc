#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

void MergeTwoSortedArrays(vector<int>& A, int m, const vector<int>& B, int n) {
  int res_i = m + n - 1;
  int A_i = m - 1;
  int B_i = n - 1;
  while (A_i >= 0 && B_i >= 0) {
    A[res_i--] = A[A_i] > B[B_i] ? A[A_i--] : B[B_i--];
  }
  while (B_i >= 0) {
    A[res_i--] = B[B_i--];
  }
}
vector<int> MergeTwoSortedArraysWrapper(vector<int> A, int m,
                                        const vector<int>& B, int n) {
  MergeTwoSortedArrays(A, m, B, n);
  return A;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "m", "B", "n"};
  return GenericTestMain(
      args, "two_sorted_arrays_merge.cc", "two_sorted_arrays_merge.tsv",
      &MergeTwoSortedArraysWrapper, DefaultComparator{}, param_names);
}
