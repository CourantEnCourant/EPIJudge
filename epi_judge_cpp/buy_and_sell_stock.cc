#include <algorithm>
#include <limits>
#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

// optimal solution of caching min price of every day
// time: O(n)
// space: O(1)
double BuyAndSellStockOnce(const vector<double>& prices) {
	double min_prices = std::numeric_limits<double>::max();
	double max_profit = 0;
	for (double price : prices) {
		min_prices = price < min_prices ? price : min_prices;
		double profit = price - min_prices;
		max_profit = profit > max_profit ? profit : max_profit;
	}
	return max_profit;
}

// my solution of caching max selling-price of each day
// time: O(n)
// space: O(n)
double BuyAndSellStockOnce1(const vector<double>& prices) {
	vector<double> max_per_day;
	max_per_day.push_back(prices[prices.size() - 1]);
	for (int i = prices.size() - 2; i >= 0; --i) {
		double local_max = prices[i] > max_per_day.back() ? prices[i] : max_per_day.back();
		max_per_day.push_back(local_max);
	}
	std::reverse(max_per_day.begin(), max_per_day.end());

	double max_diff = 0;
	for (int i = 0; i < prices.size(); ++i) {
		double diff = max_per_day[i] - prices[i];
		max_diff = diff > max_diff ? diff : max_diff;
	}

	return max_diff;
}

// brute force
double BuyAndSellStockOnce0(const vector<double>& prices) {
	double max_profit = 0;
	for (int i = 0; i < prices.size(); ++i) {
		double local_profit = 0;
		for (int j = i + 1; j < prices.size(); ++j) {
			double profit = prices[j] - prices[i];
			local_profit = profit > local_profit ? profit : local_profit;
		}
		max_profit = local_profit > max_profit ? local_profit : max_profit;
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
