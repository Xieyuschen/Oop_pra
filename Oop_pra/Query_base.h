#ifndef ABSTRACT_H
#define ABSTRACT_H
#include<string>
#include<memory>
#include"Query12.3.h"
//class Query;
class Query_base
{
	friend class Query;

protected:
	using lineNo = TextQuery::LineNo;
	virtual ~Query_base() = default;
private:
	virtual QueryResult eval(const TextQuery&)const = 0;
	virtual std::string rep()const = 0;
};

//Query类向外提供接口，同时隐藏继承体系。
class Query
{
	friend Query operator~(const Query&);
	friend Query operator|(const Query&, const Query&);
	friend Query operator|(const Query&, const Query&);

public:
	Query(const std::string&);
	QueryResult eval(const TextQuery& t)const { return q->eval(t); }
	std::string rep()const { return q->rep(); }
private:
	Query(std::shared_ptr<Query_base> query) :q(query) {}
	std::shared_ptr<Query_base> q;
};


#endif // !ABSTRACT_H
