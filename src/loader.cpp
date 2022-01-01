#include "loader.h"
#include <fstream>
#include <stdexcept>

void load_memory_from_file(std::string s, memory &m,addr_t offset)
{
    std::ifstream file = std::ifstream();
    file.open(s, std::ifstream::ate | std::ios::binary);
    if (!file.good())
    {
        throw std::runtime_error("Файл не найден");
    }
    std::streamsize size = VM_MEMORY_SIZE;
    if (static_cast<size_t>(file.tellg()) < VM_MEMORY_SIZE)
    {
        size = static_cast<std::streamsize>(file.tellg());
    }
    file.seekg(0);
    int tablesize = 0;
    file.read(reinterpret_cast<char*>(&tablesize), sizeof(int));
    addr_t* movable = new addr_t[tablesize];
    file.read(reinterpret_cast<char*>(movable), tablesize);
    file.seekg(tablesize * 2 + sizeof(int));
    file.read(reinterpret_cast<char*>(m.data), size - tablesize * sizeof(addr_t) + sizeof(int));
    for (size_t i = 0; i < tablesize; i++)
    {
        converter cov;
        cov.data[0] = m.data[tablesize];
        cov.data[1] = m.data[tablesize + 1];
        cov.short_unsigned[0] += offset;
        m.data[tablesize] = cov.data[0];
        m.data[tablesize + 1] = cov.data[1];
    }
    delete movable;
    file.close();
}