#ifndef TILEEDGE_H
#define TILEEDGE_H

class tileNode;

class tileEdge {
public:
    tileEdge(tileNode* aFrom, tileNode* aTo, float aWeight);

    tileNode* getOtherSide(tileNode* aNode) const;

    float getWeight() const;

private:
    tileNode* mFrom;
    tileNode* mTo;
    float mWeight;
};

#endif // TILEEDGE_H