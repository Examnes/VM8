#if !defined(EXPRESSIONS_H)
#define EXPRESSIONS_H

#include "token.h"
#include "metadata_provider.h"
#include "math_expression_member.h"

enum class expression_type
{
    unspecified,
    reg,
    number,
    identifier,
    math,
    mnemonic,
    command
};

struct expression
{
    expression_type type;
    token value;
    expression(token value, expression_type type = expression_type::unspecified): type(type),value(value){}
};

struct register_expression : expression
{
    int register_id;
    register_expression(token t): expression(t, expression_type::reg)
    {
        register_id = metadata_provider::register_ids[t.value];
    }

    static bool is_register(token t)
    {
        return metadata_provider::register_ids.count(t.value);
    }
};

struct number_expression : expression
{
    int number_value;
    number_expression(token t): expression(t, expression_type::number)
    {
        number_value = std::stoi(t.value);
    }
};

struct identifier_expression : expression
{
    identifier_expression(token t): expression(t, expression_type::identifier){}
};

struct mnemonic_expression : expression
{
    int opcode;
    mnemonic_expression(token t): expression(t, expression_type::mnemonic)
    {
        opcode = metadata_provider::opcode_ids[t.value];
    }

    static bool is_opcode(token t)
    {
        return metadata_provider::opcode_ids.count(t.value);
    }
};

struct math_expression : expression
{
    std::vector<math_expression_member> members;
    math_expression(std::vector<math_expression_member> members): expression(token(), expression_type::mnemonic), members(members){}
};

enum class command_type
{
    no_command = 0,
    commnad8,
    command16,
    command24,
    command32
};

struct command_expression : expression
{
    expression* label;
    expression* mnemonic;
    expression* arg1;
    expression* arg2;
    expression* arg3;
    command_type type;
    command_expression(): expression(token(), expression_type::command){}
};


#endif // EXPRESSIONS_H
