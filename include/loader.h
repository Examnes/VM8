#ifndef VM_LOADER_H
#define VM_LOADER_H

#include <string>
#include "memory.h"

void load_memory_from_file(std::string s,memory& m,addr_t offset);

#endif