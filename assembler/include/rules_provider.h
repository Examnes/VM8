#if !defined(RULES_PROVIDER_HH)
#define RULES_PROVIDER_HH

typedef int state_type;
typedef std::function<state_type(symbol_provider&, std::stack<expression*>&,std::stack<state_type>&)> rule;
#include "rpn.h"

class rules_provider
{
public:
    static std::map<state_type,rule> get_rules()
    {
        std::map<state_type,rule> m;
        m.insert({1,
            [](symbol_provider& sp ,std::stack<expression*>& expr,std::stack<state_type>& st)
            {
                expr.push(new expression(sp.get_next()));
                st.push(1);
                if (expr.top()->value.type == token_type::ident)
                {
                    if(mnemonic_expression::is_opcode(expr.top()->value))
                        return 4;
                    return 2;
                }

                if (expr.top()->value.type == token_type::newline)
                    return 17;

                if (expr.top()->value.type == token_type::ending)
                    return 277013;
                
                return 0;
            }
        });

        m.insert({2,
            [](symbol_provider& sp ,std::stack<expression*>& expr,std::stack<state_type>& st)
            {
                expression* t = expr.top();
                expr.pop();
                expr.push(new identifier_expression(t->value));
                expr.push(new expression(sp.get_next()));
                st.push(2);
                if (expr.top()->value.type == token_type::colon)
                    return 3;
                return 0;
            }
        });

        m.insert({3,
            [](symbol_provider& sp ,std::stack<expression*>& expr,std::stack<state_type>& st)
            {
                expr.pop();
                expr.push(new expression(sp.get_next()));
                st.push(3);
                if(mnemonic_expression::is_opcode(expr.top()->value))
                    return 4;
                if (expr.top()->value.type == token_type::newline)
                    return 11;
                return 0;
            }
        });

        m.insert({4,
            [](symbol_provider& sp ,std::stack<expression*>& expr,std::stack<state_type>& st)
            {
                expression* t = expr.top();
                expr.pop();
                expr.push(new mnemonic_expression(t->value));
                return 5;
            }
        });

        m.insert({5,
            [](symbol_provider& sp ,std::stack<expression*>& expr,std::stack<state_type>& st)
            {
                if (expr.top()->value.type == token_type::left_brace)
                    return 6;
                if (expr.top()->value.type == token_type::number)
                    return 7;
                if (expr.top()->value.type == token_type::ident)
                {
                    expression* e = expr.top();
                    expr.pop();
                    if(register_expression::is_register(expr.top()->value))
                    {
                        expr.push(new register_expression(e->value));
                    }else
                        expr.push(new identifier_expression(e->value));
                    return 7;
                }
                return 0;
            }
        });

        m.insert({6,
            [](symbol_provider& sp ,std::stack<expression*>& expr,std::stack<state_type>& st)
            {
                expr.pop();
                rpn r = rpn(sp,token({"]",token_type::right_brace}));
                expr.push(new math_expression(r.translated));
                return 7;
            }
        });


        m.insert({7,
            [](symbol_provider& sp ,std::stack<expression*>& expr,std::stack<state_type>& st)
            {
                if (expr.top()->value.type == token_type::newline)
                    return 11;
                if (st.top() == 4)
                    return 8;
                if (st.top() == 9)
                    return 10;
                if (st.top() == 8)
                    return 9;
                if (st.top() == 10)
                    return 11;
                return 0;
            }
        });

        m.insert({8,
            [](symbol_provider& sp ,std::stack<expression*>& expr,std::stack<state_type>& st)
            {
                expr.push(new expression(sp.get_next()));
                st.push(8);
                return 5;
            }
        });

        m.insert({9,
            [](symbol_provider& sp ,std::stack<expression*>& expr,std::stack<state_type>& st)
            {
                expr.push(new expression(sp.get_next()));
                st.push(9);
                return 5;
            }
        });

        m.insert({10,
            [](symbol_provider& sp ,std::stack<expression*>& expr,std::stack<state_type>& st)
            {
                expr.push(new expression(sp.get_next()));
                st.push(10);
                return 5;
            }
        });

        m.insert({11,
            [](symbol_provider& sp ,std::stack<expression*>& expr,std::stack<state_type>& st)
            {
                expr.push(new command_expression());
                if(st.top() == 8)
                    return 14;
                if(st.top() == 10)
                    return 12;
                if(st.top() == 9)
                    return 13;
                if(st.top() == 3)
                    return 16;
                return 0;
            }
        });

        m.insert({12,
            [](symbol_provider& sp ,std::stack<expression*>& expr,std::stack<state_type>& st)
            {
                command_expression* ce = (command_expression*) expr.top();
                expr.pop();
                ce->arg3 = expr.top();
                expr.pop();
                expr.push(ce);
                st.pop();
                return 13;
            }
        });

        m.insert({13,
            [](symbol_provider& sp ,std::stack<expression*>& expr,std::stack<state_type>& st)
            {
                command_expression* ce = (command_expression*) expr.top();
                expr.pop();
                ce->arg2 = expr.top();
                expr.pop();
                expr.push(ce);
                st.pop();
                return 14;
            }
        });

        m.insert({14,
            [](symbol_provider& sp ,std::stack<expression*>& expr,std::stack<state_type>& st)
            {
                command_expression* ce = (command_expression*) expr.top();
                expr.pop();
                ce->arg1 = expr.top();
                expr.pop();
                expr.push(ce);
                st.pop();
                return 15;
            }
        });

        m.insert({15,
            [](symbol_provider& sp ,std::stack<expression*>& expr,std::stack<state_type>& st)
            {
                command_expression* ce = (command_expression*) expr.top();
                expr.pop();
                ce->mnemonic = (mnemonic_expression*)expr.top();
                expr.pop();
                expr.push(ce);
                st.pop();
                if(st.top() == 3)
                    return 16;
                return 17;
            }
        });
        m.insert({16,
            [](symbol_provider& sp ,std::stack<expression*>& expr,std::stack<state_type>& st)
            {
                command_expression* ce = (command_expression*) expr.top();
                expr.pop();
                ce->label = (identifier_expression*)expr.top();
                expr.pop();
                expr.push(ce);
                st.pop();
                return 17;
            }
        });

        m.insert({17,
            [](symbol_provider& sp ,std::stack<expression*>& expr,std::stack<state_type>& st)
            {
                while(!expr.empty())
                    expr.pop();
                while(!st.empty())
                    st.pop();
                return 1;
            }
        });

        return m;
    }
};



#endif // RULES_PROVIDER_HH
