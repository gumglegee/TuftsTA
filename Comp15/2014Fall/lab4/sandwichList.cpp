/* sandwichList.cpp
 * Comp 15 
 * Spring 2014 
 * Lab 4
 */

#include "sandwichList.h"


SandwichList::SandwichList()
{
	capacity = INITIAL_SIZE;
	orders = new Order[INITIAL_SIZE];
	orderCount = 0;

	back = 0;
	front = 0;
}

bool SandwichList::isEmpty()
{
	if (size() == 0)
		return true;
	else
		return false;
}


int SandwichList::size()
{
        return orderCount;
        // you could use the following arithmetic (but be careful):
	//return (back - front + capacity) % capacity;
}

//function to remove Order from the front of the queue
Order SandwichList::dequeue()
{

// TODO: Students write code here
	Order fOrder = orders[front];

	if (front == capacity-1)
		front = 0;
	else
		front++;

	orderCount--;

	return fOrder;
}

//add an element, make sure it is not full, if it is call expand funciton
void SandwichList::enqueue(const Order& sw)
{

// TODO: Students write code here
	//expend the queue if it is full
	if (capacity == orderCount)
		expandList();

	orders[back] = sw;

	if (back == capacity-1)
		back = 0;
	else
		back++;
	
	orderCount++;
}

//Double the queue size, copy the values, and reset back and front
void SandwichList::expandList()
{

// TODO: Students write code here
	Order* newOrders = new Order[capacity * 2];

	for (int i=0; i < capacity; i++) {
		newOrders[i] = orders[(front+i)%capacity];
	}

	delete [] orders;

	orders = newOrders;

	front = 0;
	back = capacity;
	capacity *= 2;

}

void SandwichList::printOrder(Order s)
{
	cout << s.sandwich << " " << s.customerName << " " << s.orderNbr << " " << s.fries;
	cout << endl;
}



