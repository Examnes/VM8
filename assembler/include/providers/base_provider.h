#if !defined(BASE_COMMAND_PROVIDER_HH)
#define BASE_COMMAND_PROVIDER_HH

#include <string>
#include <map>
#include <vector>
#include <memory>
#include <algorithm>
#include <sstream>
#include "math_parser.h"

class base_provider
{
public:
    struct components_t
    {
        uint8_t register_id;
        uint16_t address;
    };
    
    static std::vector<std::string> get_arguments(std::string command_string)
    {
        std::vector<std::string> seglist;
        command_string.erase(0,command_string.find_first_of(' '));
        command_string.erase(0,command_string.find_first_not_of(' '));
        std::stringstream ss(command_string);
        
        std::string segment;
        while(std::getline(ss, segment, ','))
        {
            segment.erase(segment.find_last_not_of(' ') + 1);
            segment.erase(0, segment.find_first_not_of(' '));
            seglist.push_back(segment);
        }
        return seglist;
    }

    components_t get_components(std::string relative_argument)
    {
        components_t c;
        c.register_id = 255;
        size_t pos = relative_argument.find("%", 0);
        while(pos != std::string::npos)
        {
            std::string symbol = relative_argument.substr(pos + 1,relative_argument.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"));
            if (is_register(symbol))
            {
                relative_argument.erase(pos,symbol.length() + 1);
                c.register_id = register_ids->at(symbol);
            }else if (is_symbol(symbol))
            {
                relative_argument.replace( pos,symbol.length(),std::to_string(symbols->at(symbol)) );
            }else
            {
                throw "Неизвестный символ";
            }
            pos = relative_argument.find("%",pos+1);
        }
        Parser p = Parser(relative_argument);
        Expression e = p.parse();
        c.address = eval(e);
        return c;
    }

    static std::string get_mnemonic(std::string command_string)
    {
        return command_string.substr(0,command_string.find_first_of(' '));
    }

    base_provider(uint8_t opcode):opcode(opcode){};
    void init(std::map<std::string, uint16_t> &symbols, std::map<std::string, uint8_t> &register_ids)
    {
        this->symbols = &symbols;
        this->register_ids = &register_ids;
    }
    virtual ~base_provider() = default;
    virtual std::vector<uint8_t> get_data(std::vector<std::string> arguments) = 0;
    virtual int get_size(std::vector<std::string> arguments) = 0;

protected:
    
    
    bool is_register(std::string argument)
    {
        return register_ids->count(argument);
    }
    bool is_symbol(std::string argument)
    {
        return symbols->count(argument);
    }
    std::map<std::string, uint16_t> *symbols;
    std::map<std::string, uint8_t> *register_ids;
    uint8_t opcode;
};

#endif // BASE_COMMAND_PROVIDER_HH
