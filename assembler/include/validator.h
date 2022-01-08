#if !defined(VALIDATOR_H)
#define VALIDATOR_H

#include "expressions.h"
#include "types.h"

struct validator
{
    bool address_created = false;
    virtual bool set_size(command_expression& cmd) = 0;
    virtual std::vector<uint8_t> evaluate(command_expression& cmd, std::map<std::string, uint16_t>& symbols) = 0;
    validator() = default;
    virtual ~validator(){};
};

struct reg_reg : validator
{
    bool set_size(command_expression& cmd)
    {
        if(cmd.arg1->type == expression_type::reg and cmd.arg2->type == expression_type::reg)
        {
            cmd.type = command_type::command16;
            return true;
        }
        return false;
    }

    std::vector<uint8_t> evaluate(command_expression& cmd, std::map<std::string, uint16_t>& symbols)
    {
        std::vector<uint8_t> res;
        command c;
        c.c16.cop = cmd.mnemonic->opcode;
        c.c16.a1 = ((register_expression*)cmd.arg1)->register_id;
        c.c16.a2 = ((register_expression*)cmd.arg2)->register_id;
        res.push_back(c.parts[0]);
        res.push_back(c.parts[1]);
        return res;
    }
};

struct reg_reg_reg : validator
{
    bool set_size(command_expression& cmd)
    {
        if(cmd.arg1->type == expression_type::reg 
        and cmd.arg2->type == expression_type::reg
        and cmd.arg3->type == expression_type::reg)
        {
            cmd.type = command_type::command16;
            return true;
        }
        return false;
    }

    std::vector<uint8_t> evaluate(command_expression& cmd, std::map<std::string, uint16_t>& symbols)
    {
        std::vector<uint8_t> res;
        command c;
        c.c16.cop = cmd.mnemonic->opcode;
        c.c16.a1 = ((register_expression*)cmd.arg1)->register_id;
        c.c16.a2 = ((register_expression*)cmd.arg2)->register_id;
        c.c16.a3 = ((register_expression*)cmd.arg3)->register_id;
        res.push_back(c.parts[0]);
        res.push_back(c.parts[1]);
        return res;
    }
};

struct no_op : validator
{
    bool set_size(command_expression& cmd)
    {
        cmd.type = command_type::command8;
        return true;
    }

    std::vector<uint8_t> evaluate(command_expression& cmd, std::map<std::string, uint16_t>& symbols)
    {
        std::vector<uint8_t> res;
        command c;
        c.c8 = cmd.mnemonic->opcode;
        res.push_back(c.parts[0]);
        return res;
    }
};

struct jmpl_v : validator
{
    bool set_size(command_expression& cmd)
    {
        if(cmd.arg1->type == expression_type::identifier)
        {
            cmd.type = command_type::command24;
            return true;
        }
        if (cmd.arg1->type == expression_type::math)
        {
            math_expression* e = (math_expression*) cmd.arg1;
            if(e->members.size() == 1)
            {
                if(e->members.back().type == math_expression_member_type::label)
                {
                    cmd.type = command_type::command24;
                    return true;
                }
            }
        }
        
        return false;
    }

    std::vector<uint8_t> evaluate(command_expression& cmd, std::map<std::string, uint16_t>& symbols)
    {
        std::vector<uint8_t> res;
        command c;
        c.c24.cop = cmd.mnemonic->opcode;
        bool indirect = false;
        std::string arg = "";
        if (cmd.arg1->type != expression_type::math)
        {
            arg = cmd.arg1->value.value;
        }else
        {
            arg = ((math_expression*) cmd.arg1)->members.back().value.value;
            indirect = true;
        }
        if(symbols.count(arg))
        {
            c.c24.addr = symbols[arg];
        }
        c.c24.b = indirect;
        res.push_back(c.parts[0]);
        res.push_back(c.parts[2]);
        res.push_back(c.parts[3]);
        return res;
    }
};

struct jmpr_v : validator
{
    bool set_size(command_expression& cmd)
    {
        if(cmd.arg1->type == expression_type::number)
        {
            cmd.type = command_type::command16;
            return true;
        }
        if (cmd.arg1->type == expression_type::math)
        {
            math_expression* e = (math_expression*) cmd.arg1;
            if(std::all_of(e->members.begin(),e->members.end(),
                [](math_expression_member m){ return
                    m.type == math_expression_member_type::label or 
                    m.type == math_expression_member_type::number;}))
            {
                cmd.type = command_type::command16;
                return true;
            }
        }
    }

    std::vector<uint8_t> evaluate(command_expression& cmd, std::map<std::string, uint16_t>& symbols)
    {
        std::vector<uint8_t> res;
        command c;
        c.c16.cop = cmd.mnemonic->opcode;
        uint8_t rel = 0;
        if(cmd.arg1->type == expression_type::number)
        {
            rel = ((number_expression*)cmd.arg1)->number_value;
        }else
        {
            
        }
        res.push_back(c.parts[0]);
        return res;
    }
};


#endif // VALIDATOR_H
