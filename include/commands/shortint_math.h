#if !defined(VM_SHORT_INT_MATH_HH)
#define VM_SHORT_INT_MATH_HH

#include "base_command_handler.h"

class adds_command_handler : public command_handler
{
public:
    adds_command_handler(memory& m, state& s,int sz):command_handler(m,s,sz){}
    ~adds_command_handler(){}
    void execute(command comm)
    {
        comm = comm;
         s.reg[comm.c16.a3] = s.reg[comm.c16.a1] + s.reg[comm.c16.a2];
    }
};

class subs_command_handler : public command_handler
{
public:
    subs_command_handler(memory& m, state& s,int sz):command_handler(m,s,sz){}
    ~subs_command_handler(){}
    void execute(command comm)
    {
        comm = comm;
        s.reg[comm.c16.a3] = s.reg[comm.c16.a1] - s.reg[comm.c16.a2];
    }
};

class muls_command_handler : public command_handler
{
public:
    muls_command_handler(memory& m, state& s,int sz):command_handler(m,s,sz){}
    ~muls_command_handler(){}
    void execute(command comm)
    {
        comm = comm;
        s.reg[comm.c16.a3] = s.reg[comm.c16.a1] * s.reg[comm.c16.a2];
    }
};

class divs_command_handler : public command_handler
{
public:
    divs_command_handler(memory& m, state& s,int sz):command_handler(m,s,sz){}
    ~divs_command_handler(){}
    void execute(command comm)
    {
        comm = comm;
        s.reg[comm.c16.a3] = s.reg[comm.c16.a1] / s.reg[comm.c16.a2];
    }
};

#endif // VM_SHORT_INT_MATH_HH
