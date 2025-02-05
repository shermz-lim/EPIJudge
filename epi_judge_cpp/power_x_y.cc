#include "test_framework/generic_test.h"
double Power(double x, int y) {
  if (y < 0) {
    x = 1 / x;
    y = -y;
  }
  double res = 1.0;
  while (y) {
    if ((y & 1) == 1) {
      res *= x;
    }
    x *= x;
    y >>= 1;
  }
  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "y"};
  return GenericTestMain(args, "power_x_y.cc", "power_x_y.tsv", &Power,
                         DefaultComparator{}, param_names);
}
