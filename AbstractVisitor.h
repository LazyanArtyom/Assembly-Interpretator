#ifndef AbstractVisitor_H
#define AbstractVisitor_H

#include "Statements.h"
#include "Expressions.h"

class AVisitor
{
public:
	virtual ~AVisitor() {}

	virtual void visit(CStatementAssignment *pSt);
	virtual void visit(CStatementFunctionDefine *pSt);
	virtual void visit(CStatementFunctionCall *pSt);
	virtual void visit(CStatementBlock *pSt);
	virtual void visit(CStatementPrint *pSt);

	virtual void visit(CExpressionFunctional *pSt);
	virtual void visit(CExpressionUnary *pSt);
	virtual void visit(CExpressionBinary *pSt);
	virtual void visit(CExpressionNumber *pSt);
	virtual void visit(CExpressionVariable *pSt);
};
#endif // AbstractVisitor_H

