#ifndef CP5_ex12_27_h
#define CP5_ex12_27_h

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <memory>
using std::shared_ptr;

#include <iostream>
#include <fstream>
#include <map>
#include <set>

class QueryResult;
class TextQuery {
public:
    using LineNo = vector<string>::size_type;
    TextQuery(std::ifstream&);
    QueryResult query(const string&) const;
private:
    shared_ptr<vector<string>> input;
    //一个string出现的所有行数会被存储在map中，因为map.second是一个set
    std::map<string, shared_ptr<std::set<LineNo>>> result;
};

class QueryResult {
public:
    friend std::ostream& print(std::ostream&, const QueryResult&);
public:
    QueryResult(const string& s, shared_ptr<std::set<TextQuery::LineNo>> set, shared_ptr<vector<string>> v) : word(s), nos(set), input(v) { }
private:
    string word;
    shared_ptr<std::set<TextQuery::LineNo>> nos;
    shared_ptr<vector<string>> input;
};

std::ostream& print(std::ostream&, const QueryResult&);

#endif