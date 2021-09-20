#ifndef __PNode_H_
#define __PNode_H_

template < typename T>
class PNode
{
private :
	T item; // A data item
	PNode<T>* next; // Pointer to next node
	int Priority;    // priority of node
	public:
	PNode();
	PNode( const T & r_Item,int p);	//passing by const ref.
	PNode( const T & r_Item, PNode<T>* nextNodePtr);
	void setItem( const T & r_Item);
	void setNext(PNode<T>* nextNodePtr);
	T getItem() const ;
	PNode<T>* getNext() const ;

	int getPriority();
	void setPriority(int p);
}; // end Node


template < typename T>
PNode<T>::PNode() 
{
	next = nullptr;
} 

template < typename T>
PNode<T>::PNode( const T& r_Item,int p)
{
	item = r_Item;
	Priority=p;
	next = nullptr;
} 

template < typename T>
PNode<T>::PNode( const T& r_Item, PNode<T>* nextNodePtr)
{
	item = r_Item;
	next = nextNodePtr;
}
template < typename T>
void PNode<T>::setItem( const T& r_Item)
{
	item = r_Item;
} 

template < typename T>
void PNode<T>::setNext(PNode<T>* nextNodePtr)
{
	next = nextNodePtr;
} 

template < typename T>
T PNode<T>::getItem() const
{
	return item;
} 

template < typename T>
PNode<T>* PNode<T>::getNext() const
{
	return next;
} 


template < typename T>

int PNode<T>::getPriority() 
{
	return Priority;

} 
template < typename T>
void PNode<T>::setPriority(int p)
{
	Priority=p;
} 





#endif