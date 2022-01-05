#if !defined(EXPRESSIONS_H)
#define EXPRESSIONS_H

#include "token.h"
#include "metadata_provider.h"

enum expression_type
{
    unspecified,
    register,
    number,
    identifier,
    math,
    mnemonic,
    command
}

struct expression
{
    expression_type type;
    token value;
    expression(token value, expression_type type = expression_type::unspecified): type(type),value(value){}
}

struct register_expression : expression
{
    int register_id;
    register_expression(token t): expression(t, expression_type::register)
    {
        register_id = metadata_provider::register_ids[t.value];
    }

    static is_register(token t)
    {
        return metadata_provider::register_ids.contains(t.value);
    }
}

struct number_expression : expression
{
    int number_value;
    number_expression(token t): expression(t, expression_type::number)
    {
        number_value = std::stoi(t.value);
    }
}

struct identifier_expression : expression
{
    identifier_expression(token t): expression(t, expression_type::identifier){}
};

struct mnemonic_expression : expression
{
    int opcode;
    identifier_expression(token t): expression(t, expression_type::mnemonic)
    {
        opcode = metadata_provider::opcode_ids[t.value];
    }
    static is_opcode(token t)
    {
        return metadata_provider::opcode_ids.contains(t.value);
    }
};

struct math_expression : expression
{
    rpn members;
    math_expression(rpn members): expression(token(), expression_type::mnemonic), members(members){}
};

struct command_expression : expression
{
    expression* label;
    expression* mnemonic;
    expression* arg1;
    expression* arg2;
    expression* arg3;
    command_expression(): expression(token(), expression_type::command), members(members){}
};


#endif // EXPRESSIONS_H
