#include "../../includes/functions.h"
int main()
{
	List <Lexeme*> l;
	string s;
	int numLex;
	cout << "print stop if you want to exit\n";
	while (1)
	{
		cin >> s;
		if (s == "stop")
			break;
		try 
		{
			numLex = NewRead(s, l);
		}
		catch (...)
		{
			cout << "error of print\n";
			l.~List();
			LexemeVar::clear();
			continue;
		}
		ReadVar();
		Stack<Lexeme*> *pSt = GetPolishNotation(l, numLex);
		//pSt->printP();
		cout <<"Your answer "<<GetAnswer(pSt)<<"\n\n";
		LexemeVar::clear();
	}
	return 0;
}