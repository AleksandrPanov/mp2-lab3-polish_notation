#include "../../gtest/gtest.h"
#include "../../includes/stack.h"
#include "../../includes/lexeme.h"
TEST(stack, can_create_stack)
{
	EXPECT_NO_THROW(Stack <int>s(10));
}

TEST(stack, cannot_create_stack_with_negative_index)
{
	EXPECT_ANY_THROW(Stack <int>s(-1));
}

TEST(stack, cannot_pop_empty)
{
	Stack <int>s(0);
	EXPECT_ANY_THROW(s.pop());
}

TEST(stack, can_push)
{
	Stack <Lexeme>s(10);
	Lexeme l("1",number);
	EXPECT_NO_THROW(s.push(l));
}

TEST(stack, stack_is_empty)
{
	Stack <int>s(10);
	EXPECT_EQ(s.isEmty(), true);
}

TEST(stack, stack_is_full)
{
	Stack <int>s(0);
	EXPECT_EQ(s.isFull(), true);
}

TEST(stack, safe_push_working)
{
	Stack <Lexeme>s(1);
	Lexeme l('1', number);
	s.push(l);
	EXPECT_ANY_THROW(s.push(l));
}

TEST(stack, safe_pop_working)
{
	Stack <Lexeme>s(1);
	Lexeme l('1', number);
	s.push(l);
	s.pop();	
	EXPECT_ANY_THROW(s.pop());
}

TEST(stack, can_pop)
{
	Stack <LexemeNum>s(9);
	LexemeNum l[10];
	char str[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
	for (int i = 0; i < 10; i++)
		l[i] = LexemeNum(str, number, i);
	int i = 0;
	while (!s.isFull())
	{
		ASSERT_NO_THROW(s.quickPush(l[i]));
		i++;
	}

	i = 8;
	while (!s.isEmty())
	{
		ASSERT_EQ(s.quickPop() == i, true);
		i--;
	}
}