#ifndef ASM_ASSEMBLER_HH
#define ASM_ASSEMBLER_HH

#include "loader.h"
#include "expressions.h"
#include <string>
#include <map>


class assembler
{
private:
    loader l;
    std::vector<command_expression*> commands;
    std::map<std::string, uint16_t> symbols;
    std::vector<uint8_t> out;
    void validate();
    void collect_symbols();
public:
    assembler(std::string file);
    void assemble();
    ~assembler()
    {

    }
};


#endif