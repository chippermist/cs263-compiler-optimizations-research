#include <iostream>
#include <unordered_set>
#include <string>
#include <vector>

using namespace std;

int main() {
	vector<string> v1 {"Raja Uthaya", "Antony Karthi" 
	,"Christopher Raja","Manickam Antony" ,"Veeramani", "Chinmay Garg" };
	vector<string> v2 {"Antony Karthi" 
	,"Christopher Raja","Veeramani" };
	unordered_set<string> s1 (v1.begin(), v1.end());
	unordered_set<string> s2 (v2.begin(), v2.end());

	for(auto it : s2) {
		if(s1.find(it) != s1.end()) {
			s1.erase(it);
		}
	}

	for(auto it : s1) {
		cout << it << endl;
	}

	return 0;
}