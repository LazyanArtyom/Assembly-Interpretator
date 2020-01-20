#ifndef Functions_H
#define Functions_H

#include <list>
#include "Statements.h"
#include "Expressions.h"

class IFunction
{
public:
	virtual ~IFunction() = default;
};

class CFunctionUserDefined : public IFunction
{
private:
    std::list<std::string> m_lstArgNames;
    IExpression* m_pBody;
    
public:
    CFunctionUserDefined(std::list<std::string> lstArgNames, IExpression* pBody);
    
    int getArgsCount();
    std::string getArgumentName(int nIndex);
    
};

#endif // Functions_H 
