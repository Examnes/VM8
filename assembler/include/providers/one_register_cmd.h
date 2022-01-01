#if !defined(ONE_REGISTER_CMD_H)
#define ONE_REGISTER_CMD_H

#include "base_provider.h"

class one_register_cmd : public base_provider
{
private:
    /* data */
public:
    int get_size(std::vector<std::string> arguments){return 2;}
    std::vector<uint8_t> get_data(std::vector<std::string> arguments)
    {
        std::vector<uint8_t> data;
        if (arguments.size() != 3)
        {
            throw "Неверное количество аргументов";
        }
        if (is_register(arguments[0]))
        {
            uint8_t r1 = register_ids->at(arguments[0]);
            data.push_back(opcode || (r1 & 1) >> 7);
            data.push_back(r1 << 1);
        }else
        {
            throw "Аргументы должны быть регистрами";
        }
        return data;
    }
    one_register_cmd(/* args */);
    ~one_register_cmd();
};


#endif // ONE_REGISTER_CMD_H
