#ifndef SymbolTable_H
#define SymbolTable_H

#include <unordered_map>
#include <string>
#include "Functions.h"

class CSymbolTable
{
public:   
    enum class EDataType { Function, Variable };
    
    struct SData
    {
        EDataType eType;
        IFunction* pFunction = nullptr;
    };
    
    CSymbolTable();
    ~CSymbolTable() = default;
    CSymbolTable(const CSymbolTable&) = delete;
    CSymbolTable& operator=(const CSymbolTable&) = delete;
    
public:
    static CSymbolTable& getInstance()
    {
        static CSymbolTable instance;
        return instance;
    }
    
    bool contains(std::string sKey, EDataType eType) const;
    SData get(std::string sKey, EDataType eType) const;
   
	void clear();
	std::string getSymbolTable();
	void set(std::string sKey, SData sData);

private:
    std::unordered_map<std::string, SData> m_mapSymbolTable;
};

#endif // SymbolTable_H
