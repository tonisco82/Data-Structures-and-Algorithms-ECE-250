//============================================================================
// Name        : undirectedGraphtest.cpp
// Author      : TS
// Version     : 1.0
// Copyright   :
// Description :
//============================================================================

#include "undirectedGraph.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
	undirectedGraph *object = new undirectedGraph();
	string command;
	while (cin >> command) {
		if (command == "i") {
			string name;
			cin >> name;

			object->i(name);

		} else if (command == "setd") {
			string FULL;
			cin >> FULL;
			string delimiter = ";";
			string name1 = FULL.substr(0, FULL.find(delimiter));
			FULL.erase(0, FULL.find(delimiter) + delimiter.length());
			string name2 = FULL.substr(0, FULL.find(delimiter));
			FULL.erase(0, FULL.find(delimiter) + delimiter.length());
			double d = stod(FULL);

			object->setd(name1, name2, d);

		} else if (command == "s") {
			string name;
			cin >> name;

			if (object->s(name) != -1) {
				cout << "found " << name << endl;
			} else {
				cout << "not found" << endl;
			}

		} else if (command == "degree") {
			string name;
			cin >> name;

			object->degree(name);

		} else if (command == "graph_nodes") {

			cout << "number of nodes " << object->graph_nodes() << endl;

		} else if (command == "graph_edges") {

			cout << "number of edges " << object->graph_edges() << endl;

		} else if (command == "d") {
			string FULL;
			cin >> FULL;
			string delimiter = ";";
			string name1 = FULL.substr(0, FULL.find(delimiter));
			FULL.erase(0, FULL.find(delimiter) + delimiter.length());
			string name2 = FULL;

			double distance = object->d(name1, name2);

			if (distance != -1) {
				cout << "direct distance " << name1 << " to " << name2 << " "
						<< distance << endl;
			}

		} else if (command == "shortest_d") {
			string FULL;
			cin >> FULL;
			string delimiter = ";";
			string name1 = FULL.substr(0, FULL.find(delimiter));
			FULL.erase(0, FULL.find(delimiter) + delimiter.length());
			string name2 = FULL;

			double distance = object->shortest_d(name1, name2);

			if (distance != -1) {
				cout << "shortest distance " << name1 << " to " << name2 << " "
						<< distance << endl;
			}

		} else if (command == "print_path") {
			string FULL;
			cin >> FULL;
			string delimiter = ";";
			string name1 = FULL.substr(0, FULL.find(delimiter));
			FULL.erase(0, FULL.find(delimiter) + delimiter.length());
			string name2 = FULL;

			object->print_path(name1, name2);

		} else if (command == "clear") {

			object->clear();

		} else {
			cout << "ERROR" << endl;

			// Test Prints
			//
		}
	}

	return 0;
}
