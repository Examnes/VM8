#ifndef VM_COMMAND_HANDLER
#define VM_COMMAND_HANDLER

#include "memory.h"
#include "types.h"

class command_handler
{
public:
    virtual void execute(command c) = 0;
    command_handler(memory& m, state& s, int sz):m(m),s(s),size(sz)
    {
    }
    virtual ~command_handler(){};
    int get_size(){return size;};
protected:
    memory& m;
    state& s;
    int size;
};

#endif