#include "Memory.h"

CMemory::CMemory()
{
	m_aGPRegisters.push(0);
	m_aAdressRegisters.push(2);
}

CMemory& CMemory::getInstance()
{
	static CMemory instance;

	return instance;
}

std::string CMemory::getGPRegister(bool bPop)
{
	std::string sReg = "R" + std::to_string(m_aGPRegisters.top());

	if (bPop)
		m_aGPRegisters.pop();
	
	return sReg;
}

std::string CMemory::AddGPRegister()
{
	std::string sReg = "R" + std::to_string(m_aGPRegisters.top() + 4);
	m_aGPRegisters.push(m_aGPRegisters.top() + 4);
	return sReg;
}

std::string CMemory::getAdressRegister(bool bPop)
{
	std::string sReg = "A" + std::to_string(m_aAdressRegisters.top());

	if (bPop)
		m_aAdressRegisters.pop();
	
	return sReg;
}

std::string CMemory::AddAdressRegister()
{
	std::string sReg = "A" + std::to_string(m_aAdressRegisters.top() + 1);
	m_aAdressRegisters.push(m_aAdressRegisters.top() + 1);
	return sReg;
}

void CMemory::clear()
{
	while (!m_aAdressRegisters.empty())
		m_aAdressRegisters.pop();

	while (!m_aGPRegisters.empty())
		m_aGPRegisters.pop();

	m_aGPRegisters.push(0);
	m_aAdressRegisters.push(2);
}
