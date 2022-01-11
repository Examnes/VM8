#if !defined(VALIDATOR_H)
#define VALIDATOR_H

#include "expressions.h"
#include "types.h"
#include "rpn.h"

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
        c.c32.cop = cmd.mnemonic->opcode;
        c.c32.a1 = cmd.arg1->to_register()->register_id;
        c.c32.a2 = cmd.arg2->to_register()->register_id;
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
        c.c32.cop = cmd.mnemonic->opcode;
        c.c32.a1 = cmd.arg1->to_register()->register_id;
        c.c32.a2 = cmd.arg2->to_register()->register_id;
        c.c32.a3 = cmd.arg3->to_register()->register_id;
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
        c.c32.cop = cmd.mnemonic->opcode;
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
            math_expression* e = cmd.arg1->to_math();
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
            arg = cmd.arg1->to_math()->members.back().str_value;
            indirect = true;
        }
        if(symbols.count(arg))
        {
            c.c24.addr = symbols[arg];
            address_created = true;
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
                    m.type == math_expression_member_type::number or
                    m.type == math_expression_member_type::op;}))
            {
                cmd.type = command_type::command16;
                return true;
            }
        }
        return false;
    }

    std::vector<uint8_t> evaluate(command_expression& cmd, std::map<std::string, uint16_t>& symbols)
    {
        std::vector<uint8_t> res;
        command c;
        c.c32.cop = cmd.mnemonic->opcode;
        uint8_t rel = 0;
        if(cmd.arg1->type == expression_type::number)
        {
            rel = cmd.arg1->to_number()->number_value;
        }else
        {
            rel = rpn::evaluate(cmd.arg1->to_math()->members, symbols);
        }
        c.c32.a3 = rel & (0b111);
        rel = rel >> 3;
        c.c32.a2 = rel & (0b111);
        rel = rel >> 3;
        c.c32.a1 = rel & (0b111);

        res.push_back(c.parts[0]);
        res.push_back(c.parts[1]);
        return res;
    }
};

struct mathw_v : validator
{
    bool set_size(command_expression& cmd)
    {
        if (cmd.arg1->type == expression_type::math and cmd.arg1->type == expression_type::math)
        {
            if (cmd.arg1->to_math()->members.size() == 1 and cmd.arg2->to_math()->members.size() == 3)
            {
                if (cmd.arg1->to_math()->members.back().type == math_expression_member_type::reg and 
                    cmd.arg2->to_math()->members[0].type == math_expression_member_type::reg and
                    cmd.arg2->to_math()->members[1].type == math_expression_member_type::reg and
                    cmd.arg2->to_math()->members[2].type == math_expression_member_type::op)
                {
                    cmd.type = command_type::command16;
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
        c.c32.cop = cmd.mnemonic->opcode;

        c.c32.a1 = cmd.arg1->to_math()->members.back().int_value;
        c.c32.a2 = cmd.arg2->to_math()->members[0].int_value;
        c.c32.a3 = cmd.arg2->to_math()->members[1].int_value;
        
        res.push_back(c.parts[0]);
        res.push_back(c.parts[1]);
        
        return res;
    }
};

struct jmplr_v : validator
{
    bool set_size(command_expression& cmd)
    {
        cmd.type = command_type::command32;
        if (cmd.arg1->type == expression_type::identifier)
        {
            if (cmd.arg1->to_identifier()->value.value != "indirect" and cmd.arg1->to_identifier()->value.value != "direct")
            {
                return false;
            }
        }
        
        if((cmd.arg2->type == expression_type::reg or cmd.arg2->type == expression_type::identifier))
        {
            if (cmd.arg3)
            {
                if ((cmd.arg2->type == expression_type::reg and cmd.arg3->type == expression_type::identifier) or
                (cmd.arg3->type == expression_type::reg and cmd.arg2->type == expression_type::identifier))
                {
                    return true;
                }
                return false;
            }
            return true;
        }
        return false;
    }

    std::vector<uint8_t> evaluate(command_expression& cmd, std::map<std::string, uint16_t>& symbols)
    {
        std::vector<uint8_t> res;
        command c;
        c.c24.cop = cmd.mnemonic->opcode;
        bool indirect = cmd.arg1->to_identifier()->value.value == "indirect";
        bool relative = cmd.arg3;
        if (cmd.arg2->type == expression_type::reg)
        {
            c.c32.a2 = cmd.arg2->to_register()->register_id;
        }else
        {
            if (symbols.count(cmd.arg2->value.value))
            {
                c.c32.addr = symbols[cmd.arg2->value.value];
                address_created = true;
            }
        }
        
        if (relative)
        {
            if (cmd.arg3->type == expression_type::reg)
            {
                c.c32.a2 = cmd.arg3->to_register()->register_id;
            }else
            {
                if (symbols.count(cmd.arg3->value.value))
                {
                    c.c32.addr = symbols[cmd.arg3->value.value];
                    address_created = true;
                }
            }
            c.c32.a1 |= 0b010;
        }

        if (indirect)
        {
            c.c32.a1 |= 0b100;
        }
    
        res.push_back(c.parts[0]);
        res.push_back(c.parts[1]);
        res.push_back(c.parts[2]);
        res.push_back(c.parts[3]);
        
        return res;
    }
};

struct mov_v : validator
{
    bool set_size(command_expression& cmd)
    {
        if (cmd.arg1->type == expression_type::reg)
        {
            if (cmd.arg3)
            {
                if ((cmd.arg2->type == expression_type::reg and cmd.arg3->type == expression_type::identifier) or
                (cmd.arg3->type == expression_type::reg and cmd.arg2->type == expression_type::identifier))
                {
                    cmd.type = command_type::command32;
                    return true;
                }
                return false;
            }else
            {
                if (cmd.arg2->type == expression_type::reg)
                {
                    cmd.type = command_type::command16;
                    return true;
                }
                if (cmd.arg2->type == expression_type::identifier)
                {
                    cmd.type = command_type::command32;
                    return true;
                }
                return false;
            }
        }
        return false;
    }

    std::vector<uint8_t> evaluate(command_expression& cmd, std::map<std::string, uint16_t>& symbols)
    {
        std::vector<uint8_t> res;
        command c;
        c.c32.cop = cmd.mnemonic->opcode;
        c.c32.a2 = cmd.arg1->to_register()->register_id;
        bool register_exist = false;
        bool address_exist = false;
        if (cmd.arg2->type == expression_type::reg)
        {
            c.c32.a3 = cmd.arg2->to_register()->register_id;
            register_exist = true;
        }else
        {
            if (symbols.count(cmd.arg2->to_identifier()->value.value))
            {
                c.c32.addr = symbols[cmd.arg2->to_identifier()->value.value];
                address_exist = true;
                address_created = true;
            }
        }

        if (cmd.arg3)
        {
            if (cmd.arg3->type == expression_type::reg)
            {
                c.c32.a3 = cmd.arg3->to_register()->register_id;
                register_exist = true;
            }else
            {
                if (symbols.count(cmd.arg3->to_identifier()->value.value))
                {
                    c.c32.addr = symbols[cmd.arg3->to_identifier()->value.value];
                    address_exist = true;
                    address_created = true;
                }
            }
        }
        
        res.push_back(c.parts[0]);
        res.push_back(c.parts[1]);
        if (address_exist and !register_exist)
        {
            c.c32.a1 = inderect;
            res.push_back(c.parts[2]);
            res.push_back(c.parts[3]);
        }else if(!address_exist and register_exist)
        {
            c.c32.a1 = direct;
        }else
        {
            c.c32.a1 = relative;
            res.push_back(c.parts[2]);
            res.push_back(c.parts[3]);
        }
        return res;
    }
};


struct float_data_v : validator
{
    bool set_size(command_expression& cmd)
    {
        cmd.type = command_type::command32;
        if (cmd.arg1->type == expression_type::number)
        {
            return true;
        }
        return false;
    }

    std::vector<uint8_t> evaluate(command_expression& cmd, std::map<std::string, uint16_t>& symbols)
    {
        std::vector<uint8_t> res;
        converter cov;
        cov.floating = cmd.arg1->to_number()->number_value;
        res.push_back(cov.data[0]);
        res.push_back(cov.data[1]);
        res.push_back(cov.data[2]);
        res.push_back(cov.data[3]);
        return res;
    }
};

struct fld_v : validator
{
    bool set_size(command_expression& cmd)
    {
        cmd.type = command_type::command32;
        if (cmd.arg1->type == expression_type::math)
        {
            return true;
        }
        return false;
    }

    std::vector<uint8_t> evaluate(command_expression& cmd, std::map<std::string, uint16_t>& symbols)
    {
        std::vector<uint8_t> res;
        command c;
        c.c32.cop = cmd.mnemonic->opcode;
        uint16_t rel = 0;
        rel = rpn::evaluate(cmd.arg1->to_math()->members, symbols);
        c.c32.addr = rel;
        auto fres = std::find_if(cmd.arg1->to_math()->members.begin(),
        cmd.arg1->to_math()->members.end(),
        [](math_expression_member m){return m.type == math_expression_member_type::reg;});
        if (fres != cmd.arg1->to_math()->members.end())
        {
            c.c32.a2 = fres->int_value;
            c.c32.a1 = 0b001;
        }
        address_created = true;
        res.push_back(c.parts[0]);
        res.push_back(c.parts[1]);
        res.push_back(c.parts[2]);
        res.push_back(c.parts[3]);
        
        return res;
    }
};

#endif // VALIDATOR_H
