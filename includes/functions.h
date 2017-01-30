#pragma once
#include "list.h"
#include "stack.h"
#include "lexeme.h"
#include "stdlib.h"
double LexemeVar::ar[26] = { 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1 };
int LexemeVar::count = 0;
bool LexemeVar::isVar[26] = { 0 };

int GetReadStatus(char *p, int i, int len)
{
	if (*p >= '0' && *p <= '9')
		return num;
	else if (*p >= 'a' && *p <= 'z')
	{
		if (*p == 'c' && i + 2 < len && p[1] == 'o' && p[2] == 's')
			return funct;
		if (*p == 's' && i + 2 < len && p[1] == 'i' && p[2] == 'n')
			return funct;
		if (*p == 't' && i + 1 < len && p[1] == 'g')
			return funct;
		return var;
	}
	else if (*p == '+' || *p == '*' || *p == '/' || *p == '^')
		return binOp;
	else if (*p == '-')
		return minus1;
	else if (*p == '(')
		return leftB;
	else if (*p == ')')
		return rightB;
	else
		return error;
}
void ReadNum(List <Lexeme*>&l, char *p1, int &i)
{
	double val;
	char *p2 = p1;
	//������� �����
	val = strtod(p1, &p2);
	//������� ������� � ���� ������
	Lexeme *pL = new LexemeNum(string(p1, p2), number, val);
	l.push_front(pL);
	//�������� i
	i = i + (p2 - p1) - 1;
}
void ReadVar(List <Lexeme*>&l, char name)
{
	Lexeme *p = new LexemeVar(name, var);
	l.push_front(p);
}
void ReadLeftB(List <Lexeme*>&l, int &statusBrackets)
{
	statusBrackets++;
	Lexeme *p = new LexemeOper('(', left_brackets);
	l.push_front(p);
}
void ReadRightB(List <Lexeme*>&l, int &statusBrackets)
{
	statusBrackets--;
	if (statusBrackets < 0)
		throw  ERROR_BRACKETS;
	Lexeme *p = new LexemeOper(')', right_brackets);
	l.push_front(p);
}
void ReadUnarOp(List <Lexeme*>&l,char p1, int &i)
{
	if (p1 == '-')
	{
		Lexeme *p = new UnaryOper('-', unary_oper);
		l.push_front(p);
	}
	else
	{
		Lexeme *p = new UnaryOper(p1, unary_oper);
		l.push_front(p);
		if (p1 == 't')
			i++;
		else i = i + 2;
	}
}
void ReadBinarOp(List <Lexeme*>&l, char name)
{
	Lexeme *p = new BinaryOper(name, binary_oper);
	l.push_front(p);
}

int NewRead(string &s, List <Lexeme*>&l, int numLex = 0)
{
	int statusRead, status = wait, statusBrackets = 0, length = s.length();
	char tmp;
	for (int i = 0; i < s.length(); i++)
	{
		numLex++;
		tmp = s[i];
		statusRead = GetReadStatus(&s[i],i, length);
		switch (status)
		{
		case wait://if end - error
			switch (statusRead)
			{
			case num:
				//������� �����
				ReadNum(l, &s[i], i);
				status = nextOp;
				break;
			case var:
				//�������� ������� ����������
				ReadVar(l, tmp);
				status = nextOp;
				break;
			case leftB:
				//������� ������, ����� ����� ������++
				ReadLeftB(l,  statusBrackets);
				status = wait;
				break;
			case minus1:
				//������� ������� �����
				ReadUnarOp(l, tmp, i);
				status = nextEx;
				break;
			case unOp:
				//������� ������� -
				ReadUnarOp(l, tmp, i);
				status = nextEx;
				break;
			case funct:
				//������� ������, ����� ����� ������++
				ReadUnarOp(l, tmp, i);
				status = wait;
				break;
			default:throw ERROR_READ;break;
			}
		break;

		case nextOp:
			switch (statusRead)
			{
			case binOp:
				//������� �������� ��
				ReadBinarOp(l, tmp);
				status = nextEx;
				break;
			case minus1:
				//������� �������� -
				ReadBinarOp(l, tmp);
				status = nextEx;
				break;
			case binOpPost:
				//������� ������� ����������� ����
				ReadBinarOp(l, tmp);
				status = nextOpBin;
				break;
			case rightB:
				//������� ������ ������, ����� ������ ������--
				ReadRightB(l, statusBrackets);
				status = nextOp;
				break;
			default:throw ERROR_READ;break;
			}
		break;

		case nextEx://if end - error
			switch (statusRead)
			{
			case num:
				//������� �����
				ReadNum(l, &s[i], i);
				status = nextOp;
				break;
			case var:
				//������� var
				ReadVar(l, tmp);
				status = nextOp;
				break;
			case leftB:
				//������� ������, ����� ����� ������++
				ReadLeftB(l, statusBrackets);
				status = wait;
				break;
			case funct:
				ReadUnarOp(l, tmp, i);
				status = wait;
				break;
			default:throw ERROR_READ; break;
			}
		break;

		case nextOpBin:
			switch (statusRead)
			{
			case binOp:
				//������� �������� �perand
				ReadBinarOp(l, tmp);
				status = nextEx;
				break;
			case minus1:
				//������� �������� -
				ReadBinarOp(l, tmp);
				status = nextEx;
				break;
			case rightB:
				//������� ������ ������, ����� ������--
				ReadRightB(l, statusBrackets);
				status = nextOp;
				break;
			default:throw ERROR_READ; break;
			}
		break;
		default:throw ERROR_READ; break;
		}
	}
	if (status == wait || status == nextEx || statusBrackets != 0)
		throw ERROR_READ;
	l.reverce();
	return numLex;
}
Stack<Lexeme*>* GetPolishNotation(List <Lexeme*>&list, int size)
{
	Stack<Lexeme*> *res  = new Stack<Lexeme *>(size);
	Stack<Lexeme *> tmp(size);
	Lexeme *l;
	while (!list.isEmpty())
	{
		l = list.quick_pop_front();
		switch (l->getType())
		{
			case number:
			{
				res->quickPush(l);
			} break;
			case var:
			{
				res->quickPush(l);
			} break;
			case binary_oper:
			{
				while (!tmp.isEmty() && *tmp.showTop() >= *l)
					res->quickPush(tmp.quickPop());
				tmp.quickPush(l);
			} break;
			case unary_oper:
			{
				while (!tmp.isEmty() && *tmp.showTop() > *l)
					res->quickPush(tmp.quickPop());
				tmp.quickPush(l);
			} break;
			case left_brackets:
			{
				tmp.quickPush(l);
			} break;
			case right_brackets:
			{
				while (*tmp.showTop() != '(')
					res->quickPush(tmp.quickPop());
				tmp.quickPop();
			} break;
		}
	}
	while (!tmp.isEmty())
		res->quickPush(tmp.quickPop());
	return res;
}
double GetAnswer(Stack<Lexeme*>* st)
{
	Lexeme *l,*l1, *l2, *count;
	Stack <Lexeme*> tmp(st->getNumTop());
	for (int i = 0; i<=st->getNumTop(); i++)
	{
		l = st->getElem(i);
		switch (l->getType())
		{
			case number: tmp.quickPush(l);  break;
			case var: tmp.quickPush(l);  break;
			case binary_oper: 
				l1 = tmp.quickPop();
				l2 = tmp.quickPop();
				count = new LexemeNum('e', number, l->binaryCalculate(l2, l1));
				tmp.quickPush( count);
				break;
			case unary_oper:
				l1 = tmp.quickPop();
				count = new LexemeNum('e', number, l->unaryCalculate(l1));
				tmp.quickPush(count);
				break;
		}
	}
	return tmp.showTop()->getVal();
}
void ReadVar()
{
	if (LexemeVar::count > 0)
	{
		for (int i = 0; i < 26 && LexemeVar::count > 0; i++)
			if (LexemeVar::isVar[i])
			{
				cout << "print value of " << (char)(i + 'a') << ' ';
				cin >> LexemeVar::ar[i];
				LexemeVar::count--;
			}
	}
}