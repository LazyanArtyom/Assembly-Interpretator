#include "Lexer.h"

CLexer::CLexer(std::ifstream* pInput) : m_pInput(pInput)
{
    next();
}

CLexer::~CLexer()
{
    clear();
}

void CLexer::addToken(TokenType eType)
{
    m_lstTokens.push_back(new CToken(eType, ""));
}

void CLexer::addToken(TokenType eType, std::string sData)
{
    m_lstTokens.push_back(new CToken(eType, sData));
}

char CLexer::peekNext()
{
    return m_pInput->peek();
}

char CLexer::peekCurrent()
{
    return m_chCurrent;
}

char CLexer::next()
{
    m_chCurrent = m_pInput->get();
    return m_chCurrent;
}

std::list<CToken*> CLexer::tokenize()
{
    char chCurrent;
    
    while ( (chCurrent = peekCurrent()) != EOF )
    {
        if (isspace(chCurrent))
        {
            next();
            continue;
        }
        
        switch(chCurrent)
        {
            case '+':
                addToken(TokenType::ADD);
                next();
                break;
            case '-':
                addToken(TokenType::SUB);
                next();
                break;
            case '*':
                addToken(TokenType::MUL);
                next();
                break;
            case '/':
                addToken(TokenType::DIV);
                next();
                break;
            case '(':
                addToken(TokenType::LPAREN);
                next();
                break;
            case ')':
                addToken(TokenType::RPAREN);
                next();
                break;
            case '=':
                addToken(TokenType::EQUAL);
                next();
                break;
            case ',':
                addToken(TokenType::COMMA);
                next();
                break;
            case ';':
                addToken(TokenType::EOL);
                next();
                break;
        }
        
        if (isdigit(chCurrent))
            tokenizeNumber();
        else if (isalpha(chCurrent))
            tokenizeWord();
    }
    
    return m_lstTokens;
}

void CLexer::tokenizeNumber()
{
    std::string strNumber;
    strNumber = peekCurrent();
    next();
    
    char ch;
    while (isdigit(ch = peekCurrent()))
    {
        strNumber += ch;
        next();
    }
    
    addToken(TokenType::NUMBER, strNumber);
}

void CLexer::tokenizeWord()
{
    std::string strWord;
    strWord = peekCurrent();
    next();
    
    char ch;
    while (isalnum(ch = peekCurrent()))
    {
        strWord += ch;
        next();
    }
    
    if (strWord == "print")
        addToken(TokenType::PRINT);
    
    else if (strWord == "def")
        addToken(TokenType::DEF);
    else
        addToken(TokenType::WORD, strWord);
}

void CLexer::clear()
{    
	for (CToken* pToken : m_lstTokens)
	{
		if (pToken != nullptr)
		{
			delete pToken;
			pToken = nullptr;
		}
	}
    m_lstTokens.clear();
}
