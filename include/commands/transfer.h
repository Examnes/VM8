#ifndef VM_TRANSFER_CAMMANDS_HANDLERS
#define VM_TRANSFER_CAMMANDS_HANDLERS
#include "base_command_handler.h"

class mov_command_handler : public command_handler
{
public:
    mov_command_handler(memory& m, state& s,int sz):command_handler(m,s,sz){}
    ~mov_command_handler(){}
    void execute(command c)
    {
        mov_type mt = static_cast<mov_type>(c.c16.a1);
        switch (mt)
        {
        case mov_type::direct:
            s.reg[c.c16.a2] = s.reg[c.c16.a3];
            size = 2;
            break;
        case mov_type::inderect:
            s.reg[c.c32.a2] = c.c32.addr;
            size = 4;
            break;
        case mov_type::relative:
            s.reg[c.c32.a2] = s.reg[c.c32.a3] + c.c32.addr;
            size = 4;
            break;
        default:
            break;
        }
    }
private:
    enum mov_type
    {
        direct,
        inderect,
        relative
    };
};

#endif