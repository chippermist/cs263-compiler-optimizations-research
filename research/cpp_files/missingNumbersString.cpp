#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

string toString(int n){
	ostringstream ss;
	ss << n;
	return ss.str();
}

string missingNumbers(vector<int> nums, int max){
	string temp = "";
	int last = 0;

	for(int i=0; i<nums.size()-1; i++){
		int difference = nums[i+1] - nums[i];

		if(difference > 2){
			temp += toString(nums[i] + 1);
			temp += "-";
			temp += toString(nums[i+1] - 1);
			last = nums[i+1];
		}
		else if(difference > 1){
			temp += toString(nums[i] + 1);
			last = nums[i] + 1;
		}

		if(i != nums.size() - 2 && difference != 1){
			temp += ", ";
		}


		if(i == nums.size() - 2 && nums[i+1] < max){
			difference = max - nums[i+1];

			temp += ", ";
			if(difference > 2){
				temp += toString(last+1);
				temp += "-";
				temp += toString(max);
			}
			else if(difference > 1){
				temp += toString(nums[i] + 1);
			}

		}
	}
	return temp;
}

int main(){
	vector<int> nums;

	nums.push_back(0);
	nums.push_back(1);
	nums.push_back(2);
	nums.push_back(50);
	nums.push_back(52);
	nums.push_back(67);
	nums.push_back(75);
	cout << missingNumbers(nums, 300) << endl;

	return 0;

}