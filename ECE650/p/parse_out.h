#include <vector>
#include <iostream>


class ParseAndOut{
    // separator character
    private:
        const char small = '<';
        const char big = '>';
        const char BPL = '{';
        const char BPR = '}';
        const char comma = ',';
        unsigned vex;
        std::vector<unsigned> nums;
        unsigned amount;
        std::vector <std::string> answer_set;
    public:
        // ParseAndOut(unsigned &v, std::vector<unsigned> &n, unsigned &a,std::vector <std::string> &a_s);
        void parse();  
        static void *CNF_SAT(void *arg); 
        static void *APPROX_VC_1(void *arg); 
};

