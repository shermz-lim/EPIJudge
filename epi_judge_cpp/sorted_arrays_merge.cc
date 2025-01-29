#include <vector>
#include <functional>
#include <queue>

#include "test_framework/generic_test.h"
using std::vector;

struct PQNode {
  int data;
  int arr_idx;
  int idx;
};

vector<int> MergeSortedArrays(const vector<vector<int>>& sorted_arrays) {
  std::priority_queue<PQNode, std::vector<PQNode>, std::function<bool(const PQNode&, const PQNode&)>>
  pq {
    [](const PQNode& a, const PQNode& b) {
      return a.data > b.data;
    }
  };

  for (int arr_idx = 0; arr_idx < sorted_arrays.size(); ++arr_idx) {
    if (!sorted_arrays[arr_idx].empty()) {
      pq.emplace(sorted_arrays[arr_idx][0], arr_idx, 0);
    }
  }

  std::vector<int> res{};
  while (!pq.empty()) {
    PQNode node{pq.top()};
    pq.pop();

    res.emplace_back(node.data);

    const auto& arr = sorted_arrays[node.arr_idx];
    const int new_idx = node.idx + 1;
    if (new_idx < arr.size()) {
      pq.emplace(arr[new_idx], node.arr_idx, new_idx);
    }
  }

  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sorted_arrays"};
  return GenericTestMain(args, "sorted_arrays_merge.cc",
                         "sorted_arrays_merge.tsv", &MergeSortedArrays,
                         DefaultComparator{}, param_names);
}
