#include "test_framework/generic_test.h"
long long Reverse(int x) {
  bool neg = x < 0;
  long long res = 0;
  while (x != 0) {
    res *= 10;
    res += abs(x % 10);
    x /= 10;
  }
  return neg ? -res : res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "reverse_digits.cc", "reverse_digits.tsv",
                         &Reverse, DefaultComparator{}, param_names);
}
