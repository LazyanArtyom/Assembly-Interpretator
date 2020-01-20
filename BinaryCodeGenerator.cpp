#include "BinaryCodeGenerator.h"
#include <iostream>
#include "SymbolTable.h"
#include "Exception.h"
#include <sstream>

CBinaryCodeGenerator::CBinaryCodeGenerator() 
	: m_oMemory(CMemory::getInstance())
{
}

void CBinaryCodeGenerator::visit(CStatementAssignment *pSt)
{
    CSymbolTable &oSymbolTable = CSymbolTable::getInstance();

    oSymbolTable.set( pSt->getIdentifier(), CSymbolTable::SData { CSymbolTable::EDataType::Variable } );
	
	m_oDataStream << "Dword " << pSt->getIdentifier() << std::endl;

	std::string sAReg = m_oMemory.AddAdressRegister();
	sAReg.erase(0, 1);
	uint8_t nARegNumber = std::stoi(sAReg);
	
	m_oCodeStream << static_cast<uint8_t>(EOpCode::assign) << nARegNumber << pSt->getIdentifier(); // ???

	IExpression *pExpression = pSt->getExpression();
	pExpression->accept(this);

	std::string sGPReg = m_oMemory.getGPRegister();
	sGPReg.erase(0, 1);
	uint8_t nGPRegNumber = std::stoi(sGPReg);

	sAReg = m_oMemory.getAdressRegister();
	sAReg.erase(0, 1);
	nARegNumber = std::stoi(sAReg);

	m_oCodeStream << static_cast<uint8_t>(EOpCode::store) << nGPRegNumber << nARegNumber;
} 

void CBinaryCodeGenerator::visit(CStatementFunctionDefine *pSt)
{
	CSymbolTable &oSymbolTable = CSymbolTable::getInstance();

	std::list<std::string> lstArgments = pSt->getArgumentList();

	for (std::string &sArg : lstArgments)
		oSymbolTable.set(sArg, CSymbolTable::SData { CSymbolTable::EDataType::Variable } );

	m_oCodeStream << pSt->getName() << ":";
	m_oCodeStream << static_cast<uint8_t>(EOpCode::pushsf);
	
	std::string sGPReg = m_oMemory.AddGPRegister();
	sGPReg.erase(0, 1);
	uint8_t nGPRegNumber = std::stoi(sGPReg);
	
	m_oCodeStream << static_cast<uint8_t>(EOpCode::assign) << nGPRegNumber << static_cast<uint8_t>(12);
	
    oSymbolTable.set(
        pSt->getName(), CSymbolTable::SData { CSymbolTable::EDataType::Function, new CFunctionUserDefined(pSt->getArgumentList(), pSt->getBody()) }
    );

	IExpression *pBody = pSt->getBody();
	pBody->accept(this);
}

void CBinaryCodeGenerator::visit(CExpressionFunctional *pSt)
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
        while (!lstArgs.empty())
        {
            oSymbolTable.set(
                pUserDefFunc->getArgumentName(i),
                CSymbolTable::SData { CSymbolTable::EDataType::Variable }
            );
            lstArgs.pop_front();

			std::string sGPReg = m_oMemory.getGPRegister();
			sGPReg.erase(0, 1);
			uint8_t nGPRegNumber = std::stoi(sGPReg);

			m_oCodeStream << static_cast<uint8_t>(EOpCode::push) << nGPRegNumber;

            i++;
        }
    }

	// function call
	m_oCodeStream << static_cast<uint8_t>(EOpCode::call) << pSt->getFunctionName();
	m_oCodeStream << static_cast<uint8_t>(EOpCode::popsf);
	m_oCodeStream << static_cast<uint8_t>(EOpCode::ret);
}

void CBinaryCodeGenerator::visit(CExpressionUnary *pSt)
{
	IExpression *pExpression = pSt->getExpression();
	pExpression->accept(this);

	std::string sGPReg = m_oMemory.getGPRegister(false);
	sGPReg.erase(0, 1);
	uint8_t nGPRegNumber = std::stoi(sGPReg);

	m_oCodeStream << static_cast<uint8_t>(EOpCode::neg) << sGPReg;
}

void CBinaryCodeGenerator::visit(CExpressionBinary *pSt)
{
	IExpression *pLeftOperand = pSt->getLeftOperand();
	IExpression *pRightOperand = pSt->getRightOperand();

	pLeftOperand->accept(this);
	pRightOperand->accept(this);

	std::string sReg2 = m_oMemory.getGPRegister();
	std::string sReg1 = m_oMemory.getGPRegister(false);

	sReg1.erase(0, 1);
	sReg2.erase(0, 1);

	uint8_t nReg1Number = std::stoi(sReg1);
	uint8_t nReg2Number = std::stoi(sReg2);

	switch (pSt->getOperation())
	{
	case '+':
		m_oCodeStream << static_cast<uint8_t>(EOpCode::add);
		break;
	case '-':
		m_oCodeStream << static_cast<uint8_t>(EOpCode::sub);
		break;
	case '*':
		m_oCodeStream << static_cast<uint8_t>(EOpCode::mul);
		break;
	case '/':
		m_oCodeStream << static_cast<uint8_t>(EOpCode::div);
		break;
	}

	m_oCodeStream << (static_cast<uint8_t>(EOpSize::DWord) | static_cast<uint8_t>(ERegsType::GGRegister)) << nReg1Number << nReg2Number;
}

void CBinaryCodeGenerator::visit(CExpressionNumber *pSt)
{
	m_oCodeStream << static_cast<uint8_t>(EOpCode::assign);
	std::string sGPReg = m_oMemory.AddGPRegister();
	sGPReg.erase(0, 1);
	uint8_t nGPRegNumber = std::stoi(sGPReg);
	m_oCodeStream << nGPRegNumber << pSt->getValue();
}

void CBinaryCodeGenerator::visit(CExpressionVariable* pSt)
{
	CSymbolTable &oSymbolTable = CSymbolTable::getInstance();

	std::string sVarName = pSt->getName();
    
	if (!oSymbolTable.contains(sVarName, CSymbolTable::EDataType::Variable))
		throw CException(sVarName + ": Unknown Constant");

	std::string sAReg = m_oMemory.AddGPRegister();
	sAReg.erase(0, 1);
	uint8_t nARegNumber = std::stoi(sAReg);
	
	m_oCodeStream << static_cast<uint8_t>(EOpCode::assign) << nARegNumber << sVarName; // bug

	std::string sGPReg = m_oMemory.AddGPRegister();
	sGPReg.erase(0, 1);
	uint8_t nGPRegNumber = std::stoi(sGPReg);

	m_oCodeStream << static_cast<uint8_t>(EOpCode::load) << nGPRegNumber << nARegNumber;
}

std::string CBinaryCodeGenerator::getOutput()
{
	CSymbolTable &oSymbolTable = CSymbolTable::getInstance();

	std::string sSymboltable = oSymbolTable.getSymbolTable();
	oSymbolTable.clear();
	m_oMemory.clear();

	return m_oDataStream.str() + m_oCodeStream.str() + sSymboltable;
}