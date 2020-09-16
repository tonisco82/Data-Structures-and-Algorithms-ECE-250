//============================================================================
// Name        : dequedriver.cpp
// Author      : TS
// Version     : 1.0
// Copyright   :
// Description :
//============================================================================

#include "dequedriver.h"
#include "deque_empty.h"

#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

void enqueue_front(int i){
	class node* NewNode = CreateNewNode(i);
	if(head == NULL){	//if list empty, this is first node
		head = NewNode;
		cout << "success";
		return;
	}
	head->prev = NewNode;
	NewNode->next = head;
	head = NewNode;
	cout << "success";
}

void enqueue_back(int i){
	class node* temp = head;
	class node* NewNode = CreateNewNode(i);
	if(head == NULL){	//if list empty, this is first node
		head = NewNode;
		cout << "success";
		return;
	}
	while(temp->next != NULL){	//traverses to last node
		temp = temp->next;
	}
	temp->next = NewNode;
	NewNode->prev = temp;
	cout << "success";
}

void dequeue_front(){
	class node* temp = head;
	if(temp == NULL){	//exception handling
		throw deque_empty();
	}
	else{
		if(head->next != NULL){	//makes sure this not last node
			head = head->next;
			head->prev = NULL;
			delete temp;
			cout << "success";
		}
		else{	//only one node left
			head = NULL;
			cout << "success";
		}
	}
}

void dequeue_back(){
	class node* temp = head;
	class node* tail;
	if(temp == NULL){	//exception handling
		throw deque_empty();
	}
	else{
		while(temp->next != NULL){	//traverses to last node
			temp = temp->next;
		}
		if(head->next != NULL){	//makes sure this not last node
			tail = temp->prev;
			tail->next = NULL;
			delete temp;
			cout << "success";
		}
		else{	//only one node left
			head = NULL;
			cout << "success";
		}
	}
}

void clear(){
	class node* current = head;	//to delete nodes
	class node* next;	//to traverse through all non-empty nodes
	if(head == NULL){	//if list empty, no work needed
		cout << "success";
	}
	else{
		while(current != NULL){	//traverses to last node
			next = current->next;
			current->next = NULL;
			delete current;
			current = next;
		}
		head->next = NULL;	//delete head, since it is left over
		head = NULL;
		delete head;
		cout << "success";
	}
}

string front(int i){
	string equal;
	class node* temp = head;
	if(head == NULL){	//exception handling
		throw deque_empty();
	}
	else if(i == temp->data){	//check equal
		equal = "success";
	}
	else{
		equal = "failure";
	}
	return equal;
}

string back(int i){
	string equal;
	class node* temp = head;
	if(head != NULL){
		while(temp->next != NULL){	//traverses to last node
			temp = temp->next;
		}
	}
	if(head == NULL){	//exception handling
		throw deque_empty();
	}
	else if(i == temp->data){
		equal = "success";
	}
	else{
		equal = "failure";
	}
	return equal;
}

void empty(){
	if(head == NULL){
		cout << "success";
	}
	else{
		cout << "failure";
	}
}

int size(){
	if(head == NULL){
		return 0;
	}
	else{
		int counter = 1;
		class node* temp = head;
		while(temp->next != NULL){	//traverses to last node
			temp = temp->next;
			counter++;
		}
		return counter;
	}
}

void print(){
	if(head != NULL){
		class node* backward;
		class node* forward = head;	//print forwards
		while(forward != NULL){
			cout << forward->data << " ";
			if(forward->next == NULL){
				backward = forward;	//once reached end, allows to reverse direction
			}
			forward = forward->next;
		}
		cout << "\n";

		while(backward != NULL){	//backward is now at tail, reverse through and delete
			cout << backward->data << " ";
			backward = backward->prev;
		}
	}
}


int main(/*int argc, char* argv[]*/) {

	string command;
	//cout << "\n";
	while(cin >> command){
		//cout << "\n";
		if(command == "enqueue_front"){
			int i;
			cin >> i;
			enqueue_front(i);
		}
		else if(command == "enqueue_back"){
			int i;
			cin >> i;
			enqueue_back(i);
		}
		else if(command == "dequeue_front"){
			try{	//exception handling
				dequeue_front();
			}
			catch(deque_empty& e){
				cout << e.msg();
			}
		}
		else if(command == "dequeue_back"){
			try{	//exception handling
				dequeue_back();
			}
			catch(deque_empty& e){
				cout << e.msg();
			}
		}
		else if(command == "clear"){
			clear();
		}
		else if(command == "front"){
			int i;
			cin >> i;
			try{	//exception handling
				cout << front(i);
			}
			catch(deque_empty& e){
				cout << e.msg();
			}
		}
		else if(command == "back"){
			int i;
			cin >> i;
			try{	//exception handling
				cout << back(i);
			}
			catch(deque_empty& e){
				cout << e.msg();
			}
		}
		else if(command == "empty"){
			empty();
		}
		else if(command == "size"){
			cout << "size is " << size();
		}
		else if(command == "print"){
			print();
		}
		else{
			cout << "ERROR";
		}
		cout << "\n";
	}
	//cout << "\n";

	return 0;
}

