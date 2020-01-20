#include "Statements.h"
#include "SymbolTable.h"
#include "AbstractVisitor.h"
#include <iostream>

////////////////////////////////////////////////////////////////////////////////
//
//	CStatementAssignment Implementation
//
CStatementAssignment::CStatementAssignment(std::string sIdentifier, IExpression *pExpression)
    : m_sIdentifier(sIdentifier), m_pExpression(pExpression)
{
	CGarbageCollector &pGarbageCollector = CGarbageCollector::getInstance();
	pGarbageCollector.addPtr(this);
}

std::string CStatementAssignment::getIdentifier()
{
	return m_sIdentifier;
}

IExpression* CStatementAssignment::getExpression()
{
	return m_pExpression;
}

void CStatementAssignment::accept(AVisitor *pVisitor)
{
	pVisitor->visit(this);
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//	CStatementPrint Implementation
//
CStatementPrint::CStatementPrint(IExpression *pExpression) : m_pExpression(pExpression)
{
	CGarbageCollector &pGarbageCollector = CGarbageCollector::getInstance();
	pGarbageCollector.addPtr(this);
}

IExpression * CStatementPrint::getExpression()
{
	return m_pExpression;
}

void CStatementPrint::accept(AVisitor *pVisitor)
{
	pVisitor->visit(this);
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//	CStatementFunctionCall Implementation
//
CStatementFunctionCall::CStatementFunctionCall(CExpressionFunctional *pFunctionalExpression)
    : m_pFunctionalExpression(pFunctionalExpression)
{
	CGarbageCollector &pGarbageCollector = CGarbageCollector::getInstance();
	pGarbageCollector.addPtr(this);
}

CExpressionFunctional* CStatementFunctionCall::getFunctionalExpression()
{
	return m_pFunctionalExpression;
}

void CStatementFunctionCall::accept(AVisitor *pVisitor)
{
	pVisitor->visit(this);
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//	CStatementFunctionDefine Implementation
//
CStatementFunctionDefine::CStatementFunctionDefine(std::string sFuncName, std::list<std::string> lstArgNames, IExpression* pBody)
    : m_sFuncName(sFuncName), m_lstArgNames(lstArgNames), m_pBody(pBody)
{
	CGarbageCollector &pGarbageCollector = CGarbageCollector::getInstance();
	pGarbageCollector.addPtr(this);
}

std::string CStatementFunctionDefine::getName()
{
	return m_sFuncName;
}

IExpression* CStatementFunctionDefine::getBody()
{
	return m_pBody;
}

std::list<std::string> CStatementFunctionDefine::getArgumentList()
{
	return m_lstArgNames;
}

void CStatementFunctionDefine::accept(AVisitor *pVisitor)
{
	pVisitor->visit(this);
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//	CStatementBlock Implementation
//
CStatementBlock::CStatementBlock()
{
	CGarbageCollector &pGarbageCollector = CGarbageCollector::getInstance();
	pGarbageCollector.addPtr(this);
}

void CStatementBlock::addStatement(IStatement *pStatement)
{
    m_lstStatements.push_back(pStatement);
}

std::list<IStatement*> CStatementBlock::getStatementList()
{
	return m_lstStatements;
}

void CStatementBlock::accept(AVisitor *pVisitor)
{
	pVisitor->visit(this);
}
////////////////////////////////////////////////////////////////////////////////