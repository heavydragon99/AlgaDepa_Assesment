#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <memory>
#include <utility>
#include <vector>
#include <memory> 
#include <unordered_map>

class LevelData; 

/**
 * @class PathFinder
 * @brief Class to find paths in a level using different algorithms.
 */
class PathFinder {
public:
    /**
     * @enum Algorithms
     * @brief Enum to represent the available pathfinding algorithms.
     */
    enum Algorithms { Dijkstra, Breathfirst };

private:
    /**
     * @struct PathFinderNode
     * @brief Struct to represent a node in the pathfinding process.
     */
    struct PathFinderNode {
        int mX; ///< X coordinate of the node
        int mY; ///< Y coordinate of the node
        int mGCost; ///< Cost to reach this node
        std::shared_ptr<PathFinderNode> mParent; ///< Parent node

        /**
         * @brief Constructor for PathFinderNode.
         * @param x X coordinate
         * @param y Y coordinate
         * @param gCost Cost to reach this node
         * @param parent Parent node
         */
        PathFinderNode(int x, int y, int gCost, std::shared_ptr<PathFinderNode> parent)
            : mX(x), mY(y), mGCost(gCost), mParent(parent) {}
    };

    /**
     * @struct PathFinderNodeCompare
     * @brief Comparator for PathFinderNode to be used in priority queues.
     */
    struct PathFinderNodeCompare {
        /**
         * @brief Comparator function.
         * @param a First node
         * @param b Second node
         * @return True if the cost of node a is greater than the cost of node b.
         */
        bool operator()(const std::shared_ptr<PathFinderNode>& a, const std::shared_ptr<PathFinderNode>& b) const {
            return a->mGCost > b->mGCost;
        }
    };

public:
    PathFinder();
    bool findPath(const LevelData* aLevelData, const std::pair<int, int>& aStart, const std::pair<int, int>& aEnd);
    void setAlgorithm(Algorithms aAlgorithm);

    int getGCost();
    int getSteps();

private:
    void reset();
    void dijkstra();
    void breathfirst();
    void setTileNodes();
    int calculateIndex(int x, int y) const;

    std::vector<std::vector<std::pair<int, int>>> mAllPaths;
    std::unordered_map<int,bool> mVisited;

    LevelData* mLevelData;
    std::pair<int, int> mStart;
    std::pair<int, int> mEnd;
    int mGCost;
    int mSteps;
};

#endif // PATHFINDER_H