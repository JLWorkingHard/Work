#include <iostream>
#include <sstream>
#include <vector>
#include "parse.h"
#include "spfa.h"
void ParseLine::parse(unsigned &vex,std::queue<unsigned> &nums,unsigned &amount)
{
// read from stdin until EOF
    Spfa B;
    std::vector<std::vector<unsigned> >adj(3);
    bool f = false;
    bool flag = false;
    bool flag1 = false;
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
                f = false;
                flag = false;
                if (flag1)
                {
                    std::vector<std::vector<unsigned> >empty(3);
                    adj = empty; 
                }
                input >> vex;
                if (input.fail()) 
                {
                    flag = true;
                    std::cerr << "Error: child_a2 Error parsing a number\n";
                    break;
                }
                flag1 = true;
                std::cout << line << std::endl;
                break;
            case 'E':
                while (!nums.empty()) 
                {
                    nums.pop();
                }
                unsigned v_edge;
                char separator;
                input >> separator;
                if (input.fail() || separator != BPL) 
                {
                    flag = true;
                    std::cerr << "Error: child_a2 Error parsing a separator\n";
                    break;
                }
                while(!input.eof())
                {
                    input >> separator;
                    if (input.fail()) 
                    {
                        flag = true;
                        std::cerr << "Error: child_a2 Error parsing a separator\n";
                        break;
                    }
                    if (separator == BPR)
                    {
                        f = true;
                        break;
                    }
                    if (separator != small)
                    {
                        flag = true;
                        std::cerr << "Error: child_a2 Error parsing a separator\n";
                        break;
                    }
                    input >> v_edge;
                    if (input.fail())
                    {
                        flag = true;
                        std::cerr << "Error: child_a2 Error parsing a number\n";
                        break;
                    }
                    if (v_edge > vex || v_edge == 0)
                    {
                        flag = true;
                        std::cerr << "Error child_a2 vertex out of range\n";
                        break;
                    }
                    else
                        {
                            nums.push(v_edge);
                        }
                    input >> separator;
                    if(input.fail() || separator != comma)
                        {
                            flag = true;
                            std::cerr << "Error child_a2 Error parsing a separator\n";
                            break;
                        }
                    input >> v_edge;
                    if (input.fail())
                    {
                        flag = true;
                        std::cerr << "Error: child_a2 Error parsing a number\n";
                        break;
                    }
                    if (v_edge > vex || v_edge == 0)
                    {
                        flag = true;
                        std::cerr << "Error: child_a2 vertex out of range\n";
                        break;
                    }
                    else
                        {
                            nums.push(v_edge);
                        }
                    input >> separator;
                    if(input.fail() || separator != big)
                        {
                            flag = true;
                            std::cerr << "Error: child_a2 Error parsing a separator\n";
                            break;
                        }
                    input >> separator;
                    if (input.fail())
                    {
                        flag = true;
                        std::cerr << "Error: child_a2 Error parsing a separator\n";
                        break;
                    }
                    if (separator == BPR)
                    {
                        break;
                    }
                    if (separator != comma)
                    {
                        flag = true;
                        std::cerr << "Error: child_a2 Error parsing a separator\n";
                    }
                }
                amount = (nums.size())/2;
                std::cout << line << std::endl;
                break;
            case 's':
                unsigned start;
                input >> start;
                if (input.fail()) 
                {
                    std::cerr << "Error: child_a2 Error parsing a number\n";
                    break;
                }
                unsigned end;
                input >> end;
                if (input.fail()) 
                {
                    std::cerr << "Error: child_a2 Error parsing a number\n";
                    break;
                }
                if (flag)
                {
                    nums = std::queue<unsigned>();
                    std::cerr << "Error: from child_a2, fail to input a graph,s is an invalid comment" << std::endl;
                    break;
                }
                if (!flag)
                {
                    if (start > vex || end > vex || start == 0 || end == 0)
                        {
                            std::cerr << "Error: child_a2 vertex out of range\n";
                            break;
                        }
                    if (f)
                    {
                        if (start != end)
                        {
                            std::cerr << "Error: from child_a2, given source and destination" << " are not connected" << std::endl;
                            break;
                        }
                    }
                    if (start == end)
                        {
                            std::cout << start << std::endl;
                            break;
                        }
                    if (!nums.empty())
                    {
                        B.resize(adj, vex);
                        for (unsigned i=0;i<amount;i++)
                        {
                            unsigned src = nums.front();
                            nums.pop();
                            unsigned dest = nums.front();
                            nums.pop();
                            B.putin(adj, src, dest);
                        }
                    }
                    B.putout(adj, start, end, vex);
                    break;
                }
            }
        break;
        }
    }
}
