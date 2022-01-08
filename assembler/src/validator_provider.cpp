#include "validator_provider.h"

std::map<std::string,validator*> validators_provider::validators = {
    {"adds",new reg_reg_reg()},
    {"muls",new reg_reg_reg()},
    {"divs",new reg_reg_reg()},
    {"subs",new reg_reg_reg()},
    {"enter",new no_op()},
    {"leave",new no_op()},
    {"jmpl",new jmpl_v()}
};
