#include "validator_provider.h"

std::map<std::string,validator*> validators_provider::validators = {
    {"adds",new reg_reg_reg()},
    {"muls",new reg_reg_reg()},
    {"divs",new reg_reg_reg()},
    {"subs",new reg_reg_reg()},
    {"enter",new no_op()},
    {"leave",new no_op()},
    {"jmpl",new jmpl_v()},
    {"jmpr",new jmpr_v()},
    {"fadd",new no_op()},
    {"fdiv",new no_op()},
    {"fmul",new no_op()},
    {"fsub",new no_op()},
    {"addws",new mathw_v()},
    {"mulws",new mathw_v()},
    {"divws",new mathw_v()},
    {"subws",new mathw_v()},
    {"addw",new mathw_v()},
    {"mulw",new mathw_v()},
    {"divw",new mathw_v()},
    {"subw",new mathw_v()}
};
