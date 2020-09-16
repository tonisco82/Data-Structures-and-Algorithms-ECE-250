//============================================================================
// Name        : tree.h
// Author      : TS
// Version     : 1.0
// Copyright   :
// Description :
//============================================================================

#ifndef tree_H
#define tree_H

#include "disjoint.h"
#include <iostream>
#include <limits>

using namespace std;

class illegal_argument { // used for failure cases
	// empty, failure printed in main
};

struct edge { // keeps track of weight and vertices linked to the edge
	double weight;
	int vertex1;
	int vertex2;
};

class tree {
private:
	static const double INF;
	double** graph;
	int num_nodes;
	int num_edges;
	int *degrees;
	tree(tree const &);
	tree &operator=(tree);
public:
	tree(int m);
	~tree();
	bool i(int u, int v, double w);
	bool d(int u, int v);
	int degree(int u) const;
	int edge_count() const;
	void clear();
	pair<double, int> mst() const;
};

const double tree::INF = numeric_limits<double>::infinity(); // used for initial values

// Tree constructor. Performs following actions:
//	1. creates graph with size n
//	2. sets variables to appropriate initial values
//	3. adds pointer array containing degree of each node
//	4. initializes all entries in graph to INF
tree::tree(int m) {
	if (m <= 0) {
		throw illegal_argument();
	}
	graph = new double*[m];
	degrees = new int[m];
	num_edges = 0;
	num_nodes = m;

	for (int i = 0; i < m; i++) {
		graph[i] = new double[m];
		degrees[i] = 0;
	}

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			graph[i][j] = INF;
		}
	}
}

// Tree destructor. Deletes all memory allocated required for program run.
tree::~tree() {
	for (int i = 0; i < num_nodes; i++) {
		delete[] graph[i];
	}
	delete[] degrees;
	delete[] graph;
}

// i function. Performs following actions:
//	1. check if parameters are in appropriate ranges, or if same node (return false)
//	2. check if edge already exists between nodes (update weight)
//	3. if no edge exists, insert weight, increment num_edges and degree of nodes
bool tree::i(int u, int v, double w) {
	if (u == v && u < num_nodes && v < num_nodes) {
		throw illegal_argument();
	}
	if (u < 0 || v < 0 || u >= num_nodes || v >= num_nodes || w < 0) {

		throw illegal_argument();
	}

	if (graph[u][v] == INF && graph[u][v] == INF) {
		graph[u][v] = w;
		graph[v][u] = w;
		num_edges++;
		degrees[u]++;
		degrees[v]++;
	} else {
		graph[u][v] = w;
		graph[v][u] = w;
	}

	return true;
}

// d function. Performs following actions:
//	1. check if parameters are in appropriate ranges, or if same node (throw argument)
//	2. check if edge exists between nodes (reset weight to INF, decrement num_edges, degree)
bool tree::d(int u, int v) {
	if (u < 0 || v < 0 || u >= num_nodes || v >= num_nodes) {
		throw illegal_argument();
	}
	if (u == v) {
		throw illegal_argument();
	}
	if (graph[u][v] != INF && graph[v][u] != INF) {
		graph[u][v] = INF;
		graph[v][u] = INF;
		num_edges--;
		degrees[u]--;
		degrees[v]--;
	} else {
		return false;
	}
	return true;
}

// degree function. Returns degree of node specified.
int tree::degree(int u) const {
	if (u < 0 || u >= num_nodes) {
		throw illegal_argument();
	} else {
		return degrees[u];
	}
}

// edge_count function. Returns number of edges connected in graph.
int tree::edge_count() const {
	return num_edges;
}

// clear function. Resets all weights back to INF, resets num_edges to 0.
void tree::clear() {
	num_edges = 0;
	for (int i = 0; i < num_nodes; i++) {
		for (int j = 0; j < num_nodes; j++) {
			graph[i][j] = INF;
			graph[j][i] = INF;
			degrees[i] = 0;
			degrees[j] = 0;
		}
	}
	return;
}

// mst function. Calculates mst of connected graph.
pair<double, int> tree::mst() const {
	disjoint sets = disjoint(num_nodes);
	int counter = 0;
	edge ** all_edges = new edge *[num_edges]; // stores all edges information in graph

	for (int i = 0; i < num_nodes; i++) {
		for (int j = 0; j < num_nodes; j++) {
			if (i > j) {
				continue;
			}
			if (graph[i][j] != INF) { // not still set at initial value
				all_edges[counter] = new edge();
				all_edges[counter]->weight = graph[i][j];
				all_edges[counter]->vertex1 = i;
				all_edges[counter]->vertex2 = j;
				counter++;
			}
		}
	}

	edge *temp;
	int i, j;
	for (i = 1; i < num_edges; i++) { // sort edges ascending to apply Kruskal's algorithm.
		temp = all_edges[i];
		j = i - 1;
		while (j >= 0 && all_edges[j]->weight > temp->weight) {
			all_edges[j + 1] = all_edges[j];
			j = j - 1;
		}
		all_edges[j + 1] = temp;
	}

	double totalWeight = 0;
	int edge_counter = 0;
	for (int i = 0; i < num_edges; i++) { // loops through edges by ascending weight
		if (sets.num_sets() == 1) { // indicates tree has completed, finished algorithm
			break;
		}
		if (sets.find_set(all_edges[i]->vertex1)
				!= sets.find_set(all_edges[i]->vertex2)) { // indicates not connected
			sets.union_sets(all_edges[i]->vertex1,
					all_edges[i]->vertex2); // union both sets together
			totalWeight += all_edges[i]->weight; // increment mst weight
			edge_counter++; // increment number of edges in mst
		}
	}

	for (int i = 0; i < num_edges; i++) { // frees memory required during algorithm run
		delete all_edges[i];
	}
	delete[] all_edges;

	if (edge_counter != num_nodes - 1) { // check if number of edges in the MST is invalid
		edge_counter = -1; //indicator that tree not connected
	}

	return pair<double, int>(totalWeight, edge_counter); // returns mst weight, number edges
}

#endif
