#ifndef VM_INTERPRETATOR_H
#define VM_INTERPRETATOR_H

#include "types.h"
#include "memory.h"
#include "base_command_handler.h"
#include "command_handlers_provider.h"
#include <map>

class interpretator
{
public:
	void start();
	interpretator(memory& m);
private:
	memory& m;
	std::map<code_t,command_handler*> handlers;
	state s;
	command cmd;
	bool load_command();
};

#endif