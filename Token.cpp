#include "Token.h"

CToken::CToken() {}

CToken::CToken(TokenType eType, std::string sDate)
    : m_eType(eType), m_sData(sDate) {}

CToken::~CToken() {}

void CToken::setType(TokenType eType)
{
    m_eType = eType;
}

TokenType CToken::getType() const
{
    return m_eType;
}

void CToken::setData(std::string sData)
{
    m_sData = sData;
}

std::string CToken::getData() const
{
    return m_sData;
}
