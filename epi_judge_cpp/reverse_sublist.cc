#include "list_node.h"
#include "test_framework/generic_test.h"

shared_ptr<ListNode<int>> ReverseSublist(shared_ptr<ListNode<int>> L, int start,
                                         int finish) {
  if (start >= finish) {
    return L;
  }

  // create a dummy head that points to start of the list
  auto head = std::make_shared<ListNode<int>>(0, L);

  // bef_start tracks the node before the start node
  auto bef_start = head;
  for (int i = 0; i < (start - 1); ++i) {
    bef_start = bef_start->next;
  }

  auto curr = bef_start->next;
  for (int i = start; i < finish; ++i) {
    auto nxt = curr->next;
    curr->next = nxt->next;
    nxt->next = bef_start->next;
    bef_start->next = nxt;
  }

  return head->next;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L", "start", "finish"};
  return GenericTestMain(args, "reverse_sublist.cc", "reverse_sublist.tsv",
                         &ReverseSublist, DefaultComparator{}, param_names);
}
