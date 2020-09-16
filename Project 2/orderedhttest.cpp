//============================================================================
// Name        : orderedhttest.cpp
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

int MAX = 100;
int current_size = 0;

struct HashTableEntry {
	long long int k;	//allows for phone number
	string caller;
	HashTableEntry *n;
	HashTableEntry *p;
	HashTableEntry(long long int k, string caller) { //used to insert an entry
		this->k = k;
		this->caller = caller;
		this->n = NULL;
		this->p = NULL;
	}
};

class HashMapTable {

public:

	HashTableEntry **hash;
	HashMapTable() {
		hash = new HashTableEntry*[MAX];//initializes array that allows chains
		for (int i = 0; i < MAX; i++) {
			hash[i] = NULL;
		}
	}

	int h1(long long int k) {	//hash function
		return k % MAX;
	}

	bool isFull() {	//checks if hash table is at capacity
		return (current_size == MAX);
	}

	bool found(long long int k) {	//checks if key is already in hash table
		int hash_k = h1(k);
		bool flag = false;
		HashTableEntry* a = hash[hash_k];
		if (a != NULL) {
			while (a != NULL && !flag) {
				if (a->k == k) {
					return true;
				}
				a = a->n;	//advances through keys
			}
		}
		return false;
	}

	void n(int m) {
		MAX = m;	//sets the size of the hash table
		current_size = 0;
		cout << "success";
	}

	void i(long long int k, string caller) {
		if (isFull()) {
			cout << "failure";	//output message, later remove (FULL)
			return;
		} else if (found(k)) {
			cout << "failure";	//output message, later remove (FOUND)
			return;
		}
		int hash_k = h1(k);
		HashTableEntry* a = hash[hash_k];
		HashTableEntry* p = NULL;	//temporary to store a
		while (a != NULL) {
			p = a;	//stores the value of a
			a = a->n;	//moves on
		}
		if (a == NULL) {
			a = new HashTableEntry(k, caller);
			if (p == NULL) {
				hash[hash_k] = a;
			} else {
				p->n = a;
			}
		} else {
			a->k = k;
			a->caller = caller;
		}
		current_size++;	//increment to validate if hash table full later
		cout << "success";
	}

	void s(long long int k) {
		int hash_k = h1(k);
		bool flag = false;
		HashTableEntry* a = hash[hash_k];
		if (a != NULL) {
			while (a != NULL && !flag) {
				if (a->k == k) {
					flag = true;
				}
				if (flag) {
					cout << "found " << a->caller << " in " << hash_k;
				}
				a = a->n;	//advance to next in linked list
			}
		}
		if (!flag) {
			cout << "not found";
		}
	}

	void d(long long int k) {
		if (!found(k)) {	//if not found in hash table, cannot delete
			cout << "failure";
			return;
		}
		int hash_k = h1(k);
		HashTableEntry* a = hash[hash_k];
		HashTableEntry* p = NULL;	//temporary to store a
		if (a == NULL && a->k != k) {
			cout << "failure";
			return;
		}
		while (a->n != NULL) {
			p = a;	//stores the value of a
			a = a->n;	//moves on
		}
		if (p != NULL) {
			p->n = a->n;
		}
		a->k = -1;	//reset to initializing value
		a = NULL;//dereference pointer to allow future inserts to this positions
		delete a;
		cout << "success";
	}

	void p(int i) {	//where i represents the address/position to start printing from
		bool flag = false;
		HashTableEntry* a = hash[i];
		if (a != NULL) {
			while (a != NULL && !flag) {
				cout << a->k << " ";
				a = a->n;	//advance to next in linked list
			}
		}
		if (!flag) {	//the chain is empty
			return;
		}
	}

	~HashMapTable() {
		delete[] hash;
	}

};

int main() {

	HashMapTable hash;	//initialization

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
		} else if (command == "p") {
			int i;
			cin >> i;

			hash.p(i);
		} else {
			cout << "ERROR";
		}
		cout << "\n";
	}
	return 0;
}
