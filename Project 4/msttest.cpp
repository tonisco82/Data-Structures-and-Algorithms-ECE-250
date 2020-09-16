//============================================================================
// Name        : msttest.cpp
// Author      : TS
// Version     : 1.0
// Copyright   :
// Description :
//============================================================================

#include "disjoint.h"
#include "tree.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
	tree *object = 0; // initializes an instance of class tree to access all needed functions

	string command;
	while (cin >> command) {
		if (command == "n") {
			int m;
			cin >> m;

			//FAILURE HANDLING
			bool fail = false;
			try {
				object = new tree(m);
			} catch (illegal_argument ) {
				cout << "failure" << endl;
				fail = true;
			}
			if (!fail) {
				cout << "success" << endl;
			}

		} else if (command == "i") {
			string FULL;
			cin >> FULL;

			string delimiter = ";";
			int u = stoi(FULL);
			FULL.erase(0, FULL.find(delimiter) + delimiter.length());
			int v = stoi(FULL);
			FULL.erase(0, FULL.find(delimiter) + delimiter.length());
			double w = stod(FULL);

			//FAILURE HANDLING
			bool fail = false;
			try {
				object->i(u, v, w);
			} catch (illegal_argument ) {
				cout << "failure" << endl;
				fail = true;
			}
			if (!fail) {
				cout << "success" << endl;
			}

		} else if (command == "d") {
			string FULL;
			cin >> FULL;

			string delimiter = ";";
			int u = stoi(FULL);
			FULL.erase(0, FULL.find(delimiter) + delimiter.length());
			int v = stoi(FULL);

			//FAILURE HANDLING
			bool fail = false;
			try {
				if (!object->d(u, v)) {
					fail = true;
				}
			} catch (illegal_argument ) { //u or v is outside valid range, or < 0
				fail = true;
			}
			if (!fail) {
				cout << "success" << endl;
			} else {
				cout << "failure" << endl;
			}

		} else if (command == "degree") {
			int vertex;
			cin >> vertex;

			//FAILURE HANDLING
			bool fail = false;
			try {
				object->degree(vertex);
			} catch (illegal_argument ) {
				cout << "failure" << endl;
				fail = true;
			}
			if (!fail) {
				cout << "degree of " << vertex << " is "
						<< object->degree(vertex) << endl;
			}

		} else if (command == "edge_count") {
			cout << "edge count is " << object->edge_count() << endl;

		} else if (command == "clear") {
			object->clear();
			cout << "success" << endl;

		} else if (command == "mst") {
			pair<double, int> actual_value = object->mst();

			if (actual_value.second == -1) { // second = -1 means mst doesn't span all nodes
				cout << "not connected" << endl;
			} else {
				cout << "mst " << actual_value.first << endl; // first represents mst weight
			}

		} else {
			cout << "ERROR" << endl;
		}

	}

	return 0;
}
