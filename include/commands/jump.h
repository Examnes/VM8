#ifndef VM_JUMP
#define VM_JUMP

#include "base_command_handler.h"
#include "types.h"

class jmpr_command_handler : public command_handler
{
public:
    jmpr_command_handler(memory& m, state& s,int sz):command_handler(m,s,sz){}
    ~jmpr_command_handler(){}
    void execute(command comm)
    {
        converter conv;
        conv.data[0] = (comm.c16.a3 + comm.c16.a2 * 8 + comm.c16.a1 * 64);
        s.psw.ip = static_cast<word>(s.psw.ip + conv.relation);
        s.psw.flags.ip_changed = true;
    }
};

class jmpre_command_handler : public command_handler
{
public:
    jmpre_command_handler(memory& m, state& s,int sz):command_handler(m,s,sz){}
    ~jmpre_command_handler(){}
    void execute(command comm)
    {
        if (s.psw.flags.zf)
        {
            converter conv;
            conv.data[0] = static_cast<word>(comm.c16.a3 + comm.c16.a2 * 8 + comm.c16.a1 * 64);
            s.psw.ip = static_cast<word>(s.psw.ip + conv.relation);
            s.psw.flags.ip_changed = true;
        }
    }
};

class jmprg_command_handler : public command_handler
{
public:
    jmprg_command_handler(memory& m, state& s,int sz):command_handler(m,s,sz){}
    ~jmprg_command_handler(){}
    void execute(command comm)
    {
        if (not s.psw.flags.nf and not s.psw.flags.zf)
        {
            converter conv;
            conv.data[0] = static_cast<word>(comm.c16.a3 + comm.c16.a2 * 8 + comm.c16.a1 * 64);
            s.psw.ip = static_cast<word>(s.psw.ip + conv.relation);
            s.psw.flags.ip_changed = true;
        }
    }
};

class jmprl_command_handler : public command_handler
{
public:
    jmprl_command_handler(memory& m, state& s,int sz):command_handler(m,s,sz){}
    ~jmprl_command_handler(){}
    void execute(command comm)
    {
        if (s.psw.flags.nf and not s.psw.flags.zf)
        {
            converter conv;
            conv.data[0] = static_cast<word>(comm.c16.a3 + comm.c16.a2 * 8 + comm.c16.a1 * 64);
            s.psw.ip = static_cast<word>(s.psw.ip + conv.relation);
            s.psw.flags.ip_changed = true;
        }
    }
};

class jmprge_command_handler : public command_handler
{
public:
    jmprge_command_handler(memory& m, state& s,int sz):command_handler(m,s,sz){}
    ~jmprge_command_handler(){}
    void execute(command comm)
    {
        if (not s.psw.flags.nf or s.psw.flags.zf)
        {
            converter conv;
            conv.data[0] = static_cast<word>(comm.c16.a3 + comm.c16.a2 * 8 + comm.c16.a1 * 64);
            s.psw.ip = static_cast<word>(s.psw.ip + conv.relation);
            s.psw.flags.ip_changed = true;
        }
    }
};

class jmprle_command_handler : public command_handler
{
public:
    jmprle_command_handler(memory& m, state& s,int sz):command_handler(m,s,sz){}
    ~jmprle_command_handler(){}
    void execute(command comm)
    {
        if (s.psw.flags.nf or s.psw.flags.zf)
        {
            converter conv;
            conv.data[0] = static_cast<word>(comm.c16.a3 + comm.c16.a2 * 8 + comm.c16.a1 * 64);
            s.psw.ip = static_cast<word>(s.psw.ip + conv.relation);
            s.psw.flags.ip_changed = true;
        }
    }
};

class jmpl_command_handler : public command_handler
{
public:
    jmpl_command_handler(memory& m, state& s,int sz):command_handler(m,s,sz){}
    ~jmpl_command_handler(){}
    void execute(command comm)
    {
        if(comm.c24.b)
        {
            s.psw.ip = m[comm.c24.addr];
        }else
        {
            s.psw.ip = comm.c24.addr;
        }
        s.psw.flags.ip_changed = true;
    }
};

class jmple_command_handler : public command_handler
{
public:
    jmple_command_handler(memory& m, state& s,int sz):command_handler(m,s,sz){}
    ~jmple_command_handler(){}
    void execute(command comm)
    {
        if (s.psw.flags.zf)
        {
            if(comm.c24.b)
            {
                s.psw.ip = m[comm.c24.addr];
            }else
            {
                s.psw.ip = comm.c24.addr;
            }
            s.psw.flags.ip_changed = true;
        }
    }
};

class jmplg_command_handler : public command_handler
{
public:
    jmplg_command_handler(memory& m, state& s,int sz):command_handler(m,s,sz){}
    ~jmplg_command_handler(){}
    void execute(command comm)
    {
        if (not s.psw.flags.nf and not s.psw.flags.zf)
        {
            if(comm.c24.b)
            {
                s.psw.ip = m[comm.c24.addr];
            }else
            {
                s.psw.ip = comm.c24.addr;
            }
            s.psw.flags.ip_changed = true;
        }
    }
};

class jmpll_command_handler : public command_handler
{
public:
    jmpll_command_handler(memory& m, state& s,int sz):command_handler(m,s,sz){}
    ~jmpll_command_handler(){}
    void execute(command comm)
    {
        if (s.psw.flags.nf and not s.psw.flags.zf)
        {
            if(comm.c24.b)
            {
                s.psw.ip = m[comm.c24.addr];
            }else
            {
                s.psw.ip = comm.c24.addr;
            }
            s.psw.flags.ip_changed = true;
        }
    }
};

class jmplge_command_handler : public command_handler
{
public:
    jmplge_command_handler(memory& m, state& s,int sz):command_handler(m,s,sz){}
    ~jmplge_command_handler(){}
    void execute(command comm)
    {
        if (not s.psw.flags.nf or s.psw.flags.zf)
        {
            if(comm.c24.b)
            {
                s.psw.ip = m[comm.c24.addr];
            }else
            {
                s.psw.ip = comm.c24.addr;
            }
            s.psw.flags.ip_changed = true;
        }
    }
};

class jmplle_command_handler : public command_handler
{
public:
    jmplle_command_handler(memory& m, state& s,int sz):command_handler(m,s,sz){}
    ~jmplle_command_handler(){}
    void execute(command comm)
    {
        if (s.psw.flags.nf or s.psw.flags.zf)
        {
            if(comm.c24.b)
            {
                s.psw.ip = m[comm.c24.addr];
            }else
            {
                s.psw.ip = comm.c24.addr;
            }
            s.psw.flags.ip_changed = true;
        }
    }
};

class jmplr_command_handler : public command_handler
{
public:
    jmplr_command_handler(memory& m, state& s,int sz):command_handler(m,s,sz){}
    ~jmplr_command_handler(){}
    void execute(command comm)
    {
        if(comm.c32.a1 & 0b100)
        {
            if(comm.c32.a1 & 0b010)
            {
                s.psw.ip = m[static_cast<word>(comm.c32.addr + s.reg[comm.c32.a2])];
            }else
            {
                s.psw.ip = m[comm.c32.addr];
            }
        }else
        {
            if(comm.c32.a1 & 0b010)
            {
                s.psw.ip = static_cast<word>(comm.c32.addr + s.reg[comm.c32.a2]);
            }else
            {
                s.psw.ip = comm.c32.addr;
            }
        }
        s.psw.flags.ip_changed = true;
    }
};

class jmplre_command_handler : public command_handler
{
public:
    jmplre_command_handler(memory& m, state& s,int sz):command_handler(m,s,sz){}
    ~jmplre_command_handler(){}
    void execute(command comm)
    {
        if (s.psw.flags.zf)
        {
            if(comm.c32.a1 & 0b100)
            {
                if(comm.c32.a1 & 0b010)
                {
                    s.psw.ip = m[static_cast<word>(comm.c32.addr + s.reg[comm.c32.a2])];
                }else
                {
                    s.psw.ip = m[comm.c32.addr];
                }
            }else
            {
                if(comm.c32.a1 & 0b010)
                {
                    s.psw.ip = static_cast<word>(comm.c32.addr + s.reg[comm.c32.a2]);
                }else
                {
                    s.psw.ip = comm.c32.addr;
                }
            }
            s.psw.flags.ip_changed = true;
        }
    }
};

class jmplrg_command_handler : public command_handler
{
public:
    jmplrg_command_handler(memory& m, state& s,int sz):command_handler(m,s,sz){}
    ~jmplrg_command_handler(){}
    void execute(command comm)
    {
        if (not s.psw.flags.nf and not s.psw.flags.zf)
        {
            if(comm.c32.a1 & 0b100)
            {
                if(comm.c32.a1 & 0b010)
                {
                    s.psw.ip = m[static_cast<word>(comm.c32.addr + s.reg[comm.c32.a2])];
                }else
                {
                    s.psw.ip = m[comm.c32.addr];
                }
            }else
            {
                if(comm.c32.a1 & 0b010)
                {
                    s.psw.ip = static_cast<word>(comm.c32.addr + s.reg[comm.c32.a2]);
                }else
                {
                    s.psw.ip = comm.c32.addr;
                }
            }
            s.psw.flags.ip_changed = true;
        }
    }
};

class jmplrl_command_handler : public command_handler
{
public:
    jmplrl_command_handler(memory& m, state& s,int sz):command_handler(m,s,sz){}
    ~jmplrl_command_handler(){}
    void execute(command comm)
    {
        if (s.psw.flags.nf and not s.psw.flags.zf)
        {
            if(comm.c32.a1 & 0b100)
            {
                if(comm.c32.a1 & 0b010)
                {
                    s.psw.ip = m[static_cast<word>(comm.c32.addr + s.reg[comm.c32.a2])];
                }else
                {
                    s.psw.ip = m[comm.c32.addr];
                }
            }else
            {
                if(comm.c32.a1 & 0b010)
                {
                    s.psw.ip = static_cast<word>(comm.c32.addr + s.reg[comm.c32.a2]);
                }else
                {
                    s.psw.ip = comm.c32.addr;
                }
            }
            s.psw.flags.ip_changed = true;
        }
    }
};

class jmplrge_command_handler : public command_handler
{
public:
    jmplrge_command_handler(memory& m, state& s,int sz):command_handler(m,s,sz){}
    ~jmplrge_command_handler(){}
    void execute(command comm)
    {
        if (not s.psw.flags.nf or s.psw.flags.zf)
        {
            if(comm.c32.a1 & 0b100)
            {
                if(comm.c32.a1 & 0b010)
                {
                    s.psw.ip = m[static_cast<word>(comm.c32.addr + s.reg[comm.c32.a2])];
                }else
                {
                    s.psw.ip = m[comm.c32.addr];
                }
            }else
            {
                if(comm.c32.a1 & 0b010)
                {
                    s.psw.ip = static_cast<word>(comm.c32.addr + s.reg[comm.c32.a2]);
                }else
                {
                    s.psw.ip = comm.c32.addr;
                }
            }
            s.psw.flags.ip_changed = true;
        }
    }
};

class jmplrle_command_handler : public command_handler
{
public:
    jmplrle_command_handler(memory& m, state& s,int sz):command_handler(m,s,sz){}
    ~jmplrle_command_handler(){}
    void execute(command comm)
    {
        if (s.psw.flags.nf or s.psw.flags.zf)
        {
            if(comm.c32.a1 & 0b100)
            {
                if(comm.c32.a1 & 0b010)
                {
                    s.psw.ip = m[static_cast<word>(comm.c32.addr + s.reg[comm.c32.a2])];
                }else
                {
                    s.psw.ip = m[comm.c32.addr];
                }
            }else
            {
                if(comm.c32.a1 & 0b010)
                {
                    s.psw.ip = static_cast<word>(comm.c32.addr + s.reg[comm.c32.a2]);
                }else
                {
                    s.psw.ip = comm.c32.addr;
                }
            }
            s.psw.flags.ip_changed = true;
        }
    }
};

class call_command_handler : public jmpl_command_handler
{
public:
    call_command_handler(memory& m, state& s,int sz):jmpl_command_handler(m,s,sz){}
    ~call_command_handler(){}
    void execute(command comm)
    {
        converter cov;
        cov.short_unsigned[0] = s.psw.ip;
        m[s.sp--] = cov.data[1];
        m[s.sp--] = cov.data[0];
        jmpl_command_handler::execute(comm);
    }
};

class ret_command_handler : public jmpl_command_handler
{
public:
    ret_command_handler(memory& m, state& s,int sz):jmpl_command_handler(m,s,sz){}
    ~ret_command_handler(){}
    void execute(command comm)
    {
        converter cov;
        cov.data[0] = m[s.sp++];
        cov.data[1] = m[s.sp++];
        comm.c24.addr = cov.short_unsigned[0];
        comm.c24.b = true;
        jmpl_command_handler::execute(comm);
    }

};

class cmp_command_handler : public command_handler
{
public:
    cmp_command_handler(memory& m, state& s,int sz):command_handler(m,s,sz){}
    ~cmp_command_handler(){}
    void execute(command comm)
    {
        converter cov1,cov2;
        cov1.data[0] = m[s.reg[comm.c16.a1]];
        cov1.data[1] = m[s.reg[comm.c16.a1] + 1];


        cov2.data[0] = m[s.reg[comm.c16.a2]];
        cov2.data[1] = m[s.reg[comm.c16.a2] + 1];


        if (cov1.wide_signed > cov2.wide_signed)
        {
            s.psw.flags.nf = 0;
            s.psw.flags.zf = 0;
        }else if (cov1.wide_signed < cov2.wide_signed) 
        { 
            s.psw.flags.nf = 1;
            s.psw.flags.zf = 0; 
        }
        else
        {
            //s.psw.flags.cf = 0;
            s.psw.flags.zf = 1; 
        }
    }
};


#endif