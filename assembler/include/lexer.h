#if !defined(LEXER_H)
#define LEXER_H

#include "token.h"
#include "expressions.h"
#include <stack>
#include <map>
#include <functional>


typedef int state_type;

typedef std::function<state_type(symbol_provider&, std::stack<expression*>&,std::stack<state_type>&)> rule;

class parser
{
private:
    state_type current_state = 0;
    std::stack<expression*> expr_st;
    std::stack<state_type> state_st;
    symbol_provider line;
    std::map<state_type,rule> relation;
public:
    parser(std::vector<token> line):line(line){};
    std::vector<command_expression*> parse()
    {
        while (current_state != 277013)
            current_state = relation[current_state](line,expr_st,state_st);
        command_expression** end   = (command_expression**)&expr_st.top() + 1;
        command_expression** begin = end - expr_st.size();
        return std::vector<command_expression*>(begin, end);
    }
};


#endif // LEXER_H