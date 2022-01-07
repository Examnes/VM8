#include "loader.h"

#include <fstream>
#include <sstream>
#include <streambuf>
using namespace std;

loader::loader(std::string filename) : filename(filename)
{
}

loader::~loader()
{
}

bool loader::load()
{
    ifstream file = ifstream(filename);
    if(file.is_open())
    {
        content = std::string((std::istreambuf_iterator<char>(file)),
                 std::istreambuf_iterator<char>());
        return true;
    }
    return false;
}
