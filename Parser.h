#ifndef Parser_H
#define Parser_H

#include <memory>
#include <list>

#include "Token.h"
#include "Expressions.h"
#include "Statements.h"

class CParser
{
private:
    std::list<CToken*> m_lstTokens;
    std::list<IStatement*> m_lstStatements;
    size_t m_nSize;
    int m_nPosition;
    
    bool match(TokenType eType);
    CToken* get(int nOffset);
    
    // parsing
    CExpressionFunctional* function();
    IExpression* expression();
    IExpression* additive();
    IExpression* multiplicative();
    IExpression* unary();
    IExpression* primary();
    
    IStatement* statement();
    IStatement* assignStatement();
    CStatementFunctionDefine* functionDefine();
    
public:
    CParser(std::list<CToken*> lstTokens);
    ~CParser();
    IStatement* parse();
};

#endif // Parser_H
