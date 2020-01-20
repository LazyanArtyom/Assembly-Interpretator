#include "AssemblyCodeGenerator.h"
#include <iostream>
#include "SymbolTable.h"
#include "Exception.h"

CAssemblyCodeGenerator::CAssemblyCodeGenerator() 
	: m_oMemory(CMemory::getInstance())
{
	m_oCodeStream << ".code \n";
	m_oDataStream << ".data \n";
}

void CAssemblyCodeGenerator::visit(CStatementAssignment *pSt)
{
    CSymbolTable &oSymbolTable = CSymbolTable::getInstance();
   
    oSymbolTable.set( pSt->getIdentifier(), CSymbolTable::SData { CSymbolTable::EDataType::Variable } );
	m_oDataStream << "dword " << pSt->getIdentifier() << std::endl;

	m_oCodeStream << "assign " << m_oMemory.AddAdressRegister() << " " << pSt->getIdentifier() << std::endl;

	IExpression *pExpression = pSt->getExpression();
	pExpression->accept(this);

	m_oCodeStream << "store " << m_oMemory.getGPRegister() << " " << m_oMemory.getAdressRegister() << std::endl; 
} 

void CAssemblyCodeGenerator::visit(CStatementFunctionDefine *pSt)
{
	CSymbolTable &oSymbolTable = CSymbolTable::getInstance();

	std::list<std::string> lstArgments = pSt->getArgumentList();

	for (std::string &sArg : lstArgments)
		oSymbolTable.set(sArg, CSymbolTable::SData { CSymbolTable::EDataType::Variable } );

	m_oCodeStream << pSt->getName() << ": " << std::endl;
	m_oCodeStream << "push SF" << std::endl;
	m_oCodeStream << "assign " << m_oMemory.AddGPRegister() << " 12" << std::endl;
	
    oSymbolTable.set(
        pSt->getName(), CSymbolTable::SData { CSymbolTable::EDataType::Function, new CFunctionUserDefined(pSt->getArgumentList(), pSt->getBody()) }
    );

	IExpression *pBody = pSt->getBody();
	pBody->accept(this);
}

void CAssemblyCodeGenerator::visit(CExpressionFunctional *pSt)
{
	std::list<IExpression*> lstArgs = pSt->getArgumentList();
	for (IExpression *pArgument : lstArgs)
	{
		pArgument->accept(this);
	}
	///////////////////////////////////////////////////

	CSymbolTable &oSymbolTable = CSymbolTable::getInstance();
    
    CSymbolTable::SData sData = oSymbolTable.get(pSt->getFunctionName(), CSymbolTable::EDataType::Function);
    IFunction* pFunction = sData.pFunction;
    
    if (pFunction == nullptr)
		throw CException(pSt->getFunctionName()  + " Function not found.");
    
    CFunctionUserDefined *pUserDefFunc = dynamic_cast<CFunctionUserDefined*>(pFunction);
    
    if (pUserDefFunc != nullptr)
    {
        if (lstArgs.size() != pUserDefFunc->getArgsCount())
			throw CException("Args count mismatch.");
        
		// push stack pop stack
        int i = 0;
		m_oCodeStream << "\n\n";
        while (!lstArgs.empty())
        {
            oSymbolTable.set(
                pUserDefFunc->getArgumentName(i),
                CSymbolTable::SData { CSymbolTable::EDataType::Variable } // arg values
            );
            lstArgs.pop_front();

			m_oCodeStream << "push " << m_oMemory.getGPRegister() << std::endl; 

            i++;
        }
    }

	// function call
	m_oCodeStream << "call " << pSt->getFunctionName() << std::endl;
	m_oCodeStream << "pop SF" << std::endl << "ret" << std::endl;
}

void CAssemblyCodeGenerator::visit(CExpressionUnary *pSt)
{
	IExpression *pExpression = pSt->getExpression();
	pExpression->accept(this);

	m_oCodeStream << "neg " << m_oMemory.getGPRegister(false) << std::endl;
}

void CAssemblyCodeGenerator::visit(CExpressionBinary *pSt)
{
	IExpression *pLeftOperand = pSt->getLeftOperand();
	IExpression *pRightOperand = pSt->getRightOperand();

	pLeftOperand->accept(this);
	pRightOperand->accept(this);

	std::string sReg2 = m_oMemory.getGPRegister();
	std::string sReg1 = m_oMemory.getGPRegister(false);

	switch (pSt->getOperation())
	{
	case '+':
		m_oCodeStream << "add " << sReg1 << " " << sReg2 << std::endl;
		break;
	case '-':
		m_oCodeStream << "sub " << sReg1 << " " << sReg2 << std::endl;
		break;
	case '*':
		m_oCodeStream << "mul " << sReg1 << " " << sReg2 << std::endl;
		break;
	case '/':
		m_oCodeStream << "div " << sReg1 << " " << sReg2 << std::endl;
		break;
	}
}

void CAssemblyCodeGenerator::visit(CExpressionNumber *pSt)
{
	m_oCodeStream << "assign " << m_oMemory.AddGPRegister() << " " << pSt->getValue() << std::endl;
}

void CAssemblyCodeGenerator::visit(CExpressionVariable* pSt)
{
	CSymbolTable &oSymbolTable = CSymbolTable::getInstance();

	std::string sVarName = pSt->getName();
    
	if (!oSymbolTable.contains(sVarName, CSymbolTable::EDataType::Variable))
		throw CException(sVarName + ": Unknown Constant");

    CSymbolTable::SData result = oSymbolTable.get(sVarName, CSymbolTable::EDataType::Variable);

	m_oCodeStream << "assign " << m_oMemory.AddAdressRegister() << " " << sVarName << std::endl;
	m_oCodeStream << "load " << m_oMemory.AddGPRegister() << " " << m_oMemory.getAdressRegister() << std::endl;
}

std::string CAssemblyCodeGenerator::getOutput()
{
	CSymbolTable &oSymbolTable = CSymbolTable::getInstance();
	std::string sSymboltable = oSymbolTable.getSymbolTable();
	oSymbolTable.clear();
	m_oMemory.clear();

	return m_oDataStream.str() +  "\n\n" + m_oCodeStream.str() + "\n\n" + sSymboltable;
}
