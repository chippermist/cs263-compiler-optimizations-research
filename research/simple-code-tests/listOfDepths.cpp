/* INCOMPLETE */
#include <iostream>
#include <vector>

using namespace std;

struct TreeNode{
    int data;
    node *right, *left;
    TreeNode : data(x);
};

TreeNode *insert(vector<int>& data, int begin, int end) {
	if(data.size() == 0)
		return nullptr;

	int mid = data.size()/2;
	TreeNode head = new TreeNode(data[mid]);
	head->left = insert(data, start, mid-1);
	head->right = insert(data, mid+1, end);

	return head;
}

// void bfs(TreeNode *root, vector<list<int> >& lists, list<int>& tempList, int level) {
// 	if(!root) return;
	
// }


int main() {
	vector<int> data {0,1,2,3,4,4};
	TreeNode *head;
	head = insert(data, 0, data.size());
	return 0;
}