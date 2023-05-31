#include <iostream>
#include "Functions.h"

int main()
{
    auto map = OsuFunctions::ReadFile("file.osu");
    std::cout << map.General.AudioFilename << std::endl;
}