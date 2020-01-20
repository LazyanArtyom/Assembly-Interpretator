#ifndef BinaryCodeGenerator_H
#define BinaryCodeGenerator_H

#include "AbstractVisitor.h"
#include "Memory.h"
#include <fstream>
#include <sstream>

class CBinaryCodeGenerator : public AVisitor
{
public:
	CBinaryCodeGenerator();

public:
	enum class ERegsType : uint8_t
	{
		AARegister  =  0b00000000,   //  Address Address  Register
		AGRegister  =  0b00000001,   //  Address Genereal Register
		GARegister  =  0b00000010,   //  Genereal Address Register
		GGRegister  =  0b00000011,   //  Genereal General Register
	};

	enum class EOpSize : uint8_t
	{
		DWord = 0b10000000,
	};

	enum class EOpCode : uint8_t
	{
		call   =   0b00000010,
		ret    =   0b00000011,
		exit   =   0b00000100,
		push   =   0b00001111,
		pop    =   0b00010000,
		pushf  =   0b00010001,
		popf   =   0b00010010,
		pushsf =   0b00010011,
		popsf  =   0b00010100,
		assign =   0b00010101,
		move   =   0b00010110,
		load   =   0b00011000,
		store  =   0b00011001,
		add    =   0b00100000,
		sub    =   0b00100001,
		mul    =   0b00100010,
		div    =   0b00100011,
		adc    =   0b00101010,
		sbb    =   0b00101011,
		imul   =   0b00101100,
		idiv   =   0b00101101,
		neg    =   0b00101110
	};

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

#endif // BinaryCodeGenerator_H
