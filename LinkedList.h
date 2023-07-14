#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <exception>
using namespace std;

template<typename T>
class LinkedList
{
public:
	struct Node
	{
		T data;
		Node* next = nullptr;
		Node* prev = nullptr;
	};
	//behaviors
	void PrintForward() const;
	void PrintReverse() const;
	void PrintForwardRecursive(const Node* node) const;
	void PrintReverseRecursive(const Node* node) const;

	//accessors
	unsigned int NodeCount() const;
	void FindAll(vector<Node*>& outData, const T& value) const;
	const Node* Find(const T& data) const;
	Node* Find(const T& data);
	const Node* GetNode(unsigned int index) const;
	Node* GetNode(unsigned int index);
	Node* Head();
	const Node* Head() const;
	Node* Tail();
	const Node* Tail() const;

	//insertion
	void AddHead(const T& data);
	void AddTail(const T& data);
	void AddNodesHead(const T* data, unsigned int count);
	void AddNodesTail(const T* data, unsigned int count);
	void InsertAfter(Node* node, const T& data);
	void InsertBefore(Node* node, const T& data);
	void InsertAt(const T& data, unsigned int index);

	//removal
	bool RemoveHead();
	bool RemoveTail();
	unsigned int Remove(const T& data);
	bool RemoveAt(unsigned int index);
	void Clear();

	//operators
	const T& operator[](unsigned int index) const;
	T& operator[](unsigned int index);
	bool operator==(const LinkedList<T>& rhs) const;
	LinkedList<T>& operator=(const LinkedList<T>& rhs);

	//construction / destruction
	LinkedList();
	LinkedList(const LinkedList<T>& list);
	~LinkedList();

private:
	Node* head;
	Node* tail;
	unsigned int numNodes;
};

//behaviors
template<typename T>
void LinkedList<T>::PrintForward() const
{
	Node* node = head;
	while (node != nullptr)
	{
		cout << node->data << endl;
		node = node->next;
	}
}

template<typename T>
void LinkedList<T>::PrintReverse() const
{
	Node* node = tail;
	while (node != nullptr)
	{
		cout << node->data << endl;
		node = node->prev;
	}
}

template<typename T>
void LinkedList<T>::PrintForwardRecursive(const Node* node) const
{
	if (node == nullptr)
	{
		return;
	}
	cout << node->data << endl;
	PrintForwardRecursive(node->next);

}

template<typename T>
void LinkedList<T>::PrintReverseRecursive(const Node* node) const
{
	if (node == nullptr)
	{
		return;
	}
	cout << node->data << endl;
	PrintReverseRecursive(node->prev);
}

//accessors
template<typename T>
unsigned int LinkedList<T>::NodeCount() const
{
	return numNodes;
}

template<typename T>
void LinkedList<T>::FindAll(vector<Node*>& outData, const T& value) const
{
	Node* node = head;
	while (node != nullptr)
	{
		if (node->data == value)
		{
			outData.push_back(node);
		}
		node = node->next;
	}
}

template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) const
{
	Node* node = head;
	while (node != nullptr)
	{
		if (node->data == data)
		{
			return node;
		}
		node = node->next;
	}
	return nullptr;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data)
{
	Node* node = head;
	while (node != nullptr)
	{
		if (node->data == data)
		{
			return node;
		}
		node = node->next;
	}
	return nullptr;
}

template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) const
{
	Node* node = head;
	if (index > numNodes - 1 || index < 0)
	{
		throw out_of_range("");
	}

	for (unsigned int i = 0; i < numNodes - 1; i++)
	{
		if (i == index)
		{
			return node;
		}
		node = node->next;
	}
	return nullptr;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index)
{
	Node* node = head;
	if (index > numNodes - 1 || index < 0)
	{
		throw out_of_range("");
	}

	for (unsigned int i = 0; i < numNodes - 1; i++)
	{
		if (i == index)
		{
			return node;
		}
		node = node->next;
	}
	return nullptr;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Head()
{
	return head;
}

template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Head() const
{
	return head;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Tail()
{
	return tail;
}

template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Tail() const
{
	return tail;
}

//insertion
template<typename T>
void LinkedList<T>::AddHead(const T& data)
{
	Node* node = new Node();

	node->data = data;

	if (head == nullptr)
	{
		head = node;
		tail = node;
	}
	else
	{
		head->prev = node;
		node->next = head;
		head = node;
	}

	numNodes++;
}

template<typename T>
void LinkedList<T>::AddTail(const T& data)
{
	Node* node = new Node();

	node->data = data;

	if (tail == nullptr)
	{
		head = node;
		tail = node;
	}
	else
	{
		tail->next = node;
		node->prev = tail;
		tail = node;
	}

	numNodes++;
}

template<typename T>
void LinkedList<T>::AddNodesHead(const T* data, unsigned int count)
{
	for (int i = count - 1; i > -1; i--)
	{
		AddHead(data[i]);
	}
}

template<typename T>
void LinkedList<T>::AddNodesTail(const T* data, unsigned int count)
{
	for (unsigned int i = 0; i < count; i++)
	{
		AddTail(data[i]);
	}
}

template<typename T>
void LinkedList<T>::InsertAfter(Node* node, const T& data)
{
	Node* newNode = new Node();
	newNode->data = data;
	newNode->next = node->next;
	node->next = newNode;
	newNode->prev = node;
	numNodes++;
}

template<typename T>
void LinkedList<T>::InsertBefore(Node* node, const T& data)
{
	Node* newNode = new Node();
	newNode->data = data;
	newNode->next = node;
	newNode->prev = node->prev;
	node->prev = newNode;
	newNode->prev->next = newNode;
	numNodes++;
}

template<typename T>
void LinkedList<T>::InsertAt(const T& data, unsigned int index)
{
	if (index < 0 || index > numNodes)
	{
		throw out_of_range("");
	}
	else if (index == 0)
	{
		AddHead(data);
	}
	else if (index == numNodes)
	{
		AddTail(data);
	}
	else
	{
		Node* oldNode = GetNode(index);
		InsertBefore(oldNode, data);
	}
}


//removal
template<typename T>
bool LinkedList<T>::RemoveHead() //remember to numNodes-- for your removal
{
	if (numNodes == 0)
	{
		return false;
	}
	else
	{
		Node* node = head;
		head = node->next;
		delete node;

		numNodes--;
		if (numNodes == 0)
		{
			head = nullptr;
			tail = nullptr;
		}
		return true;
	}
}

template<typename T>
bool LinkedList<T>::RemoveTail()
{
	if (numNodes == 0)
	{
		return false;
	}
	else if (tail == nullptr)
	{
		return false;
	}
	else
	{
		Node* node = tail;
		tail = tail->prev;
		if (tail != nullptr)
		{
			tail->next = nullptr;
		}
		delete node;

		numNodes--;
		if (numNodes == 0)
		{
			head = nullptr;
			tail = nullptr;
		}
		return true;
	}
}

template<typename T>
unsigned int LinkedList<T>::Remove(const T& data)
{
	unsigned int numRemoved = 0;
	Node* node = head;

	while (node != nullptr)
	{
		Node* temp = node->next;
		if (node->data == data)
		{
			if (node == head)
			{
				RemoveHead();
			}
			else if (node == tail)
			{
				RemoveTail();
			}
			else
			{

				node->prev->next = node->next;
				node->next->prev = node->prev;
				delete node;
				numNodes--;
			}

			numRemoved++;
		}
		node = temp;
	}

	return numRemoved;
}

template<typename T>
bool LinkedList<T>::RemoveAt(unsigned int index)
{
	if (numNodes == 0)
	{
		return false;
	}
	if (index < 0 || index > numNodes)
	{
		return false;
	}
	else if (index == 0)
	{
		RemoveHead();
	}
	else if (index == numNodes)
	{
		RemoveTail();
	}
	else
	{
		Node* node = GetNode(index);
		node->prev->next = node->next;
		node->next->prev = node->prev;
		delete node;
		numNodes--;
	}

	return true;
}

template<typename T>
void LinkedList<T>::Clear()
{
	Node* node = head;
	while (node != nullptr)
	{
		Node* temp = node->next;
		delete node;
		node = temp;
	}
	numNodes = 0;
	head = nullptr;
	tail = nullptr;
}


//operators
template<typename T>
const T& LinkedList<T>::operator[](unsigned int index) const
{
	if ((index > numNodes - 1) || (index < 0))
	{
		throw out_of_range("");
	}
	Node* node = GetNode(index);
	return node->data;
}

template<typename T>
T& LinkedList<T>::operator[](unsigned int index)
{
	if ((index > numNodes - 1) || (index < 0))
	{
		throw out_of_range("");
	}
	Node* node = GetNode(index);
	return node->data;
}

template<typename T>
bool LinkedList<T>::operator==(const LinkedList<T>& rhs) const
{
	Node* a = this->head;
	Node* b = rhs.head;
	while (a != nullptr)
	{
		if (a->data != b->data)
		{
			return false;
		}
		a = a->next;
		b = b->next;
	}
	if (b != nullptr)
	{
		return false;
	}
	return true;
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs)
{
	Node* node = head;
	while (node != nullptr)
	{
		Node* temp = node->next;
		delete node;
		node = temp;
	}
	node = rhs.head;
	this->head = nullptr;
	this->tail = nullptr;
	this->numNodes = 0;
	while (node != nullptr)
	{
		this->AddTail(node->data);
		node = node->next;
	}
	return *this;
}


//constructors / destructors
template<typename T>
LinkedList<T>::LinkedList()
{
	numNodes = 0;
	head = nullptr;
	tail = nullptr;
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list)
{
	head = nullptr;
	tail = nullptr;
	numNodes = 0;
	Node* node = list.head;
	while (node != nullptr)
	{
		this->AddTail(node->data);
		node = node->next;
	}
}

template<typename T>
LinkedList<T>::~LinkedList()
{
	Node* node = head;
	while (node != nullptr)
	{
		Node* temp = node->next;
		delete node;
		node = temp;
	}
}