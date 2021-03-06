#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <string>
#include "LinkedListInterface.h"

using namespace std;

template<typename T>
class LinkedList : public LinkedListInterface<T> {
	private:
		struct Node {
			T data;
			Node* next;
			Node(T theData, Node* nextNode = NULL) : data(theData), next(nextNode) {};
		};

		Node* head;
		int numItems;

		Node* find(T findMe) {
			if (numItems == 0) {
				return NULL;
			}
			Node* i;
			for(i = head; i != NULL; i = i->next) {
				if (i->data == findMe) {
					return i;
				}
			}
			return NULL;
		}

	public:
		LinkedList() : head(NULL), numItems(0) {};
		~LinkedList() {
			Node* currItem = head;
			Node* nextItem = NULL;
			while (currItem != NULL) {
				nextItem = currItem->next;
				delete currItem;
				currItem = nextItem;
			}
		};

		/*
		insertHead

		A node with the given value should be inserted at the beginning of the list.

		Do not allow duplicate values in the list.
		*/
		void insertHead(T value) {
			if (find(value) == NULL) {
				Node* newItem = new Node(value, head);
				head = newItem;
				++numItems;
			}
		};

		/*
		insertTail

		A node with the given value should be inserted at the end of the list.

		Do not allow duplicate values in the list.
		*/
		void insertTail(T value) {
			if (numItems == 0) {
				head = new Node(value);
				++numItems;
			}
			else if (find(value) == NULL) {
				Node* newItem = new Node(value);
				Node* currItem = head;
				while (currItem->next != NULL) {
					currItem = currItem->next;
				}
				//Now currItem points to the last item of the list
				currItem->next = newItem;
				++numItems;
			}
		};

		/*
		insertAfter

		A node with the given value should be inserted immediately after the
		node whose value is equal to insertionNode.

		A node should only be added if the node whose value is equal to
		insertionNode is in the list. Do not allow duplicate values in the list.
		*/
		void insertAfter(T value, T insertionNode) {
			Node* afterMe = find(insertionNode);
			if (afterMe == NULL) return;
			Node* newNode = new Node(value, afterMe->next);
			afterMe->next = newNode;
			++numItems;
		};

		/*
		remove

		The node with the given value should be removed from the list.

		The list may or may not include a node with the given value.
		*/
		void remove(T value) = 0;

		/*
		clear

		Remove all nodes from the list.
		*/
		void clear() = 0;

		/*
		at

		Returns the value of the node at the given index. The list begins at
		index 0.

		If the given index is out of range of the list, throw an out of range exception.
		*/
		T at(int index) = 0;

		/*
		size

		Returns the number of nodes in the list.
		*/
		int size() = 0;

		/*
		toString
		
		Returns a string representation of the list, with the value of each node listed in order (Starting from the head) and separated by a single space
		There should be no trailing space at the end of the string

		For example, a LinkedList containing the value 1, 2, 3, 4, and 5 should return
		"1 2 3 4 5"
		*/
		string toString() = 0;

};



#endif