#include<sys/types.h>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>

int child_a1(void)
{
    char *args[3];
    args[0] = (char*)"python3 -u";
    args[1] = (char*)"./ece650-a1.py";
    args[2] = NULL;
    execv("/usr/bin/python3", args);
    return 0;
}
int child_a2(void)
{
    char *args[2];
    args[0] = (char*)"ece650-a2";
    args[1] = NULL;
    execv("./ece650-a2", args);
    return 0;
} 
int monitor_input(void)
{
    char *args[2];
    args[0] = (char*)"monitor_input";
    args[1] = NULL;
    execv("./monitor_input", args);
    return 0;
}
int main (int argc, char **argv) 
{
    std::vector<pid_t> kids;
    int rgentoa1[2];
    pipe(rgentoa1);
    int a1toa2[2];
    pipe(a1toa2);
    auto child_pid_1 = fork();
    if (child_pid_1 == 0) 
    { 
        dup2(rgentoa1[1],STDOUT_FILENO);
        close(rgentoa1[0]);
        close(rgentoa1[1]);
        return execv("./rgen", argv);             
    }
    else if(child_pid_1 < 0) 
    {
        std::cerr << "Error: Failed to start rgen.exe!\n";
        return -1;
    }
    kids.push_back(child_pid_1);
    auto child_pid_2 = fork();
    if (child_pid_2 == 0)
    {
        dup2(rgentoa1[0],STDIN_FILENO);
        close(rgentoa1[0]);
        close(rgentoa1[1]); 
        dup2(a1toa2[1],STDOUT_FILENO);
        close(a1toa2[0]);
        close(a1toa2[1]);
        return child_a1();
    }
    else if(child_pid_2 < 0) 
    {
        std::cerr << "Error: Failed to start ece650-a1.exe!\n";
        return -1;
    }
    kids.push_back(child_pid_2);
    auto child_pid_3 = fork();
    if (child_pid_3 == 0) 
    { 
        dup2(a1toa2[0],STDIN_FILENO);
        close(a1toa2[0]);
        close(a1toa2[1]);
        return child_a2();     
    }
    else if(child_pid_3 < 0) 
    {
        std::cerr << "Error: Failed to start ece650-a2.exe!\n";
        return -1;
    }
    kids.push_back(child_pid_3);

    auto child_pid_4 = fork();
    if (child_pid_4 == 0) 
    { 
        dup2(a1toa2[1],STDOUT_FILENO);
        close(a1toa2[0]);
        close(a1toa2[1]);
        return monitor_input();
    }
    else if(child_pid_4 < 0) 
    {
        std::cerr << "Error: Failed to start giving s command to a2!\n";
        return -1;
    }
    kids.push_back(child_pid_4);
    close(rgentoa1[0]);
    close(rgentoa1[1]);
    close(a1toa2[0]);
    close(a1toa2[1]);
    int status1;
    int status2;
    while(!waitpid(kids[0], &status1, WNOHANG))
    {
        if (waitpid(kids[3], &status2, WNOHANG))
        {
            for (pid_t k : kids)
            {
                if (k != kids[3])
                {
                    int status;
                    kill(k,SIGTERM);
                    waitpid(k, &status, 0);
                }
            }
            return 0;
        }
    }
    for (pid_t k : kids)
    {
        if (k != kids[0])
        {
            int status;
            kill(k,SIGTERM);
            waitpid(k, &status, 0);
        }
    }
    return 0;
}
