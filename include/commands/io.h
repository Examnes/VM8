#if !defined(VM_IO_H)
#define VM_IO_H

#include "base_command_handler.h"
#include "types.h"
#include <iostream>

class in_command_handler : public command_handler
{
public:
    in_command_handler(memory &m, state &s, int sz) : command_handler(m, s, sz) {}
    ~in_command_handler() {}
    void execute(command comm)
    {
        converter conv;
        bool is_float = comm.c16.a1 & 1;
        bool is_inderect = comm.c16.a1 & 2;
        bool is_wide = comm.c16.a1 & 4;

        if (is_float)
        {
            std::cin >> conv.floating;
        }
        else
        {
            if (is_wide)
            {
                std::cin >> conv.wide_signed;
            }
            else
            {
                std::cin >> conv.short_signed[0];
            }
        }

        if (is_float || is_wide)
        {
            m[s.reg[comm.c16.a2] + is_inderect ? s.reg[comm.c16.a3] : 0] = conv.data[0];
            m[s.reg[comm.c16.a2] + is_inderect ? s.reg[comm.c16.a3] : 0 + 1] = conv.data[1];
        }
        else
        {
            m[s.reg[comm.c16.a2] + is_inderect ? s.reg[comm.c16.a3] : 0] = conv.data[0];
        }
    }
};

class out_command_handler : public command_handler
{
public:
    out_command_handler(memory &m, state &s, int sz) : command_handler(m, s, sz) {}
    ~out_command_handler() {}
    void execute(command comm)
    {
        converter conv;
        bool is_float = comm.c16.a1 & 1;
        bool is_inderect = comm.c16.a1 & 2;
        bool is_wide = comm.c16.a1 & 4;

        if (is_float || is_wide)
        {
            conv.data[0] = m[s.reg[comm.c16.a2] + is_inderect ? s.reg[comm.c16.a3] : 0];
            conv.data[1] = m[s.reg[comm.c16.a2] + is_inderect ? s.reg[comm.c16.a3] : 0 + 1];
        }
        else
        {
            conv.data[0] = m[s.reg[comm.c16.a2] + is_inderect ? s.reg[comm.c16.a3] : 0];
        }

        if (is_float)
        {
            std::cout << conv.floating;
        }
        else
        {
            if (is_wide)
            {
                std::cout << conv.wide_signed;
            }
            else
            {
                std::cout << conv.short_signed[0];
            }
        }
    }
};

class print_command_handler : public command_handler
{
public:
    print_command_handler(memory &m, state &s, int sz) : command_handler(m, s, sz) {}
    ~print_command_handler() {}
    void execute(command comm)
    {
        std::cout << reinterpret_cast<char *>(&m[s.reg[comm.c16.a1]]);
    }
};

#endif // VM_IO_H
