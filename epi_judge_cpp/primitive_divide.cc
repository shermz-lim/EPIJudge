#include "test_framework/generic_test.h"
int Divide(int x, int y) {
  int k = 0;
  long long y2k = y;
  while (y2k <= x) {
    y2k <<= 1;
    k++;
  }

  int res = 0;
  while (x >= y) {
    while (y2k > x) {
      y2k >>= 1;
      k--;
    }

    res += (1 << k);
    x -= y2k;
  }
  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "y"};
  return GenericTestMain(args, "primitive_divide.cc", "primitive_divide.tsv",
                         &Divide, DefaultComparator{}, param_names);
}
