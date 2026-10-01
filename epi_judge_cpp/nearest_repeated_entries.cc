#include <climits>
#include <string>
#include <unordered_map>
#include <vector>

#include "test_framework/generic_test.h"
using std::string;
using std::unordered_map;
using std::vector;

struct WordInfo {
	int last;
	int minimum;
};

int FindNearestRepetition(const vector<string>& paragraph) {
	unordered_map<string, WordInfo> m;
	for (int i = 0; i < paragraph.size(); ++i) {
		auto it = m.find(paragraph[i]);
		if (it == m.end())
			m[paragraph[i]] = {i, INT_MAX};
		else {
			auto& [_, info] = *it;
			int cur = i - info.last;
			info.last = i;
			info.minimum = cur < info.minimum ? cur : info.minimum;
		}
	}
	int minimum = INT_MAX;
	for (auto& [_, info] : m)
		minimum = info.minimum < minimum ? info.minimum : minimum;
	return minimum == INT_MAX ? -1 : minimum;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{argv + 1, argv + argc};
	std::vector<std::string> param_names{"paragraph"};
	return GenericTestMain(args, "nearest_repeated_entries.cc",
						   "nearest_repeated_entries.tsv", &FindNearestRepetition,
						   DefaultComparator{}, param_names);
}
