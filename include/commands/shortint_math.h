#if !defined(VM_SHORT_INT_MATH_HH)
#define VM_SHORT_INT_MATH_HH

#include "base_command_handler.h"
#include "base_math.h"

class adds_command_handler : public base_math
{
public:
    adds_command_handler(memory& m, state& s,int sz):base_math(m,s,sz){}
    ~adds_command_handler(){}
    void execute(command comm)
    {
        comm = comm;
         s.reg[comm.c16.a3] = s.reg[comm.c16.a1] + s.reg[comm.c16.a2];
         s.psw.flags = get_new_flags<uint16_t>(s.reg[comm.c16.a1],s.reg[comm.c16.a2],s.reg[comm.c16.a3]);
    }
};

class subs_command_handler : public base_math
{
public:
    subs_command_handler(memory& m, state& s,int sz):base_math(m,s,sz){}
    ~subs_command_handler(){}
    void execute(command comm)
    {
        comm = comm;
        s.reg[comm.c16.a3] = s.reg[comm.c16.a1] - s.reg[comm.c16.a2];
        s.psw.flags = get_new_flags<uint16_t>(s.reg[comm.c16.a1],s.reg[comm.c16.a2],s.reg[comm.c16.a3]);
    }
};

class muls_command_handler : public base_math
{
public:
    muls_command_handler(memory& m, state& s,int sz):base_math(m,s,sz){}
    ~muls_command_handler(){}
    void execute(command comm)
    {
        comm = comm;
        s.reg[comm.c16.a3] = s.reg[comm.c16.a1] * s.reg[comm.c16.a2];
        s.psw.flags = get_new_flags<uint16_t>(s.reg[comm.c16.a1],s.reg[comm.c16.a2],s.reg[comm.c16.a3]);
    }
};

class divs_command_handler : public base_math
{
public:
    divs_command_handler(memory& m, state& s,int sz):base_math(m,s,sz){}
    ~divs_command_handler(){}
    void execute(command comm)
    {
        comm = comm;
        s.reg[comm.c16.a3] = s.reg[comm.c16.a1] / s.reg[comm.c16.a2];
        s.psw.flags = get_new_flags<uint16_t>(s.reg[comm.c16.a1],s.reg[comm.c16.a2],s.reg[comm.c16.a3]);
    }
};

#endif // VM_SHORT_INT_MATH_HH
