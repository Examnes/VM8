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
        std::cin >> conv.floating;
        m[s.sp--] = conv.data[3];
        m[s.sp--] = conv.data[2];
        m[s.sp--] = conv.data[1];
        m[s.sp--] = conv.data[0];
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
        conv.data[0] = m[s.sp++];
        conv.data[1] = m[s.sp++];
        conv.data[2] = m[s.sp++];
        conv.data[3] = m[s.sp++];
        std::cout << conv.floating;
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
