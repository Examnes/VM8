#if !defined(COMMAND_PROVIDERS_H)
#define COMMAND_PROVIDERS_H

#include "providers/base_provider.h"
#include "providers/int_math_provider.h"
#include "providers/jump_provider.h"
#include "providers/mov_command_provider.h"
#include "providers/one_byte_cmd.h"
#include "providers/one_register_cmd.h"
#include "providers/short_math_provider.h"

std::map<std::string, base_provider*> get_providers()
{
    std::map<std::string, base_provider*> m;

    return m;
}

#endif // COMMAND_PROVIDERS_H
