#if !defined(METADATA_PROVIDER_H)
#define METADATA_PROVIDER_H

#include <map>

class metadata_provider
{
public:
    static std::map<std::string,int> register_ids;
    static std::map<std::string,int> opcode_ids;
};


#endif // METADATA_PROVIDER_H
