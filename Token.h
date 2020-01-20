#ifndef Token_H
#define Token_H

#include <string>

enum class TokenType
{
    NUMBER, MUL, DIV, ADD, SUB, EQUAL, PRINT, COMMA, DEF,
    LPAREN, RPAREN, WORD, EOL, END
};

class CToken final
{
private:
    TokenType m_eType;
    std::string m_sData;
    
public:
    CToken();
    CToken(TokenType eType, std::string sData);
    ~CToken();
    
    TokenType getType() const;
    void setType(TokenType eType);
    
    std::string getData() const;
    void setData(std::string sData);
};

#endif // Token_H
