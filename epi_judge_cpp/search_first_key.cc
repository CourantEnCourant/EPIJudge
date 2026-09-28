#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

typedef std::vector<int>::const_iterator iterator;

int SearchFirstOfK(const vector<int>& A, int k) {
	if (A.empty())
		return -1;
	int l = 0;
	int u = A.size() - 1;
	while (l <= u) {
		int m = l + (u - l) / 2;
		if (A[m] > k)
			u = m - 1;
		else if (A[m] < k)
			l = m + 1;
		else if (m == 0 || A[m - 1] != k)
			return m;
		else
			u = m - 1;
	}
	return -1;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{argv + 1, argv + argc};
	std::vector<std::string> param_names{"A", "k"};
	return GenericTestMain(args, "search_first_key.cc", "search_first_key.tsv",
						   &SearchFirstOfK, DefaultComparator{}, param_names);
}
