#include "metadata_provider.h"

std::map<std::string,int> metadata_provider::register_ids = {
    {"eax",1},
    {"ebx",2},
    {"ecx",3},
    {"edx",4},
    {"esi",5},
    {"esi",6}
};
std::map<std::string,int> metadata_provider::opcode_ids = {
    {"adds",1}
};
