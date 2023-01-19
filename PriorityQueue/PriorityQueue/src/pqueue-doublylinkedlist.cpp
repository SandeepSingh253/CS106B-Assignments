/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-doublylinkedlist.h"
#include "error.h"
#include <iostream>

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
	listSize=0;
	list=NULL;
}

DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
	deallocate(list);
}

int DoublyLinkedListPriorityQueue::size() {
	return listSize;
}

bool DoublyLinkedListPriorityQueue::isEmpty() {
	return listSize==0;
}

void DoublyLinkedListPriorityQueue::enqueue(string value) {
	if(list==NULL){
		list=new node;
		list->data=value;
		list->prev=NULL;
		list->next=NULL;
	}else{
		node* newOne=new node;
		newOne->data=value;
		newOne->next=list;
		list->prev=newOne;
		newOne->prev=NULL;
		list=newOne;
	}
	listSize++;
}

string DoublyLinkedListPriorityQueue::peek() {
	if(isEmpty())
		//error("peek on empty PQueue");
		return "error";

	node* minNode=findMinNode();
	return minNode->data;
}

string DoublyLinkedListPriorityQueue::dequeueMin() {
	if(isEmpty())
		//error("dequeue on empty PQueue");
		return "error";
	node* minNode=findMinNode();
	string min=minNode->data;
	removeNode(minNode);
	return min;
}

void DoublyLinkedListPriorityQueue::deallocate(node* n){
	if(n!=NULL){
		deallocate(n->next);
		delete n;
	}
}

DoublyLinkedListPriorityQueue::node* DoublyLinkedListPriorityQueue::findMinNode(){
	node* minNode=list;
	for(node* cur=list; cur!=NULL; cur=cur->next){
		if(minNode->data > cur->data){
			minNode=cur;
		}
	}
	return minNode;
}

void DoublyLinkedListPriorityQueue::removeNode(node* n){
	if(n->prev==NULL){
		list=n->next;
		if(list!=NULL)
			list->prev=NULL;
		delete n;
	}else{
		node* preNode=n->prev;
		node* nextNode=n->next;

		preNode->next=nextNode;
		if(nextNode!=NULL)
			nextNode->prev=preNode;
		delete n;
	}
	listSize--;
}