#include "interpretator.h"
#include "types.h"
#include <stdexcept>


interpretator::interpretator(memory& m): m(m)
{
    handlers = command_handlers_provider::get_command_handlers(m,s);
}

bool interpretator::load_command()
{
    cmd.parts[0] = m[s.psw.ip];
    cmd.parts[1] = m[static_cast<word>(s.psw.ip + 1)];
    cmd.parts[2] = m[static_cast<word>(s.psw.ip + 2)];
    cmd.parts[3] = m[static_cast<word>(s.psw.ip + 3)];
    
    if (cmd.parts[0] == 240)
    {
        return false;
    }
    return true;
}

void interpretator::start()
{
    while (load_command())
    {
        if(handlers.count(cmd.c16.cop) != 0)
        {
            handlers[cmd.c16.cop]->execute(cmd);
        }else
        {
            throw std::runtime_error("Неопознанная команда: " + std::to_string(static_cast<int>(cmd.c16.cop)));
        }
    }
}