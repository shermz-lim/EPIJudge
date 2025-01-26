#include <vector>
#include <cmath>
#include <limits>

#include "test_framework/generic_test.h"
using std::vector;
double BuyAndSellStockOnce(const vector<double>& prices) {
  double max_profit = 0;
  double min_price = std::numeric_limits<double>::infinity();
  for (double price : prices) {
    // the max profit if we sell at this price is the
    // price - min price seen so far
    double max_profit_i = price - min_price;
    max_profit = fmax(max_profit, max_profit_i);
    min_price = fmin(min_price, price);
  }
  return max_profit;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"prices"};
  return GenericTestMain(args, "buy_and_sell_stock.cc",
                         "buy_and_sell_stock.tsv", &BuyAndSellStockOnce,
                         DefaultComparator{}, param_names);
}
