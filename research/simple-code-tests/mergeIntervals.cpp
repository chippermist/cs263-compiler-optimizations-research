#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <unordered_set>
#include <utility>

using namespace std;

pair<int, int> findBoundaries(string str) {
	const string delimiter = "-";
	int a, b;
	size_t pos = 0;
	string token;
	while ((pos = str.find(delimiter)) != string::npos) {
	    token = str.substr(0, pos);
	    //cout << token << std::endl;
	    a = atoi(token.c_str());
	    str.erase(0, pos + delimiter.length());
	}
	b = atoi(str.c_str());
	//cout << a << " " << b << endl;
	return pair<int,int> (a,b);
}

vector<string> mergeIntervals(vector<string>& arr1, vector<string>& arr2) {
	vector<pair<int,int> > intervals;
	vector<pair<int,int> > res;
	vector<string> result;

	for(string it : arr1) {
		intervals.push_back(findBoundaries(it));
	}
	for(string it : arr2) {
		intervals.push_back(findBoundaries(it));
	}

	

	sort(intervals.begin(), intervals.end(), [&](pair<int,int> a, pair<int,int> b){
		return a.first <= b.first;
	});

	for(auto it : intervals) {
		cout << it.first << " " << it.second << endl;
	}

	res.push_back(intervals[0]);

	for(auto it : intervals) {
		if(res.back().second < it.first) {
			res.push_back(it);
		} else {
			res.back().second = max(res.back().second, it.second);
		}
	}

	for(auto it : res) {
		result.push_back(to_string(it.first) + "-" + to_string(it.second));
	}

	return result;
}

int main() {
	vector<string> arr1 {"3-11","17-25","58-73"};
	vector<string> arr2 {"6-18","40-47"};
	vector<string> result = mergeIntervals(arr1, arr2);
	cout << endl;
	for(auto i : result) {
		cout << i << " ";
	}
	cout << endl;
	return 0;
}