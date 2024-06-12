#ifndef DFS_H
#define DFS_H

#include <unordered_set>

#include "Graph.h"

// Traverses graph by DFS, marking visited nodes along the way
void DFS(Graph graph, int node, std::unordered_set<int>& visited);

#endif