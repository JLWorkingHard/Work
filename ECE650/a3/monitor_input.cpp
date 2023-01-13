#include <iostream>
int main(void)
{
    while (!std::cin.eof()) 
        {
            std::string user_command;
            std::getline(std::cin, user_command);
            if (user_command.size() > 0)
            {
            std::cout << user_command << std::endl;
            }
        } 
    return 0;
}