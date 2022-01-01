#if !defined(VM_INT_MATH_HH)
#define VM_INT_MATH_HH

#include "base_math.h"

class addws_command_handler : public base_math
{
public:
    addws_command_handler(memory& m, state& s,int sz):base_math(m,s,sz){}
    ~addws_command_handler(){}
    void execute(command comm)
    {

        converter conv;
        conv.data[0] = m[s.reg[comm.c32.a1]];
        conv.data[1] = m[s.reg[comm.c32.a1] + 1];
        conv.data[2] = m[s.reg[comm.c32.a1] + 2];
        conv.data[3] = m[s.reg[comm.c32.a1] + 3];
        
        int a = conv.wide_signed;

        conv.data[0] = m[s.reg[comm.c32.a2] + s.reg[comm.c32.a3]];
        conv.data[1] = m[s.reg[comm.c32.a2] + s.reg[comm.c32.a3] + 1];
        conv.data[2] = m[s.reg[comm.c32.a2] + s.reg[comm.c32.a3] + 2];
        conv.data[3] = m[s.reg[comm.c32.a2] + s.reg[comm.c32.a3] + 3];
        
        int b = conv.wide_signed;

        int c = a + b;

        conv.wide_signed = c;

        m[s.reg[comm.c32.a1]] = conv.data[0];
        m[s.reg[comm.c32.a1] + 1] = conv.data[1];
        m[s.reg[comm.c32.a1] + 2] = conv.data[2];
        m[s.reg[comm.c32.a1] + 3] = conv.data[3];
        s.psw.flags = get_new_flags<int>(a,b,c);
    }
};

class subws_command_handler : public base_math
{
public:
    subws_command_handler(memory& m, state& s,int sz):base_math(m,s,sz){}
    ~subws_command_handler(){}
    void execute(command comm)
    {
        converter conv;
        conv.data[0] = m[s.reg[comm.c32.a1]];
        conv.data[1] = m[s.reg[comm.c32.a1] + 1];
        conv.data[2] = m[s.reg[comm.c32.a1] + 2];
        conv.data[3] = m[s.reg[comm.c32.a1] + 3];
        
        int a = conv.wide_signed;

        conv.data[0] = m[s.reg[comm.c32.a2] + s.reg[comm.c32.a3]];
        conv.data[1] = m[s.reg[comm.c32.a2] + s.reg[comm.c32.a3] + 1];
        conv.data[2] = m[s.reg[comm.c32.a2] + s.reg[comm.c32.a3] + 2];
        conv.data[3] = m[s.reg[comm.c32.a2] + s.reg[comm.c32.a3] + 3];
        
        int b = conv.wide_signed;

        int c = a - b;

        conv.wide_signed = c;

        m[s.reg[comm.c32.a1]] = conv.data[0];
        m[s.reg[comm.c32.a1] + 1] = conv.data[1];
        m[s.reg[comm.c32.a1] + 2] = conv.data[2];
        m[s.reg[comm.c32.a1] + 3] = conv.data[3];
        s.psw.flags = get_new_flags<int>(a,b,c);
    }
};

class mulws_command_handler : public base_math
{
public:
    mulws_command_handler(memory& m, state& s,int sz):base_math(m,s,sz){}
    ~mulws_command_handler(){}
    void execute(command comm)
    {
        converter conv;
        conv.data[0] = m[s.reg[comm.c32.a1]];
        conv.data[1] = m[s.reg[comm.c32.a1] + 1];
        conv.data[2] = m[s.reg[comm.c32.a1] + 2];
        conv.data[3] = m[s.reg[comm.c32.a1] + 3];
        
        int a = conv.wide_signed;

        conv.data[0] = m[s.reg[comm.c32.a2] + s.reg[comm.c32.a3]];
        conv.data[1] = m[s.reg[comm.c32.a2] + s.reg[comm.c32.a3] + 1];
        conv.data[2] = m[s.reg[comm.c32.a2] + s.reg[comm.c32.a3] + 2];
        conv.data[3] = m[s.reg[comm.c32.a2] + s.reg[comm.c32.a3] + 3];
        
        int b = conv.wide_signed;

        int c = a * b;

        conv.wide_signed = c;

        m[s.reg[comm.c32.a1]] = conv.data[0];
        m[s.reg[comm.c32.a1] + 1] = conv.data[1];
        m[s.reg[comm.c32.a1] + 2] = conv.data[2];
        m[s.reg[comm.c32.a1] + 3] = conv.data[3];
        s.psw.flags = get_new_flags<int>(a,b,c);
    }
};

class divws_command_handler : public base_math
{
public:
    divws_command_handler(memory& m, state& s,int sz):base_math(m,s,sz){}
    ~divws_command_handler(){}
    void execute(command comm)
    {
        converter conv;
        conv.data[0] = m[s.reg[comm.c32.a1]];
        conv.data[1] = m[s.reg[comm.c32.a1] + 1];
        conv.data[2] = m[s.reg[comm.c32.a1] + 2];
        conv.data[3] = m[s.reg[comm.c32.a1] + 3];
        
        int a = conv.wide_signed;

        conv.data[0] = m[s.reg[comm.c32.a2] + s.reg[comm.c32.a3]];
        conv.data[1] = m[s.reg[comm.c32.a2] + s.reg[comm.c32.a3] + 1];
        conv.data[2] = m[s.reg[comm.c32.a2] + s.reg[comm.c32.a3] + 2];
        conv.data[3] = m[s.reg[comm.c32.a2] + s.reg[comm.c32.a3] + 3];
        
        int b = conv.wide_signed;

        int c = a / b;

        conv.wide_signed = c;

        m[s.reg[comm.c32.a1]] = conv.data[0];
        m[s.reg[comm.c32.a1] + 1] = conv.data[1];
        m[s.reg[comm.c32.a1] + 2] = conv.data[2];
        m[s.reg[comm.c32.a1] + 3] = conv.data[3];
        s.psw.flags = get_new_flags<int>(a,b,c);
    }
};

class addw_command_handler : public base_math
{
public:
    addw_command_handler(memory& m, state& s,int sz):base_math(m,s,sz){}
    ~addw_command_handler(){}
    void execute(command comm)
    {

        converter conv;
        conv.data[0] = m[s.reg[comm.c32.a1]];
        conv.data[1] = m[s.reg[comm.c32.a1] + 1];
        conv.data[2] = m[s.reg[comm.c32.a1] + 2];
        conv.data[3] = m[s.reg[comm.c32.a1] + 3];
        
        unsigned int a = conv.wide_unsigned;

        conv.data[0] = m[s.reg[comm.c32.a2] + s.reg[comm.c32.a3]];
        conv.data[1] = m[s.reg[comm.c32.a2] + s.reg[comm.c32.a3] + 1];
        conv.data[2] = m[s.reg[comm.c32.a2] + s.reg[comm.c32.a3] + 2];
        conv.data[3] = m[s.reg[comm.c32.a2] + s.reg[comm.c32.a3] + 3];
        
        unsigned int b = conv.wide_unsigned;

        unsigned int c = a + b;

        conv.wide_unsigned = c;

        m[s.reg[comm.c32.a1]] = conv.data[0];
        m[s.reg[comm.c32.a1] + 1] = conv.data[1];
        m[s.reg[comm.c32.a1] + 2] = conv.data[2];
        m[s.reg[comm.c32.a1] + 3] = conv.data[3];
        s.psw.flags = get_new_flags<unsigned int>(a,b,c);
    }
};

class subw_command_handler : public base_math
{
public:
    subw_command_handler(memory& m, state& s,int sz):base_math(m,s,sz){}
    ~subw_command_handler(){}
    void execute(command comm)
    {
        converter conv;
        conv.data[0] = m[s.reg[comm.c32.a1]];
        conv.data[1] = m[s.reg[comm.c32.a1] + 1];
        conv.data[2] = m[s.reg[comm.c32.a1] + 2];
        conv.data[3] = m[s.reg[comm.c32.a1] + 3];
        
        unsigned int a = conv.wide_unsigned;

        conv.data[0] = m[s.reg[comm.c32.a2] + s.reg[comm.c32.a3]];
        conv.data[1] = m[s.reg[comm.c32.a2] + s.reg[comm.c32.a3] + 1];
        conv.data[2] = m[s.reg[comm.c32.a2] + s.reg[comm.c32.a3] + 2];
        conv.data[3] = m[s.reg[comm.c32.a2] + s.reg[comm.c32.a3] + 3];
        
        unsigned int b = conv.wide_unsigned;

        unsigned int c = a - b;

        conv.wide_unsigned = c;

        m[s.reg[comm.c32.a1]] = conv.data[0];
        m[s.reg[comm.c32.a1] + 1] = conv.data[1];
        m[s.reg[comm.c32.a1] + 2] = conv.data[2];
        m[s.reg[comm.c32.a1] + 3] = conv.data[3];
        s.psw.flags = get_new_flags<unsigned int>(a,b,c);
    }
};

class mulw_command_handler : public base_math
{
public:
    mulw_command_handler(memory& m, state& s,int sz):base_math(m,s,sz){}
    ~mulw_command_handler(){}
    void execute(command comm)
    {
        converter conv;
        conv.data[0] = m[s.reg[comm.c32.a1]];
        conv.data[1] = m[s.reg[comm.c32.a1] + 1];
        conv.data[2] = m[s.reg[comm.c32.a1] + 2];
        conv.data[3] = m[s.reg[comm.c32.a1] + 3];
        
        unsigned int a = conv.wide_unsigned;

        conv.data[0] = m[s.reg[comm.c32.a2] + s.reg[comm.c32.a3]];
        conv.data[1] = m[s.reg[comm.c32.a2] + s.reg[comm.c32.a3] + 1];
        conv.data[2] = m[s.reg[comm.c32.a2] + s.reg[comm.c32.a3] + 2];
        conv.data[3] = m[s.reg[comm.c32.a2] + s.reg[comm.c32.a3] + 3];
        
        unsigned int b = conv.wide_unsigned;

        unsigned int c = a * b;

        conv.wide_unsigned = c;

        m[s.reg[comm.c32.a1]] = conv.data[0];
        m[s.reg[comm.c32.a1] + 1] = conv.data[1];
        m[s.reg[comm.c32.a1] + 2] = conv.data[2];
        m[s.reg[comm.c32.a1] + 3] = conv.data[3];
        s.psw.flags = get_new_flags<unsigned int>(a,b,c);
    }
};

class divw_command_handler : public base_math
{
public:
    divw_command_handler(memory& m, state& s,int sz):base_math(m,s,sz){}
    ~divw_command_handler(){}
    void execute(command comm)
    {
        converter conv;
        conv.data[0] = m[s.reg[comm.c32.a1]];
        conv.data[1] = m[s.reg[comm.c32.a1] + 1];
        conv.data[2] = m[s.reg[comm.c32.a1] + 2];
        conv.data[3] = m[s.reg[comm.c32.a1] + 3];
        
        unsigned int a = conv.wide_unsigned;

        conv.data[0] = m[s.reg[comm.c32.a2] + s.reg[comm.c32.a3]];
        conv.data[1] = m[s.reg[comm.c32.a2] + s.reg[comm.c32.a3] + 1];
        conv.data[2] = m[s.reg[comm.c32.a2] + s.reg[comm.c32.a3] + 2];
        conv.data[3] = m[s.reg[comm.c32.a2] + s.reg[comm.c32.a3] + 3];
        
        unsigned int b = conv.wide_unsigned;

        unsigned int c = a / b;

        conv.wide_unsigned = c;

        m[s.reg[comm.c32.a1]] = conv.data[0];
        m[s.reg[comm.c32.a1] + 1] = conv.data[1];
        m[s.reg[comm.c32.a1] + 2] = conv.data[2];
        m[s.reg[comm.c32.a1] + 3] = conv.data[3];
        s.psw.flags = get_new_flags<unsigned int>(a,b,c);
    }
};

class neg_command_handler : public base_math
{
public:
    neg_command_handler(memory& m, state& s,int sz):base_math(m,s,sz){}
    ~neg_command_handler(){}
    void execute(command comm)
    {
        converter conv;
        conv.data[0] = m[s.reg[comm.c32.a1]];
        conv.data[1] = m[s.reg[comm.c32.a1] + 1];
        conv.data[2] = m[s.reg[comm.c32.a1] + 2];
        conv.data[3] = m[s.reg[comm.c32.a1] + 3];
        
        conv.wide_signed = -conv.wide_signed;

        m[s.reg[comm.c32.a1]] = conv.data[0];
        m[s.reg[comm.c32.a1] + 1] = conv.data[1];
        m[s.reg[comm.c32.a1] + 2] = conv.data[2];
        m[s.reg[comm.c32.a1] + 3] = conv.data[3];
    }
};

#endif // VM_INT_MATH_HH
