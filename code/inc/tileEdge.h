#ifndef TILEEDGE_H
#define TILEEDGE_H

class tileNode;

class tileEdge
{
public:
    tileEdge(tileNode &aNodeA, tileNode &aNodeB);

    tileNode& getOtherSide(tileNode &aNode) const;

    float getWeight() const;

private:
    tileNode &mNodeA;
    tileNode &mNodeB;
};

#endif // TILEEDGE_H