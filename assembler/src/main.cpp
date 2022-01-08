#include "assembler.h"
#include <iostream>

int main(int argc,char** argv)
{
    if (argc != 3)
    {
        std::cout << "Ассемблер требует путь к компилируемому файлу и выходному файлу" << std::endl;
    }
    assembler ass = assembler(argv[1]);
    ass.assemble();
    ass.write(argv[2]);
    return 0;
}