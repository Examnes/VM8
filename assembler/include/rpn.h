#if !defined(RPN_H)
#define RPN_H

#include "token.h"

enum math_expression_member_type
{
    register,
    label,
    number,
    operator
};

struct math_expression_member
{
    token* value;
    math_expression_member_type type;
};

class rpn
{
public:
    std::vector<math_expression_member> translated;
    rpn(symbol_provider& s, token stop)
    {
        std::stack<token> cultivator;
        token current = s.get_next();
        while (current != stop)
        {
            if(current.type == token_type::left_round_brace)
                cultivator.push(current);
            if(current.type == token_type::right_round_brace)
            {
                while (cultivator.top().type != token_type::left_round_brace)
                {
                    math_expression_member mem;
                    mem.value = cultivator.top();
                    if(cultivator.top().type = number)
                        mem.type = math_expression_member_type::number;
                    
                    translated.push_back()
                }
                
            }
                cultivator.push(current)
        }
        
    }
};


#endif // RPN_H
