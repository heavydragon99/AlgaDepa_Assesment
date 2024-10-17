#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <utility>
#include <vector>
#include <memory> // Include for smart pointers

class LevelData; // Forward declaration

class PathFinder {
public:
    enum Algorithms { Dijkstra, Breathfirst };

private:
    struct PathFinderNode {
        int mX;
        int mY;
        int mGCost;
        std::shared_ptr<PathFinderNode> mParent;

        PathFinderNode(int x, int y, int gCost, std::shared_ptr<PathFinderNode> parent)
            : mX(x), mY(y), mGCost(gCost), mParent(parent) {}
    };

    struct PathFinderNodeCompare {
        bool operator()(const std::shared_ptr<PathFinderNode>& lhs, const std::shared_ptr<PathFinderNode>& rhs) const {
            return lhs->mGCost > rhs->mGCost;
        }
    };

public:
    PathFinder();
    bool findPath(const LevelData* aLevelData, const std::pair<int, int>& aStart, const std::pair<int, int>& aEnd);
    void setAlgorithm(Algorithms aAlgorithm);

private:
    void reset();
    void dijkstra();
    void breathfirst();
    void setTileNodes();

    std::vector<std::pair<int, int>> mPath;
    std::vector<std::vector<std::pair<int, int>>> mAllPaths;
    std::vector<std::pair<int, int>> mVisited;
    Algorithms mAlgorithm;

    LevelData* mLevelData;
    std::pair<int, int> mStart;
    std::pair<int, int> mEnd;
    int mGCost;
    int mSteps;
};

#endif // PATHFINDER_H