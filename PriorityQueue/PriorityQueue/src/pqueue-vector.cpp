/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */
 
#include "pqueue-vector.h"
#include "error.h"
#include <iostream>

VectorPriorityQueue::VectorPriorityQueue() {
}

VectorPriorityQueue::~VectorPriorityQueue() {
}

int VectorPriorityQueue::size() {	
	return vec.size();
}

bool VectorPriorityQueue::isEmpty() {
	return vec.isEmpty();
}

void VectorPriorityQueue::enqueue(string value) {
	vec.add(value);
}

string VectorPriorityQueue::peek() {
	if(vec.isEmpty()){
		//error("Peek on Empty PQueue");
		return "error";
	}
	int minIndex=findMinIndex();
	string min=vec[minIndex];

	return min;
}

string VectorPriorityQueue::dequeueMin() {
	if(vec.isEmpty()){
		//error("Dequeue on Empty PQueue");
		return "error";
	}
	int minIndex=findMinIndex();
	string min=vec[minIndex];

	vec.removeAt(minIndex);
	return min;
}

int VectorPriorityQueue::findMinIndex(){
	int minIndex=0;
	for(int i=0;i<vec.size();i++){
		if(vec[minIndex]>vec[i]){
			minIndex=i;
		}
	}
	return minIndex;
}