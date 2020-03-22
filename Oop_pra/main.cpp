#include"Employee.h"
#include<string>
using namespace std;
int main() {
	string s = "zhao";
	//b=a这里调用的是拷贝构造函数，不会调用赋值运算符
	Employee a(s), b=a, c;
	c = b;
	f(a); f(b); f(c);
	return 0;
}