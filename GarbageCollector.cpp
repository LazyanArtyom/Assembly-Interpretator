#include "GarbageCollector.h"
#include "Node.h"

CGarbageCollector& CGarbageCollector::getInstance()
{
	static CGarbageCollector instance;
	return instance;
}

void CGarbageCollector::addPtr(INode* pNode)
{
	m_aGarbage.push_back(pNode);
}

void CGarbageCollector::clearMemory()
{
	for (INode* pNode : m_aGarbage)
	{
		if (pNode != nullptr)
		{
			delete pNode;
			pNode = nullptr;
		}
	}
}