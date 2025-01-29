#include "test_framework/generic_test.h"

int SquareRoot(int k) {
  if (k == 0 || k == 1) return k;

  long low = 0;
  long high = k;
  while (low < high) {
    long mid = low + (high - low) / 2;
    if (mid * mid > k) {
      high = mid;
    } else {
      low = mid + 1;
    }
  }
  return low - 1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"k"};
  return GenericTestMain(args, "int_square_root.cc", "int_square_root.tsv",
                         &SquareRoot, DefaultComparator{}, param_names);
}
