#include <string>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
using std::string;

string IntToString(int x) {
  bool neg = x < 0;

  std::string res{};
  do {
    res.push_back(abs(x % 10) + '0');
    x /= 10;
  } while (x);

  if (neg) {
    res.push_back('-');
  }
  std::reverse(res.begin(), res.end());

  return res;
}
int StringToInt(const string& s) {
  int i = 0;
  bool neg = false;
  if (s[i] == '-') {
    i++;
    neg = true;
  } else if (s[i] == '+') {
    i++;
  }

  int x = 0;
  for (; i < s.size(); i++) {
    x *= 10;
    x += (s[i] - '0');
  }

  return neg ? -x : x;
}
void Wrapper(int x, const string& s) {
  if (stoi(IntToString(x)) != x) {
    throw TestFailure("Int to string conversion failed");
  }

  if (StringToInt(s) != x) {
    throw TestFailure("String to int conversion failed");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "s"};
  return GenericTestMain(args, "string_integer_interconversion.cc",
                         "string_integer_interconversion.tsv", &Wrapper,
                         DefaultComparator{}, param_names);
}
