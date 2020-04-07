#ifndef SALEDATA_H
#define SALEDATA_H
#include<string>
class Sale_data {
private:
	std::string bookNo;
	int units_sold = 0;
	double revenue = 0.0;
public:
	Sale_data(std::string _bookNo, int u, double _revenue) :bookNo(_bookNo),units_sold(u),revenue(_revenue){};
	//与默认合成的拷贝构造函数相同
	Sale_data(const Sale_data& org) :bookNo(org.bookNo), units_sold(org.units_sold), revenue(org.revenue) {};




};

#endif // !SALDATA_H
