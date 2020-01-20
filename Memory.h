#ifndef Memory_H
#define Memory_H

#include <string>
#include <stack>

class CMemory
{
public:
	CMemory();
	~CMemory() = default;

	CMemory(const CMemory&) = delete;
	CMemory& operator=(const CMemory&) = delete;

	static CMemory& getInstance();

	std::string getGPRegister(bool bPop = true);
	std::string AddGPRegister();

	std::string getAdressRegister(bool bPop = true);
	std::string AddAdressRegister();

	void clear();

private:
	std::stack<int> m_aGPRegisters;
	std::stack<int> m_aAdressRegisters;
};

#endif // Memory_H
