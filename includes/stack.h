#pragma once
#include <iostream>
#include "defines.h"
using namespace std;

template <class Data>
class Stack
{
protected:
	int size;
	int top;
	Data *ar;
public:
	Stack(){}
	Stack(int _size)
	{
		if (_size >= 0)
			top = -1;
		else throw NEGATIVE_INDEX;
		size = _size;
		ar = new Data[size];
	}
	void push(Data num)
	{
		if (top + 1 < size)
			ar[++top] = num;
		else throw STACK_FULL;
	}
	void quickPush(Data num)
	{
		ar[++top] = num;
	}
	Data pop()
	{
		if (top >= 0)
			return ar[top--];
		else throw STACK_EMPTY;
	}
	Data quickPop()
	{
		return ar[top--];
	}
	Data& showTop()
	{
		return ar[top];
	}
	Data getElem(int i)
	{
		return ar[i];
	}
	bool isEmty()
	{
		return (top == -1);
	}
	bool isFull()
	{
		return (top + 1 == size);
	}
	int getNumTop()
	{
		return top;
	}
	void setTop(int _top)
	{
		top = _top;
	}
	void printP()
	{
		for (int i = 0; i <= top; i++)
			cout << *ar[i];
	}
	~Stack()
	{
		if (ar != 0 && size > 0)
			delete[] ar;
	}
	friend ostream& operator<< (ostream & ostr, Stack& obj) 
	{
		for (int i = 0; i < obj.size; i++)
			ostr << obj.ar[i] << " ";
		return ostr;
	}
};