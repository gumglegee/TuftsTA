#include "List_linked_list.h"

#include <iostream>
#include <cassert>

using namespace std;

// hint: in your constructor, you might want to set the head to NULL
List_linked_list::List_linked_list() {
	//constructor
	//set the head to NULL
	head = NULL;
}


List_linked_list::~List_linked_list()
{
	// delete list by looping through and deleting each node
	while (head != NULL) {
		Card_Node *current = head;
		head = head -> next;
		delete current;
	}
}

// copy constructor
List_linked_list::List_linked_list(const List_linked_list& source) {
	// explicit copy constructor necessary because of cards array
	if (source.head == NULL) return; // nothing to do

	head = new Card_Node;
	Card_Node *this_current = head;
	Card_Node *source_current = source.head;

	while (source_current != NULL) {
		// deep copy each Card_Node
		if (source_current->next != NULL) {
			Card_Node *new_node = new Card_Node();
			this_current->next = new_node;
			new_node->card = source_current->next->card;
		}
		else {
			this_current->next = NULL; // at tail
		}
		source_current = source_current->next;
		this_current = this_current->next;
	}
}

// operator= overload
List_linked_list List_linked_list::operator =(const List_linked_list&
		source) {
	// explicit operator= overload necessary because of cards array

	// check for self-assignment -- return without doing anything
	if (this == &source) {
		return *this;
	}
	// delete all current cards
	while (head != NULL) {
		Card_Node *next = head->next;
		delete head;
		head = next;
	}
	// copy over all cards from source list
	if (source.head == NULL) return *this; // nothing to do

	head = new Card_Node;
	Card_Node *this_current = head;
	Card_Node *source_current = source.head;

	while (source_current != NULL) {
		// deep copy each Card_Node
		this_current->card = source_current->card;
		if (source_current->next != NULL) {
			Card_Node *new_node = new Card_Node();
			this_current->next = new_node;
		}
		else {
			this_current->next = NULL; // at tail
		}
		source_current = source_current->next;
		this_current = this_current->next;
	}
	return *this;
}

void List_linked_list::print_list()
{
	Card_Node *current = head;
	while (current != NULL) {
		current->card.print_card();
		if (current->next != NULL) {
			cout << ",";
		}
		else {
			cout << "\n";
		}
		current = current->next;
	}
}

void List_linked_list::print_list_int()
{
	Card_Node *current = head;
	while (current != NULL) {
		current->card.print_card_int();
		if (current->next != NULL) {
			cout << ",";
		}
		else {
			cout << "\n";
		}
		current = current->next;
	}
}

int List_linked_list::cards_in_hand() {
	int numCards = 0;
	Card_Node *current = head;

	//loop through the linked list
	while (current != NULL) {
		//increase the number of cards
		numCards++;
		//go to the next node
		current = current->next;
	}

	return numCards;
}

void List_linked_list::make_empty() {
	//loop through the linked list
	while (head != NULL) {
		Card_Node *current = head;
		head = head -> next;
		delete current;
	}
}

// inserts a card at the head
// Should allow insert into an empty list
void List_linked_list::insert_at_head(Card c) {
	//create a new node
	Card_Node *newNode = new Card_Node();
	//initial the new node
	newNode->card = c;
	newNode->next = NULL;

	//update the next pointer
	if (head != NULL)
		newNode->next = head->next;

	//update the head
	head = newNode;
}

// inserts a card at the tail (final node)
// should allow insert into an empty list
void List_linked_list::insert_at_tail(Card c) {
	//create a new node
	Card_Node *newNode = new Card_Node();
	//initial the new node
	newNode->card = c;
	newNode->next = NULL;

	//if the list is empty, just update the head
	if (head == NULL) {
		head = newNode;
	}
	else {	//if the list is not empty, insert the node at the tail
		Card_Node *current = head;

		//loop through the linked list, and go to the tail
		while (current->next != NULL) {
			current = current->next;
		}

		//after the while loop, current will point to the tail
		//insert the node at the tail
		current->next = newNode;
	}
}

// inserts a card at an index such that
// all cards following the index will be moved farther
// down the list by one.
// The index can be one after the tail of the list
// I.e., you can insert at index 0 into an empty list,
// and you can insert at index 4 in a list with 4 nodes.
// In the first case, the node inserted would become the head
// In the second case, the node inserted would be inserted
// after the current tail.
void List_linked_list::insert_at_index(Card c, int index) {
	// TODO:

	//if insert at index 0, just insert the card at the head
	if (index == 0)
		insert_at_head(c);
	else {	//insert at index other than the head
		if (head != NULL) { //works only if the list is not empty
			Card_Node *newNode = new Card_Node();
			newNode->card = c;
			newNode->next = NULL;

			Card_Node *current = head;
			int currentIndex = 0;

			//loop through the linked list, and go to the node at index-1
			while ((current->next != NULL)
					&& (currentIndex < (index - 1))) {
				current = current->next;
				currentIndex++;
			}

			if (currentIndex == (index - 1)) {	// at index-1
				//link the newNode with the original index node
				newNode->next = current->next;

				//link the newNode with the index-1 node
				current->next = newNode;
			}
		}	//end if
	}	//end else
}

// replaces the card at index
// A card at index must already exist
void List_linked_list::replace_at_index(Card c, int index) {
	Card_Node *current = head;
	int currentIndex = 0;

	//loop through the linked list
	while ((current != NULL) && (currentIndex < index)) {
		current = current->next;
		currentIndex++;
	}

	if (current != NULL) {	//index does not exceed the length of the list
		//replace the card
		current->card = c;
	}
}

// returns the card at index.
// allowed to crash if index is not in the list
Card List_linked_list::card_at(int index) {
	//if the list is empty, return NULL
	if (head == NULL)
		return NULL;

	int currentIndex = 0;
	Card_Node *current = head;

	//loop through the linked list, and go to the index node
	while ((current != NULL) && (currentIndex < index)) {
		current = current->next;
		currentIndex++;
	}

	if (current == NULL)	//the card is not in the list
		return NULL;
	else {			//returns the card at index
		return current->card;
	}

}

bool List_linked_list::has_card(Card c) {
	Card_Node *current = head;

	//loop through the linked list
	while (current != NULL) {
		//for each node, use same_card() to compare with the Card c
		if (current->card.same_card(c)) {
			// returns true if the card is in the list
			return true;
		}

		current=current->next;
	}

	// returns false if the card is not in the list
	return false;
}

// removes the card from the list
// Returns true if the card was removed
// Returns false if the card was not in the list
bool List_linked_list::remove(Card c) {

	//returns false if the list is empty
	if (head == NULL)
		return false;


	Card_Node *current = head;

	//corner case: c is in the head
	if (head->card.same_card(c)) {
		//update head
		head = head->next;

		//delete the original head
		delete current;

		return true;
	}
	else {	//c is not in the head
		Card_Node *prev = NULL;
		//loop through the linked list, until find one node matches c
		while (current != NULL) {
			if (current->card.same_card(c)) { //matches c
				//update link
				prev->next = current->next;

				//delete the node
				delete current;

				return true;
			}

			//update the iterators
			prev = current;
			current = current->next;
		}

		//returns false is the card is not in the linked list
		return false;
	}	//end else

}

// Removes the card from the head, and assigns the head
// to head->next
// Returns the card that was removed
// Allowed to fail if list is empty
Card List_linked_list::remove_from_head() {
	//if the list is empty, return NULL
	if (head == NULL)
		return NULL;

	Card_Node *current = head;
	Card c = current->card;

	//update the head
	head = head->next;

	//delete the old head
	delete current;

	//return the card
	return c;
}

// Removes the card from the tail
// Returns the card that was removed
// Allowed to fail if the list is empty
Card List_linked_list::remove_from_tail() {
	//if the list is empty, return NULL
	if (head == NULL)
		return NULL;

	Card_Node *current = head;
	Card_Node *prev = NULL;

	//loop through the linked list, and go to the node ahead of tail
	//after the while loop:
	//prev points to the node ahead of tail,
	//	or NULL (if the list contains only one node)
	//current points to the tail
	while (current->next != NULL) {
		prev = current;
		current = current->next;
	}

	Card c = current->card;
	//there is a corner case:
	//the list only contains one node (update head as well)
	if (prev == NULL) {
		//if the list only contains one node
		//just delete the node and update the head
		delete current;
		head = NULL;
	}
	else {
		//update the next point of the prev node
		prev->next = NULL;

		//delete the tail
		delete current;
	}

	//return the card
	return c;
}

// Removes the card from index
// Returns the card that was removed
// Allowed to fail if index is beyond the end of the list
Card List_linked_list::remove_from_index(int index) {
	// TODO:

}
