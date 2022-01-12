#include "interpretator.h"
#include "loader.h"
#include <iostream>

using namespace std;

int main(int argc,char** argv)
{
    if (argc == 0)
    {
        std::cout << "Виртуальная машина требует путь к исполняемому файлу в качестве первого аргумента коммандной строки" << std::endl;
    }

    memory m = memory();
    try
    {
        load_memory_from_file(argv[1],m,std::stoi(argv[2]));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    interpretator vm = interpretator(m);

    try
    {
        vm.start();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}