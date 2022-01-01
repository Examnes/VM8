#include "assembler.h"
#include <sstream>
#include <cstring>
#include "trim.h"

assembler::assembler(std::string file)
{
    l = loader(file);
    register_ids.insert({"eax", 0});
    register_ids.insert({"ebx", 1});
    register_ids.insert({"ecx", 2});
    register_ids.insert({"edx", 3});
    register_ids.insert({"esi", 4});
    register_ids.insert({"edi", 5});
    register_ids.insert({"eax", 6});
    providers = get_providers();
}


void assembler::collect_symbols()
{
    uint16_t ip = 0;
    for (auto line : l.lines)
    {
        trimmer::trim(line);
        if (line.back() == ':')
        {
            line.erase(line.end());
            if (std::all_of(line.begin(),line.end(),::isalpha))
            {
                symbols.insert({line,ip});
            }else
            {
                throw "Имя метки может состоять только из букв";
            }
        }else
        {
            std::string mnemonic = base_provider::get_mnemonic(line);
            if (providers.count(mnemonic))
            {
                ip += providers[mnemonic]->get_size(base_provider::get_arguments(line));
            }else
            {
                throw "Команда не найдена";
            }
        }
    }
}

assembler::~assembler()
{
}