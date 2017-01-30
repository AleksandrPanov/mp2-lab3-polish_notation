#pragma once
template <class Data>
class SmartPtr
{
	Data *d;
	int count;
public:
	SmartPtr()
	{
		d = 0;
		count = 0;
	};
	SmartPtr(Data *_d): count(1), d(_d) {};
	SmartPtr &operator = (Data *obj)
	{
		if (d == obj)
			return *this;
		count++;
		d = obj;
		return *this;
	}
	Data* operator->() {
		return d;
	}
	~SmartPtr()
	{
		if (count == 0)
			delete d;
		else count--;
	}

};