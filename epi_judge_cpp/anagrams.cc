#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

#include "test_framework/generic_test.h"
using std::string;
using std::unordered_map;
using std::vector;

typedef unordered_map<string, vector<string>>::iterator iterator;

static string copy_sort(const string& str) {
	string str_copy(str);
	std::sort(str_copy.begin(), str_copy.end());
	return str_copy;
}

vector<vector<string>> FindAnagrams(const vector<string>& dictionary) {
	unordered_map<string, vector<string>> groups;
	for (const string& word : dictionary) {
		string word_id(copy_sort(word));
		iterator it = groups.find(word_id);
		if (it == groups.end()) {
			vector<string> group;
			group.push_back(word);
			groups.insert({word_id, group});
		} else {
			vector<string>& group = (*it).second;
			group.push_back(word);
		}
	}
	vector<vector<string>> ret;
	for (iterator it = groups.begin(); it != groups.end(); ++it) {
		vector<string>& group = (*it).second;
		if (group.size() > 1)
			ret.push_back(group);
	}
	return ret;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{argv + 1, argv + argc};
	std::vector<std::string> param_names{"dictionary"};
	return GenericTestMain(args, "anagrams.cc", "anagrams.tsv", &FindAnagrams,
						   UnorderedComparator{}, param_names);
}
