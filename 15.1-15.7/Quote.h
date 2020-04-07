#ifndef QUOTE_H
#define QUOTE_H
#include<string>
#include<iostream>
using namespace std;

class Quote
{
	//��Ȼ��Ҫ!=�������Ϊʲô��������Ϊ��Ա�������ǳ�Ϊ��Ԫ��
	//��ϣ���ڼ̳е�ʱ�������������������Ǽ�Ȼ������Ҫ����Ƚ���ô����������Ҳ����Ҫ�ġ�
	//һ���һ�����ϰɡ�
	friend bool operator !=(const Quote& lhs, const Quote& rhs);

public:
	Quote()=default;
	Quote(const std::string& book, double sales_price) :bookNo(book), price(sales_price) {};

	//�������Ƴ�Ա��
	Quote(const Quote& rhs) {
		bookNo = rhs.bookNo;
		price = rhs.price;
	}
	Quote& operator=(const Quote& rhs) {
		if (this != &rhs) {
			bookNo = rhs.bookNo;
			price = rhs.price;
		}
		return *this;
	}
	Quote(Quote&& rhs) :bookNo(move(rhs.bookNo)), price(move(rhs.price)) {};
	Quote& operator=(Quote&& rhs) {
		if (this != &rhs) {
			bookNo = move(rhs.bookNo);
			price = move(rhs.price);
		}
		return *this;
	}
	std::string isbn() const { return bookNo; }
	virtual double net_price(std::size_t n) const { return n * price; }
	virtual ~Quote()=default;
	virtual void debug() const {
		cout << "The data members are: 1.bookNo 2.price" << endl;
	}
private:
	std::string bookNo;
protected:
	double price = 0.0;
};
bool inline
operator !=(const Quote& lhs, const Quote& rhs)
{
	return lhs.bookNo != rhs.bookNo
		&&
		lhs.price != rhs.price;
}



//ostream���ܿ�������������
class Bulk_quote:public Quote
{
public:
	
	Bulk_quote(const std::string& book, double sales_price, std::size_t qty, double _discount) :Quote(book, sales_price),min_qty(qty),discount(_discount) {};
		
	double net_price(std::size_t n)const override {
		if (n >= min_qty) {
			return n * (1 - discount) * price;
		}
		else
			return n * price;
	}
	void debug()const override {
		cout << "The data members are: 1.bookNo 2.price 3.min_qty 4.discount" << endl;
	}
private:
	std::size_t min_qty;
	double discount;
};
class Limited_Quote:public Quote
{
public:
	Limited_Quote(const std::string& book, double sales_price, std::size_t qty, double _discount) :Quote(book, sales_price), min_qty(qty), discount(_discount) {};
	double net_price(size_t n)const override {
		if (n < min_qty) {
			return n * (1 - discount) * price;
		}
		else
		{
			return n * price - discount * price * min_qty;
		}
	}
	void debug()const override {
		cout << "The data members are: 1.bookNo 2.price 3.min_qty 4.discount" << endl;
	}
private:
	size_t min_qty;
	double discount;
};
double print_total(std::ostream& os, const Quote& item, std::size_t n) {
	double ret = item.net_price(n);
	os << "ISBN: " << item.isbn() << " #sold: " << n << " total due: " << ret << endl;
	return ret;
}

#endif // !QUOTE_H
