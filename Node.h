#ifndef Node_H
#define Node_H

#include "GarbageCollector.h"

class AVisitor;

class INode
{
public:
	virtual void accept(AVisitor *pVisitor) = 0;

	virtual ~INode() = default; 
};

#endif // Node_H