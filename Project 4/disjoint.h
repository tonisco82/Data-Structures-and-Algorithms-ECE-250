//============================================================================
// Name        : disjoint.h
// Author      : TS
// Version     : 1.0
// Copyright   :
// Description :
//============================================================================

#ifndef disjoint_H
#define disjoint_H

#include <limits>

using namespace std;

struct node;
struct node_info;

struct node { // represents each element of the linked list
	int content;
	node_info* to_info; // pointer to the info entry of the corresponding set
	node* next;

};

struct node_info { // keeps track of the information (size, pointers to head/tail) of each set
	node* head;
	node* tail;
	int size;
};

class disjoint {
private:
	node** nodes;
	node_info** sets;
	int set_counter;
	int initial_num_sets;
public:
	disjoint(int n);
	~disjoint();
	int find_set(int item) const;
	int num_sets() const;
	void union_sets(int index1, int index2);
};

// Disjoint constructor. Initializes array of nodes and sets.
disjoint::disjoint(int n) :
		nodes(new node*[n]), sets(new node_info*[n]), set_counter(n), initial_num_sets(
				n) {
	// initialize the sets
	for (int i = 0; i < initial_num_sets; i++) {
		nodes[i] = new node();
		sets[i] = new node_info();
		sets[i]->head = nodes[i];
		sets[i]->tail = nodes[i];
		sets[i]->size = 1;
		nodes[i]->to_info = sets[i];
		nodes[i]->next = nullptr;
		nodes[i]->content = i;
	}
}

// Disjoint destructor. Frees all the memory assigned in the constructor.
disjoint::~disjoint() {
	for (int i = 0; i < initial_num_sets; i++) {
		delete sets[i];
		delete nodes[i];
	}
	delete[] sets; // deallocate memory
	delete[] nodes;
}

// find_set function. Returns index of the first node inside the set that contains the node searching for.
int disjoint::find_set(int item) const {
	return nodes[item]->to_info->head->content;
}

// num_sets function. Returns the number of sets left.
int disjoint::num_sets() const {
	return set_counter;
}

// union_sets function. Combines two sets, by:
//	1. pointing all nodes in smaller set to larger
//	2. setting tail node's "next" to smaller set's "head"
//	3. setting larger set's "tail" to smaller set's "tail"
//	4. decrement set_counter
void disjoint::union_sets(int index1, int index2) {

	if (index1 == index2) {
		return;
	}

	node_info* si1 = nodes[index1]->to_info;
	node_info* si2 = nodes[index2]->to_info;
	int ni1 = si1->size >= si2->size ? index1 : index2; // index of larger set
	int ni2 = si1->size < si2->size ? index1 : index2; // index of smaller set

	// iterate through shorter list, change necessary pointers
	int new_size = nodes[ni1]->to_info->size + nodes[ni2]->to_info->size; // combine sizes
	node_info* smaller_set = nodes[ni2]->to_info;
	node_info* larger_set = nodes[ni1]->to_info;

	node* temp = nodes[ni2]->to_info->head; // used to traverse through, change info
	while (temp != nullptr) {
		temp->to_info = larger_set;
		temp = temp->next;
	}

	larger_set->size = new_size;
	larger_set->tail->next = smaller_set->head;
	larger_set->tail = smaller_set->tail;

	set_counter--; // since we combined two sets
}

#endif
