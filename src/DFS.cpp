#include "../include/DFS.h"

void DFS(Graph graph, int startNode, std::unordered_set<int>& visited)
{
    visited.insert(startNode);
    std::vector<int>* adjacentNodes = graph.getAdjacentNodes(startNode);

    for (int node : *adjacentNodes)
    {
        if (visited.find(node) == visited.end())
        {
            DFS(graph, node, visited);
        }
    }
}