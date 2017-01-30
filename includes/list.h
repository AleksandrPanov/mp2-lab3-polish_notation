#pragma once
#pragma once
#include <iostream>
#include "defines.h"
using namespace std;

template <class Data>
struct Node
{
	Data data;
	Node* next;
};

template <class Data>
class List
{
protected:
	Node <Data> *head;
public:
	List() : head(0) {};
	bool isEmpty() { return (head == NULL); }
	Data quick_pop_front()
	{
			Node<Data> tmp = *head;
			Node<Data> *p = head;
			if (head->next)
			{
				head = head->next;
				delete p;
			}
			else 
			{
				delete head;
				head = 0;
			}
			return tmp.data;
	}
	void push_front(Data obj)
	{
		Node<Data> *newNode = new Node<Data>;
		newNode->data = obj;
		newNode->next = head;
		head = newNode;
	}
	int reverce()
	{
		int count = 0;
		Node<Data> *tmp = 0;
		Node<Data> *next = 0;
		if (head)
			next = head->next;
		while (next != 0)
		{
			head->next = tmp;
			tmp = head;
			head = next;
			next = head->next;
			count++;
		}
		count = count + 1;
		head->next = tmp;
		return count;
	}
	~List()
	{
		Node <Data> *tmp;
		while (!isEmpty())
		{
			tmp = head;
			head = head->next;
			delete tmp;
		}
	}
};