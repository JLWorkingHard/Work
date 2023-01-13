#include <vector>


class ParseLine{
    // separator character
    private:
        const char small = '<';
        const char big = '>';
        const char BPL = '{';
        const char BPR = '}';
        const char comma = ',';
    public:
        void parse(unsigned &vex, std::vector<unsigned> &nums, unsigned &amount);  
        void CNF_SAT(unsigned &vex,unsigned &amount,std::vector<unsigned> &nums); 
};