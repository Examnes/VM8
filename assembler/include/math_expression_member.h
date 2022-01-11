#if !defined(MATH_EXPRESSION_MEMBER_H)
#define MATH_EXPRESSION_MEMBER_H

#include "token.h"

enum class math_expression_member_type
{
    reg,
    label,
    number,
    op
};

enum class math_operation_type
{
    add = token_type::plus,
    sub = token_type::minus,
    mul = token_type::multiply,
    div = token_type::divide,
    error
};

struct math_expression_member
{
    math_expression_member_type type;
    float int_value;
    std::string str_value;
    math_operation_type op_value;
    math_expression_member(int a)
    {
        int_value = a;
        type = math_expression_member_type::number;
    }
    math_expression_member() = default;
};

#endif // MATH_EXPRESSION_MEMBER_H
