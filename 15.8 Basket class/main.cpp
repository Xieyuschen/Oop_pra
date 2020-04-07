#include<iostream>
#include"Basket.h"
#include"Quote.h"
#include"Bulk_quote.h"
using namespace std;
int main() {
	Bulk_quote bulk("0000", 10, 2, 0.1);
	Basket basket;
	basket.add_item(bulk);

	basket.total_receipt(cout);
	return 0;
}