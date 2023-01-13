#include <iostream>
#include <string>
#include <sstream>
#include <random>
#include <vector>
#include <unistd.h>
#include <regex>

std::string translate(int val)
{
    const std::string dictA[]=
    {
        "Zero", "One", "Two", "Three", "Four",
        "Five", "Six", "Seven", "Eight", "Nine",
        "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen",
        "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"
    };
    const std::string dictB[]=
    {
        "Zero", "Ten", "Twenty", "Thirty", "Forty",
        "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"
    };
    const std::string dictC[]=
    {
        "", "Thousand", "Million", "Billion", "Trillion"
        "Thousand Trillion", "Million Trillion", "Billion Trillion"
    };
	std::string s = "";
	unsigned int v = val % 100;
	if(v <= 19)
		s = dictA[v];
	else if(v > 19 && v % 10 == 0)
		s = dictB[v / 10];
	else
		s = ((v / 10)? dictB[v / 10] + " " : "") + dictA[v % 10];
 
	s = ((val / 100)? dictA[val / 100] + " Hundred and " : "") + s;
 
	return s;
}

float PointPosionOfLine(int M_x,int M_y,int A_x,int A_y,int B_x,int B_y)
    {
        // return > 0 right, = 0 online, < 0 left
        return (B_y - M_y) * (A_x - M_x) - (A_y - M_y) * (B_x - M_x);
    }

bool IsPointOnLine(int M_x,int M_y,int A_x,int A_y,int B_x,int B_y)
{
    if (PointPosionOfLine(M_x,M_y,A_x,A_y,B_x,B_y) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }      
}

bool LineCoincide(int A_x,int A_y,int B_x,int B_y,int C_x,int C_y,int D_x,int D_y)
{

    bool onLineA, onLineB, onLineC, onLineD;
    onLineA = IsPointOnLine(A_x,A_y,C_x,C_y,D_x,D_y);
    onLineB = IsPointOnLine(B_x,B_y,C_x,C_y,D_x,D_y);
    onLineC = IsPointOnLine(C_x,C_y,A_x,A_y,B_x,B_y);
    onLineD = IsPointOnLine(D_x,D_y,A_x,A_y,B_x,B_y);
    bool coincide01 = (onLineA && onLineB) || (onLineC && onLineD);
    bool coincide02 = (onLineA && onLineC && (A_x != C_x)&& (A_y != C_y))
        || (onLineA && onLineD && (A_x != D_x) && (A_y != D_y))
        || (onLineB && onLineC && (B_x != C_x) && (B_y != C_y))
        || (onLineB && onLineD && (B_x != D_x) && (B_y != D_y));
    return (coincide01 || coincide02);
}

bool intersection(int A_x,int A_y,int B_x,int B_y,int C_x,int C_y,int D_x,int D_y)
{
    if ((A_x > B_x ? A_x : B_x) < (C_x < D_x ? C_x : D_x) ||
        (A_y > B_y ? A_y : B_y) < (C_y < D_y ? C_y : D_y) ||
        (C_x > D_x ? C_x : D_x) < (A_x < B_x ? A_x : B_x) ||
        (C_y > D_y ? C_y : D_y) < (A_y < B_y ? A_y : B_y))
    {
        return false;
    }
    if ((((A_x - C_x)*(D_y - C_y) - (A_y - C_y)*(D_x - C_x))*
        ((B_x - C_x)*(D_y - C_y) - (B_y - C_y)*(D_x - C_x))) > 0 ||
        (((C_x - A_x)*(B_y - A_y) - (C_y - A_y)*(B_x - A_x))*
        ((D_x - A_x)*(B_y - A_y) - (D_y - A_y)*(B_x - A_x))) > 0)
    {
        return false;
    }
    return true;
}

int main(int argc, char ** argv)
{
    int s_k = 10; //how many street
    int n_k = 5; //how many line segments
    int l_k = 5; //how much time to wait
    int c_k = 20; //range of coordinates
    std::string line;
    if (argc > 1)
    {
        line = argv[1];
        std::string space = " ";
        for (int i = 2; i<argc; i++)
        {
            line = line + space + std::string(argv[i]);
        }
        std::regex newlines_re("-");
        line = std::regex_replace(line, newlines_re, "");
        std::istringstream input(line);
        char command;
        while(!input.eof())
        {
            input >> command;
            if (input.fail())
            {
                std::cerr << "Error: from child_rgen, please provide a command in the correct format\n";
                return -1;
            }
            switch (command)
            {
            case 's':
                input >> s_k;
                if (input.fail()) 
                    {
                        std::cerr << "Error: child_rgen Error parsing a number\n";
                        return -1;
                    }
                if (s_k < 2)
                {
                    s_k = 2;
                }
                break;
            case 'n':
                input >> n_k;
                if (input.fail()) 
                    {
                        std::cerr << "Error: child_rgen Error parsing a number\n";
                        return -1;
                    }
                if (n_k < 1)
                {
                    n_k = 1;
                }
                break;
            case 'l':
                input >> l_k;
                if (input.fail()) 
                    {
                        std::cerr << "Error: child_rgen Error parsing a number\n";
                        return -1;
                    }
                if (l_k < 5)
                {
                    l_k = 5;
                }
                break;
            case 'c':
                input >> c_k;
                if (input.fail()) 
                    {
                        std::cerr << "Error: child_rgen Error parsing a number\n";
                        return -1;
                    }
                break;
            }
        }
    }
    std::uniform_int_distribution<int> s(2, s_k);
    std::uniform_int_distribution<int> n(1, n_k);
    std::uniform_int_distribution<int> l(5, l_k);
    std::uniform_int_distribution<int> c(-c_k, c_k);
    std::random_device rd; //seed source using /dev/urandom
    std::default_random_engine rng(rd()); //random number generator
    typedef struct Street
        {
            std::string name;
            int count_edges;
            std::vector <int> coor;
        }Street;
    int count = 0; 
    int Last_street_count = 0;
    bool Not_first_time = false;
    while(count<25)
    {
        bool flag1 = false;
        bool flag2 = false;
        int n_s = s(rng);
        int n_l = l(rng);
        Street street[n_s];
        for (int i = 0; i<n_s; i++)
        {
            street[i].name = "\"street " + translate(i+1) + "\"";
            int n_n = n(rng);
            street[i].count_edges = n_n;
            int start_x = c(rng);
            int start_y = c(rng);
            street[i].coor.push_back(start_x);
            street[i].coor.push_back(start_y);
            for (int j = 0; j<n_n; j++)
            {
                int next_x = c(rng);
                int next_y = c(rng);
                street[i].coor.push_back(next_x);
                street[i].coor.push_back(next_y);
            }
            //test whether same street has edge with 0 distance and whether edges intersect with another one
            for (int k = 0; k+2<((street[i].count_edges+1)*2); k+=2)
            {
                if (street[i].coor[k] == street[i].coor[k+2] && street[i].coor[k+1] == street[i].coor[k+3])
                {
                    flag1 = true;
                    break;
                }
                for (int l = k+2; l+2<((street[i].count_edges+1)*2); l+=2)
                {
                    if(LineCoincide(street[i].coor[k],street[i].coor[k+1],street[i].coor[k+2],street[i].coor[k+3],street[i].coor[l],street[i].coor[l+1],street[i].coor[l+2],street[i].coor[l+3]))
                    {
                        flag1 = true;
                        break;
                    }
                }
                if (flag1)
                {
                    break;
                }
                for (int m = k+4; m+2<((street[i].count_edges+1)*2); m+=2)
                {
                    if (intersection(street[i].coor[k],street[i].coor[k+1],street[i].coor[k+2],street[i].coor[k+3],street[i].coor[m],street[i].coor[m+1],street[i].coor[m+2],street[i].coor[m+3]))
                    {
                        flag1 = true;
                        break;
                    }
                }
                if (flag1)
                {
                    break;
                }
            }
            if (flag1)
            {
                break;
            }
        }
        if (flag1)
        {
            count+=1;
            continue;
        }
        //test whether diff streets have coincidence
        for(int i = 0; i<n_s; i++)
        {
            for(int j = i+1; j<n_s; j++)
            {
                for (int k = 0; k+2<((street[i].count_edges+1)*2); k+=2)
                {
                    for (int l = 0; l+2<((street[j].count_edges+1)*2); l+=2)
                    {
                        if(LineCoincide(street[i].coor[k],street[i].coor[k+1],street[i].coor[k+2],street[i].coor[k+3],street[j].coor[l],street[j].coor[l+1],street[j].coor[l+2],street[j].coor[l+3]))
                        {
                            flag2 = true;
                            break;
                        }
                    }
                    if (flag2)
                    {
                        break;
                    }
                }
                if (flag2)
                {
                    break;
                }
            }
            if (flag2)
            {
                break;
            }
        }
        if (flag2)
        {
            count+=1;
            continue;
        }
        if (Not_first_time)
        {
            for (int i = 0; i<Last_street_count; i++)
            {
                std::cout << "rm "<< "\"street " + translate(i+1) + "\"" << std::endl;
            }
        }
        for (int i = 0; i<n_s; i++)
        {
            std::cout << "add " << street[i].name;
            for (int j = 0; j<((street[i].count_edges+1)*2); j+=2)
            {
                std::cout <<" " << "(" << std::to_string(street[i].coor[j]) << "," << std::to_string(street[i].coor[j+1]) << ")";
            }
            std::cout << std::endl;
        }
        std::cout << "gg" << std::endl;
        Last_street_count = n_s;
        Not_first_time = true;
        if (count != 0)
        {
            count = 0;
        }
        sleep(n_l);
    }
    if (count == 25)
    {
    std::cerr << "Error: from child_rgen, failed to generate valid input for 25 simultaneous attempts, child rgen has been exit" << std::endl;
    }
    exit(0);
}

