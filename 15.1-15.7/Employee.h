#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include<string>
#include<iostream>
class Employee
{
public:
	Employee(){ employId=startId++; }
	Employee(const std::string& n) { name = n;  employId = startId++; }
	Employee& operator=(Employee& n) {
		employId = startId++;
		name = n.name;
		return *this;
	}
	Employee(const Employee& n) {
		employId = startId++;
		name = n.name;
	}
	~Employee()=default;
	//不希望修改就const修饰,引用效率高用着爽
	const std::string& get_name(Employee& s) { return s.name; }
	const int& get_id(Employee& s) { return s.employId; }
private:
	static int startId;
	int employId;
	std::string name;
};
int Employee::startId = 0;
void f(Employee& s) {
	std::cout << s.get_name(s) << " 's id is :" << s.get_id(s) << std::endl;
}
#endif // EMPLOYEE_H
