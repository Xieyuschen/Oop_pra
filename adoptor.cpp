#include<iostream>
#include<vector>
#include<stack>
#include<concurrent_priority_queue.h>
#include<algorithm>
using namespace std;
int main() {
	vector<int> vec{ 4,3,2,1,6,0,9 };
	stack<int,vector<int>> s(vec);
	while (!s.empty()) {
		cout << s.top() << ends;
		s.pop();
	}
}