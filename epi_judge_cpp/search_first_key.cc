#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

int SearchFirstOfK(const vector<int>& A, int k) {
  int low = 0;
  int high = A.size();
  while (low < high) {
    int mid = low + (high - low) / 2;
    if (A[mid] < k) {
      low = mid + 1;
    } else {
      high = mid;
    }
  }
  return (low >= A.size() || A[low] != k) ? -1 : low;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "k"};
  return GenericTestMain(args, "search_first_key.cc", "search_first_key.tsv",
                         &SearchFirstOfK, DefaultComparator{}, param_names);
}
