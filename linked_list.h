#include <iostream>
using namespace std;

class Node
{
void* data;
Node* next;
public:
Node(void* data);
Node* getNext();
void* getDataPtr();
void setNext(Node* nextPtr);


};

class Linked_List
{
Node* head;
Node* tail;
public:
Linked_List()
Node* getTail();
void insertNode(void* dataPtr);
void deleteNode(void* dataPtr);
	
};