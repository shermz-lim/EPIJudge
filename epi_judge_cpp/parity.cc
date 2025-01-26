#include "test_framework/generic_test.h"

short Parity(unsigned long long x) {
  // initialize parity lookup table for 16 bit integers
  constexpr int table_sz = 1 << 16;
  static constexpr std::array<bool, table_sz> lookup_table = []() constexpr {
    std::array<bool, table_sz> table{};

    for (int x = 0; x < table_sz; ++x) {
      int tmp = x;
      for (int width = 8; width > 0; width >>= 1) {
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
