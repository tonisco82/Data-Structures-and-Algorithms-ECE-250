//============================================================================
// Name        : openhttest.cpp
// Author      : TS
// Version     : 1.0
// Copyright   : 
// Description :
//============================================================================

#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
using namespace std;

int MAX = 0;

class DoubleHash {

	long long int *keys;	//to accommodate 10 digits
	string *names;
	int current_size;

public:

	DoubleHash() {
		keys = new long long int[MAX];	//to accommodate 10 digits
		names = new string[MAX];
		for (int i = 0; i < MAX; i++) {	//initialize all keys to -1 (phone number format set)
			keys[i] = -1;
			names[i] = "";
		}
		current_size = 0;
	}

	bool isFull() {	//checks if hash table is at capacity
		return (current_size == MAX);
	}

	bool found(long long int k) {
		for (int i = 0; i < MAX; i++) {
			if (keys[i] == k) {
				return true;
			}
		}
		return false;
	}

	int h1(long long int k) {	//primary hash function
		return (k % MAX);
	}

	int h2(long long int k) {	//secondary hash function
		int hash2 = (k / MAX) % MAX;
		if (hash2 % 2 == 0) {	//adding one if hash value is even
			return hash2 + 1;
		} else {
			return hash2;
		}
	}

	void n(int m) {	//defines size of new hash table
		MAX = m;
		keys = new long long int[MAX];	//to accommodate 10 digits
		names = new string[MAX];
		for (int i = 0; i < MAX; i++) {	//initialize all keys to -1 (phone number format set)
			keys[i] = -1;
			names[i] = "";
		}
		current_size = 0;
		cout << "success";
	}

	void i(long long int k, string caller) {
		if (isFull()) {
			cout << "failure";	//output message, later remove (FULL)
		} else if (found(k)) {
			cout << "failure";	//output message, later remove (FOUND)
		} else {
			int probe = h1(k);
			int offset = h2(k);
			while (keys[probe] != -1) {
				probe = (probe + offset) % MAX;	//following algorithm until space found
			}
			keys[probe] = k;
			names[probe] = caller;
			current_size++;
			cout << "success";
		}
	}

	void s(long long int k) {
		bool found = false;
		for (int i = 0; i < MAX && !found; i++) {	//step through array
			if (keys[i] == k) {
				cout << "found " << names[i] << " in " << i;	//found message
				found = true;
			}
		}
		if (!found) {
			cout << "not found";
		}
	}

	void d(long long int k) {
		bool found = false;
		for (int i = 0; i < MAX && !found; i++) {	//step through array
			if (keys[i] == k) {
				keys[i] = -1;	//set keys, names to initial values
				names[i] = "";
				cout << "success";
				found = true;
			}
		}
		if (!found) {
			cout << "failure";
		}
	}

	~DoubleHash() {
		delete[] keys;
		delete[] names;
	}

};

int main() {

	DoubleHash hash;	//initialization

	string command;
	while (cin >> command) {
		if (command == "n") {
			int m;
			cin >> m;

			hash.n(m);
		} else if (command == "i") {
			string k_caller;
			getline(cin, k_caller);	//read until end of line
			k_caller.pop_back();//to avoid going to next line (since getline includes \n)

			string delimiter = ";";
			string k_str = k_caller.substr(0, k_caller.find(delimiter));
			long long int k;	//to fit all phone numbers
			istringstream(k_str) >> k;	//convert to integer

			k_caller.erase(0, k_caller.find(delimiter) + delimiter.length()); //erase phone number
			string caller = k_caller;

			hash.i(k, caller);
		} else if (command == "s") {
			long long int k;
			cin >> k;

			hash.s(k);
		} else if (command == "d") {
			long long int k;
			cin >> k;

			hash.d(k);
		} else {
			cout << "ERROR";
		}
		cout << "\n";
	}
	return 0;
}
