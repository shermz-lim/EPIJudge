#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

bool HasThreeSum(vector<int> A, int t) {
  std::sort(A.begin(), A.end());
  for (int x : A) {
    int t_new = t - x;
    // two sum problem to find new_t, allowing for using the same entry
    int i = 0;
    int j = A.size() - 1;
    while (i <= j) {
      int a = A[i];
      int b = A[j];
      if (a + b == t_new) {
        return true;
      } else if (a + b < t_new) {
        i++;
      } else {
        j--;
      }
    }
  }
  return false;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "t"};
  return GenericTestMain(args, "three_sum.cc", "three_sum.tsv", &HasThreeSum,
                         DefaultComparator{}, param_names);
}
