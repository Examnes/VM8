#include "assembler.h"
#include <sstream>
#include <cstring>
#include "token.h"
#include "lexer.h"
#include "metadata_provider.h"
#include "validator_provider.h"

assembler::assembler(std::string file)
{
    l = loader(file);
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
        symbols["currentaddress"] = current_address;
        std::vector<uint8_t> data = validators_provider::validators[c->mnemonic->value.value]->evaluate(*c,symbols);
        out.insert(std::end(out), std::begin(data), std::end(data));
        current_address += (int)c->type;
    }
}