#include "parent.hpp"

int Parent(const char* path_to_child, std::istream &in) {
    std::string filename;
    in >> filename;
    int pipe1_fd[2];
    pipe(pipe1_fd);
    int id = fork();
    if (id < 0){
        perror("fork failed");
        return 1;
    }
    else if(id > 0){
        close(pipe1_fd[0]);

        float num;
        while (in >> num) {
            write(pipe1_fd[1], &num, sizeof(num));
        }

        close(pipe1_fd[1]);
        wait(nullptr);
    }
    else{
        close(pipe1_fd[1]);

        if (dup2(pipe1_fd[0], STDIN_FILENO) == -1) {
            perror("dup2 error");
            return 1;
        }

        execl(path_to_child, path_to_child, filename.c_str(), nullptr);

        close(pipe1_fd[0]);
    }
    return 0;
}