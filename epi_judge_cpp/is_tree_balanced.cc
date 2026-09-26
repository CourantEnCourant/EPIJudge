#include <cmath>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

struct Result {
	int level;
	bool is_balanced;
};

Result isSubTreeBalanced(const unique_ptr<BinaryTreeNode<int>>& node) {
	if (!node->left && !node->right) {
		return {1, true};
	}
	Result left = {0, true};
	Result right = {0, true};
	if (node->left) {
		left = isSubTreeBalanced(node->left);
		if (!left.is_balanced)
			return left;
	}
	if (node->right) {
		right = isSubTreeBalanced(node->right);
		if (!right.is_balanced)
			return right;
	}
	if (std::abs(left.level - right.level) > 1)
		return {0, false};
	if (left.level > right.level)
		return {left.level + 1, true};
	else
		return {right.level + 1, true};
}

bool IsBalanced(const unique_ptr<BinaryTreeNode<int>>& tree) {
	if (!tree)
		return true;
	return isSubTreeBalanced(tree).is_balanced;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{argv + 1, argv + argc};
	std::vector<std::string> param_names{"tree"};
	return GenericTestMain(args, "is_tree_balanced.cc", "is_tree_balanced.tsv",
						   &IsBalanced, DefaultComparator{}, param_names);
}
