#include "Stream.h"
#include <sstream>

CStream::CStream(std::string sFileName)
	: m_pInput(new std::ifstream(sFileName)),
	  m_pOutput(new std::ofstream),
	  m_sFileName("")
{
	std::stringstream ss(sFileName);

	while (ss.peek() != '.')
		m_sFileName += ss.get();
}

CStream::~CStream()
{
	m_pInput->close();
	m_pOutput->close();

	delete m_pInput;
	delete m_pOutput;
}

std::ifstream* CStream::getInput()
{
	return m_pInput;
}

void CStream::setOutput(std::string sOutput, bool bBinary)
{
	if (bBinary)
	{
		m_sFileName += ".bin.txt";
		m_pOutput->open(m_sFileName, std::ios::out | std::ios::binary);
		m_pOutput->write(reinterpret_cast<char*>(&sOutput), sOutput.size());
	}
	else
	{
		m_sFileName += ".asm.txt";
		m_pOutput->open(m_sFileName);
		*m_pOutput << sOutput;
	}
}