/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */

#include "pqueue-linkedlist.h"
#include "error.h"

LinkedListPriorityQueue::LinkedListPriorityQueue() {
	head=NULL;
	listSize=0;
}

LinkedListPriorityQueue::~LinkedListPriorityQueue() {
	deallocate(head);
}

int LinkedListPriorityQueue::size() {
	return listSize;
}

bool LinkedListPriorityQueue::isEmpty() {
	return listSize==0;
}

void LinkedListPriorityQueue::enqueue(string value) {
	if(isEmpty()){
		head=new node;
		head->data=value;
		head->next=NULL;
	}else{
		node* newOne=new node;
		newOne->data=value;
		newOne->next=NULL;
		insertSorted(head,newOne);
	}
	listSize++;
}

string LinkedListPriorityQueue::peek() {
	if(isEmpty()){
		//error("Peek on empty PQueue");
		return "error";
	}	
	return head->data;
}

string LinkedListPriorityQueue::dequeueMin() {
	if(isEmpty()){
		//error("dequeue on empty PQueue");
		return "error";
	}	
	string min=head->data;
	
	if(listSize==1){
		delete head;
		head=NULL;
		listSize--;
	}else{
		node* newOne=head->next;
		delete head;
		head=newOne;
		listSize--;
	}
	return min;
}

void LinkedListPriorityQueue::insertSorted(node* &head ,node* newOne){
	
	node* cur;
	node* pre=NULL;

	for(cur=head;cur!=NULL;cur=cur->next){
		if(cur->data > newOne->data)
			break;
		pre=cur;
	}
	
	if(pre==NULL){
		newOne->next=head;
		head=newOne;
	}else{
		newOne->next = pre->next;
		pre->next=newOne;
	}

	// stack overflow!!!
	/*if(cur==NULL || cur->data > newOne->data){
		newOne->next=cur;
		cur=newOne;
	}else{
		insertSorted(cur->next,newOne);
	}*/
}

void LinkedListPriorityQueue::deallocate(node * n){
	if(n==NULL){
		return;
	}else{
		deallocate(n->next);
		delete n;
	}
}