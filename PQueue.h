#ifndef __PQUEUE_H_
#define __PQUEUE_H_


#include "PNode.h"
template <typename T>
class PQueue
{
private :
	
	PNode <T>* backPtr;
	PNode <T>* frontPtr;
public :
	PQueue();	
	PQueue(PQueue<T>& );
	bool isEmpty() const ;
	bool enqueue(const T& newEntry,int);
	bool dequeue(T& frntEntry);  
	bool peekFront(T& frntEntry) const;
	PNode<T>* GetFrontptr();
	
	//toArray function to be used ONLY when drawing the queue items
	const T* toArray(int& count);	//returns array of T (array of items)


	~PQueue();
};
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: Queue()
The constructor of the Queue class.

*/

template <typename T>
PQueue<T>::PQueue()
{
	backPtr=nullptr;
	frontPtr=nullptr;

}
/////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
PQueue<T>::PQueue(PQueue<T>& copyQueue)
{
	backPtr = nullptr;
	frontPtr = nullptr;
	if (copyQueue.isEmpty())
		return;
	PNode<T>* nptr = copyQueue.frontPtr;
	while (nptr)
	{
		enqueue(nptr->getItem(), nptr->getPriority());
		nptr = nptr->getNext();
	}
}
/*
Function: isEmpty
Sees whether this queue is empty.

Input: None.
Output: True if the queue is empty; otherwise false.
*/
template <typename T>
bool PQueue<T>::isEmpty() const
{
	if(frontPtr==nullptr)
		return true;
	else
		return false;
}

/////////////////////////////////////////////////////////////////////////////////////////

/*Function:enqueue
Adds newEntry at the back of this queue.

Input: newEntry .
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool PQueue<T>::enqueue( const T& newEntry,int p)
{

	PNode <T>* newNode = new PNode<T>(newEntry,p);
	// Insert the new node
	if (isEmpty())
	{
		frontPtr = newNode; // 
		backPtr = newNode;
	}
	else if(newNode->getPriority()>frontPtr->getPriority())
	{
		newNode->setNext(frontPtr);
		frontPtr = newNode; 
	}
	else
	{
		PNode<T>* curr  = frontPtr;
	while (curr->getNext()!= nullptr)
	{  
		if(curr->getNext()->getPriority()>= newNode->getPriority())
		{
			curr=curr->getNext();
		}
		else
		{
			newNode->setNext(curr->getNext());
			curr->setNext(newNode);
			break;
		}
	}
	if (!curr->getNext())
	{
		curr->setNext(newNode);
	}
	if (!newNode->getNext())
		backPtr = newNode;
	}
	return true ;

} // end enqueue


/////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Function: dequeue
Removes the front of this queue. That is, removes the item that was added
earliest.

Input: None.
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool PQueue<T>:: dequeue(T& frntEntry)  
{
	if(isEmpty())
		return false;

	PNode<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: one node in queue
		backPtr = nullptr ;	
		
	// Free memory reserved by the dequeued node
	delete nodeToDeletePtr;


	return true;

}

/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: peekFront
gets the front of this queue. The operation does not modify the queue.

Input: None.
Output: The front of the queue.
return: flase if Queue is empty
*/
template <typename T>
bool PQueue<T>:: peekFront(T& frntEntry) const 
{
	if(isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;

}
///////////////////////////////////////////////////////////////////////////////////

template <typename T>
PQueue<T>::~PQueue()
{
}

/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: toArray
returns an array of "T" 
Output: count: the length of the returned array (zero if Queue is empty)
returns: The array of T. (nullptr if Queue is empty)
*/

//IMPORTANT:
//toArray function to be used ONLY when drawing the queue items

template <typename T>
const T* PQueue<T>::toArray(int& count)
{

	//IMPORTANT:
	//toArray function to be used ONLY when drawing the queue items

	count=0;

	if(!frontPtr)
		return nullptr;
	//counting the no. of items in the Queue
	PNode<T>* p = frontPtr;
	while(p)
	{
		count++;
		p = p->getNext();
	}


	T* Arr= new T[count];
	p = frontPtr;
	for(int i=0; i<count;i++)
	{
		Arr[i] = p->getItem();
		p = p->getNext();
	}
	return Arr;
	//IMPORTANT:
	//toArray function to be used ONLY when drawing the queue items

}
template <typename T>
PNode<T>* PQueue<T>::GetFrontptr()
{
	if (frontPtr)
		return frontPtr;
	return nullptr;
}

#endif