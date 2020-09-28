/*
* Student: Audrey Nguyen
* Professor: Christopher Esposito
* Assignment #3: Dijkstra's Algorithm & Depth First Search
* Description: Cpp file for the GraphL class
* Represents a graph that is constructed through an adjacency list
*/

#include "graphl.h"

// GLOBAL CONSTANT
const int CHARLIMIT = 50;

// Constructor for the graph
GraphL::GraphL()
{
	size = 0;
	G = new GraphNode[MAXNODES];

	//Initializes all values in G
	for (int i = 1; i < MAXNODES; i++)
	{
		G[i].data = nullptr;
		G[i].edgeHead = nullptr;
		G[i].visited = false;
	}
}

// Destructor
GraphL::~GraphL()
{
	// Removes all values from G
	for (int i = 1; i < MAXNODES; i++)
	{
		// Deletes the data values
		delete G[i].data;
		G[i].data = nullptr;

		// Deletes the edges
		edgeRemover(i);
		G[i].edgeHead = nullptr;

		// Sets node as unvisited
		G[i].visited = false;
	}
	size = 0; 
	delete[] G; 
}

// Builds the graph with a file's input
bool GraphL::buildGraph(ifstream& input)
{
	// Reads in the number of nodes
	input >> size;
	string nodeName;
	getline(input, nodeName); // reads empty line
	
	// Reading in the names of the nodes
	for (int i = 1; i <= size; i++)
	{
		getline(input, nodeName);

		// If the string exceeds the character limit, stop  building the graph return false
		if (nodeName.length() > CHARLIMIT)
		{
			size = 0;
			return false;
		}

		NodeData* newNode = new NodeData(nodeName);
		G[i].data = newNode;
	}

	// Reading in the edges of the nodes
	while (!input.fail() && !input.eof())
	{
		int fromNode, toNode;
		input >> fromNode >> toNode;

		// breaks if the from node's value is 0
		if (fromNode == 0)
		{
			break;
		}

		// Creates the edge and inserts it into the graph
		EdgeNode* newEdge = new EdgeNode();
		newEdge->adjGraphNode = toNode;
		newEdge->nextEdge = G[fromNode].edgeHead;

		G[fromNode].edgeHead = newEdge;
	}
	return true;
}

// Displays all the nodes and edges 
void GraphL::displayGraph()
{
	string tinyGap = "  ";					// 2 spaces
	string smallGap = "    ";				// 4 spaces
	string midGap = "      ";				// 6 spaces
	string largeGap = "                ";	// 8 spaces
	
	cout << "Graph: " << endl;
	for (int i = 1; i <= size; i++)
	{
		cout << "Node " << i << largeGap << *(G[i].data) << endl << endl;
		EdgeNode* current = G[i].edgeHead;
		while (current != nullptr)
		{
			cout << smallGap << "edge " << i << " " << current->adjGraphNode << endl;
			current = current->nextEdge;
		}
	}
	cout << endl;
}

// Prints out the nodes in depth first order
void GraphL::depthFirstSearch()
{
	resetVisited();
	cout << "Depth-first ordering: ";
	depthFirstSearchHelper(1); // Seaches 1 first since it is the first node
	cout << endl << endl;
}

// Helper method for depthFirstSearch()
// Recursively prints out the nodes in depth first order
void GraphL::depthFirstSearchHelper(int root)
{
	// checks if root is valid
	if (root > 0 && root <= size)
	{
		// Ignores the node if it has been visited already
		if (G[root].visited)
		{
			return;
		}

		// Prints out the current node
		cout << root << " ";

		// Looks for adjacent nodes
		EdgeNode* current = G[root].edgeHead;
		G[root].visited = true;
		while (current != nullptr)
		{
			// If the adjacent node has not been visited, visit it
			if (!G[current->adjGraphNode].visited)
			{
				depthFirstSearchHelper(current->adjGraphNode);
				G[current->adjGraphNode].visited = true;
			}
			current = current->nextEdge;
		}
	}
}

// Helper method for depthFirstSearch()
// Sets all the nodes as unvisited
void GraphL::resetVisited()
{
	for (int i = 1; i <= size; i++)
	{
		G[i].visited = false;
	}
}

// Helper method for destructor
// Removes and deletes all the edge nodes a node has
void GraphL::edgeRemover(int nodeIndex)
{
	// Checks if root is valid
	if (nodeIndex > 0 && nodeIndex <= size)
	{
		EdgeNode* current = G[nodeIndex].edgeHead;
		while (current != nullptr)
		{
			EdgeNode* nextEdge = current->nextEdge;
			delete current;
			current = nextEdge;
		}
		current = nullptr;
	}
}
