#include "list_node.h"
#include "test_framework/generic_test.h"
shared_ptr<ListNode<int>> MergeTwoSortedLists(shared_ptr<ListNode<int>> L1,
                                              shared_ptr<ListNode<int>> L2) {
  ListNode<int> bef_head{};
  ListNode<int>* tail = &bef_head;
  while (L1 && L2) {
    auto& smaller = L1->data < L2->data ? L1 : L2;
    tail->next = smaller;
    tail = smaller.get();
    smaller = smaller->next;
  }
  tail->next = L1 ? L1 : L2;
  return bef_head.next;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L1", "L2"};
  return GenericTestMain(args, "sorted_lists_merge.cc",
                         "sorted_lists_merge.tsv", &MergeTwoSortedLists,
                         DefaultComparator{}, param_names);
}
