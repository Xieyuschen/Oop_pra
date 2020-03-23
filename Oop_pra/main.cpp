#include"myStrBlob.h"
#include<string>
#include<vector>
#include<iostream>
#include<memory>
#include<algorithm>
using namespace std;
int main() {
	vector<int> vec;
	vector<int>::iterator it;
	vector<int>::allocator_type alloc;
	for (int i = 0; i < 10; i++) {
		vec.push_back(i);
	}
	for (it = vec.begin(); it != vec.end(); it++) {
		cout << *it << ends;
	}
	cout << endl;
	allocator<int>::const_pointer ptr;
	const int k = 6;
	ptr = alloc.address(*find(vec.begin(), vec.end(), k));
	//alloc.destroy(ptr);
	//alloc.construct(ptr, 10000);
	for (it = vec.begin(); it != vec.end(); it++) {
		cout << *it << ends;
	}
	return 0;
}