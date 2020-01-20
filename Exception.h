#ifndef Exception_H
#define Exception_H

#include <exception>
#include <string>

class CException : public std::exception
{
public:
	CException(std::string const sErrorMsg);
	~CException();

	const char* what() const override;

private:
	std::string m_sErrorMsg;
};

#endif // Exception_H