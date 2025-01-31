#include <string>
#include <vector>
#include <limits>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;

int FindNearestRepetition(const vector<string>& paragraph) {
  std::unordered_map<std::string, int> seen_words{};
  int nearest_dist = std::numeric_limits<int>::max();

  for (int i = 0; i < paragraph.size(); ++i) {
    const std::string& word = paragraph[i];

    auto word_prev_it = seen_words.find(word);
    if (word_prev_it != seen_words.end()) {
      int dist = abs(i - word_prev_it->second);
      nearest_dist = std::min(nearest_dist, dist);
    }

    seen_words[word] = i;
  }

  return nearest_dist == std::numeric_limits<int>::max()
    ? -1
    : nearest_dist;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"paragraph"};
  return GenericTestMain(args, "nearest_repeated_entries.cc",
                         "nearest_repeated_entries.tsv", &FindNearestRepetition,
                         DefaultComparator{}, param_names);
}
