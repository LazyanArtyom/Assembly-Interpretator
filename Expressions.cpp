#include <iostream>
#include "Expressions.h"
#include "Token.h"
#include "SymbolTable.h"
#include "AbstractVisitor.h"

////////////////////////////////////////////////////////////////////////////////
//
//	CExpressionNumber Implementation
//
CExpressionNumber::CExpressionNumber(int iValue) : m_iValue(iValue)
{
	CGarbageCollector &pGarbageCollector = CGarbageCollector::getInstance();
	pGarbageCollector.addPtr(this);
}

int CExpressionNumber::getValue()
{
	return m_iValue;
}

void CExpressionNumber::accept(AVisitor *pVisitor)
{
	pVisitor->visit(this);
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//	CExpressionVariable Implementation
//
CExpressionVariable::CExpressionVariable(std::string sName) : m_sName(sName)
{
	CGarbageCollector &pGarbageCollector = CGarbageCollector::getInstance();
	pGarbageCollector.addPtr(this);
}

std::string CExpressionVariable::getName()
{
	return m_sName;
}

void CExpressionVariable::accept(AVisitor *pVisitor)
{
	pVisitor->visit(this);
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//	CExpressionFunctional Implementation
//
CExpressionFunctional::CExpressionFunctional(std::string sFuncName) : m_sFuncName(sFuncName)
{
	CGarbageCollector &pGarbageCollector = CGarbageCollector::getInstance();
	pGarbageCollector.addPtr(this);
}

CExpressionFunctional::CExpressionFunctional(std::string sFuncName, std::list<IExpression*> lstArgs)
    : m_sFuncName(sFuncName), m_lstArgs(lstArgs)
{
	CGarbageCollector &pGarbageCollector = CGarbageCollector::getInstance();
	pGarbageCollector.addPtr(this);
}

void CExpressionFunctional::addArgument(IExpression *pArg)
{
    m_lstArgs.push_back(pArg);
}

std::string CExpressionFunctional::getFunctionName()
{
	return m_sFuncName;
}

std::list<IExpression*> CExpressionFunctional::getArgumentList()
{
	return m_lstArgs;
}

void CExpressionFunctional::accept(AVisitor *pVisitor)
{
	pVisitor->visit(this);
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//	CExpressionUnary Implementation
//
CExpressionUnary::CExpressionUnary(char chOperation, IExpression* pExpr)
: m_chOperation(chOperation), m_pExpr(pExpr)
{
	CGarbageCollector &pGarbageCollector = CGarbageCollector::getInstance();
	pGarbageCollector.addPtr(this);
}

char CExpressionUnary::getOperation()
{
	return m_chOperation;
}

IExpression* CExpressionUnary::getExpression()
{
	return m_pExpr;
}

void CExpressionUnary::accept(AVisitor *pVisitor)
{
	pVisitor->visit(this);
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//	CExpressionBinary Implementation
//
CExpressionBinary::CExpressionBinary(
    char chOperation, IExpression *pLeftOperand, IExpression *pRightOperand
)
    : m_chOperation(chOperation), m_pLeftOperand(pLeftOperand), m_pRightOperand(pRightOperand)
{
	CGarbageCollector &pGarbageCollector = CGarbageCollector::getInstance();
	pGarbageCollector.addPtr(this);
}

char CExpressionBinary::getOperation()
{
	return m_chOperation;
}

IExpression* CExpressionBinary::getLeftOperand()
{
	return m_pLeftOperand;
}

IExpression* CExpressionBinary::getRightOperand()
{
	return m_pRightOperand;
}

void CExpressionBinary::accept(AVisitor *pVisitor)
{
	pVisitor->visit(this);
}
////////////////////////////////////////////////////////////////////////////////