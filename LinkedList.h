#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <string>
#include <iostream>
#include <sstream>
#include "LinkedListInterface.h"

using namespace std;

template<typename T>
class LinkedList : public LinkedListInterface<T> {
	private:
		struct Node {
			T data;
			Node* next;
			Node(T theData, Node* nextNode = NULL) : data(theData) {
				next = nextNode;
			};
		};

		Node* head;
		int numItems;

		Node* find(T findMe) {
			cout << "In find v1, finding " << findMe << endl;
			if (numItems == 0) {
				cout << "No items in list. Returning null..." << endl;
				return NULL;
			}
			Node* i;
			for(i = head; i != NULL; i = i->next) {
				cout << "Current list item: " << i->data << endl;
				if (i->data == findMe) {
					cout << "Found " << i->data << "! Returning..." << endl;
					return i;
				}
			}
			cout << "Not found. Returning null..." << endl;
			return NULL;
		}

		Node* find(T findMe, Node** nodeBefore) {
			cout << "In find v2, finding " << findMe << endl;
			if (numItems == 0) {
				cout << "Empty list. Returning null..." << endl;
				return NULL;
			}
			Node* i = head;
			*nodeBefore = NULL;
			while (i != NULL) {
				cout << "Current list item: " << i->data << endl;
				if (i->data == findMe) {
					cout << "Found " << i->data << "!" << endl;
					if (*nodeBefore == NULL) {
						cout << "Node before is NULL. Head is " << head->data << ". Returning..." << endl;
					}
					else {
						cout << "Node before is " << (*nodeBefore)->data << ". Returning..." << endl;
					}
					return i;
				}
				*nodeBefore = i;
				i = i->next;
			}
			cout << "Not found. Returning null..." << endl;
			return NULL;
		}

	public:
		LinkedList() : head(NULL), numItems(0) {};
		~LinkedList() {clear();};

		/*
		insertHead

		A node with the given value should be inserted at the beginning of the list.

		Do not allow duplicate values in the list.
		*/
		void insertHead(T value) {
			cout << "In insertHead. Inserting " << value << "..." << endl;
			if (find(value) == NULL) {
				cout << "Back in insertHead. Item " << value << " not found. Proceeding with insert..." << endl;
				cout << "Old head: ";
				if (head == NULL) {cout << "null. ";}
				else {cout << head->data << ". ";}
				Node* newItem = new Node(value, head);
				head = newItem;
				++numItems;
				cout << "New head: " << head->data << ". Head->next: ";
				if (head->next == NULL) {cout << "null";}
				else {cout << head->next->data;}
				cout << ". Returning..." << endl;
			}
			else {cout << "Item " << value << " already present. Returning..." << endl;}
		};

		/*
		insertTail

		A node with the given value should be inserted at the end of the list.

		Do not allow duplicate values in the list.
		*/
		void insertTail(T value) {
			cout << "In insertTail. Inserting " << value << "." << endl;
			if (numItems == 0) {
				cout << "Empty list. Head is now ";
				head = new Node(value);
				++numItems;
				cout << head->data << ". ";
			}
			else if (find(value) == NULL) {
				cout << value << " not found. Proceeding with insert. Parsing list..." << endl;
				Node* newItem = new Node(value);
				Node* currItem = head;
				cout << "Current item is " << currItem->data << endl;
				while (currItem->next != NULL) {
					currItem = currItem->next;
					cout << "Current item is " << currItem->data << endl;
				}
				//Now currItem points to the last item of the list
				cout << "This is currently the last item in list." << endl;
				currItem->next = newItem;
				++numItems;
				cout << "New last item: " << currItem->next->data << endl;
			}
			cout << "Returning..." << endl;
		};

		/*
		insertAfter

		A node with the given value should be inserted immediately after the
		node whose value is equal to insertionNode.

		A node should only be added if the node whose value is equal to
		insertionNode is in the list. Do not allow duplicate values in the list.
		*/
		void insertAfter(T value, T insertionNode) {
			cout << "In insertAfter..." << endl;
			Node* afterMe = find(insertionNode);
			if (afterMe == NULL) {
				cout << insertionNode << " not found. Cannot insert " << value << ". Returning..." << endl;
				return;
			}
			else {
				cout << "Found " << insertionNode << ". Current order: " << afterMe->data << ", ";
				if (afterMe->next == NULL) {cout << "null";}
				else {cout << afterMe->next->data;}
				cout << ". Inserting..." << endl;
				Node* newNode = new Node(value, afterMe->next);
				afterMe->next = newNode;
				++numItems;
				cout << "New order: " << afterMe->data << ", " << afterMe->next->data << ", ";
				if (afterMe->next->next == NULL) {cout << "null";}
				else {cout << afterMe->next->next->data;}
				cout << ". Returning..." << endl;
			}
		};

		/*
		remove

		The node with the given value should be removed from the list.

		The list may or may not include a node with the given value.
		*/
		void remove(T value) {
			cout << "In remove." << endl;
			//FIXME: if empty, do nothing
			//FIXME: if head, special case
			Node* nodeBefore = NULL;
			Node* removeMe = find(value, &nodeBefore);
			if (removeMe != NULL) {	//If found value
				cout << "Found value " << removeMe->data << " after value ";
				if (nodeBefore == NULL) {	//If value is in head
					cout << "null. Assuming value is head." << endl;
					cout << "Check: head is " << head->data << endl;
					head = head->next;
					cout << "New head is ";
					if (head->next == NULL) {cout << "null. ";}
					else {cout << head->next->data << ". ";}
					cout << "Removing " << removeMe->data << endl;
					delete removeMe;
					cout << "Returning..." << endl;
				}
				else {
					cout << nodeBefore->data << ". Current order: " << nodeBefore->data << ", " << nodeBefore->next->data << ", ";
					if (nodeBefore->next->next == NULL) {cout << "null";}
					else {cout << nodeBefore->next->next->data;}
					cout << endl;
					nodeBefore->next = removeMe->next;
					delete removeMe;
					cout << "New order: " << nodeBefore->data << ", ";
					if (nodeBefore->next == NULL) {cout << "null";}
					else {cout << nodeBefore->next->data;}
					cout << ". Returning..." << endl;
				}
				--numItems;
			}
			else {cout << value << " not found, cannot be removed. Returning..." << endl;}
		};

		/*
		clear

		Remove all nodes from the list.
		*/
		void clear() {
			cout << "In clear. Parsing list..." << endl;
			Node* currItem = head;
			Node* nextItem = NULL;
			cout << "currItem is ";
			while (currItem != NULL) {
				cout << currItem->data << ". " << endl << "currItem is ";
				nextItem = currItem->next;
				delete currItem;
				currItem = nextItem;
			}
			if (currItem == NULL) {cout << "null. List empty. Returning" << endl;}
			else {cout << "ERROR. Returning..." << endl;}
			numItems = 0;
		};

		/*
		at

		Returns the value of the node at the given index. The list begins at
		index 0.

		If the given index is out of range of the list, throw an out of range exception.
		*/
		T at(int index) {
			cout << "In at. Index: " << index << endl;
			if (index < 0 || index >= numItems) {
				ostringstream errorMsg;
				errorMsg << "at::Index " << index << " is out of range!";
				cout << "Out of range! Throwing exception..." << endl;
				throw std::out_of_range(errorMsg.str());
			}
			else {
				Node* currItem = head;
				cout << "Parsing list. Index 0 is ";
				if (currItem == NULL) {cout << "null." << endl;}
				else {cout << currItem->data << ". " << endl;}
				for (int i = 1; i <= index; ++i) {
					currItem = currItem->next;
					cout << "Index " << i << " is ";
					if (currItem == NULL) {cout << "null." << endl;}
					else {cout << currItem->data << ". " << endl;}
				}
				cout << "Found item " << currItem->data << " at index " << index << ". Returning..." << endl;
				return currItem->data;
			}
		};

		/*
		size

		Returns the number of nodes in the list.
		*/
		int size() {
			cout << "In size. Size is " << numItems << ". Returning..." << endl;
			return numItems;
			};

		/*
		toString
		
		Returns a string representation of the list, with the value of each node listed in order (Starting from the head) and separated by a single space
		There should be no trailing space at the end of the string

		For example, a LinkedList containing the value 1, 2, 3, 4, and 5 should return
		"1 2 3 4 5"
		*/
		string toString() {
			cout << "In toString." << endl;
			ostringstream theData;
			Node* currItem = head;
			for (int i = 0; i < numItems; ++i) {
				theData << currItem->data;
				if (i != (numItems - 1)) {
					theData << " ";
				}
			}
			cout << "Returning with: " << theData.str() << endl;
			return theData.str();
		};

};



#endif