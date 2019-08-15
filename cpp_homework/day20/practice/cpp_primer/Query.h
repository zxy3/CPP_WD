#ifndef QUERY_H
#define QUERY_H
#include "TextQuery.h"
#include <string>
#include <set>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>

//抽象类作为具体查询类型的基类;所有成员都是私有的
class Query_base
{
    friend class Query;

protected:
    typedef TextQuery::line_no line_no; // 在eval函数中使用
    virtual ~Query_base() {}

private:
    // eval返回与此查询匹配的QueryResult
    virtual QueryResult eval(const TextQuery &) const = 0;
    // rep是查询的字符串表示形式
    virtual std::string rep() const = 0;
};

// 接口类来管理Query_base继承层次结构
class Query
{
    // 这些操作符需要访问shared_ptr构造函数
    friend Query operator~(const Query &);
    friend Query operator|(const Query &, const Query &);
    friend Query operator&(const Query &, const Query &);

public:
    Query(const std::string &); // 构建一个新的WordQuery
    // 接口函数:调用相应的Query_base操作
    QueryResult eval(const TextQuery &t) const
    {
        return q->eval(t);
    }
    std::string rep() const { return q->rep(); }

private:
    Query(std::shared_ptr<Query_base> query) : q(query) {}
    std::shared_ptr<Query_base> q;
};
inline std::ostream &
operator<<(std::ostream &os, const Query &query)
{
    // Query::rep通过它指向rep()的Query_base指针进行虚拟调用。
    return os << query.rep();
}

class WordQuery : public Query_base
{
    friend class Query; // Query使用WordQuery构造函数
    WordQuery(const std::string &s) : query_word(s) {}

    // 具体类:WordQuery定义所有继承的纯虚拟函数
    QueryResult eval(const TextQuery &t) const
    {
        return t.query(query_word);
    }
    std::string rep() const { return query_word; }
    std::string query_word; // 要搜索的单词
};

inline Query::Query(const std::string &s) : q(new WordQuery(s)) {}

class NotQuery : public Query_base
{
    friend Query operator~(const Query &);
    NotQuery(const Query &q) : query(q) {}

    // 具体类:NotQuery定义所有继承的纯虚拟函数
    std::string rep() const { return "~(" + query.rep() + ")"; }
    QueryResult eval(const TextQuery &) const;
    Query query;
};

class BinaryQuery : public Query_base
{
protected:
    BinaryQuery(const Query &l, const Query &r, std::string s) : lhs(l), rhs(r), opSym(s) {}

    // 抽象类:BinaryQuery没有定义eval
    std::string rep() const { return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")"; }

    Query lhs, rhs;    // 左右操作数
    std::string opSym; // 操作人员姓名
};

class AndQuery : public BinaryQuery
{
    friend Query operator&(const Query &, const Query &);
    AndQuery(const Query &left, const Query &right) : BinaryQuery(left, right, "&") {}

    // 具体类:AndQuery继承rep并定义其余的纯虚拟
    QueryResult eval(const TextQuery &) const;
};

class OrQuery : public BinaryQuery
{
    friend Query operator|(const Query &, const Query &);
    OrQuery(const Query &left, const Query &right) : BinaryQuery(left, right, "|") {}

    QueryResult eval(const TextQuery &) const;
};

inline Query operator&(const Query &lhs, const Query &rhs)
{
    return std::shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}

inline Query operator|(const Query &lhs, const Query &rhs)
{
    return std::shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}

inline Query operator~(const Query &operand)
{
    return std::shared_ptr<Query_base>(new NotQuery(operand));
}

std::ifstream &open_file(std::ifstream &, const std::string &);
TextQuery get_file(int, char **);
bool get_word(std::string &);
bool get_words(std::string &, std::string &);
std::ostream &print(std::ostream &, const QueryResult &);

#endif
