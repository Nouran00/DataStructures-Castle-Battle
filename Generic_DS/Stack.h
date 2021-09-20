#pragma once
#ifndef __STACK_H_
#define __STACK_H_

#include "Generic_DS/Node.h"

template <typename T>
class Stack
{
private:
	Node <T>* headptr;
public:
	Stack();
	bool isEmpty();
	bool Push(const T& newEntry);
	bool Pop(T& DeleteEntry);
	bool peek(T& PeekEntry);

	//toArray function to be used ONLY when drawing the stack items
	const T* toArray(int& count);	//returns array of T (array of items)

	Node <T>* getheadptr();
	~Stack();
};

template <typename T>
Stack<T>::Stack()
{
	headptr = NULL;

}

template <typename T>
bool Stack<T>::isEmpty() //const
{
	if (headptr == nullptr)
		return true;
	else
		return false;
}
template <typename T>
Node <T>*  Stack<T>:: getheadptr()
{
	if (headptr)
		return headptr;
	return nullptr;
}

template <typename T>
bool Stack<T>::Push(const T& newEntry)
{
	Node<T>* newNodePtr = new Node<T>(newEntry);

	if (isEmpty())
	{
		headptr = newNodePtr;
		newNodePtr->setNext(nullptr);
	}
	else
	{
		newNodePtr->setNext(headptr);
		headptr = newNodePtr;
	}
		return true;
	
}

template <typename T>
bool Stack<T>::Pop(T& DeleteEntry)
{
	if (isEmpty())
		return false;

	DeleteEntry=headptr->getItem();
	Node<T>* Dptr = headptr;
	/*headptr->setNext(headptr->getNext());
	DeleteEntry = Dptr->getItem();*/
	headptr=headptr->getNext();
	delete Dptr;
	Dptr=NULL;
}


template <typename T>
bool Stack<T>::peek(T& PeekEntry)
{
	if (isEmpty())
		return false;

	PeekEntry = headptr->getItem();
	return true;
}


template <typename T>
Stack<T>::~Stack()
{
}


/*
Function: toArray
returns an array of "T"
Output: count: the length of the returned array (zero if stack is empty)
returns: The array of T. (nullptr if Queue is empty)
*/

//IMPORTANT:
//toArray function to be used ONLY when drawing the queue items

template <typename T>
const T* Stack<T>::toArray(int& count)
{

	//IMPORTANT:
	//toArray function to be used ONLY when drawing the queue items

	count = 0;

	if (!headptr)
		return nullptr;
	//counting the no. of items in the Queue
	Node<T>* p = headptr;
	while (p)
	{
		count++;
		p = p->getNext();
	}


	T* Arr = new T[count];
	p = headptr; //reset pointer
	for (int i = 0; i < count;i++)
	{
		Arr[i] = p->getItem();
		p = p->getNext();
	}
	return Arr;

	//IMPORTANT:
	//toArray function to be used ONLY when drawing the stack items

}


#endif
