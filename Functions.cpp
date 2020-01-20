#include "Functions.h"
#include <iostream>
#include <cmath>

CFunctionUserDefined::CFunctionUserDefined(std::list<std::string> lstArgNames, IExpression* pBody)
    : m_lstArgNames(lstArgNames), m_pBody(pBody) {}

int CFunctionUserDefined::getArgsCount()
{
    return (int)m_lstArgNames.size();
}

std::string CFunctionUserDefined::getArgumentName(int nIndex)
{
    return *(std::next(m_lstArgNames.begin(), nIndex));
}