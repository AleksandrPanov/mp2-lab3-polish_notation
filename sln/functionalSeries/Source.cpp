#include "../../includes/functions.h"
int main()
{
	List <Lexeme*> l;
	string s;
	double ans = 0;
	int numLex, n;
	cout << "print stop if you want to exit\n";
	while (1)
	{
		cout << "print n member of functional series\n";
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
		Stack<Lexeme*> *pSt = GetPolishNotation(l, numLex);
		LexemeVar::blockVar('n');
		ReadVar();
		cout << "print n ";
		cin >> n;
		for (int i = 1; i <= n; i++)
		{
			LexemeVar::setVar('n', i);
			ans += GetAnswer(pSt);
		}
		cout << "Your answer " << ans << "\n\n";
		ans = 0;
		LexemeVar::clear();
	}
	return 0;
}