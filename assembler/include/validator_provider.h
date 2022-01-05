#if !defined(VALIDATOR_PROVIDER_H)
#define VALIDATOR_PROVIDER_H

#include "validator.h"

class validators_provider
{
public:
    static std::map<std::string,validator*> validators;
};

#endif // VALIDATOR_PROVIDER_H
