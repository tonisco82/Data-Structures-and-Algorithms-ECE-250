
//============================================================================
// Name        : qttest.cpp
// Author      : TS
// Version     : 1.0
// Copyright   :
// Description :
//============================================================================

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

// The objects that we want stored in the quadtree
struct Node {
	string Name;
	double x;
	double y;
	int p;
	int r;
	int s;
	Node(string _Name, double _x, double _y, int _p, int _r, int _s) {
		Name = _Name;
		x = _x;
		y = _y;
		p = _p;
		r = _r;
		s = _s;
	}
};

// The main quadtree class
class Quad {
public:
	// Contains details of node
	Node *n;
	// Children of this tree
	Quad *NW;
	Quad *NE;
	Quad *SW;
	Quad *SE;
	Quad(Node* _n) {	// Constructor
		n = _n;
		NW = nullptr;
		NE = nullptr;
		SW = nullptr;
		SE = nullptr;
	}
	bool i(Node* _n, Quad* quad);
	Quad* s(double _x, double _y, Quad* quad);	// Changed to return Quad*
	long q_max(string _d, string _attr, Quad* quad);
	long q_min(string _d, string _attr, Quad* quad);
	long q_total(string _d, string _attr, Quad* quad);
	void print();
	void clear();
	int size();
	~Quad();
};

bool Quad::i(Node* _n, Quad* quad) {
	if(s(_n->x, _n->y, quad)){	// Indicates the node was found in the tree
		return false;	// ROOT is still assigned this failure (new) node
	}
	else{
                // Insert NW
                if (_n->x < n->x && _n->y >= n->y) {	// Comparing the insertion node to existing nodes
			if (NW != nullptr) {
                                NW->i(_n, quad);
                        }
			else{
				NW = quad;
				return true;
			}
                }
                // Insert NE
		else if (_n->x >= n->x && _n->y > n->y) {
                	if (NE != nullptr) {
        	                NE->i(_n, quad);
      	                }
                        else{
				NE = quad;
				return true;
                        }
                }
                // Insert SW
       	        else if (_n->x <= n->x && _n->y < n->y) {
                        if (SW != nullptr) {
                                SW->i(_n, quad);
                        }
                        else{
				SW = quad;
				return true;
                        }
                }
                // Insert SE
                else if (_n->x > n->x && _n->y <= n->y) {
                        if (SE != nullptr) {
                                SE->i(_n, quad);
                        }
                        else{
				SE = quad;
				return true;
                        }
                }
//	return false;
	}
}

Quad* Quad::s(double _x, double _y, Quad* quad) {	// Where quad starts off at the root

	Quad* found_name = nullptr;

	// CHECK: empty (sub)tree (current node is leaf)
	if (!NW && !NE && !SW && !SE) {
		if (_x == n->x && _y == n->y) {
			found_name = quad;	// Since leaf, this is the last one to search
		}
	}
	else{
		// Recursion
		if (_x == n->x && _y == n->y) {
			found_name = quad;
		} else {
			// Move NW
			if (_x < n->x && _y >= n->y) {
				if (NW && quad) {	// If equals nullptr, keep looking through quadtree
					quad = quad->NW;	// Advance to next node
					return NW->s(_x, _y, quad);
				}
			}
			// Move NE
			else if (_x >= n->x && _y > n->y) {
				if (NE && quad) {
					quad = quad->NE;
					return NE->s(_x, _y, quad);
				}
			}
			// Move SW
			else if (_x <= n->x && _y < n->y) {
				if (SW && quad) {
					quad = quad->SW;
					return SW->s(_x, _y, quad);
				}
			}
			// Move SE
			else if (_x > n->x && _y <= n->y) {
				if (SE && quad) {
					quad = quad->SE;
					return SE->s(_x, _y, quad);
				}
			}
		}
	}
	return found_name;
}

long Quad::q_max(string _d, string _attr, Quad* temp) {
	long maximum;

	if(_d == "NW"){ // Adjust for direction
		temp = NW;
	}
	else if(_d == "NE"){
		temp = NE;
	}
	else if(_d == "SW"){
		temp = SW;
	}
	else if(_d == "SE"){
		temp = SE;
	}
	if(!temp){	// FAILURE CASE: direction is empty
		return -1;
	}

        if(_attr == "p"){
		maximum = temp->n->p;
	}
	else if(_attr == "r"){
		maximum = temp->n->r;
	}
	else if(_attr == "s"){
		maximum = temp->n->s;
	}

	maximum = max(temp->q_max("NW", _attr, temp), max(temp->q_max("NE", _attr, temp), max(temp->q_max("SW",
		_attr, temp), max(temp->q_max("SE", _attr, temp), maximum))));

	return maximum;

}

long Quad::q_min(string _d, string _attr, Quad* temp) {
        long minimum;

	if(_d == "NW"){	// Adjust for direction
		temp = NW;
	}
        else if(_d == "NE"){ // Adjust for direction
		temp = NE;
        }
        else if(_d == "SW"){ // Adjust for direction
		temp = SW;
        }
        else if(_d == "SE"){ // Adjust for direction
		temp = SE;
        }
	if(!temp){ // FAILURE CASE: direction is empty
		return -1;
	}

	if(_attr == "p"){
		minimum = temp->n->p;
	}
        if(_attr == "r"){
		minimum = temp->n->r;
	}
        if(_attr == "s"){
		minimum = temp->n->s;
	}

	// Using ternary conditional operators to deal with nullptrs (temp->...)
        long NORTHWEST = (temp->NW) ? temp->q_min("NW", _attr, temp) : minimum;
	NORTHWEST  = (NORTHWEST  >= 0) ? NORTHWEST : minimum;

	long NORTHEAST = (temp->NE) ? temp->q_min("NE", _attr, temp) : minimum;
	NORTHEAST = (NORTHEAST >= 0) ? NORTHEAST : minimum;

        long SOUTHWEST = (temp->SW) ? temp->q_min("SW", _attr, temp) : minimum;
	SOUTHWEST = (SOUTHWEST >= 0) ? SOUTHWEST : minimum;

        long SOUTHEAST = (temp->SE) ? temp->q_min("SE", _attr, temp) : minimum;
	SOUTHEAST = (SOUTHEAST >= 0) ? SOUTHEAST : minimum;

	//Find the lowest of all the values generated recursively
	minimum = min(NORTHWEST, min(NORTHEAST, min(SOUTHWEST, min(SOUTHEAST, minimum))));

	return minimum;

}

long Quad::q_total(string _d, string _attr, Quad* temp) {
	long sum;

	if(_d == "NW"){	// Adjust for direction
		temp = NW;
	}
	else if(_d == "NE"){	// Adjust for direction
		temp = NE;
	}
	else if(_d == "SW"){	// Adjust for direction
		temp = SW;
	}
	else if(_d == "SE"){	// Adjust for direction
		temp = SE;
	}
	if(!temp){
		return -1;
	}

	if(_attr == "p"){
		sum = temp->n->p;
	}
	else if(_attr == "r"){
		sum = temp->n->r;
	}
	else if(_attr == "s"){
		sum = temp->n->s;
	}
	else{
		return -1;
	}

	long NORTHWEST = (temp->NW) ? temp->q_total("NW", _attr, temp):0;

	long NORTHEAST = (temp->NE) ? temp->q_total("NE", _attr, temp):0;

	long SOUTHWEST = (temp->SW) ? temp->q_total("SW", _attr, temp):0;

	long SOUTHEAST = (temp->SE) ? temp->q_total("SE", _attr, temp):0;

	sum += NORTHEAST + SOUTHEAST + SOUTHWEST + NORTHWEST;

	return sum;

}

void Quad::print() {
	// PRINT EACH DIRECTION RECURSIVELY ACCORDING TO IN-ORDER TRAVERSAL
	// THE ORDER IS: NE->NW->ROOT->SW->SE

	if(NE){
		NE->print();
	}

	if(NW){
		NW->print();
	}

	cout<<n->Name<<" ";

	if(SW){
		SW->print();
	}

	if(SE){
		SE->print();
	}
}

void Quad::clear() {
	// IF THE NODES ARE NOT EMPTY, WE MUST ALSO DELETE THEM

	if(NW){
		NW->clear();
		NW->~Quad();
		NW = nullptr;
	}
	if(NE){
		NE->clear();
		NE->~Quad();
		NE = nullptr;
	}
	if(SW){
		SW->clear();
		SW->~Quad();
		SW = nullptr;
	}
	if(SE){
		SE->clear();
		SE->~Quad();
		SE = nullptr;
	}
}

int Quad::size() {
	int NUM_NODES = 1;

	NUM_NODES += (NW == nullptr)? 0 : NW->size();
	NUM_NODES += (NE == nullptr)? 0 : NE->size();
	NUM_NODES += (SW == nullptr)? 0 : SW->size();
	NUM_NODES += (SE == nullptr)? 0 : SE->size();

	return NUM_NODES;
}

Quad::~Quad(){

}

;

// Root initialization (to check empty)
Quad* ROOT = nullptr;

int main() {
	string command;
	while (cin >> command) {
		if (command == "i") {
			string FULL;
			cin>>FULL;

			string delimiter = ";";
			string NAME = FULL.substr(0, FULL.find(delimiter));
			FULL.erase(0, FULL.find(delimiter) + delimiter.length());
			double X = std::stod(FULL);
			FULL.erase(0, FULL.find(delimiter) + delimiter.length());
			double Y = std::stod(FULL);
			FULL.erase(0, FULL.find(delimiter) + delimiter.length());
			int P = std::stoi(FULL);
			FULL.erase(0, FULL.find(delimiter) + delimiter.length());
			int R = std::stoi(FULL);
			FULL.erase(0, FULL.find(delimiter) + delimiter.length());
			int S = std::stoi(FULL);

			Node *temp = new Node(NAME, X, Y, P, R, S);	// To insert node into quadtree
			Quad *quad = new Quad(temp);
			Quad *_root = ROOT;

			if (ROOT) {	// Normal insertion process
				if(ROOT->i(temp, quad)){
					cout<<"success";
				}
				else{
					cout<<"failure";
				}
			} else {	// Indicates first node - set ROOT to node manually
				ROOT = quad;
				cout << "success";
			}
		}

		else if (command == "s") {
			if(!ROOT){	// FAILURE CASE: empty quadtree
				cout<<"not found";
				string overflow;	// Otherwise will overflow into next command
				cin>>overflow;
			}
			else{
				string FULL;
				cin>>FULL;

				string delimiter = ";";
				double X = std::stod(FULL);
				FULL.erase(0, FULL.find(delimiter) + delimiter.length());
				double Y = std::stod(FULL);

				Quad *quad = ROOT;

				if(ROOT->s(X, Y, quad)){	// Indicates node was found (since not nullptr)
					cout<<"found "<<ROOT->s(X, Y, quad)->n->Name;
				}
				else{
					cout<<"not found";
				}
			}
		}

		else if (command == "q_max") {
			string FULL;
			cin>>FULL;

			string delimiter = ";";
			double X = std::stod(FULL);
			FULL.erase(0, FULL.find(delimiter) + delimiter.length());
			double Y = std::stod(FULL);
			FULL.erase(0, FULL.find(delimiter) + delimiter.length());
			string D = FULL.substr(0, FULL.find(delimiter));
			FULL.erase(0, FULL.find(delimiter) + delimiter.length());
			string ATTR = FULL.substr(0, FULL.find(delimiter));

			Quad *quad = ROOT->s(X, Y, ROOT);	// Constructs off the found node in quadtree

			if(quad->q_max(D, ATTR, quad) == -1){
				cout<<"failure";
			}
			else{
				cout<<"max "<<quad->q_max(D, ATTR, quad);
			}
		}

		else if (command == "q_min") {
	                string FULL;
			cin>>FULL;

			string delimiter = ";";
			double X = std::stod(FULL);
			FULL.erase(0, FULL.find(delimiter) + delimiter.length());
			double Y = std::stod(FULL);
			FULL.erase(0,FULL.find(delimiter) + delimiter.length());
			string D = FULL.substr(0, FULL.find(delimiter));
			FULL.erase(0,FULL.find(delimiter) + delimiter.length());
			string ATTR = FULL.substr(0, FULL.find(delimiter));

                        Quad *quad = ROOT->s(X, Y, ROOT); // Constructs off the found node in quadtree

			if(quad->q_min(D, ATTR, quad) == -1){
				cout<<"failure";
			}
			else{
				cout<<"min "<<quad->q_min(D, ATTR, quad);
			}
		}

		else if (command == "q_total") {
                        if(!ROOT){	// FAILURE CASE: root node not initialized
				cout<<"failure";
			}
			else{
				string FULL;
				cin>>FULL;

				string delimiter = ";";
				double X = std::stod(FULL);
				FULL.erase(0, FULL.find(delimiter) + delimiter.length());
				double Y = std::stod(FULL);
				FULL.erase(0,FULL.find(delimiter) + delimiter.length());
				string D = FULL.substr(0, FULL.find(delimiter));
				FULL.erase(0,FULL.find(delimiter) + delimiter.length());
				string ATTR = FULL.substr(0, FULL.find(delimiter));

				Quad *quad = ROOT->s(X, Y, ROOT);

				if(quad){
					long total = quad->q_total(D, ATTR, quad);
					if(total >= 0){
						cout<<"total "<<total;
					}
					else{	// FAILURE CASE: direction is empty
						cout<<"failure";
					}
				}
				else{	// FAILURE CASE: node not found
					cout<<"failure";
				}
			}
		}

		else if (command == "print") {
			if(ROOT){
				ROOT->print();
			}
		}

		else if (command == "clear") {
			if(ROOT){
				ROOT->clear();

				// NEED TO PROPERLY DEREFERENCE AND DELETE MEMORY
                                ROOT->~Quad();	// Destructor class
				ROOT = nullptr;
			}
			cout<<"success";
		}

		else if (command == "size") {
			if(ROOT){
				cout<<"tree size "<<ROOT->size();
			}
			else {	// Tree size by default 0
				cout<<"tree size 0";
			}
		}
//
		else {
			cout << "INVALID COMMAND";
		}

		cout << "\n";
	}
	return 0;
}
