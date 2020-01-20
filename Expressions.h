#ifndef Expressions_H
#define Expressions_H

#include <list>
#include <string>
#include "Node.h"

class AVisitor;

/////////////////////////////////////////////////
//
//	IExpression
//
class IExpression : public INode
{
public:
    virtual ~IExpression() = default;
};
/////////////////////////////////////////////////

/////////////////////////////////////////////////
//
//	CExpressionNumber
//
class CExpressionNumber : public IExpression
{
private:
    int m_iValue;
    
public:
    CExpressionNumber(int iValue);

	int getValue();
	void accept(AVisitor *pVisitor) override;
};
/////////////////////////////////////////////////

/////////////////////////////////////////////////
//
//	CExpressionVariable
//
class CExpressionVariable : public IExpression
{
private:
    std::string m_sName;
    
public:
    CExpressionVariable(std::string sName);
    
	std::string getName();
	void accept(AVisitor *pVisitor) override;
};
/////////////////////////////////////////////////

/////////////////////////////////////////////////
//
//	CExpressionFunctional
//
class CExpressionFunctional : public IExpression
{
private:
    std::string m_sFuncName;
    std::list<IExpression*> m_lstArgs;
    
public:
    CExpressionFunctional(std::string sFuncName);
    CExpressionFunctional(std::string sFuncName, std::list<IExpression*> lstArgs);
    
    void addArgument(IExpression *pArg);    
	
	std::string getFunctionName();
	std::list<IExpression*> getArgumentList();

	void accept(AVisitor *pVisitor) override;
};
/////////////////////////////////////////////////

/////////////////////////////////////////////////
//
//	CExpressionUnary
//
class CExpressionUnary : public IExpression
{
private:
    char m_chOperation;
    IExpression* m_pExpr;

public:
    CExpressionUnary(char chOperation, IExpression* pExpr);

	char getOperation();
	IExpression* getExpression();

	void accept(AVisitor *pVisitor) override;
};
/////////////////////////////////////////////////

/////////////////////////////////////////////////
//
//	CExpressionVariable
//
class CExpressionBinary : public IExpression
{
private:
    IExpression *m_pLeftOperand;
    IExpression *m_pRightOperand;
    char m_chOperation;
    
public:
    CExpressionBinary(char chOperation, IExpression *pLeftOperand, IExpression *pRightOperand);

	char getOperation();
	IExpression* getLeftOperand();
	IExpression* getRightOperand();

	void accept(AVisitor *pVisitor) override;
};
/////////////////////////////////////////////////

#endif // Expressions_H
