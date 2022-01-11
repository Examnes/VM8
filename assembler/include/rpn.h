#if !defined(RPN_H)
#define RPN_H

#include "token.h"
#include "math_expression_member.h"
#include "expressions.h"
#include <stdexcept>

class rpn
{
private:
    static math_operation_type get_operator(token t)
    {
        if (t.type == token_type::plus or t.type == token_type::minus or
                 t.type == token_type::multiply or t.type == token_type::divide)
        return (math_operation_type)t.type;
        return math_operation_type::error;
    }

    static int priority(token t)
    {
        if (t.type == token_type::plus or t.type == token_type::minus)
            return 1;
        if(t.type == token_type::multiply or t.type == token_type::divide)
            return 2;
        return 0;
    }

public:
    std::vector<math_expression_member> translated;
    rpn(symbol_provider& s, token stop)
    {
        std::stack<token> cultivator;
        token current = s.get_next();
        while (current.type != stop.type)
        {
            if (current.type == token_type::number)
            {
                math_expression_member mem;
                mem.type = math_expression_member_type::number;
                mem.int_value = std::stoi(current.value);
                translated.push_back(mem);
            }

            if (current.type == token_type::ident)
            {
                math_expression_member mem;
                if(register_expression::is_register(current))
                {
                    mem.type = math_expression_member_type::reg;
                }else
                    mem.type = math_expression_member_type::label;
                mem.str_value = current.value;
                translated.push_back(mem);
            }
            
            
            if(current.type == token_type::left_round_brace)
            {
                cultivator.push(current);
            }else if(current.type == token_type::right_round_brace)
            {
                while (cultivator.top().type != token_type::left_round_brace)
                {
                    math_expression_member mem;
                    
                    if(cultivator.top().type == token_type::number)
                    {
                        mem.type = math_expression_member_type::number;
                        mem.int_value = std::stoi(cultivator.top().value);
                    }else if(cultivator.top().type == token_type::ident)
                    {
                        if(register_expression::is_register(cultivator.top()))
                        {
                            mem.type = math_expression_member_type::reg;
                            mem.int_value = metadata_provider::register_ids[cultivator.top().value];
                        }else
                        {
                            mem.type = math_expression_member_type::label;
                            
                        }
                        mem.str_value = cultivator.top().value;
                    }else if(get_operator(cultivator.top()) != math_operation_type::error)
                    {
                        mem.type = math_expression_member_type::op;
                        mem.op_value = get_operator(cultivator.top());
                    }else
                    {
                        throw std::logic_error("Неизвестное выражение: " + cultivator.top().value);
                    }
                    translated.push_back(mem);
                    cultivator.pop();
                }
                cultivator.pop();
            }else if(get_operator(current) != math_operation_type::error)
            {
                if (!cultivator.empty())
                    while (priority(current) < priority(cultivator.top()))
                    {
                        math_expression_member mem;
                        mem.op_value = get_operator(cultivator.top());
                        mem.type = math_expression_member_type::op;
                        translated.push_back(mem);
                        cultivator.pop();
                    }
                cultivator.push(current);
            }
            current = s.get_next();
        }
        
        while (!cultivator.empty())
        {
            math_expression_member mem;
            mem.op_value = get_operator(cultivator.top());
            mem.type = math_expression_member_type::op;
            translated.push_back(mem);
            cultivator.pop();
        }
        
    }
    static int evaluate(std::vector<math_expression_member> members, std::map<std::string, uint16_t>& symbols)
    {
        std::stack<math_expression_member> cultivator;
        std::reverse(members.begin(),members.end());
        math_expression_member current = members.back(); members.pop_back();
        while (!members.empty())
        {
            if(current.type != math_expression_member_type::op)
            {
                cultivator.push(current);
            }else
            {
                math_expression_member arg1,arg2;
                arg1 = cultivator.top(); cultivator.pop();
                arg2 = cultivator.top(); cultivator.pop();
                int val1,val2;
                if(arg1.type == math_expression_member_type::number)
                    val1 = arg1.int_value;
                if(arg1.type == math_expression_member_type::reg)
                    val1 = 0;
                if(arg1.type == math_expression_member_type::label)
                {
                    if (symbols.count(arg1.str_value))
                    {
                        val1 = symbols[arg1.str_value];
                    }
                }

                if(arg2.type == math_expression_member_type::number)
                    val2 = arg2.int_value;
                if(arg2.type == math_expression_member_type::reg)
                    val2 = 0;
                if(arg2.type == math_expression_member_type::label)
                {
                    if (symbols.count(arg2.str_value))
                    {
                        val2 = symbols[arg2.str_value];
                    }
                }

                switch(current.op_value)
                {
                    case math_operation_type::add :
                        cultivator.push(math_expression_member(val1 + val2));
                        break;
                    case math_operation_type::sub :
                        cultivator.push(math_expression_member(val1 - val2));
                        break;
                    case math_operation_type::div :
                        cultivator.push(math_expression_member(val1 / val2));
                        break;
                    case math_operation_type::mul :
                        cultivator.push(math_expression_member(val1 * val2));
                        break;
                    default:
                        break;
                };
            }
            current = members.back(); members.pop_back();
        }
        return cultivator.top().int_value;
    }
};


#endif // RPN_H
