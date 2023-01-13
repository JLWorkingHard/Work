#include "parse.h"
#include <iostream>
int main() 
{
    unsigned vex;
    std::queue<unsigned> nums;
    unsigned amount;
    ParseLine P;
    P.parse(vex,nums,amount);
    return 0;
}