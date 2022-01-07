#if !defined(RPN_H)
#define RPN_H

#include "token.h"
#include "math_expression_member.h"
#include "expressions.h"
#include <stdexcept>

class rpn
{
private:
    static bool is_operator(token t)
    {
        return t.type == token_type::plus or t.type == token_type::minus or
                 t.type == token_type::multiply or t.type == token_type::divide;
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
            if(current.type == token_type::left_round_brace)
            {
                    cultivator.push(current);
            }else if(current.type == token_type::right_round_brace)
            {
                while (cultivator.top().type != token_type::left_round_brace)
                {
                    math_expression_member mem;
                    mem.value = cultivator.top();
                    if(cultivator.top().type == token_type::number)
                    {
                            mem.type = math_expression_member_type::number;
                    }else if(cultivator.top().type == token_type::ident)
                    {
                        if(register_expression::is_register(cultivator.top()))
                        {
                            mem.type = math_expression_member_type::reg;
                        }else
                            mem.type = math_expression_member_type::label;
                    }else if(is_operator(cultivator.top()))
                    {
                        mem.type = math_expression_member_type::op;
                    }else
                    {
                        throw std::logic_error("Неизвестное выражение: " + cultivator.top().value);
                    }
                    translated.push_back(mem);
                    cultivator.pop();
                }
                cultivator.pop();
            }else if(is_operator(current))
            {
                while (priority(current) < priority(cultivator.top()))
                {
                    math_expression_member mem;
                    mem.value = cultivator.top();
                    mem.type = math_expression_member_type::op;
                    translated.push_back(mem);
                    cultivator.pop();
                }
                cultivator.push(current);
            }
        }
        
        while (!cultivator.empty())
        {
            math_expression_member mem;
            mem.value = cultivator.top();
            mem.type = math_expression_member_type::op;
            translated.push_back(mem);
            cultivator.pop();
        }
        
    }
};


#endif // RPN_H
