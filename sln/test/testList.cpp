#include "../../gtest/gtest.h"
#include "../../includes/list.h"
#include "../../includes/lexeme.h"
#include "../../includes/smart_pointer.h"
TEST(list, canPush)
{
	List <int>l;
	EXPECT_NO_THROW(l.push_front(1));
}
TEST(list, canPop)
{
	List <int>l;
	l.push_front(1);
	EXPECT_NO_THROW(l.quick_pop_front());
}
TEST(list, safely_pop)
{
	List <int>l;
	for (int i = 0; i < 10; i++)
		l.push_front(i);
	while (!l.isEmpty())
		EXPECT_NO_THROW(l.quick_pop_front());
}
TEST(list, workingVirtual)
{
	List <Lexeme*>list;
	Lexeme *ar[4];
	EXPECT_NO_THROW(list.push_front(&LexemeNum("14", number, 14)));
	EXPECT_NO_THROW(list.push_front(&BinaryOper('+', binary_oper)));
	Lexeme *p = list.quick_pop_front();
	EXPECT_EQ(p->getPriority(), low);
	p = list.quick_pop_front();
	EXPECT_EQ(p->getPriority(), -1);
}
TEST(list, nameIsWork)
{
	List <SmartPtr<Lexeme>>l;
	SmartPtr<Lexeme> p = new Lexeme('9', number);
	l.push_front(p);
	EXPECT_EQ(l.quick_pop_front()->getName(), "9");
}
TEST(list, p_lexemes_name_is_saved_in_list)
{
	Lexeme *l1 = new LexemeOper('(', left_brackets);
	List <Lexeme*> l;
	l.push_front(l1);

	EXPECT_EQ(l.quick_pop_front()->getName(), "(");
}

TEST(list, reverce)
{
	List <int>l;
	for (int i = 0; i < 10; i++)
		l.push_front(i);
	l.reverce();
	for (int i = 0; i< 10; i++)
		EXPECT_EQ(l.quick_pop_front(), i);
}