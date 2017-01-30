#include "../../gtest/gtest.h"
#include "../../includes/lexeme.h"

TEST(lexeme, can_create)
{
	Lexeme l('1',number);
}

TEST(lexeme, lexemes_name_is_saved)
{
	Lexeme l1("(", left_brackets), l2(')', right_brackets);
	EXPECT_EQ(l1.getName(), "(");
	EXPECT_EQ(l2.getName(), ")");
}


TEST(lexeme, num_lexemes_name_is_saved)
{
	LexemeNum l1("13", num, 13), l2('2', num, 2);
	EXPECT_EQ(l1.getName(), "13");
	EXPECT_EQ(l2.getName(), "2");
}

TEST(lexeme, p_lexemes_name_is_saved)
{
	Lexeme *l1 = new LexemeOper('(', right_brackets);

	EXPECT_EQ(l1->getName(), "(");
}