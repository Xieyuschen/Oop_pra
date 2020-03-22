#ifndef HASPTR_H
#define HASPTR_H
#include<string>
#include<iostream>
using namespace std;
class HasPtr
{
public:
	HasPtr(const string& s = string()) :
		ps(new string(s)), i(0) {}; 
	HasPtr(const HasPtr &p) :ps(new string(*p.ps)), i(p.i) {};

	HasPtr& operator=(const HasPtr& p) {
		auto newps = new string(*p.ps);
		delete ps;
		ps = newps;
		i = p.i;
		return *this;
	}
	~HasPtr() {
		delete ps;
	}

private:
	string* ps;
	int i;
};


#endif // !HASPTR_H
