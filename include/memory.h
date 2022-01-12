#ifndef VM_MEMORY_H
#define VM_MEMORY_H

#include "types.h"
#include <stdexcept>
#include <vector>

#define VM_MEMORY_SIZE 8 * 8 * 8 * 8 * sizeof(word)

class memory
{
public:
	int start;
	memory()
	{
		data = std::vector<word>(VM_MEMORY_SIZE,0);
	}

	word &operator[](word i)
	{
		if (i >= VM_MEMORY_SIZE)
		{
			throw std::out_of_range("Адрес за границами допустимых значений (от 0 до 8^4)");
		}
		return data[i];
	}
private:
	friend void load_memory_from_file(std::string s, memory &m, addr_t offset);
	std::vector<word> data;
};

#endif