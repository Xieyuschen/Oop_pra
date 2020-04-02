#include"StrVec.h"
#include<string>
using namespace std;
void StrVec::range_initialize(const std::string* b, const std::string* c) {
	auto newpair=alloc_n_copy(b, c);
	elements = newpair.first;
	first_free = cap = newpair.second;
}
std::pair<string*,string*>
StrVec::alloc_n_copy(const std::string* b, const std::string* c) {
	auto data = alloc.allocate(c - b);
	return { data,uninitialized_copy(b,c,data) };
}
StrVec::StrVec(initializer_list<string> li) {
	range_initialize(li.begin(), li.end());
}

void StrVec::free() {
	if (elements) {
		for (auto p = first_free; p != elements;) {
			alloc.destroy(--p);
		}
		alloc.deallocate(elements, cap - elements);
	}
}
StrVec::~StrVec() {
	free();
}
StrVec::StrVec(const StrVec& rhs) {
	alloc_n_copy(rhs.begin(), rhs.end());
}
StrVec& StrVec::operator=(const StrVec& rhs) {
	auto data = alloc_n_copy(rhs.begin(), rhs.end());
	free();
	elements = data.first;
	first_free = cap = data.second;
	return *this;
}
void StrVec::alloc_n_move(size_t new_cap)
{
	auto newdata = alloc.allocate(new_cap);
	auto dest = newdata;
	auto elem = elements;
	for (size_t i = 0; i != size(); ++i)
		//���¹���ĸ�ֵ���Ѿɿռ��е�ֵ������������Ȼ��Ѿ������ͷŵ���
		alloc.construct(dest++, std::move(*elem++));
	free();
	elements = newdata;
	first_free = dest;
	cap = elements + new_cap;
}
void StrVec::reallocate() {
	size_t len = size() ? 2 * size() : 1;
	alloc_n_move(len);
	//��������ݼ��ϵ�һ�е����������ʼд�Ķ���
	//auto data=alloc.allocate(len);
	//�������ǲ��Եģ��ڸ�ֵ��ʱ������ô��
	//uninitailizer_copy����һ�����ǹ�initializer_listʹ�õģ��㶯̬allocate����������peach
	//�Թ��Լ�����ȥ�� mia~
	//auto it=uninitialized_copy(elements, first_free, data);
	//free();
	//elements = data;
	//first_free = cap;
}
void StrVec::push_back(const string& s) {
	chk_n_alloc();
	//��Ҫ++first_free ����first_free++
	alloc.construct(first_free++, s);
}

StrVec::StrVec(StrVec&& rhs):elements(rhs.elements),first_free(rhs.first_free),cap(rhs.cap){
	rhs.elements = rhs.first_free = rhs.cap = nullptr;
}
StrVec& StrVec::operator=(StrVec&& rhs)noexcept {
	if (this != &rhs) {
		free();
		elements = rhs.elements;
		first_free = rhs.first_free;
		cap = rhs.cap;
		rhs.elements = rhs.first_free = rhs.cap = nullptr;
	}
	return *this;
}