#ifndef AssemblyCodeGenerator_H
#define AssemblyCodeGenerator_H

#include "AbstractVisitor.h"
#include "Memory.h"
#include <fstream>
#include <sstream>

class CAssemblyCodeGenerator : public AVisitor
{
public:
	CAssemblyCodeGenerator();

	void visit(CStatementAssignment *pSt) override;
	void visit(CStatementFunctionDefine *pSt) override;

	void visit(CExpressionFunctional *pSt) override;
	void visit(CExpressionUnary *pSt) override;
	void visit(CExpressionBinary *pSt) override;
	void visit(CExpressionNumber *pSt) override;
	void visit(CExpressionVariable *pSt) override;

	std::string getOutput();
private:
	CMemory& m_oMemory;
	std::stringstream m_oDataStream;
	std::stringstream m_oCodeStream;
};

#endif // AssemblyCodeGenerator_H
