#if !defined(VALIDATOR_H)
#define VALIDATOR_H

#include "expressions.h"

struct validator
{
    virtual bool set_size(command_expression& cmd) = 0;
    virtual std::vector<uint8_t> evaluate(command_expression& cmd, std::map<std::string, uint16_t>& symbols) = 0;
    validator() = default;
    virtual ~validator() = 0;
};


#endif // VALIDATOR_H
