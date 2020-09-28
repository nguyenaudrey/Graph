/*
* Student: Audrey Nguyen
* Professor: Christopher Esposito
* Assignment #3: Dijkstra's Algorithm & Depth First Search
* Description: Header file for a representation of a Graph
* Represents a graph that is constructed through an adjacency list
* Focuses on depth first search
* This file was provided by the professor and modified by the student
*/

#ifndef GRAPHL_H
#define GRAPHL_H

#include <fstream>
#include <iostream>
#include "nodedata.h"

class GraphL {
public:
	GraphL();
	~GraphL();

	bool buildGraph(ifstream& input);
	void displayGraph();
	void depthFirstSearch();

private:
    // Global Constant
    static const int MAXNODES = 101; // Maximum nodes is actually 100, but 101 is the size of the array

    struct EdgeNode;      // forward reference for the compiler

    struct GraphNode {    // structs used for simplicity, use classes if desired
        EdgeNode* edgeHead; // head of the list of edges
        NodeData* data;     // data information about each node
        bool visited;
    };

    struct EdgeNode {
        int adjGraphNode;  // subscript of the adjacent graph node
        EdgeNode* nextEdge;
    };

    // Number of nodes
    int size; 

	// array of GraphNodes
    GraphNode* G;

    // Helper Methods
    void depthFirstSearchHelper(int root);
    void resetVisited();
    void edgeRemover(int nodeIndex);
};


#endif