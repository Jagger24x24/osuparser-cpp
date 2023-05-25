#include <iostream>
#include "Classes.h"

int main()
{
    std::cout << "Hello World!\n";
    HitCirlce test;
    test.Position = { 0, 0 };
    test.Time = 0;
    test.ObjectType = ObjectType::HitCircle;
    test.HitSound = 3;
    test.HitSample = { 3, 2, 0, 50, "0" };
    std::cout << test.to_string() << std::endl;
}
