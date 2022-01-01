#if !defined(JUMP_PROVIDER_H)
#define JUMP_PROVIDER_H

#include "base_provider.h"

class jump_relative_provider :public base_provider
{
private:
    /* data */
public:
    int get_size(std::vector<std::string> arguments){return 2;}
    std::vector<uint8_t> get_data(std::vector<std::string> arguments)
    {
        std::vector<uint8_t> data;
        if (arguments.size() != 1)
        {
            throw "Неверное количество аргументов";
        }
        if (std::all_of(arguments[0].begin(), arguments[0].end(), ::isdigit))
        {
            int8_t relation = std::stoi(arguments[0]);
            data.push_back(opcode || (relation & 1) >> 7);
            data.push_back(relation << 1);
        }else
        {
            throw "Аргумент должен быть числом";
        }
        return data;
    }
    jump_relative_provider(/* args */);
    ~jump_relative_provider();
};

class jump_long_provider :public base_provider
{
private:
    /* data */
public:
    int get_size(std::vector<std::string> arguments){return 3;}
    std::vector<uint8_t> get_data(std::vector<std::string> arguments)
    {
        std::vector<uint8_t> data;
        if (arguments.size() != 1)
        {
            throw "Неверное количество аргументов";
        }
        uint8_t indirect = false;
        if (arguments[0][0] == '[')
        {
            arguments[0] = arguments[0].substr(1,arguments[0].size() - 1);
            indirect = 0b00000001;
        }
        
        if (is_symbol(arguments[0]))
        {
            data.push_back(opcode | indirect);
            uint16_t address = symbols->at(arguments[0]);
            data.push_back(address & 0xFF);
            data.push_back(address << 8);
        }else
        {
            throw "Аргумент должен быть меткой";
        }
        return data;
    }
    jump_long_provider(/* args */);
    ~jump_long_provider();
};

class jump_long_relative_provider :public base_provider
{
private:
    /* data */
public:
    int get_size(std::vector<std::string> arguments){return 4;}
    std::vector<uint8_t> get_data(std::vector<std::string> arguments)
    {
        std::vector<uint8_t> data;
        if (arguments.size() != 1)
        {
            throw "Неверное количество аргументов";
        }
        uint8_t indirect = false;
        if (arguments[0][0] == '[')
        {
            arguments[0] = arguments[0].substr(1,arguments[0].size() - 1);
            indirect = 0b00000001;
        }
        components_t components = get_components(arguments[0]);
        data.push_back(opcode | indirect);
        uint8_t r1,r2,r3;
        if (components.address)
        {
            r1 = 1;
            r2 = 255;
            if (components.register_id != 255)
            {
                r2 = components.register_id;
            }
        }else
        {
            throw "Должен быть адрес";
            r1 = 0;
        }
        
        
        return data;
    }
    jump_long_relative_provider(/* args */);
    ~jump_long_relative_provider();
};



#endif // JUMP_PROVIDER_H
