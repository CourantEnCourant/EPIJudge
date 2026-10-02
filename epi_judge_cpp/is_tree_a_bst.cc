#include <climits>
#include <memory>
#include <queue>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::queue;
using std::unique_ptr;

struct QNode {
	const BinaryTreeNode<int>* tree_ptr;
	int lowest;
	int largest;
};

static bool bfsCheck(const unique_ptr<BinaryTreeNode<int>>& tree) {
	queue<QNode> q;
	q.push({tree.get(), INT_MIN, INT_MAX});
	while (!q.empty()) {
		auto cur = q.front();
		q.pop();
		if (cur.tree_ptr == nullptr)
			continue;
		if (cur.tree_ptr->data < cur.lowest || cur.tree_ptr->data > cur.largest)
			return false;
		q.push({cur.tree_ptr->left.get(), cur.lowest, cur.tree_ptr->data});
		q.push({cur.tree_ptr->right.get(), cur.tree_ptr->data, cur.largest});
	}
	return true;
}

static bool recursiveCheck1(const unique_ptr<BinaryTreeNode<int>>& tree, int lowest, int largest) {
	if (tree == nullptr)
		return true;
	if (tree->data < lowest || tree->data > largest)
		return false;
	if (!recursiveCheck1(tree->left, lowest, tree->data))
		return false;
	if (!recursiveCheck1(tree->right, tree->data, largest))
		return false;
	return true;
}

bool IsBinaryTreeBST(const unique_ptr<BinaryTreeNode<int>>& tree) {
	return bfsCheck(tree);
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{argv + 1, argv + argc};
	std::vector<std::string> param_names{"tree"};
	return GenericTestMain(args, "is_tree_a_bst.cc", "is_tree_a_bst.tsv",
						   &IsBinaryTreeBST, DefaultComparator{}, param_names);
}
