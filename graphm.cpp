/*
* Student: Audrey Nguyen
* Professor: Christopher Esposito
* Assignment #3: Dijkstra's Algorithm & Depth First Search
* Description: Cpp file for the GraphM class
* Represents a graph that is constructed through an adjacency matrix
*/

#include "graphm.h"
#include <cstdint>
#include <limits>
#include <iomanip>
using namespace std;

// GLOBAL CONSTANT
const int MAXDIST = 9999; // can also be set to INT_MAX
const int CHARLIMIT = 50;

// Constructor for the graph
GraphM::GraphM()
{
	// Initializes values in the arrays
	for (int i = 1; i < MAXNODES; i++)
	{
		for (int j = 1; j < MAXNODES; j++)
		{
			C[i][j] = MAXDIST;
			T[i][j].visited = false;
			T[i][j].path = 0;
			T[i][j].dist = MAXDIST;
		}
	}

	// Sets the size
	size = 0;
}

// Builds the graph with a file's input
bool GraphM::buildGraph(ifstream& input)
{
	// Reads in the number of nodes
	input >> size;

	string nodeName;
	getline(input, nodeName); //// reads empty line

	// Reads in the names of the nodes
	for (int i = 1; i <= size; i++)
	{	
		getline(input, nodeName);

		// If the string exceeds the character limit, stop  building the graph return false
		if (nodeName.length() > CHARLIMIT)
		{
			size = 0;
			return false;
		}

		data[i] = NodeData(nodeName);
	}
	
	// Reads the paths between the nodes
	while (!input.fail() && !input.eof())
	{
		int fromNode, toNode, dist;
		input >> fromNode >> toNode >> dist;

		// Breaks if the from node's value is 0
		if (fromNode == 0)
		{
			break;
		}

		C[fromNode][toNode] = dist;
	}

	return true;
}

// Insert an edge between two nodes with a user defined distance. Returns true if successful
bool GraphM::insertEdge(int fromNode, int toNode, int dist)
{
	// Checks if the inputs are within the valid range
	if ((fromNode > 0 && fromNode <= size) && (toNode > 0 && toNode <= size) && (dist < MAXDIST))
	{
		// Return false if from and to nodes are the same node 
		// but user is attempting to input a distance other than 0 between them
		if (fromNode == toNode && dist != 0)
		{
			return false;
		}

		// Inserts the edge into the graph
		clearPaths();
		C[fromNode][toNode] = dist;
		findShortestPath();

		return true;
	}

	// Returns false if inputs are invalid
	return false;
}

// Removes the edge between two nodes. Returns true if successful. 
bool GraphM::removeEdge(int fromNode, int toNode)
{
	// Checks if the nodes are within the valid range
	if ((fromNode > 0 && fromNode <= size) && (toNode > 0 && toNode <= size))
	{
		clearPaths();
		C[fromNode][toNode] = MAXDIST;
		findShortestPath();
		return true;
	}

	// Returns false if inputs are invalid
	return false;
}

// Finds the shortest paths using Dijkstra's algorithm
bool GraphM::findShortestPath()
{
	// Finds shortest paths for each vertice
	for (int source = 1; source <= size; source++)
	{
		// Sets distance with current source node to itself to be 0
		T[source][source].visited = true;
		T[source][source].dist = 0;
		T[source][source].path = source;

		// Current node that the algorithm is checking for adjacent nodes
		int current = source;
		
		for (int i = 1; i <= size; i++) // Looks for the most promising vertex
		{
			int shortestIndex = MAXNODES - 1;
			int testIndex = -1; //Most promising index
			current = i;

			// Checks for adjacent nodes
			for (int adj = 1; adj <= size; adj++) // Find the adjacent nodes, adj represents v
			{
				// Checks if there is a path between the nodes, that the nodes are not identical, and that the edge is unvisited
				// If the most promising index is found, update testIndex to be the most promising index
				if (current != adj && !T[current][adj].visited)
				{
					if (testIndex == -1 || C[current][adj] < C[current][testIndex])
					{
						testIndex = adj;
					}
					
				}
			}

			// Checks if the most promising index is valid
			if (testIndex != -1)
			{
				// If the most promising index provides a shorter distance than the current shortest path, update it
				if (C[current][testIndex] < T[current][testIndex].dist) 
				{
					T[current][testIndex].dist = C[current][testIndex];
				}
				T[current][testIndex].visited = C[current][testIndex]; // Marks the path as visited

				// Checks for adjacent nodes
				for (int adj = 1; adj <= size; adj++) // Find adjacent nodes, adj represents w
				{
					// If an adjacent node has been found, update shortest paths
					if (C[testIndex][adj] != MAXDIST && testIndex != adj) 
					{
						// Updates the array to have the shortest path
						int min = findMin(T[source][adj].dist, T[source][testIndex].dist + C[testIndex][adj]);
						if (min == T[source][testIndex].dist + C[testIndex][adj])
						{
							T[source][adj].path = testIndex;
						}
						// Sets the distance
						T[source][adj].dist = min;
						
					}
				}
			}
		}
	}
	return true;
}

// Helper method for findShortest()
// Returns the smaller number out of two numners
int GraphM::findMin(int a, int b)
{
	if (a < b)
	{
		return a;
	}

	return b;
}

// Displays the shortest path between the nodes
const void GraphM::display(int fromNode, int toNode)
{
	string tinyGap = "  ";					// 2 spaces
	string smallGap = "    ";				// 4 spaces
	string midGap = "      ";				// 6 spaces
	string largeGap = "                ";	// 8 spaces
	// Prints header
	cout << smallGap << fromNode << midGap << toNode << midGap;
	
	// If there is no distance betweeb the paths
	if (T[fromNode][toNode].dist == MAXDIST)
	{
		cout << "----" << endl << endl;
	}

	else
	{
		cout << T[fromNode][toNode].dist << midGap << midGap;
		printPaths(fromNode, toNode);
		cout << toNode << endl;
		printPathNames(fromNode, toNode);
		cout << data[toNode] << endl;
	}
	cout << endl;
}

// Displays all the paths
const void GraphM::displayAll()
{
	string tinyGap = "  ";					// 2 spaces
	string smallGap = "    ";				// 4 spaces
	string midGap = "      ";				// 6 spaces
	string largeGap = "                ";	// 8 spaces
	// Prints header
	cout << "Description" << largeGap << "From Node"
		<< midGap << "To Node" << midGap
		<< "Dijkstra's" << midGap << "Path" << endl;

	// Prints out information for each node
	for (int fromNode = 1; fromNode <= size; fromNode++)
	{
		// Prints out nodes's name
		cout << data[fromNode] << endl << endl;

		for (int toNode = 1; toNode <= size; toNode++)
		{
			// Do not printpath info if both the from and to nodes are the same node
			if (fromNode == toNode)
			{
				continue;
			}

			else
			{
				cout << largeGap << largeGap << fromNode << midGap << midGap << toNode << midGap << midGap;

				// If the nodes have no path between them, print out ---- to represent that
				if (T[fromNode][toNode].dist == MAXDIST)
				{
					cout << "----" << endl;
				}

				// Prints out the path between the nodes
				else
				{
					cout << T[fromNode][toNode].dist << midGap << midGap;
					printPaths(fromNode, toNode);
					cout << toNode << endl;
				}
			}
		}
	}
	cout << endl;
}

// Helper method for displayAll()
// Recursively prints out the paths between two nodes
const void GraphM::printPaths(int fromNode, int toNode)
{
	// Base Case: reaches the fromNode
	// Prints out the fromNode
	if (T[fromNode][toNode].path == fromNode || T[fromNode][toNode].path == 0) //when no more paths to reach, print and return
	{
		cout << fromNode << " "; 
		return;
	}

	// Recursively calls to print out the other paths
	printPaths(fromNode, T[fromNode][toNode].path);

	// Prints out the path
	cout << T[fromNode][toNode].path << " ";
}

// Helper method for displayAll()
// Recursively prints out the path names between two nodes
const void GraphM::printPathNames(int fromNode, int toNode)
{
	// Base Case: reaches the fromNode
	// Prints out the fromNode's name
	if (T[fromNode][toNode].path == fromNode || T[fromNode][toNode].path == 0) //when no more paths to reach, print and return
	{
		cout << data[fromNode] << endl << endl; //" PATH: " << 
		return;
	}

	// Recursively calls to print out the other paths
	printPathNames(fromNode, T[fromNode][toNode].path);

	// Prints out the path
	cout << data[T[fromNode][toNode].path] << endl << endl; //" PATH: " 
}

// Removes all the shortest paths between the nodes. Does not remove edges
void GraphM::clearPaths()
{
	// Initializes values in the arrays
	for (int i = 1; i < MAXNODES; i++)
	{
		for (int j = 1; j < MAXNODES; j++)
		{
			T[i][j].visited = false;
			T[i][j].path = 0;
			T[i][j].dist = MAXDIST;
		}
	}
}
		