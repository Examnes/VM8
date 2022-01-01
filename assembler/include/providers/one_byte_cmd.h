#if !defined(ONE_BYTE_CMD_HH)
#define ONE_BYTE_CMD_HH

#include "base_provider.h"

class one_byte_cmd : public base_provider
{
private:
    /* data */
public:
    int get_size(std::vector<std::string> arguments){return 1;}
    std::vector<uint8_t> get_data(std::vector<std::string> arguments)
    {
        std::vector<uint8_t> data;
        data.push_back(opcode);
        return data;
    }
    one_byte_cmd(/* args */);
    ~one_byte_cmd();
};




#endif // ONE_BYTE_CMD_HH
