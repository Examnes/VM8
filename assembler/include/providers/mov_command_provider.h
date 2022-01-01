#if !defined(MOV_COMMAND_PROVIDER_HH)
#define MOV_COMMAND_PROVIDER_HH

#include "base_provider.h"

class mov_command_provider : public base_provider
{
private:
    /* data */
public:
    int get_size(std::vector<std::string> arguments)
    {
        if (arguments.size() < 2)
        {
            throw "Неверное количество аргументов";
        }

        if (not is_register(arguments[0]))
        {
            throw "Первый аргумент должен быть: регистр";
        }

        if (is_register(arguments[1]))
            return 2;

        return 4;
    }
    
    std::vector<uint8_t> get_data(std::vector<std::string> arguments)
    {
        std::vector<uint8_t> data;

        uint8_t r2 = register_ids->at(arguments[0]);
        uint8_t r1 = 0;
        uint8_t r3 = 0;
        uint16_t address = 0;
        if (is_register(arguments[1]))
        {
            r3 = register_ids->at(arguments[1]);
        }
        else
        {
            components_t components = get_components(arguments[1]);
            r3 = components.register_id;
            address = components.address;
            if (address != 0 and r3 != 255)
            {
                r1 = 2;
            }
            else if (address != 0)
            {
                r1 = 1;
            }
        }

        data.push_back(opcode | (r1 & 1) >> 7);
        data.push_back(r1 << 1 | r2 >> 2 | r3 >> 5);
        if (r1)
        {
            data.push_back(address & 0xFF);
            data.push_back(address << 8);
        }
        return data;
    }
    mov_command_provider(/* args */);
    ~mov_command_provider();
};

#endif // MOV_COMMAND_PROVIDER_HH