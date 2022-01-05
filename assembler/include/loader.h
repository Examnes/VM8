#if !defined(ASM_LOADER_HH)
#define ASM_LOADER_HH
#include <string>
#include <vector>

class loader
{
private:
    std::string filename;
public:
    std::string content;
    loader() = default;
    loader(std::string filename);
    bool load();
    ~loader();
};


#endif // ASM_LOADER_HH
