#include "SymbolTable.h"
#include <iostream>
#include "Exception.h"

CSymbolTable::CSymbolTable() {}

bool CSymbolTable::contains(std::string sKey, EDataType eType) const
{
    switch (eType)
    {
        case EDataType::Variable:
            return m_mapSymbolTable.find("V" + sKey) != m_mapSymbolTable.end();
       
        case EDataType::Function:
            return m_mapSymbolTable.find("F" + sKey) != m_mapSymbolTable.end();
       
        default:
			throw CException("Wrong data type.");
    }

	return false;
}

CSymbolTable::SData CSymbolTable::get(std::string sKey, EDataType eType) const
{
    switch (eType)
    {
        case EDataType::Variable:
        {
            if (!contains(sKey, EDataType::Variable))
                return SData();
            
            return m_mapSymbolTable.find("V" + sKey)->second;
        }
        case EDataType::Function:
        {
            if (!contains(sKey, EDataType::Function))
                return SData();
            
            return m_mapSymbolTable.find("F" + sKey)->second;
        }
        default:
            throw CException("Wrong data type.");
    }

	return SData();

}

void CSymbolTable::set(std::string sKey, SData sData)
{
    switch (sData.eType)
    {
        case EDataType::Variable:
        {
            m_mapSymbolTable.insert(std::make_pair<std::string, SData>(
                "V" + sKey,
                std::move(sData))
            );
            break;
        }
        case EDataType::Function:
        {
            m_mapSymbolTable.insert(std::make_pair<std::string, SData>(
                "F" + sKey,
                std::move(sData))
            );
            break;
        }
        default:
			throw CException("Wrong data type.");
    }
}

void CSymbolTable::clear()
{
	for (auto item : m_mapSymbolTable)
	{
		if (item.second.pFunction != nullptr)
		{
			delete item.second.pFunction;
			item.second.pFunction = nullptr;
		}
	}
	m_mapSymbolTable.clear();
}

std::string CSymbolTable::getSymbolTable()
{
	std::string sSymbolTable = ".symbolTable \n";
	for (auto const& item : m_mapSymbolTable)
		sSymbolTable += (item.first + "\n");

	clear();
	return sSymbolTable;
}
