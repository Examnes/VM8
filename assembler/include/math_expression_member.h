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

struct math_expression_member
{
    token value;
    math_expression_member_type type;
};

#endif // MATH_EXPRESSION_MEMBER_H
