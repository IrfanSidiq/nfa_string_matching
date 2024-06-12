#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

class Graph
{
    private:
        int numOfNodes;
        std::vector<std::vector<int>> adjacencyList;
    
    public:
        // Creates an empty graph with no nodes
        Graph();

        // Creates an empty graph with initial nodes
        Graph(int numOfNodes);

        // Adds a directed edge from node to destNode
        void addEdge(int node, int destNode);

        // Returns pointer to list of nodes adjacent to a given node
        std::vector<int>* getAdjacentNodes(int node);

        // Returns number of nodes in graph
        int getNumOfNodes();
};

#endif