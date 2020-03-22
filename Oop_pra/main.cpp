#include"myStrBlob.h"
#include<string>
#include<iostream>
using namespace std;
int main() {
	
	StrBlob a;
	for (int i = 0; i < 10; i++) {
		a.push_back(to_string(i));
	}

	return 0;
}