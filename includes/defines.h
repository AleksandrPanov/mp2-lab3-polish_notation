#pragma once
//error of lexeme
#define UNKNOWN_TYPE 0

//error of stack
#define STACK_FULL 10
#define STACK_EMPTY 11
#define NEGATIVE_INDEX 12

//error read lexeme
#define ERROR_READ 20
#define ERROR_BRACKETS 21

enum types {binary_oper, unary_oper, number, left_brackets, right_brackets};
enum status { wait = right_brackets + 1, nextOp, nextEx, nextOpBin, binOp, unOp, binOpPost, leftB, rightB, num, var, error };
enum priority { lowest = error + 1, low, medium, high, highest};
enum status_read{ minus1 = highest + 1, funct};