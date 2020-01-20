#ifndef Statemenst_H
#define Statemenst_H

#include "Expressions.h"
#include "Node.h"

class AVisitor;

/////////////////////////////////////////////////
//
//	IStatement
//
class IStatement : public INode
{
public:
	virtual ~IStatement() = default;
};
/////////////////////////////////////////////////

/////////////////////////////////////////////////
//
//	CStatementAssignment
//
class CStatementAssignment : public IStatement
{
private:
    std::string m_sIdentifier;
    IExpression *m_pExpression;
    
public:
    CStatementAssignment(std::string sIdentifier, IExpression *pExpression);

	std::string getIdentifier();
	IExpression* getExpression();

	void accept(AVisitor *pVisitor) override;
};
/////////////////////////////////////////////////

/////////////////////////////////////////////////
//
//	CStatementPrint
//
class CStatementPrint : public IStatement
{
private:
    IExpression *m_pExpression;
    
public:
    CStatementPrint(IExpression* pExpression);
   
	IExpression* getExpression();
	
	void accept(AVisitor *pVisitor) override;
};
/////////////////////////////////////////////////

/////////////////////////////////////////////////
//
//	CStatementFunctionCall
//
class CStatementFunctionCall : public IStatement
{
private:
    CExpressionFunctional *m_pFunctionalExpression;
    
public:
    CStatementFunctionCall(CExpressionFunctional *pFunctionalExpression);
    
	CExpressionFunctional* getFunctionalExpression();
	
	void accept(AVisitor *pVisitor) override;
};
/////////////////////////////////////////////////

/////////////////////////////////////////////////
//
//	CStatementFunctionDefine
//
class CStatementFunctionDefine : public IStatement
{
private:
    std::string m_sFuncName;
    std::list<std::string> m_lstArgNames;
    IExpression* m_pBody;
    
public:
    CStatementFunctionDefine(std::string sFuncName, std::list<std::string> lstArgNames, IExpression* pBody);
    
	std::string getName();
	IExpression* getBody();
	std::list<std::string> getArgumentList();

	void accept(AVisitor *pVisitor) override;
};
/////////////////////////////////////////////////

/////////////////////////////////////////////////
//
//	CStatementBlock
//
class CStatementBlock : public IStatement
{
private:
    std::list<IStatement*> m_lstStatements;

public:
	CStatementBlock();

    void addStatement(IStatement* pStatement);
	std::list<IStatement*> getStatementList();
	
	void accept(AVisitor *pVisitor) override;
};
/////////////////////////////////////////////////

#endif // Statemenst_H
