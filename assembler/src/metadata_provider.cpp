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
    {"adds",17},
    {"muls",20},
    {"divs",19},
    {"subs",18},
    {"enter",13},
    {"leave",14},
    {"jmpl",11},
    {"jmpr",10},
    {"jmplr",12},
    {"fadd",2},
    {"fdiv",4},
    {"fmul",5},
    {"fsub",3},
    {"addws",21},
    {"mulws",24},
    {"call",15},
    {"ret",16},
    {"divws",23},
    {"subws",22},
    {"addw",6},
    {"mulw",9},
    {"divw",8},
    {"subw",7},
    {"mov",1}
};
