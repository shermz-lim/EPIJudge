#include <string>

#include "test_framework/generic_test.h"
using std::string;

bool IsLetterConstructibleFromMagazine(const string& letter_text,
                                       const string& magazine_text) {
  std::unordered_map<char, int> char_freq{};
  for (char c : magazine_text) {
    char_freq[c]++;
  }
  for (char c : letter_text) {
    char_freq[c]--;
    if (char_freq[c] < 0) {
      return false;
    }
  }
  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"letter_text", "magazine_text"};
  return GenericTestMain(args, "is_anonymous_letter_constructible.cc",
                         "is_anonymous_letter_constructible.tsv",
                         &IsLetterConstructibleFromMagazine,
                         DefaultComparator{}, param_names);
}
