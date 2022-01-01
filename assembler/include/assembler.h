#ifndef ASM_ASSEMBLER_HH
#define ASM_ASSEMBLER_HH

#include "loader.h"
#include <string>
#include <map>
#include "command_providers.h"

class assembler
{
private:
    loader l;
    std::map<std::string, uint16_t> symbols;
    std::map<std::string, uint8_t> register_ids;
    std::map<std::string, base_provider*> providers;

    void collect_symbols();
public:
    assembler(std::string file);
    ~assembler();
};




#endif