#include <cstddef>
#include <cstdlib>
#include <sstream>
#include <stack>
#include <string>

#include "test_framework/generic_test.h"
using std::string;

static int eval(const std::string& exp, int lhs, int rhs) {
	if (exp == "+")
		return lhs + rhs;
	else if (exp == "-")
		return lhs - rhs;
	else if (exp == "*")
		return lhs * rhs;
	else
		return lhs / rhs;
}

int Evaluate(const string& expression) {
	std::stack<int> nums;
	std::stringstream ss(expression);
	for (string exp; std::getline(ss, exp, ',');) {
		if (exp == "+" || exp == "-" || exp == "*" || exp == "/") {
			int rhs = nums.top();
			nums.pop();
			int lhs = nums.top();
			nums.pop();
			nums.push(eval(exp, lhs, rhs));
		} else {
			nums.push(std::atoi(exp.c_str()));
		}
	}
	return nums.top();
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{argv + 1, argv + argc};
	std::vector<std::string> param_names{"expression"};
	return GenericTestMain(args, "evaluate_rpn.cc", "evaluate_rpn.tsv", &Evaluate,
						   DefaultComparator{}, param_names);
}
