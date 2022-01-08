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


#endif // VALIDATOR_H
