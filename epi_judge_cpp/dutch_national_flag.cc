#include <array>
#include <cstddef>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::vector;
enum class Color { kRed,
				   kWhite,
				   kBlue };

typedef vector<Color>::iterator ColorIt;

static void swap(Color& a, Color& b) {
	Color tmp = a;
	a = b;
	b = tmp;
}

void DutchFlagPartition(int pivot_index, vector<Color>* A_ptr) {
	vector<Color>& A = *A_ptr;
	const Color pivot = A[pivot_index];
	int smaller = 0;
	int bigger = A.size() - 1;
	for (int i = 0; i <= bigger;) {
		if (A[i] < pivot)
			swap(A[i++], A[smaller++]);
		else if (A[i] > pivot)
			swap(A[i], A[bigger--]);
		else
			++i;
	}
}

void DutchFlagPartition2(int pivot_index, vector<Color>* A_ptr) {
	vector<Color>& A = *A_ptr;
	const Color pivot = A[pivot_index];
	int smaller = 0;
	for (int i = 0; i < A.size(); ++i) {
		if (A[i] < pivot)
			swap(A[i], A[smaller++]);
	}
	int bigger = A.size() - 1;
	for (int i = A.size() - 1; i >= smaller; --i) {
		if (A[i] > pivot)
			swap(A[i], A[bigger--]);
	}
}

void DutchFlagPartition1(int pivot_index, vector<Color>* A_ptr) {
	vector<Color>& A = *A_ptr;
	const Color pivot = A[pivot_index];
	for (int i = 0; i < A.size(); ++i) {
		for (int j = i + 1; j < A.size(); ++j) {
			if (A[j] < pivot) {
				swap(A[j], A[i]);
				break;
			}
		}
	}
	for (int i = A.size() - 1; i >= 0; --i) {
		for (int j = i - 1; j >= 0; --j) {
			if (A[j] > pivot) {
				swap(A[j], A[i]);
				break;
			}
		}
	}
}

void DutchFlagPartition0(int pivot_index, vector<Color>* A_ptr) {
	vector<Color>& A = *A_ptr;
	vector<Color> B;
	size_t i = 0;
	for (ColorIt it = A.begin(); it != A.end(); ++it) {
		if (*it < A[pivot_index]) {
			B.insert(B.begin() + i, *it);
			++i;
		} else if (*it == A[pivot_index])
			B.insert(B.begin() + i, *it);
		else
			B.push_back(*it);
	}
	A = B;
	return;
}

void DutchFlagPartitionWrapper(TimedExecutor& executor, const vector<int>& A,
							   int pivot_idx) {
	vector<Color> colors;
	colors.resize(A.size());
	std::array<int, 3> count = {0, 0, 0};
	for (size_t i = 0; i < A.size(); i++) {
		count[A[i]]++;
		colors[i] = static_cast<Color>(A[i]);
	}
	Color pivot = colors[pivot_idx];

	executor.Run([&] { DutchFlagPartition(pivot_idx, &colors); });

	int i = 0;
	while (i < colors.size() && colors[i] < pivot) {
		count[static_cast<int>(colors[i])]--;
		++i;
	}

	while (i < colors.size() && colors[i] == pivot) {
		count[static_cast<int>(colors[i])]--;
		++i;
	}

	while (i < colors.size() && colors[i] > pivot) {
		count[static_cast<int>(colors[i])]--;
		++i;
	}

	if (i != colors.size()) {
		throw TestFailure("Not partitioned after " + std::to_string(i) +
						  "th element");
	} else if (count != std::array<int, 3>{0, 0, 0}) {
		throw TestFailure("Some elements are missing from original array");
	}
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{argv + 1, argv + argc};
	std::vector<std::string> param_names{"executor", "A", "pivot_idx"};
	return GenericTestMain(args, "dutch_national_flag.cc",
						   "dutch_national_flag.tsv", &DutchFlagPartitionWrapper,
						   DefaultComparator{}, param_names);
}
