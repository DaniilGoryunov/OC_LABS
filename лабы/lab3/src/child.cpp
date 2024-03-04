#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "semaphore.h"
#include "utils.hpp"

bool isVowel(char c) {
    return c == 'e' ||
           c == 'u' ||
           c == 'i' ||
           c == 'o' ||
           c == 'a';
}


int main(int argc, char **argv) {
    if (argc < 3) {
        printf("No input file.\n");
        exit(EXIT_FAILURE);
    }

    const char* name1 = argv[2];

    sem_t *semptr = CreateSemaphore(SEM_1, 0);

    int shd_fd1 = CreateShm(name1);
    char *memptr1 = MapSharedMemory(FILE_SIZE, shd_fd1);

    sem_wait(semptr);
    sem_post(semptr);

    std::string filename(argv[1]);
    std::ofstream file(filename);
    std::stringstream shmem(memptr1);

    for (std::string line; std::getline(shmem, line); ) {
        line.push_back('\n');
        int len = line.length();
        if (len > 0) { 
            line.erase(std::remove_if(line.begin(), line.end(), 
                [](unsigned char x) 
                {
                    return isVowel(tolower(x));
                }), line.end());
        }
        file << line;
    }
    sem_close(semptr);
    sem_unlink(SEM_1);

    shm_unlink(name1);
    munmap(memptr1, FILE_SIZE);
    close(shd_fd1);

    return 0;
}