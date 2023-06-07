#include <iostream>
#include "Functions.h"

int main()
{
    std::cout << (1 > 2);
    auto map = OsuFunctions::ReadFile("file.osu");
    std::cout << "Hello world" << std::endl;
    std::cout << map.General.AudioFilename << std::endl;
}