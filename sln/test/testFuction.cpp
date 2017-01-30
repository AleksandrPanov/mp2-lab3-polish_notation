#include "../../gtest/gtest.h"
#include "../../includes/functions.h"

TEST(function, can_read)
{
	string s = "-1";
	List <Lexeme*> list;
	ASSERT_NO_THROW(NewRead(s, list));
	string s1 = "-1234+1";
	ASSERT_NO_THROW(NewRead(s1, list));
}
TEST(function, read_znak_working)
{
	List <Lexeme*> list;
	string s = "-1";
	Lexeme *l1 = new UnaryOper ('-',unary_oper);
	NewRead(s, list);
	Lexeme *l2 = list.quick_pop_front();
	EXPECT_EQ(*l1 == *l2, true);
}
TEST(function, read_num_working)
{
	List <Lexeme*> list;
	string s = "123";
	Lexeme *l1 = new LexemeNum("123", number, 123);
	NewRead(s, list);
	Lexeme *l2 = list.quick_pop_front();
	EXPECT_EQ(*l1 == *l2, true);
}
TEST(function, p_read_working)
{
	List <Lexeme*> list;
	string s = "73";
	LexemeNum *l1 = new LexemeNum("73", number, 73);
	NewRead(s, list);
	Lexeme *l2 = list.quick_pop_front();
	EXPECT_EQ(l2->getName(), "73");
}
TEST(function, read_catch_wrong_brarackets1)
{
	List <Lexeme*> l;
	string s = "(((1))";
	EXPECT_ANY_THROW(NewRead(s,l));
}
TEST(function, read_catch_wrong_brarackets2)
{
	List <Lexeme*> l;
	string s = "((2)))";
	EXPECT_ANY_THROW(NewRead(s, l));
}
TEST(function, read_catch_wrong_brarackets3)
{
	List <Lexeme*> l;
	string s = "((3)+(4)))";
	EXPECT_ANY_THROW(NewRead(s, l));
}
TEST(function, read_true_brarackets1)
{
	List <Lexeme*> l;
	string s = "((1)+(2)+(-100)+((3)))";
	EXPECT_NO_THROW(NewRead(s, l));
}
TEST(function, read_catch_wrong_operator1)
{
	List <Lexeme*> l;
	string s = "3+-2";
	EXPECT_ANY_THROW(NewRead(s, l));
}
TEST(function, read_catch_wrong_operator2)
{
	List <Lexeme*> l;
	string s = "--3-2";
	EXPECT_ANY_THROW(NewRead(s, l));
}
TEST(function, read_catch_wrong_operator3)
{
	List <Lexeme*> l;
	string s = "3-2++";
	EXPECT_ANY_THROW(NewRead(s, l));
}
TEST(function, read_catch_wrong_operator4)
{
	List <Lexeme*> l;
	string s = "3-2+";
	EXPECT_ANY_THROW(NewRead(s, l));
}
TEST(function, read_catch_wrong_operator5)
{
	List <Lexeme*> l;
	string s = "3-()2";
	EXPECT_ANY_THROW(NewRead(s, l));
}
TEST(function, read_catch_wrong_operator6)
{
	List <Lexeme*> l;
	string s = "3-2+()";
	EXPECT_ANY_THROW(NewRead(s, l));
}
TEST(function, read_catch_wrong_operator7)
{
	List <Lexeme*> l;
	string s = "()3-2";
	EXPECT_ANY_THROW(NewRead(s, l));
}
TEST(function, read_can_read_right_operators1)
{
	List <Lexeme*> l;
	string s = "33-2+190000000";
	EXPECT_NO_THROW(NewRead(s, l));
}
TEST(function, read_can_read_right_operators2)
{
	List <Lexeme*> l;
	string s = "-1*3+(-2)";
	NewRead(s, l);
	EXPECT_NO_THROW(NewRead(s, l));
}
TEST(function, read_can_read_right_operators3)
{
	List <Lexeme*> l;
	string s = "(-1*3+(-2))";
	NewRead(s, l);
	EXPECT_NO_THROW(NewRead(s, l));
}
TEST(function, read_can_read_right_operators4)
{
	List <Lexeme*> l;
	string s = "(-1*3+(-2)/(3+(-1)))";
	NewRead(s, l);
	EXPECT_NO_THROW(NewRead(s, l));
}
TEST(function, read_can_read_right_operators5)
{
	List <Lexeme*> l;
	string s = "-3-(-5)-(3*2)+(2)";
	NewRead(s, l);
	EXPECT_NO_THROW(NewRead(s, l));
}
TEST(function, read_is_right)
{
	List <Lexeme*> l;
	string s = "-30-(-5)-(3*200)";
	Lexeme *ar[13];
	ar[0] = new UnaryOper('-',unary_oper);
	ar[1] = new LexemeNum("30", number, 30);
	ar[2] = new BinaryOper('-', binary_oper);
	ar[3] = new LexemeOper('(', left_brackets);
	ar[4] = new UnaryOper('-', unary_oper);
	ar[5] = new LexemeNum("5", number, 5);
	ar[6] = new LexemeOper(')', right_brackets);
	ar[7] = new BinaryOper('-', binary_oper);
	ar[8] = new LexemeOper('(', left_brackets);
	ar[9] = new LexemeNum("3", number, 3);
	ar[10] = new BinaryOper('*', binary_oper);
	ar[11] = new LexemeNum("200", number, 200);
	ar[12] = new LexemeOper(')', right_brackets);
	NewRead(s, l);
	int i = 0;
	while (!l.isEmpty() && i>= 0)
	{
		Lexeme *tmp = l.quick_pop_front();
		cout << *tmp << " " << tmp->getType()<< " "<< *ar[i]<<'\n';
		EXPECT_TRUE(*tmp == *ar[i++]);
	}
	NewRead(s, l);
	for (int i = 0; i < 13; i++)
	{
		Lexeme *tmp = l.quick_pop_front();
		EXPECT_TRUE(*tmp == *ar[i]);
	}
}
TEST(function, publish_notation1)
{
	List <Lexeme*> l;
	string s= "1+2*3";
	int len = NewRead(s, l);
	Stack<Lexeme*> *pSt =  GetPolishNotation(l, len);
	for (int i = 0; i <= pSt->getNumTop(); i++)
		cout<<*pSt->getElem(i);
}
TEST(function, publish_notation2)
{
	List <Lexeme*> l;
	string s = "(1+2)*3";
	int len = NewRead(s, l);
	Stack<Lexeme*> *pSt = GetPolishNotation(l,len);
	for (int i = 0; i <= pSt->getNumTop(); i++)
		cout << *pSt->getElem(i)<<" ";
}
TEST(function, polish_notation3)
{
	List <Lexeme*> l;
	string s = "(10+2)*3/2+3*(-1+21)";
	int len = NewRead(s, l);
	Stack<Lexeme*> *pSt = GetPolishNotation(l, len);
	for (int i = 0; i <= pSt->getNumTop(); i++)
		cout << *pSt->getElem(i)<<" ";
}
TEST(function, get_answer1)
{
	List <Lexeme*> l;
	string s = "(1+2)*3";
	int len = NewRead(s, l);
	Stack<Lexeme*> *pSt = GetPolishNotation(l, len);
	EXPECT_EQ(9, GetAnswer(pSt));
}
TEST(function, get_answer2)
{
	List <Lexeme*> l;
	string s = "(8+2*5)/(1+3*2-4)";
	int len = NewRead(s, l);
	Stack<Lexeme*> *pSt = GetPolishNotation(l, len);
	EXPECT_EQ(6, GetAnswer(pSt));
}
TEST(function, get_answer3)
{
	List <Lexeme*> l;
	string s = "((-7)+12*(2+1))/29+(-1)";
	int len = NewRead(s, l);
	Stack<Lexeme*> *pSt = GetPolishNotation(l, len);
	EXPECT_EQ(0, GetAnswer(pSt));
}
TEST(function, get_answer4)
{
	List <Lexeme*> l;
	string s = "-13*(-1)*((1-1)-(-10+11+6+(-2+1)*3*2))";
	int len = NewRead(s, l);
	Stack<Lexeme*> *pSt = GetPolishNotation(l, len);
	EXPECT_EQ(-13, GetAnswer(pSt));
}
TEST(function, get_answer5)
{
	List <Lexeme*> l;
	string s = "2*(3.14+0.86)";
	int len = NewRead(s, l);
	Stack<Lexeme*> *pSt = GetPolishNotation(l, len);
	EXPECT_EQ(8, GetAnswer(pSt));
}
TEST(function, get_answer6)
{
	List <Lexeme*> l;
	string s = "(cos(3.14))^2+(sin(3.14))^2";
	int len = NewRead(s, l);
	Stack<Lexeme*> *pSt = GetPolishNotation(l, len);
	EXPECT_TRUE(abs(1-GetAnswer(pSt))<0.000001 );

}
TEST(fuction, newRead)
{
	List <Lexeme*> l;
	string s = "3.14 1";
	double val;
	for (int i = 0; i < s.size(); i++)
	{
		if (num  == GetReadStatus(&s[i], i, s.size()))
		{
			//считали число
			char *p1 = &s[i], *p2 = p1;
			val = strtod(p1, &p2);
			//создали лексему с этим числом
			Lexeme *pL = new LexemeNum(string(p1, p2), number, val);
			l.push_front(pL);
			//сдвинули i
			i = i + (p2 - p1);
		}
		else i++;
	}
	EXPECT_EQ(1, l.quick_pop_front()->getVal());
	EXPECT_EQ(3.14, l.quick_pop_front()->getVal());
}