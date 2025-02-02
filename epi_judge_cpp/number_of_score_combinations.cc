#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

int NumCombinationsForFinalScore(int final_score,
                                 const vector<int>& individual_play_scores) {
  int n = individual_play_scores.size();
  // init bottom-up dp array
  std::vector<std::vector<int>> num_combis(
    n, std::vector<int>(final_score + 1, 0)
  );

  // fill with starting values
  for (int score = 0; score <= final_score; score += individual_play_scores[0]) {
    num_combis[0][score] = 1;
  }

  // bottom-up dp
  for (int i = 1; i < n; ++i) {
    int play_score = individual_play_scores[i];
    for (int score = 0; score <= final_score; ++score) {
      num_combis[i][score] = num_combis[i - 1][score] + (
        (score >= play_score)
        ? num_combis[i][score - play_score]
        : 0
      );
    }
  }
  return num_combis[n - 1][final_score];
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"final_score", "individual_play_scores"};
  return GenericTestMain(args, "number_of_score_combinations.cc",
                         "number_of_score_combinations.tsv",
                         &NumCombinationsForFinalScore, DefaultComparator{},
                         param_names);
}
