#if !defined(SHORT_MATH_PROVIDER_HH)
#define SHORT_MATH_PROVIDER_HH

#include "base_provider.h"

class short_math_provider : public base_provider
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
        if (is_register(arguments[0]) and is_register(arguments[1]) and is_register(arguments[2]))
        {
            uint8_t r1 = register_ids->at(arguments[0]);
            uint8_t r2 = register_ids->at(arguments[1]);
            uint8_t r3 = register_ids->at(arguments[2]);
            data.push_back(opcode | (r1 & 1) >> 7);
            data.push_back(r1 << 1 | r2 >> 2 | r3 >> 5);
        }else
        {
            throw "Аргументы должны быть регистрами";
        }
        return data;
    }
    short_math_provider(/* args */);
    ~short_math_provider();
};

#endif // SHORT_MATH_PROVIDER_HH
