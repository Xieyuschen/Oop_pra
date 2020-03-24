#ifndef STRING_H
#define STRING_H
#include<memory>
#include<initializer_list>
#include<iostream>
#include<string>
using namespace std;
class String
{
public:
    String() : String("") { }
    String(const char*);
    String(const String&);
    String& operator=(const String&);
    ~String();

    const char* c_str() const { return elements; }
    size_t size() const { return end - elements; }
    size_t length() const { return end - elements - 1; }

private:
    std::pair<char*, char*> alloc_n_copy(const char*, const char*);
    void range_initializer(const char*, const char*);
    void free();

private:
    char* elements;
    char* end;
    std::allocator<char> alloc;
};

#endif // !STRING_H

//嗯我写的稀烂的代码，仍这里学习别人的吧。。。
//class String
//{
//public:
//	String(const char* s)
//	{
//		size_t len = leng(s);
//		char* it = alloc.allocate(len);
//		element = it;
//		for (size_t i = 0; i < len; i++) {
//			alloc.construct(it++, s++);
//		}
//		first_free = it;
//	}
//	~String();
//
//private:
//	char* element;
//	char* first_free;
//	std::allocator<char> alloc;
//};
//size_t leng(const char* s) {
//	size_t len = 0;
//	while (*s++ != '\0') {
//		++len;
//	}
//	return len;
//}
