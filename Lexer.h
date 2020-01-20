#ifndef Lexer_H
#define Lexer_H

#include <list>

#include "Stream.h"
#include "Token.h"

class CLexer final
{    
public:
    CLexer(std::ifstream* pInput);
    ~CLexer();
    
    std::list<CToken*> tokenize();
    void clear();

private:
	std::ifstream* m_pInput;
    std::list<CToken*> m_lstTokens;
    char m_chCurrent;
    
    void addToken(TokenType eType);
    void addToken(TokenType eType, std::string sData);
    
    void tokenizeNumber();
    void tokenizeWord();
    
    char peekNext();
    char peekCurrent();
    char next();
};

#endif // Lexer_H
