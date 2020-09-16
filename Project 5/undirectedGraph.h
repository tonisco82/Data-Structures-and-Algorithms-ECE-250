//============================================================================
// Name        : undirectedGraph.h
// Author      : TS
// Version     : 1.0
// Copyright   :
// Description :
//============================================================================

#ifndef undirectedGraph_H
#define undirectedGraph_H

#include <iostream>
#include <string>
#define INFINITY 9999
#define max 100

using namespace std;

class undirectedGraph {
private:
	int nodeCount;
	int edgeCount;
	double **adjacencyMatrix;
	int *degrees;
	string *cities;
public:
	undirectedGraph();
	~undirectedGraph();
	void i(string name);
	void setd(string name1, string name2, double d);
	int s(string name); // Return the node # for other operations
	void degree(string name);
	int graph_nodes();
	int graph_edges();
	double d(string name1, string name2);
	double shortest_d(string name1, string name2);
	void print_path(string name1, string name2);
	void clear();
};

undirectedGraph::undirectedGraph() {
	nodeCount = 0; // Initial number of nodes is 0
	edgeCount = 0; // Initial number of edges is 0
	adjacencyMatrix = new double*[max];
	degrees = new int[max];
	cities = new string[max];
	for (int i = 0; i < max; i++) {
		adjacencyMatrix[i] = new double[max];
		degrees[i] = 0; // Initial value of all degrees in list
		cities[i] = ""; // Initial value of all cities in list
		for (int j = 0; j < max; j++) {
			adjacencyMatrix[i][j] = -1; // Initial value, since invalid (d > 0)
		}
	}
}

undirectedGraph::~undirectedGraph() {
	for (int i = 0; i < nodeCount; i++) {
		delete[] adjacencyMatrix[i];
	}
	delete[] adjacencyMatrix;
	delete[] degrees;
	delete[] cities;
}

void undirectedGraph::i(string name) {
	if (s(name) != -1) { // Indicates the city already exists
		cout << "failure" << endl;
	} else {
		cities[nodeCount] = name;
		nodeCount++;
		cout << "success" << endl;
	}
}

void undirectedGraph::setd(string name1, string name2, double d) {
	int index1 = s(name1);
	int index2 = s(name2);
	if (index1 == -1 || index2 == -1 || d <= 0 || name1 == name2) {
		cout << "failure" << endl;
	} else {
		if (adjacencyMatrix[index1][index2] == -1
				&& adjacencyMatrix[index1][index2] == -1) { // Indicates new edge
			adjacencyMatrix[index1][index2] = d;
			adjacencyMatrix[index2][index1] = d;
			edgeCount++;
			degrees[index1]++;
			degrees[index2]++;
			cout << "success" << endl;
		} else { // Indicates updated edge
			adjacencyMatrix[index1][index2] = d;
			adjacencyMatrix[index2][index1] = d;
			cout << "success" << endl;
		}
	}
}

int undirectedGraph::s(string name) {
	for (int i = 0; i < max; i++) {
		if (cities[i] == name) {
			return i; // Returns the node # for the found node (0 to 99)
		}
	}
	return -1; // Indicates that city was not found (-1 is never a valid node)
}

void undirectedGraph::degree(string name) {
	int index = s(name);
	if (index == -1) { // Indicates that city was not found
		cout << "failure" << endl;
	} else {
		cout << "degree of " << name << " " << degrees[index] << endl;
	}
}

int undirectedGraph::graph_nodes() {
	return nodeCount;
}

int undirectedGraph::graph_edges() {
	return edgeCount;
}

double undirectedGraph::d(string name1, string name2) {
	int index1 = s(name1);
	int index2 = s(name2);
	if (index1 == -1 || index2 == -1 || adjacencyMatrix[index1][index2] == -1
			|| name1 == name2) {
		cout << "failure" << endl;
		return -1; // Indicates failure case for main function detection
	}
	return adjacencyMatrix[index1][index2];
}

double undirectedGraph::shortest_d(string name1, string name2) {
	int index1 = s(name1);
	int index2 = s(name2);
	if (index1 == -1 || index2 == -1 || name1 == name2) {
		cout << "failure" << endl;
		return -1; // Indicates failure case for main function detection
	} else if (adjacencyMatrix[index1][index2] != -1) { // Direct connection
		return adjacencyMatrix[index1][index2];
	} else {
		double cost[max][max], distances[max], mindistance;
		int visited[max], nextnode, count, numCities;
		for (int i = 0; i < nodeCount; i++) {
			for (int j = 0; j < nodeCount; j++) {
				if (adjacencyMatrix[i][j] == -1) { // Indicates nodes not directly connected
					cost[i][j] = INFINITY; // So this path is not taken
				} else {
					cost[i][j] = adjacencyMatrix[i][j];
				}
			}
		}
		for (int i = 0; i < nodeCount; i++) {
			distances[i] = cost[index1][i];
			visited[i] = 0;
		}
		distances[index1] = 0; // For the initial node only
		visited[index1] = 1;
		count = 1;
		numCities = 1;
		while (count < nodeCount - 1) {
			mindistance = INFINITY;
			for (int i = 0; i < nodeCount; i++) {
				if (distances[i] < mindistance && !visited[i]) {
					mindistance = distances[i];
					nextnode = i;
				}
			}
			visited[nextnode] = 1;
			for (int i = 0; i < nodeCount; i++) {
				if (!visited[i]) {
					if (mindistance + cost[nextnode][i] < distances[i]) {
						distances[i] = mindistance + cost[nextnode][i];
						numCities++;
					}
				}
			}
			count++;
		}
		if (distances[index2] == INFINITY) { // Indicates there is no possible path between indexes
			cout << "failure" << endl;
			return -1;
		}
		return distances[index2]; // Returns the minimum distance to index2 (from index1)
	}
}

void undirectedGraph::print_path(string name1, string name2) {
	int index1 = s(name1);
	int index2 = s(name2);
	if (index1 == -1 || index2 == -1 || name1 == name2) {
		cout << "failure" << endl;
	} else if (adjacencyMatrix[index1][index2] != -1) { // Direct connection
		cout << cities[index1] << " " << cities[index2] << endl;
	} else {
		double cost[max][max], distances[max], cities_reverse[max], mindistance;
		int visited[max], nextnode, count, numCities;
		for (int i = 0; i < nodeCount; i++) {
			for (int j = 0; j < nodeCount; j++) {
				if (adjacencyMatrix[i][j] == -1) { // Indicates nodes not directly connected
					cost[i][j] = INFINITY; // So this path is not taken
				} else {
					cost[i][j] = adjacencyMatrix[i][j];
				}
			}
		}
		for (int i = 0; i < nodeCount; i++) {
			distances[i] = cost[index1][i];
			cities_reverse[i] = index1;
			visited[i] = 0;
		}
		distances[index1] = 0; // For the initial node only
		visited[index1] = 1;
		count = 1;
		while (count < nodeCount - 1) {
			mindistance = INFINITY;
			for (int i = 0; i < nodeCount; i++) {
				if (distances[i] < mindistance && !visited[i]) {
					mindistance = distances[i];
					nextnode = i;
				}
			}
			visited[nextnode] = 1;
			for (int i = 0; i < nodeCount; i++) {
				if (!visited[i]) {
					if (mindistance + cost[nextnode][i] < distances[i]) {
						distances[i] = mindistance + cost[nextnode][i];
						cities_reverse[i] = nextnode;
					}
				}
			}
			count++;
		}
		if (distances[index2] == INFINITY) { // Indicates there is no possible path between indexes
			cout << "failure" << endl;
		} else {
			int j = index2;
			numCities = 1; // Includes the last city above, represented by index2
			do {
				j = cities_reverse[j];
				numCities++; // Used to find the correct number of cities for our array (in order)
			} while (j != index1);
			int cityOrder[numCities];
			int a = numCities - 1; // The destination city
			int k = index2;
			cityOrder[numCities] = k;
			do {
				k = cities_reverse[k];
				cityOrder[a] = k;
				a--;
			} while (k != index1 && a >= 0);
			cityOrder[0] = index1; // For the last city in the list, our destination
			for (int i = 1; i < numCities; i++) { // Prints out cities in order
				cout << cities[cityOrder[i]] << " ";
			}
			cout << cities[cityOrder[numCities]] << endl; // Prints last city without space at end
		}
	}
}

void undirectedGraph::clear() {
	nodeCount = 0;
	edgeCount = 0;
	for (int i = 0; i < max; i++) {
		degrees[i] = 0;
		cities[i] = "";
		for (int j = 0; j < max; j++) {
			adjacencyMatrix[i][j] = -1;
			adjacencyMatrix[j][i] = -1;
		}
	}
	cout << "success" << endl;
}

#endif
