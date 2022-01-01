#ifndef VM_FLOAT_CAMMANDS_HANDLERS
#define VM_FLOAT_CAMMANDS_HANDLERS
#include "base_math.h"

class fadd_command_handler : public base_math
{
public:
    fadd_command_handler(memory& m, state& s,int sz):base_math(m,s,sz){}
    ~fadd_command_handler(){}
    void execute(command comm)
    {
        comm = comm;
        converter conv;
        conv.data[0] = m[s.sp--];
        conv.data[1] = m[s.sp--];
        conv.data[2] = m[s.sp--];
        conv.data[3] = m[s.sp--];
        
        float a = conv.floating;

        conv.data[0] = m[s.sp--];
        conv.data[1] = m[s.sp--];
        conv.data[2] = m[s.sp--];
        conv.data[3] = m[s.sp--];

        float b = conv.floating;
        float c = a + b;

        conv.floating = c;

        m[s.sp++] = conv.data[0];
        m[s.sp++] = conv.data[1];
        s.psw.flags = get_new_flags<float>(a,b,c);
    }
};

class fmul_command_handler : public base_math
{
public:
    fmul_command_handler(memory& m, state& s,int sz):base_math(m,s,sz){}
    ~fmul_command_handler(){}
    void execute(command comm)
    {
        comm = comm;
        converter conv;
        conv.data[0] = m[s.sp--];
        conv.data[1] = m[s.sp--];
        conv.data[2] = m[s.sp--];
        conv.data[3] = m[s.sp--];

        float a = conv.floating;

        conv.data[0] = m[s.sp--];
        conv.data[1] = m[s.sp--];
        conv.data[2] = m[s.sp--];
        conv.data[3] = m[s.sp--];

        float b = conv.floating;
        float c = a * b;

        conv.floating = c;

        m[s.sp++] = conv.data[0];
        m[s.sp++] = conv.data[1];
        s.psw.flags = get_new_flags<float>(a,b,c);
    }
};

class fsub_command_handler : public base_math
{
public:
    fsub_command_handler(memory& m, state& s,int sz):base_math(m,s,sz){}
    ~fsub_command_handler(){}
    void execute(command comm)
    {
        comm = comm;
        converter conv;
        conv.data[0] = m[s.sp--];
        conv.data[1] = m[s.sp--];
        conv.data[2] = m[s.sp--];
        conv.data[3] = m[s.sp--];
        
        float a = conv.floating;

        conv.data[0] = m[s.sp--];
        conv.data[1] = m[s.sp--];
        conv.data[2] = m[s.sp--];
        conv.data[3] = m[s.sp--];

        float b = conv.floating;
        float c = a - b;

        conv.floating = c;

        m[s.sp++] = conv.data[0];
        m[s.sp++] = conv.data[1];
        s.psw.flags = get_new_flags<float>(a,b,c);
    }
};

class fdiv_command_handler : public base_math
{
public:
    fdiv_command_handler(memory& m, state& s,int sz):base_math(m,s,sz){}
    ~fdiv_command_handler(){}
    void execute(command comm)
    {
        comm = comm;
        converter conv;
        conv.data[0] = m[s.sp--];
        conv.data[1] = m[s.sp--];
        conv.data[2] = m[s.sp--];
        conv.data[3] = m[s.sp--];
        
        float a = conv.floating;

        conv.data[0] = m[s.sp--];
        conv.data[1] = m[s.sp--];
        conv.data[2] = m[s.sp--];
        conv.data[3] = m[s.sp--];

        float b = conv.floating;
        float c = a / b;

        conv.floating = c;

        m[s.sp++] = conv.data[0];
        m[s.sp++] = conv.data[1];
        s.psw.flags = get_new_flags<float>(a,b,c);
    }
};

#endif