/*
* Student: Audrey Nguyen
* Professor: Christopher Esposito
* Assignment #3: Dijkstra's Algorithm & Depth First Search
* Description: Header file for a representation of a Graph
* Represents a graph that is constructed through an adjacency matrix
* Focuses on Dijkstra's shortest path algorithm
* This file was provided by the professor and modified by the student
*/

#ifndef GRAPHM_H
#define GRAPHM_H

#include <fstream>
#include <iostream>
#include "nodedata.h"

using namespace std;

class GraphM {
public:
	GraphM();

	bool buildGraph(ifstream& input);
	bool insertEdge(int fromNode, int toNode, int dist);
	bool removeEdge(int fromNode, int toNode);
	bool findShortestPath();
	const void display(int fromNode, int toNode);
	const void displayAll();
	
private:
	// Global Constant
	static const int MAXNODES = 101; // Maximum nodes is actually 100, but 101 is the size of the array

	struct TableType {
		bool visited;          // whether node has been visited
		int dist;              // shortest distance from source known so far
		int path;              // previous node in path of min dist
	};
	
	NodeData data[MAXNODES];              // data for graph nodes 
	int C[MAXNODES][MAXNODES];            // Cost array, the adjacency matrix
	int size;                             // number of nodes in the graph
	TableType T[MAXNODES][MAXNODES];      // stores visited, distance, path

	// Helper Methods
	void clearPaths();
	int findMin(int a, int b); // Helper method to find the minimum length
	const void printPaths(int fromNode, int toNode); //Helper method to print out the nodes between two nodes in a path
	const void printPathNames(int fromNode, int toNode); //Helper method to print out the names of nodes between two nodes in a path
};

#endif