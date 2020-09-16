//============================================================================
// Name        : dequedriver.h
// Author      : TS
// Version     : 1.0
// Copyright   :
// Description :
//============================================================================

#ifndef DEQUEDRIVER_H_
#define DEQUEDRIVER_H

#include <string>
using namespace std;

class node{
public:
	int data;
	node* next;
	node* prev;
};

class node* CreateNewNode(int i){
	class node* node = new (class node);	//creates in heap, so not lost when stack cleared
	node->data = i;
	node->next = NULL;
	node->prev = NULL;
	return node;
}

class node* head = NULL;	//global variable

void enqueue_front(int i);
void enqueue_back(int i);
void dequeue_front();
void dequeue_back();
void clear();
string front(int i);
string back(int i);
void empty();
int size();
void print();

#endif /* DEQUEDRIVER_H_ */
