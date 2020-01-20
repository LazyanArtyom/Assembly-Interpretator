#ifndef GarbageCollector_H
#define GarbageCollector_H

#include <vector>
//#include "Node.h"

class INode;

class CGarbageCollector
{
public:
	CGarbageCollector() = default;
	~CGarbageCollector() = default;
	
	CGarbageCollector(CGarbageCollector const&) = delete;
	CGarbageCollector& operator=(CGarbageCollector const&) = delete;

	static CGarbageCollector& getInstance();

	void addPtr(INode* pNode);
	void clearMemory();

private:
	std::vector<INode*> m_aGarbage;
};

#endif // GarbageCollector_H

