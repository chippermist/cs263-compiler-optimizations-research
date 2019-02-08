#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
	vector<int> nums{1,1,1,3,4,4,4,4,4,6,7,7,6,5,4,8,9,8,7,0};
	unordered_map<int,int> mp;

	for(auto i : nums) {
		if(mp.find(i) != mp.end()) {
			mp[i]++;
		} else {
			mp[i] = 1;
		}
	}

	for(auto i : mp) {
		if(i.second % 2 != 0)
			cout << i.first << " ";
	}
	return 0;
}