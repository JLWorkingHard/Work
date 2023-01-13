#include <memory>
#include <iostream>
#include <sstream>
#include <pthread.h>
#include <algorithm>
#include "parse_out.h"
#include "minisat/core/SolverTypes.h"
#include "minisat/core/Solver.h"


pthread_mutex_t mutex;


// -----------------------------------------------------------------------------------------------------------------


void *ParseAndOut::CNF_SAT(void *arg)
{
    ParseAndOut* P = (ParseAndOut*)arg;
    std::vector<int> answers;
    int vcover = 1;
    std::unique_ptr<Minisat::Solver> solver(new Minisat::Solver());
    std::vector< std::vector<Minisat::Lit> > litero;
    Minisat::vec<Minisat::Lit> clause;
    bool res;
    bool flag = false;
    std::string output = "CNF_SAT_VC: ";
    while(vcover <= static_cast<int>(P->amount))
    {
        solver.reset(new Minisat::Solver());
        litero.clear();
        litero.resize(P->vex,std::vector<Minisat::Lit>(vcover));
        for (unsigned i=0; i<P->vex; i++)
        {
            for (int j=0; j<vcover; j++)
            {
                litero[i][j] = Minisat::mkLit(solver->newVar());
            }
        }
        //clause 1
        for (int i=0; i<vcover;i++)
        {
            for(unsigned n=0;n<P->vex;n++)
            {	
                clause.push(litero[n][i]);
                //(x 1,i ∨ x 2,i ∨ · · · ∨ x n,i )
            }
            solver->addClause_(clause);
		    clause.clear();
        }
        //clause 2
        for (unsigned m=0; m<P->vex;m++)
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
            for(unsigned p=0;p<P->vex;p++)
            {
                for(unsigned q=p+1;q<P->vex;q++)
                {
                    solver->addClause(~litero[p][m],~litero[q][m]);             
                    //(¬x p,m ∨ ¬x q,m )	
                }
            }
        }
        //clause 4
        for (unsigned i=0;i<P->nums.size();i+=2) //elength 4
        {
            for (int k=0; k<vcover;k++)
            {
                clause.push(litero[P->nums[i]-1][k]);
                clause.push(litero[P->nums[i+1]-1][k]);
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
            for (unsigned i = 0; i < P->vex; i++)
            {
                for (int j = 0; j < vcover; j++)
                {
                    if(Minisat::toInt(solver->modelValue(litero[i][j])) == 0)
                    {
                        answers.push_back(i+1);
                    }
                }
            }
            for (int i : answers) 
            {
                if(i != answers.back())
                {
                    output += std::to_string(i) + " ";
                }
                else
                {
                    output += std::to_string(i);
                }  
            }
            flag = true;
            break;
        }
    }
    if (!flag)
    {
        std::cerr << "vertex cover for this input graph does not exist" << std::endl;
    }
    pthread_mutex_lock(&mutex);
    P->answer_set.push_back(output);
    pthread_mutex_unlock(&mutex);
    return NULL;
}


// ----------------------------------------------------------------------------------------------------------------


unsigned HighestDegree(std::vector <unsigned> &vertices,std::vector<unsigned> &temp) 
{
    unsigned answers = 0;
    int maxCount = 0;
    for (unsigned i : vertices) 
    {
        int count = 0;
        for (unsigned j=0; j<temp.size(); j+=2) 
        {
            if (i == temp[j] || i == temp[j+1]) 
            {
                count++;
            }
        }
        if (count > maxCount) 
        {
            maxCount = count;
            answers = i;
        }
    }
    std::vector<unsigned> new_temp;
    for (unsigned i=0; i<temp.size(); i+=2)
    {
        if (answers != temp[i] && answers != temp[i+1]) 
        {
            new_temp.push_back(temp[i]);
            new_temp.push_back(temp[i+1]);
        }
    }
    temp = new_temp;
    return answers;
}

// ----------------------------------------------------------------------------------------------------------------


void *ParseAndOut::APPROX_VC_1(void *arg) 
{
    ParseAndOut* P = (ParseAndOut*)arg;
    std::vector <int> Answer1;
    std::vector<unsigned> temp = P->nums;
    std::vector <unsigned> vertices;
    std::string output = "APPROX_VC_1: ";
    for (unsigned i=0; i<P->vex; i++)
    {
        vertices.push_back(i+1);
    }
    while (temp.size() > 0) 
    {
        Answer1.push_back(HighestDegree(vertices,temp));
    }
    sort(Answer1.begin(), Answer1.end());
    for (int i : Answer1) 
    {
        if(i != Answer1.back())
        {
            output += std::to_string(i) + " ";
        }
        else
        {
            output += std::to_string(i);
        }  
    }
    pthread_mutex_lock(&mutex);
    P->answer_set.push_back(output);
    pthread_mutex_unlock(&mutex);
    return NULL;
}


// ----------------------------------------------------------------------------------------------------------------


void ParseAndOut::parse()
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
                pthread_t t1, t2;
                pthread_create(&t1, NULL, &CNF_SAT, this);
                pthread_create(&t2, NULL, &APPROX_VC_1, this);
                // pthread_create(&t3, NULL, &APPROX_VC_2, NULL);
                pthread_join(t1, NULL);
                pthread_join(t2, NULL);
                // pthread_join(t3, NULL);
                std::string cnf, appr1, appr2;
                for(auto str : answer_set) 
                {
                    if(str.find("CNF_SAT_VC")!=std::string::npos) 
                    {
                        cnf = str;
                    }
                    if(str.find("APPROX_VC_1")!=std::string::npos) 
                    {
                        appr1 = str;
                    }
                    // if(str.find("APPROX_VC_2")!=std::string::npos) 
                    // {
                    //     appr2 = str;
                    // }
                }
                std::cout << cnf << std::endl << appr1 << std::endl;
                break;
            }
        break;
        }
    }
}
