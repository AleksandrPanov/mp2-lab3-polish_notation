#pragma once
#include <string>
#include "defines.h"
#include <iostream>
#include <string>
#include <math.h>
#include <winbase.h>
using namespace std;

class Lexeme
{
protected:
	string name;
	int type;
public:
	Lexeme() {};
	Lexeme(string s, int _type) : type(_type), name(s){}
	Lexeme(char s, int _type) : type(_type)
	{	
		name.push_back(s);
	};
	int getType() { return type; }
	virtual int getPriority() { return -1; }
	virtual double binaryCalculate(Lexeme *l1, Lexeme *l2) { return -1; }
	virtual double unaryCalculate(Lexeme *l1) { return -1; }
	virtual double getVal() { return -1; }
	string getName() { return name; }
	virtual bool operator >= (Lexeme& l)
	{
		return false;
	}
	virtual bool operator > (Lexeme& l)
	{
		return false;
	}
	Lexeme& operator=(const Lexeme& l)
	{
		if (this == &l)
			return *this;
		name = l.name;
		type = l.type;
		return *this;
	}
	bool operator==(const Lexeme &l)
	{
		return (type == l.type && name == l.name);
	}
	bool operator!=(char s)
	{
		return (name[0] != s);
	}
	friend ostream &operator<<(ostream &ostr, const Lexeme &obj)
	{
		ostr << obj.name;
		return ostr;
	}
};
class LexemeNum : public Lexeme
{
double val;
public:
	LexemeNum():Lexeme() {};
	LexemeNum(char s, int _type, double _val) : Lexeme(s, _type), val(_val) {};
	LexemeNum(string s, int _type, double _val) : Lexeme(s, _type), val(_val){	};
	double getVal() { return  val; }
	bool operator==(int num)
	{
		return ( val == (double)num);
	}
};
class LexemeVar : public Lexeme
{
public:
	static double ar[26];
	static bool isVar[26];
	static int count;
	LexemeVar() :Lexeme() {};
	LexemeVar(char s, int _type) :Lexeme(s, _type) 
	{
		count++;
		isVar[s - 'a'] = true;
	};
	double getVal() 
	{
		return  ar[name[0]-'a'];
	}
	static void clear()
	{
		for (int i = 0; i < 26; i++)
		{
			ar[i] = 1;
			isVar[i] = false;
		}
	}
};
/*double LexemeVar::ar[26] = { 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1};
int LexemeVar::count = 0;
bool LexemeVar::isVar[26] = {0};*/
class LexemeOper : public Lexeme
{
protected:
int priority = lowest;
public:
	LexemeOper(char s, int _type) : Lexeme(s, _type) {	};
	int getPriority() { return priority; }
	bool operator >= (Lexeme& l)
	{
		return (getPriority() >= l.getPriority());
	}
	bool operator > (Lexeme& l)
	{
		return (getPriority() > l.getPriority());
	}
};
class UnaryOper : public LexemeOper
{
public:
	UnaryOper(char s, int _type) : LexemeOper(s, _type) { priority = high; }
	double unaryCalculate(Lexeme *l1)
	{
		switch (name[0])
		{
			case '-': return (-l1->getVal()); break;
			case 'c': return (cos(l1->getVal())); break;
			case 's': return (sin(l1->getVal())); break;
			case 't': return (tan(l1->getVal())); break;
			default: throw UNKNOWN_TYPE; break;
		}
	}
};
class BinaryOper : public LexemeOper
{
public:
	BinaryOper(char s, int _type) : LexemeOper(s, _type)
	{
		if (name == "+" || name == "-") priority = low;
		else if (name == "*" || name == "/" || name == "^") priority = medium;
	}
	double binaryCalculate(Lexeme *l1, Lexeme *l2)
	{
		switch (name[0])
		{
			case '+': return (l1->getVal() + l2->getVal()); break;
			case '-': return (l1->getVal() - l2->getVal()); break;
			case '*': return (l1->getVal() * l2->getVal()); break;
			case '/': return (l1->getVal() / l2->getVal()); break;
			case '^': return (pow(l1->getVal(),l2->getVal())); break;
			default: throw UNKNOWN_TYPE; break;
		}
	}
};