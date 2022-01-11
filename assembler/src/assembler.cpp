#include "assembler.h"
#include <sstream>
#include <cstring>
#include <fstream>
#include "token.h"
#include "lexer.h"
#include "metadata_provider.h"
#include "validator_provider.h"

assembler::assembler(std::string file)
{
    l = loader(file);
    l.load();
    std::vector<token> tokens = tokenizer::parse(l.content);
    parser p = parser(tokens);
    commands = p.parse();
}

void assembler::validate()
{
    for (auto &&c : commands)
    {
        if (c->mnemonic)
        {
            if (validators_provider::validators.count(c->mnemonic->value.value))
            {
                if ( !validators_provider::validators[c->mnemonic->value.value]->set_size(*c))
                {

                }
            }
        }else
        {
            c->type = command_type::no_command;
        }
        
    }
}

void assembler::collect_symbols()
{
    int current_address = 0;
    for (auto &&c : commands)
    {
        if (c->label)
        {
            symbols.insert({c->label->value.value,current_address});
        }
        current_address += (int)c->type;
    }
}

void assembler::assemble()
{
    validate();
    collect_symbols();
    int current_address = 0;
    for (auto &&c : commands)
    {
        if (c->type == command_type::no_command)
            continue;
        symbols["currentaddress"] = current_address;
        std::vector<uint8_t> data = validators_provider::validators[c->mnemonic->value.value]->evaluate(*c,symbols);
        out.insert(std::end(out), std::begin(data), std::end(data));
        if(validators_provider::validators[c->mnemonic->value.value]->address_created)
        {
            if (c->type == command_type::command24)
            {
                movable_names.push_back(current_address + 1);
            }else
                movable_names.push_back(current_address + 2);
            validators_provider::validators[c->mnemonic->value.value]->address_created = false;
        }
        current_address += (int)c->type;
    }
}

void assembler::write(std::string outfile)
{
    std::ofstream wr = std::ofstream(outfile,std::ios_base::binary);
    if(wr.is_open())
    {
        uint16_t count = movable_names.size();
        wr.write((char*)&count,sizeof(count));
        wr.write((char*)movable_names.data(),sizeof(uint16_t) * movable_names.size());
        wr.write((char*)out.data(),out.size());
        wr.close();
    }
}