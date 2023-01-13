#include <queue>
#include <iostream>
#include <sstream>
#include "parse.h"
#include <algorithm>
#include <memory>
#include "minisat/core/SolverTypes.h"
#include "minisat/core/Solver.h"

void ParseLine::CNF_SAT(unsigned &vex,unsigned &amount,std::vector<unsigned> &nums)
{
    std::queue<int> answers;
    int vcover = 1;
    std::unique_ptr<Minisat::Solver> solver(new Minisat::Solver());
    std::vector< std::vector<Minisat::Lit> > litero;
    Minisat::vec<Minisat::Lit> clause;
    bool res;
    bool flag = false;
    while(vcover <= static_cast<int>(amount))
    {
        solver.reset(new Minisat::Solver());
        litero.clear();
        litero.resize(vex,std::vector<Minisat::Lit>(vcover));
        for (unsigned i=0; i<vex; i++)
        {
            for (int j=0; j<vcover; j++)
            {
                litero[i][j] = Minisat::mkLit(solver->newVar());
            }
        }
        //clause 1
        for (int i=0; i<vcover;i++)
        {
            for(unsigned n=0;n<vex;n++)
            {	
                clause.push(litero[n][i]);
                //(x 1,i ∨ x 2,i ∨ · · · ∨ x n,i )
            }
            solver->addClause_(clause);
		    clause.clear();
        }
        //clause 2
        for (unsigned m=0; m<vex;m++)
        {
            for (int p=0;p<vcover;p++)
            {	
                for(int q=p+1;q<vcover;q++)
                {
                    solver->addClause(~litero[m][p],~litero[m][q]);
                    //(¬x m,p ∨ ¬x m,q )
                }
            }
        }
        //clause 3
        for (int m=0; m<vcover;m++)
        {
            for(unsigned p=0;p<vex;p++)
            {
                for(unsigned q=p+1;q<vex;q++)
                {
                    solver->addClause(~litero[p][m],~litero[q][m]);             
                    //(¬x p,m ∨ ¬x q,m )	
                }
            }
        }
        //clause 4
        for (unsigned i=0;i<nums.size();i+=2) //elength 4
        {
            for (int k=0; k<vcover;k++)
            {
                clause.push(litero[nums[i]-1][k]);
                clause.push(litero[nums[i+1]-1][k]);
            }
            solver->addClause_(clause);
		    clause.clear();
        }
        res = solver->solve();
        if (res == 0)
        {
            vcover++;
        }
        else
        {
            for (unsigned i = 0; i < vex; i++)
            {
                for (int j = 0; j < vcover; j++)
                {
                    if(Minisat::toInt(solver->modelValue(litero[i][j])) == 0)
                    {
                        answers.push(i+1);
                    }
                }
            }
            if (!answers.empty())
            {
                std::cout << answers.front();
                answers.pop();
            }
            while(!answers.empty())
            {
                std::cout << " " << answers.front();
                answers.pop();
            }
            std::cout << std::endl;
            flag = true;
            break;
        }
    }
    if (!flag)
    {
        std::cerr << "vertex cover for this input graph does not exist" << std::endl;
    }
}
void ParseLine::parse(unsigned &vex, std::vector<unsigned> &nums, unsigned &amount)
{
// read from stdin until EOF
    while (!std::cin.eof()) 
    {
        std::string line;

        std::getline(std::cin, line);
        std::istringstream input(line);
        while (!input.eof()) 
        {
            char command;
            input >> command;
            if (input.fail())
            {
                break;
            }
            switch(command)
            {
            case 'V':
                input >> vex;
                if (input.fail()) 
                {
                    std::cerr << "Error: Error parsing a number\n";
                    break;
                }
                break;
            case 'E':
                if (!nums.empty()) 
                {
                    nums.clear();
                }
                unsigned v_edge;
                char separator;
                input >> separator;
                if (input.fail() || separator != BPL) 
                {
                    std::cerr << "Error: Error parsing a separator\n";
                    break;
                }
                while(!input.eof())
                {
                    input >> separator;
                    if (input.fail()) 
                    {
                        std::cerr << "Error: Error parsing a separator\n";
                        break;
                    }
                    if (separator == BPR)
                    {
                        break;
                    }
                    if (separator != small)
                    {
                        std::cerr << "Error: Error parsing a separator\n";
                        break;
                    }
                    input >> v_edge;
                    if (input.fail())
                    {
                        std::cerr << "Error: Error parsing a number\n";
                        break;
                    }
                    if (v_edge > vex || v_edge == 0)
                    {
                        std::cerr << "Error: vertex out of range\n";
                        break;
                    }
                    else
                        {
                            nums.push_back(v_edge);
                        }
                    input >> separator;
                    if(input.fail() || separator != comma)
                        {
                            std::cerr << "Error: Error parsing a separator\n";
                            break;
                        }
                    input >> v_edge;
                    if (input.fail())
                    {
                        std::cerr << "Error: Error parsing a number\n";
                        break;
                    }
                    if (v_edge > vex || v_edge == 0)
                    {
                        std::cerr << "Error: vertex out of range\n";
                        break;
                    }
                    else
                        {
                            nums.push_back(v_edge);
                        }
                    input >> separator;
                    if(input.fail() || separator != big)
                        {
                            std::cerr << "Error: Error parsing a separator\n";
                            break;
                        }
                    input >> separator;
                    if (input.fail())
                    {
                        std::cerr << "Error: Error parsing a separator\n";
                        break;
                    }
                    if (separator == BPR)
                    {
                        break;
                    }
                    if (separator != comma)
                    {
                        std::cerr << "Error: Error parsing a separator\n";
                    }
                }
                amount = (nums.size())/2;
                CNF_SAT(vex,amount,nums);
                break;
            }
        break;
        }
    }
}
