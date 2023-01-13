 #include "parse.h"

int main(int argc, char **argv) 
{
    unsigned vex;
    std::vector<unsigned> nums;
    unsigned amount;
    ParseLine P;
    P.parse(vex,nums,amount);
    return 0;
}
