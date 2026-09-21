#include <cstddef>

#include "test_framework/generic_test.h"

static short preComputedParity[65536];

short Parity(unsigned long long x) {
	static int kMask = 0xFFFF;
	x ^= x >> 32;
	x ^= x >> 16;
	return preComputedParity[x & kMask];
}

short Parity3(unsigned long long x) {
	x ^= x >> 32;
	x ^= x >> 16;
	x ^= x >> 8;
	x ^= x >> 4;
	x ^= x >> 2;
	x ^= x >> 1;
	return x & 1;
}

short Parity2(unsigned long long x) {
	static int kMaskSize = 16;
	static int kMask = 0xFFFF;
	return preComputedParity[x >> (3 * kMaskSize)] ^
		   preComputedParity[x >> (2 * kMaskSize) & kMask] ^
		   preComputedParity[x >> kMaskSize & kMask] ^
		   preComputedParity[x & kMask];
}

short Parity1(unsigned long long x) {
	short ret = 0;
	while (x) {
		x &= (x - 1);
		ret ^= 1;
	}
	return ret;
}

int main(int argc, char* argv[]) {
	// prepare cache
	for (std::size_t i = 0; i < 65536; ++i)
		preComputedParity[i] = Parity1(i);
	std::vector<std::string> args{argv + 1, argv + argc};
	std::vector<std::string> param_names{"x"};
	return GenericTestMain(args, "parity.cc", "parity.tsv", &Parity,
						   DefaultComparator{}, param_names);
}
