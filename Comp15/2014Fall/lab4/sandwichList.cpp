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

}

//add an element, make sure it is not full, if it is call expand funciton
void SandwichList::enqueue(const Order& sw)
{

// TODO: Students write code here
	
}

//Double the queue size, copy the values, and reset back and front
void SandwichList::expandList()
{

// TODO: Students write code here

}

void SandwichList::printOrder(Order s)
{
	cout << s.sandwich << " " << s.customerName << " " << s.orderNbr << " " << s.fries;
	cout << endl;
}



