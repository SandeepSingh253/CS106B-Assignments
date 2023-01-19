/*************************************************************
 * File: pqueue-heap.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 */
 
#include "pqueue-heap.h"
#include "error.h"
#include <iostream>

HeapPriorityQueue::HeapPriorityQueue() {
	arraySize=10;
	elemCount=0;
	arr=new string[arraySize];
	dummy="";
	arr[0]=dummy;
}

HeapPriorityQueue::~HeapPriorityQueue() {
	delete[] arr;
}

int HeapPriorityQueue::size() {	
	return elemCount;
}

bool HeapPriorityQueue::isEmpty() {	
	return elemCount==0;
}

void HeapPriorityQueue::enqueue(string value) {
	insert(value);
	elemCount++;
	bubbleUp(elemCount);
}

string HeapPriorityQueue::peek() {
	if(isEmpty())
		//error("peek on empty string");
		return "error";
	return arr[1];
}

string HeapPriorityQueue::dequeueMin() {
	if(isEmpty())
		//error("dequeue on empty string");
		return "error";

	string min=arr[1];
	swapStr(arr[1],arr[elemCount]);
	elemCount--;
	bubbleDown(1);
	return min;
}

bool HeapPriorityQueue::isArrFull(){
	return arraySize==elemCount+1;
}

void HeapPriorityQueue::doubleArray(){
	int newS=arraySize*2;
	string* newArray= new string[newS];

	for(int i=0;i<arraySize;i++){
		newArray[i]=arr[i];
	}

	delete[] arr;
	arr=newArray;
	arraySize=newS;
}

void HeapPriorityQueue::insert(string value){
	if(isArrFull())
		doubleArray();
	arr[elemCount+1]=value;
}

void HeapPriorityQueue::swapStr(string &a,string& b){
    string temp=a;
    a=b;
    b=temp;
}

void HeapPriorityQueue::bubbleDown(int index){
	if(!noChild(index)){
		int minChild;
		if(elemCount<(index*2)+1){
			minChild=index*2;
		}else{
			minChild=arr[index*2]<arr[(index*2)+1] ? index*2 : (index*2)+1;
		}
		if(arr[index]>arr[minChild]){
			swapStr(arr[index],arr[minChild]);
			bubbleDown(minChild);
		}
	}
}

void HeapPriorityQueue::bubbleUp(int index){
	if(index!=1){
		if(arr[index] < arr[index/2]){
			swapStr(arr[index],arr[index/2]);
			bubbleUp(index/2);
		}
	}
}

bool HeapPriorityQueue::noChild(int index){
	return index*2 > elemCount;
}