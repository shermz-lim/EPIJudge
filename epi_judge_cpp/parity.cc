#include "test_framework/generic_test.h"
short Parity(unsigned long long x) {
  static const std::vector<bool> lookup_table = []() {
    // initialize parity lookup table for 16 bit integers
    size_t size = 1 << 16;
    std::vector<bool> table(size);

    for (size_t x = 0; x < size; x++) {
      size_t tmp = x;
      for (size_t width = 8; width > 0; width >>= 1) {
        tmp ^= (tmp >> width);
      }
      tmp &= 0x1;

      table[x] = tmp;
    }

    return table;
  }();

  x ^= (x >> 32);
  x ^= (x >> 16);
  x &= 0xFFFF;
  return lookup_table[x];
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "parity.cc", "parity.tsv", &Parity,
                         DefaultComparator{}, param_names);
}
