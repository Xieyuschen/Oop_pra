#include"Employee.h"
#include<string>
using namespace std;
int main() {
	string s = "zhao";
	//b=a������õ��ǿ������캯����������ø�ֵ�����
	Employee a(s), b=a, c;
	c = b;
	f(a); f(b); f(c);
	return 0;
}