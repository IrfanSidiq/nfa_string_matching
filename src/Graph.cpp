#include "../include/Graph.h"

Graph::Graph() : Graph(0) {}

Graph::Graph(int numOfNodes)
{
    this->numOfNodes = numOfNodes;
    this->adjacencyList.resize(numOfNodes, std::vector<int>());
}

void Graph::addEdge(int node, int destNode)
{
    adjacencyList[node].push_back(destNode);
}

std::vector<int>* Graph::getAdjacentNodes(int node)
{
    return &adjacencyList[node];
}

int Graph::getNumOfNodes()
{
    return numOfNodes;
}