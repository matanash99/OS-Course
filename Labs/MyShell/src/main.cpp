#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>

int main(){


    while (1){
        std::cout << "$ ";

        std::string input;
        if (!std::getline(std::cin, input) || input == "exit"){
            break;
        }
        
        std::istringstream iss(input);
        std::string token;
        std::vector<std::string> tokens;

        while (iss >> token){
            tokens.push_back(token);
        }

        if (tokens.empty()) {
            continue;
        }

        for ( const auto& arg : tokens){
            std::cout << arg;
        }

        if (tokens[0] == "cd") {
            const char* path = nullptr;
            
            if (tokens.size() == 1) {
                path = std::getenv("HOME"); 
            } else {
                path = tokens[1].c_str();
            }
            
            if (path != nullptr) {
                if (chdir(path) != 0) {
                    perror("cd failed");
                }
            }
            continue; 
        }

        pid_t pid = fork();

        if (pid < 0) {
            std::cerr << "Fork failed\n";
            continue;
        }


        else if (pid == 0) { // chlid

            std::vector<char*> pointers;

            for (const auto& token : tokens){
                pointers.push_back(const_cast<char>(token.c_str()));
            }
            pointers.push_back(nullptr);

            execv(tokens[0],c_str(), pointers.data());

            perror("execv failed");
        }

        else { //parent
            
            

            int status;
            waitpid(pid, &status, 0);

        }
    }

    return 0;
}
