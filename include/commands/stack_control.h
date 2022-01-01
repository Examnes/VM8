#ifndef VM_STACK_CTRL
#define VM_STACK_CTRL

#include "base_command_handler.h"


class enter_command_handler : public command_handler
{
public:
    enter_command_handler(memory& m, state& s,int sz):command_handler(m,s,sz){}
    ~enter_command_handler(){}
    void execute(command comm)
    {
        s.bp = s.sp;
    }
};

class leave_command_handler : public command_handler
{
public:
    leave_command_handler(memory& m, state& s,int sz):command_handler(m,s,sz){}
    ~leave_command_handler(){}
    void execute(command comm)
    {
        s.sp = s.bp;
    }
};


#endif