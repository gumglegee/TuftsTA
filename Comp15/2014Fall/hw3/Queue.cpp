/*
 * Queue.cpp
 *
 */

#include <iostream>
#include "Queue.h"

Queue::Queue() {
	//initialize all the private member variables
	capacity = Queue_INIT_CAPACITY;
	front = back = 0;
	size = 0;

	queue_array = new Student[capacity];
}

// destructor
Queue::~Queue() {
	delete[] queue_array;
}

// enqueue a char onto at the back of the queue
void Queue::enqueue(Student stu) {
	//expend the queue if it is full
	if (size == capacity)
		expand();

	queue_array[back] = stu;

	if (back == capacity - 1)
		back = 0;
	else
		back++;

	size++;

}

// dequeue a char from the front of the queue
Student Queue::dequeue() {
	Student fStu = queue_array[front];

	if (front == capacity - 1)
		front = 0;
	else
		front++;

	size--;

	return fStu;

}

// returns true if there are no elements in the
// queue, false if the queue has elements
bool Queue::is_empty() {
	if (size == 0)
		return true;
	else
		return false;

}

// expand the circular queue
void Queue::expand() {
	Student* newQueue = new Student[capacity * 2];

	for (int i = 0; i < capacity; i++) {
		newQueue[i] = queue_array[(front + i) % capacity];
	}

	delete[] queue_array;

	queue_array = newQueue;

	front = 0;
	back = capacity;
	capacity *= 2;

}
