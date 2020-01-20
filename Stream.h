#ifndef Stream_H
#define Stream_H

#include <fstream>
#include <string>

class CStream 
{
public:
	CStream(std::string sFileName);
	~CStream();

	std::ifstream* getInput();
	void setOutput(std::string sOutput, bool bBinary = false);

private:
	std::ifstream*  m_pInput;
	std::ofstream*  m_pOutput;
	std::string     m_sFileName;
};

#endif // Stream_H