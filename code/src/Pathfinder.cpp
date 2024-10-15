#include "PathFinder.h"
#include "levelData.h"

#include <iostream>
#include <queue>
#include <set>
#include <unordered_map>

PathFinder::PathFinder() : mAlgorithm(Algorithms::Dijkstra), mLevelData(nullptr), mGCost(0), mSteps(0) {}

bool PathFinder::findPath(const LevelData* aLevelData, const std::pair<int, int>& aStart, const std::pair<int, int>& aEnd) {
    mLevelData = const_cast<LevelData*>(aLevelData);
    mStart = aStart;
    mEnd = aEnd;

    reset();

    int cols = mLevelData->getCols();
    int start = aStart.second * cols + aStart.first;
    int end = aEnd.second * cols + aEnd.first;

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
    switch (mAlgorithm) {
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

void PathFinder::setAlgorithm(Algorithms aAlgorithm) {
    mAlgorithm = aAlgorithm;
}

void PathFinder::reset() {
    // Reset the state of the grid
    for (auto& node : mLevelData->getGrid()) {
        node.setIsPath(false);
        node.setIsVisited(false);
    }

    mPath.clear();
    mVisited.clear();
    mGCost = 0;
    mSteps = 0;
}

// Dijkstra's Algorithm
void PathFinder::dijkstra() {
    std::priority_queue<std::shared_ptr<PathFinderNode>, std::vector<std::shared_ptr<PathFinderNode>>, PathFinderNodeCompare> openList;
    std::set<std::pair<int, int>> closedList;

    int cols = mLevelData->getCols();

    // Initialize the start node
    auto startNode = std::make_shared<PathFinderNode>(mStart.first, mStart.second, 0, nullptr);
    openList.push(startNode);

    while (!openList.empty()) {
        auto currentNode = openList.top();
        openList.pop();

        std::pair<int, int> currentPos = {currentNode->mX, currentNode->mY};
        mVisited.push_back(currentPos);
        int currentId = currentNode->mY * cols + currentNode->mX;

        // Check if the end node is reached
        if (currentPos == mEnd) {
            mGCost = currentNode->mGCost;
            // Reconstruct path
            auto parentNode = currentNode;
            while (parentNode != nullptr) {
                mSteps++;
                mPath.push_back({parentNode->mX, parentNode->mY});
                parentNode = parentNode->mParent;
            }
            return;
        }

        closedList.insert(currentPos);

        // Explore neighbors
        for (auto& neighbor : mLevelData->getGrid()[currentId].getNeighbors()) {
            int neighborX = neighbor.get().getX();
            int neighborY = neighbor.get().getY();
            std::pair<int, int> neighborPos = {neighborX, neighborY};

            // Skip if the neighbor is already in the closed list
            if (closedList.find(neighborPos) != closedList.end()) {
                continue;
            }

            int tentativeG = currentNode->mGCost + neighbor.get().getWeight();
            auto neighborNode = std::make_shared<PathFinderNode>(neighborX, neighborY, tentativeG, currentNode);

            openList.push(neighborNode);
        }
    }
}

// Breadth-First Search (BFS)
void PathFinder::breathfirst() {
    std::queue<std::pair<int, int>> queue;
    std::unordered_map<int, std::pair<int, int>> previousNodes;
    std::unordered_map<int, bool> visitedNodes;

    int columns = mLevelData->getCols();
    int startIndex = mStart.second * columns + mStart.first;
    int endIndex = mEnd.second * columns + mEnd.first;

    queue.push(mStart);
    visitedNodes[startIndex] = true;

    while (!queue.empty()) {
        auto currentNode = queue.front();
        queue.pop();

        int currentIndex = currentNode.second * columns + currentNode.first;

        // Check if the end node is reached
        if (currentNode == mEnd) {
            // Reconstruct path
            while (currentNode != mStart) {
                mSteps++;
                mPath.push_back(currentNode);
                currentNode = previousNodes[currentIndex];
                currentIndex = currentNode.second * columns + currentNode.first;
            }
            mPath.push_back(mStart);
            return;
        }

        // Explore neighbors
        for (auto& neighbor : mLevelData->getGrid()[currentIndex].getNeighbors()) {
            int neighborIndex = neighbor.get().getY() * columns + neighbor.get().getX();
            if (!visitedNodes[neighborIndex]) {
                visitedNodes[neighborIndex] = true;
                previousNodes[neighborIndex] = currentNode;
                queue.push({neighbor.get().getX(), neighbor.get().getY()});
            }
        }
    }
}

void PathFinder::setTileNodes() {
    // Mark the path nodes
    for (auto& path : mPath) {
        int index = path.second * mLevelData->getCols() + path.first;
        mLevelData->getGrid()[index].setIsPath(true);
    }

    // Mark the visited nodes
    for (auto& visited : mVisited) {
        int index = visited.second * mLevelData->getCols() + visited.first;
        mLevelData->getGrid()[index].setIsVisited(true);
    }
}