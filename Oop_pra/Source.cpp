#include "Header.h"
#include <sstream>
#include <algorithm>


TextQuery::TextQuery(std::ifstream& ifs) : input(new vector<string>)
{
    LineNo lineNo{ 0 };
    for (string line; std::getline(ifs, line); ++lineNo) {
        input->push_back(line);
        std::istringstream line_stream(line);
        //流在输入字符的时候会自动在空格处断开
        for (string text, word; line_stream >> text; word.clear()) {
            // avoid read a word followed by punctuation(such as: word, )
            std::remove_copy_if(text.begin(), text.end(), std::back_inserter(word), ispunct);
            // use reference avoid count of shared_ptr add.
            //如果map没有[]中所标识的值，那么就会在里面自动加一个
            auto& nos = result[word];
            if (!nos) nos.reset(new std::set<LineNo>);
            nos->insert(lineNo);
        }
    }
}

QueryResult TextQuery::query(const string& str) const
{
    // use static just allocate once.
    static shared_ptr<std::set<LineNo>> nodata(new std::set<LineNo>);
    //返回的是一个二元组
    auto found = result.find(str);
    //如果是尾后指针，则返回一个空的QueryResult对象
    if (found == result.end()) return QueryResult(str, nodata, input);
    else return QueryResult(str, found->second, input);
}

std::ostream& print(std::ostream& out, const QueryResult& qr)
{
    out << qr.word << " occurs " << qr.nos->size() << (qr.nos->size() > 1 ? " times" : " time") << std::endl;
    for (auto i : *qr.nos)
        out << "\t(line " << i + 1 << ") " << qr.input->at(i) << std::endl;
    return out;
}