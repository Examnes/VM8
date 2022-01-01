#if !defined(INT_MATH_PROVIDER_H)
#define INT_MATH_PROVIDER_H

#include "base_provider.h"
#include "trim.h"

class int_math_provider : public base_provider
{
private:
    /* data */
public:
    int get_size(std::vector<std::string> arguments) { return 2; }
    std::vector<uint8_t> get_data(std::vector<std::string> arguments)
    {
        std::vector<uint8_t> data;
        if (arguments.size() != 2)
        {
            throw "Неверное количество аргументов";
        }
        if (is_register(arguments[0]))
        {
            std::vector<std::string> components = trimmer::split(arguments[1], "+");
            if (components.size() == 2)
            {
                trimmer::trim(components[0]);
                trimmer::trim(components[1]);
                if (is_register(components[0]) and is_register(components[1]))
                {
                    uint8_t r1 = register_ids->at(arguments[0]);
                    uint8_t r2 = register_ids->at(components[0]);
                    uint8_t r3 = register_ids->at(components[1]);
                    data.push_back(opcode | (r1 & 1) >> 7);
                    data.push_back(r1 << 1 | r2 >> 2 | r3 >> 5);
                }
                else
                {
                    throw "Аргументы должны быть регистрами";
                }
            }
        }
        else
        {
            throw "Аргументы должны быть регистрами";
        }
        return data;
    }
    int_math_provider(/* args */);
    ~int_math_provider();
};

#endif // INT_MATH_PROVIDER_H
