#include "assembler.h"
#include <iostream>

int main(int argc,char** argv)
{
    if (argc == 0)
    {
        std::cout << "Ассемблер требует путь к компилируемому файлу" << std::endl;
    }
    return 0;
}