#include "validator_provider.h"

std::map<std::string,validator*> validators_provider::validators = {
    {"adds",new reg_reg_reg()}
};
