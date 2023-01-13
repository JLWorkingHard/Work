#include <queue>
class ParseLine{
    // separator character
    private:
        const char small = '<';
        const char big = '>';
        const char BPL = '{';
        const char BPR = '}';
        const char comma = ',';
    public:
        void parse(unsigned &vex,std::queue<unsigned> &nums,unsigned &amount);   
};