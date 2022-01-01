#include "loader.h"

#include <fstream>
#include <sstream>
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
        while (!file.eof())
        {
            std::string line;
            getline(file,line);
            lines.push_back(line);            
        }
        return true;
    }
    return false;
}
