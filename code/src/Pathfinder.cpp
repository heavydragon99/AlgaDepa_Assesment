#include "PathFinder.h"
#include "Configuration.h"
#include "LevelData.h"

#include <iostream>
#include <limits>
#include <queue>
#include <unordered_set>

// Define a hash function for std::pair<int, int>
struct pair_hash {
    /**
     * @brief Hash function for std::pair<int, int>.
     * @param pair The pair to hash.
     * @return The hash value.
     */
    template <class T1, class T2> std::size_t operator()(const std::pair<T1, T2>& pair) const {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};

/**
 * @brief Constructor for PathFinder.
 */
PathFinder::PathFinder() : mLevelData(nullptr), mGCost(0), mSteps(0) {}

/**
 * @brief Finds a path from start to end using the selected algorithm.
 * @param aLevelData Pointer to the level data.
 * @param aStart Start position.
 * @param aEnd End position.
 * @return True if a path is found, false otherwise.
 */
bool PathFinder::findPath(const LevelData* aLevelData, const std::pair<int, int>& aStart,
                          const std::pair<int, int>& aEnd) {
    mLevelData = const_cast<LevelData*>(aLevelData);
    mStart = aStart;
    mEnd = aEnd;

    reset();
    int start = calculateIndex(aStart.first, aStart.second);
    int end = calculateIndex(aEnd.first, aEnd.second);

    // Validate start and end positions
    if (start < 0 || start >= mLevelData->getGrid().size() || end < 0 || end >= mLevelData->getGrid().size()) {
        std::cerr << "Invalid start or end position" << std::endl;
        return false;
    }
    if (mLevelData->getGrid()[start].getTile().getColor() == 'W' ||
        mLevelData->getGrid()[end].getTile().getColor() == 'W') {
        std::cerr << "Start or end position is a white tile" << std::endl;
        return false;
    }

    // Execute the selected algorithm
    Algorithms Algorithm;
    if (Configuration::getInstance().getConfig("PathfindingMethodDijkstra")) {
        Algorithm = Algorithms::Dijkstra;
    } else {
        Algorithm = Algorithms::Breathfirst;
    }

    switch (Algorithm) {
    case Algorithms::Dijkstra:
        dijkstra();
        break;
    case Algorithms::Breathfirst:
        breathfirst();
        break;
    }

    setTileNodes();

    return true;
}

/**
 * @brief Resets the state of the grid.
 */
void PathFinder::reset() {
    // Reset the state of the grid
    for (auto& node : mLevelData->getGrid()) {
        node.setIsPath(false);
        node.setIsVisited(false);
    }

    mAllPaths.clear();
    mVisited.clear();
    mGCost = 0;
    mSteps = 0;
}

/**
 * @brief Implements Dijkstra's algorithm to find the shortest path.
 */
void PathFinder::dijkstra() {
    std::priority_queue<std::shared_ptr<PathFinderNode>, std::vector<std::shared_ptr<PathFinderNode>>,
                        PathFinderNodeCompare>
        openList;
    std::unordered_set<std::pair<int, int>, pair_hash> closedList; // unordered_set for faster lookups
    std::unordered_map<int, int> distanceMap;

    // Initialize the start node
    auto startNode = std::make_shared<PathFinderNode>(mStart.first, mStart.second, 0, nullptr);
    openList.push(startNode);
    // init distance map to max values
    for (const auto& node : mLevelData->getGrid()) {
        int id = calculateIndex(node.getX(), node.getY());
        distanceMap[id] = std::numeric_limits<int>::max();
    }
    distanceMap[calculateIndex(mStart.first, mStart.second)] = 0;

    bool shortestPathFound = false;
    int shortestPathCost = std::numeric_limits<int>::max(); // Track the shortest path cost

    while (!openList.empty()) {
        auto currentNode = openList.top();
        openList.pop();

        std::pair<int, int> currentPos = {currentNode->mX, currentNode->mY};
        mVisited[calculateIndex(currentPos.first, currentPos.second)] = true;
        int currentId = calculateIndex(currentNode->mX, currentNode->mY);

        // If the current node's cost exceeds the shortest path cost, stop exploring
        if (shortestPathFound && currentNode->mGCost > shortestPathCost) {
            break;
        }

        // Check if the end node is reached
        if (currentPos == mEnd) {
            if (!shortestPathFound) {
                shortestPathFound = true;
                shortestPathCost = currentNode->mGCost;
                mGCost = currentNode->mGCost;
            }
            // Reconstruct path
            std::vector<std::pair<int, int>> path;
            auto parentNode = currentNode;
            while (parentNode != nullptr) {
                mSteps++;
                path.push_back({parentNode->mX, parentNode->mY});
                parentNode = parentNode->mParent;
            }
            mAllPaths.push_back(path);
            continue;
        }

        closedList.insert(currentPos);

        // Explore neighbors
        for (auto& neighbor : mLevelData->getGrid()[currentId].getNeighbors()) {
            int neighborX = neighbor.get().getX();
            int neighborY = neighbor.get().getY();
            std::pair<int, int> neighborPos = {neighborX, neighborY};
            int neighborId = calculateIndex(neighborX, neighborY);

            // Skip if the neighbor is already in the closed list or is a white tile
            if (closedList.find(neighborPos) != closedList.end() || neighbor.get().getTile().getColor() == 'W') {
                continue;
            }

            int tentativeG = currentNode->mGCost + neighbor.get().getWeight();

            // Only proceed if the new tentative distance is shorter
            if (tentativeG < distanceMap[neighborId] || distanceMap.find(neighborId) == distanceMap.end()) {
                distanceMap[neighborId] = tentativeG;
                openList.push(std::make_shared<PathFinderNode>(neighborX, neighborY, tentativeG, currentNode));
            }
        }
    }

    if (!shortestPathFound) {
        std::cerr << "No path found" << std::endl;
    }
}

/**
 * @brief Implements Breadth-First Search (BFS) algorithm to find a path.
 */
void PathFinder::breathfirst() {
    std::queue<std::pair<int, int>> queue;
    std::unordered_map<int, std::pair<int, int>> previousNodes;

    int startIndex = calculateIndex(mStart.first, mStart.second);
    int endIndex = calculateIndex(mEnd.first, mEnd.second);

    queue.push(mStart);
    mVisited[startIndex] = true;

    while (!queue.empty()) {
        auto currentNode = queue.front();
        queue.pop();

        int currentIndex = calculateIndex(currentNode.first, currentNode.second);

        // Check if the end node is reached
        if (currentNode == mEnd) {
            std::vector<std::pair<int, int>> path;
            // Reconstruct path
            while (currentNode != mStart) {
                mSteps++;
                path.push_back(currentNode);
                currentNode = previousNodes[currentIndex];
                currentIndex = calculateIndex(currentNode.first, currentNode.second);
            }
            path.push_back(mStart);
            mAllPaths.push_back(path);
            return;
        }

        // Explore neighbors
        for (auto& neighbor : mLevelData->getGrid()[currentIndex].getNeighbors()) {
            int neighborIndex = calculateIndex(neighbor.get().getX(), neighbor.get().getY());
            // Skip if the neighbor is a white tile
            if (mVisited[neighborIndex] || neighbor.get().getTile().getColor() == 'W') {
                continue;
            } else {
                mVisited[neighborIndex] = true;
                previousNodes[neighborIndex] = currentNode;
                queue.push({neighbor.get().getX(), neighbor.get().getY()});
            }
        }
    }
}

/**
 * @brief Sets the nodes in the path and visited nodes in the grid.
 */
void PathFinder::setTileNodes() {
    // Mark the path nodes
    for (auto& path : mAllPaths[0]) {
        int index = path.second * mLevelData->getCols() + path.first;
        mLevelData->getGrid()[index].setIsPath(true);
    }

    // Mark the visited nodes
    for (auto& visited : mVisited) {
        int index = visited.first;
        mLevelData->getGrid()[index].setIsVisited(visited.second);
    }
}

/**
 * @brief Gets the total cost of the path.
 * @return The total cost.
 */
int PathFinder::getGCost() { return mGCost; }

/**
 * @brief Gets the number of steps in the path.
 * @return The number of steps.
 */
int PathFinder::getSteps() { return mSteps; }

/**
 * @brief Calculates the index of a node in the grid.
 * @param x X coordinate
 * @param y Y coordinate
 * @return The index in the grid.
 */
int PathFinder::calculateIndex(int x, int y) const { return y * mLevelData->getCols() + x; }
