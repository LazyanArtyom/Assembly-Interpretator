#include <iostream>
#include "Parser.h"
#include "Exception.h"

CParser::CParser(std::list<CToken*> lstTokens)
: m_lstTokens(lstTokens), m_nSize(m_lstTokens.size()), m_nPosition(0) {}

CParser::~CParser() {}

bool CParser::match(TokenType eType)
{
    CToken* currentToken = get(0);
    
    if (eType != currentToken->getType())
        return false;
   
    m_nPosition++;
    
    return true;
}

CToken* CParser::get(int nOffset)
{
    int nPos = m_nPosition + nOffset;
   
    if (nPos >= m_nSize)
        return new CToken(TokenType::END, "");
    
    // return Token from TokenList by position
    return *(std::next(m_lstTokens.begin(), nPos));
}

CExpressionFunctional* CParser::function()
{
    if (get(0)->getType() == TokenType::WORD)
    {
        std::string sFuncName = get(0)->getData();
        match(TokenType::WORD);
        
        if (match(TokenType::LPAREN))
        {
            CExpressionFunctional *pFunctionalExpr = new CExpressionFunctional(sFuncName);
            while (!match(TokenType::RPAREN))
            {
                pFunctionalExpr->addArgument(expression());
                match(TokenType::COMMA);
            }
            
            return pFunctionalExpr;
        }
        else
			throw CException("Invalid Function.");
    }
    
	throw CException("Missing bracket in function.");
    return nullptr;
}

IExpression* CParser::expression()
{
    return additive();
}

IExpression* CParser::additive()
{
    IExpression* pResult = multiplicative();
    
    while (true)
    {
        if (match(TokenType::ADD))
        {
            pResult = new CExpressionBinary('+', pResult, multiplicative());
            continue;
        }
        if (match(TokenType::SUB))
        {
            pResult = new CExpressionBinary('-', pResult, multiplicative());
            continue;
        }
        break;
    }
    
    return pResult;
}

IExpression* CParser::multiplicative()
{
    IExpression* pResult = unary();
    
    while (true)
    {
        if (match(TokenType::MUL))
        {
            pResult = new CExpressionBinary('*', pResult, unary());
            continue;
        }
        if (match(TokenType::DIV))
        {
            pResult = new CExpressionBinary('/', pResult, unary());
            continue;
        }
        break;
    }
    
    return pResult;
}

IExpression* CParser::unary()
{
    if (match(TokenType::SUB))
        return new CExpressionUnary('-', primary());
    if (match(TokenType::ADD))
        return primary();

    return primary();
}

IExpression* CParser::primary()
{
    CToken* pCurrentToken = get(0);
    
    if (match(TokenType::NUMBER))
        return new CExpressionNumber(std::stoi(pCurrentToken->getData()));
    
    if (get(0)->getType() == TokenType::WORD && get(1)->getType() == TokenType::LPAREN)
    {
        return function();
    }
    
    if (match(TokenType::WORD))
        return new CExpressionVariable(pCurrentToken->getData());
    
    if (match(TokenType::LPAREN))
    {
        IExpression *pResult = expression();
        if (!match(TokenType::RPAREN))
			throw CException("Missing Brackets.");
        
		return pResult;
    }
    
	throw CException("Unknown expression.");
}

IStatement* CParser::parse()
{
    CStatementBlock *pBlock = new CStatementBlock();
    
    while (!match(TokenType::END))
    {
        pBlock->addStatement(statement());
       
        if (!match(TokenType::EOL))
			throw CException("Expected ';' after expression.");
        else
            while (match(TokenType::EOL));
    }
    
    return pBlock;
}

IStatement* CParser::statement()
{
    if (match(TokenType::PRINT))
    {
        return new CStatementPrint(expression());
    }
    if (match(TokenType::DEF))
    {
        return functionDefine();
    }
    
    if (get(0)->getType() == TokenType::WORD && get(1)->getType() == TokenType::LPAREN)
    {
        return new CStatementFunctionCall(function());
    }
        
    return assignStatement();
}

IStatement* CParser::assignStatement()
{
    CToken* pCurrent = get(0);
    
    if (match(TokenType::WORD) && get(0)->getType() == TokenType::EQUAL)
    {
        match(TokenType::WORD);
        std::string sIdentifier = pCurrent->getData();
        match(TokenType::EQUAL);
        return new CStatementAssignment(sIdentifier, expression());
    }
    
	throw CException("Unknown statement.");
}

CStatementFunctionDefine* CParser::functionDefine()
{
    if (get(0)->getType() == TokenType::WORD)
    {
        std::string sFuncName = get(0)->getData();
        match(TokenType::WORD);
        
        if (match(TokenType::LPAREN))
        {
            std::list<std::string> argNames;
            
            while (!match(TokenType::RPAREN))
            {
                if (get(0)->getType() == TokenType::WORD)
                {
                    argNames.push_back(get(0)->getData());
                    match(TokenType::WORD);
                    match(TokenType::COMMA);
                }
                else
					throw CException("Invalid function argument.");
            }
            
            if (!match(TokenType::EQUAL))
				throw CException("Invalid function.");
            
            IExpression* pFuncBody = expression();
            
            return new CStatementFunctionDefine(sFuncName, argNames, pFuncBody);
        }
        else
			throw CException("Invalid function.");
    }
    
	throw CException("Missing bracket in function.");
}