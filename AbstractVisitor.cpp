#include "AbstractVisitor.h"
#include <iostream>

void AVisitor::visit(CStatementAssignment *pSt)
{
	IExpression *pExpression = pSt->getExpression();
	pExpression->accept(this);
}

void AVisitor::visit(CStatementFunctionDefine *pSt)
{
	IExpression *pBody = pSt->getBody();
	pBody->accept(this);
}

void AVisitor::visit(CStatementFunctionCall *pSt)
{
	CExpressionFunctional *pExprFunctional = pSt->getFunctionalExpression();
	pExprFunctional->accept(this);
}

void AVisitor::visit(CStatementBlock *pSt)
{
	std::list<IStatement*>  lstStatements = pSt->getStatementList();
	for (IStatement *pStatement : lstStatements)
	{
		pStatement->accept(this);
	}
}

void AVisitor::visit(CStatementPrint *pSt)
{
	IExpression *pExpression = pSt->getExpression();
	pExpression->accept(this);
}

void AVisitor::visit(CExpressionFunctional *pSt)
{
	std::list<IExpression*> lstArgs = pSt->getArgumentList();
	for (IExpression *pArgument : lstArgs)
	{
		pArgument->accept(this);
	}
}

void AVisitor::visit(CExpressionUnary *pSt)
{
	IExpression *pExpression = pSt->getExpression();
	pExpression->accept(this);
}

void AVisitor::visit(CExpressionBinary *pSt)
{
	IExpression *pLeftOperand = pSt->getLeftOperand();
	IExpression *pRightOperand = pSt->getRightOperand();
	pLeftOperand->accept(this);
	pRightOperand->accept(this);
}

void AVisitor::visit(CExpressionNumber *pSt)
{
}

void AVisitor::visit(CExpressionVariable * pSt)
{
}