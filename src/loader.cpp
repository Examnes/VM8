#include "loader.h"
#include <fstream>
#include <stdexcept>
#include <algorithm>

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
    uint16_t tablesize = 0;
    file.read(reinterpret_cast<char*>(&tablesize), sizeof(uint16_t));
    addr_t* movable = new addr_t[tablesize];
    file.read(reinterpret_cast<char*>(movable), tablesize * sizeof(uint16_t));
    file.read(reinterpret_cast<char*>(m.data.data()), size - (tablesize * sizeof(addr_t) + sizeof(uint16_t)));
    for (size_t i = 0; i < tablesize; i++)
    {
        converter cov;
        cov.data[0] = m.data[movable[i]];
        cov.data[1] = m.data[movable[i] + 1];
        cov.short_unsigned[0] += offset;
        m.data[movable[i]] = cov.data[0];
        m.data[movable[i] + 1] = cov.data[1];
    }
    std::rotate(m.data.rbegin(), m.data.rbegin() + offset, m.data.rend());
    delete movable;
    m.start = offset;
    file.close();
}