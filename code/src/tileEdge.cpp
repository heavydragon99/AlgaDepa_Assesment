#include "tileEdge.h"
#include "tileNode.h"


tileEdge::tileEdge(tileNode &aNodeA, tileNode &aNodeB)
    : mNodeA(aNodeA), mNodeB(aNodeB){}

tileNode *tileEdge::getOtherSide(tileNode &aNode) const
{
    if (&aNode == &mNodeA)
    {
        return &mNodeB;
    }
    if (&aNode == &mNodeB)
    {
        return &mNodeA;
    }
    return nullptr;
}