#include <functional>
#include <queue>
#include <vector>

#include "test_framework/generic_test.h"
using std::priority_queue;
using std::vector;

typedef vector<int>::const_iterator iterator;

struct Result {
	int value;
	iterator cur;
	iterator end;
};

bool od(Result a, Result b) { return a.value > b.value; }

vector<int> MergeSortedArrays(const vector<vector<int>>& sorted_arrays) {
	priority_queue<Result, vector<Result>, std::function<bool(Result, Result)>> pq(od);
	/*
	for (int i = 0; i < sorted_arrays.size(); ++i)
		pq.push({sorted_arrays[i][0], sorted_arrays[i].begin() + 1, sorted_arrays[i].end()});
	*/
	// remember to use reference with for (T item : items)
	for (const vector<int>& v : sorted_arrays)
		pq.push({v[0], v.begin() + 1, v.end()});
	vector<int> ret;
	while (!pq.empty()) {
		Result r = pq.top();
		pq.pop();
		ret.push_back(r.value);
		if (r.cur != r.end) {
			int cur_val = *r.cur;
			iterator it = r.cur + 1;
			pq.push({cur_val, it, r.end});
		}
	}
	return ret;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{argv + 1, argv + argc};
	std::vector<std::string> param_names{"sorted_arrays"};
	return GenericTestMain(args, "sorted_arrays_merge.cc",
						   "sorted_arrays_merge.tsv", &MergeSortedArrays,
						   DefaultComparator{}, param_names);
}
