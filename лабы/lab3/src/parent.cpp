#include "parent.hpp"
#include "utils.hpp"
#include "semaphore.h"

void ParentRoutine(const char *pathToChild, std::istream &in) {
    std::string filename1, filename2;
    std::getline(in, filename1);
    std::getline(in, filename2);

    int cnt1 = 0;
    int cnt2 = 0;
    const char *name1 = "SharedMemory1";
    const char *name2 = "SharedMemory2";

    sem_t *semptr = CreateSemaphore(SEM_1, 0);

    int shd_fd1 = CreateShm(name1);
    char *memptr1 = MapSharedMemory(FILE_SIZE, shd_fd1);

    int shd_fd2 = CreateShm(name2);
    char *memptr2 = MapSharedMemory(FILE_SIZE, shd_fd2);

    std::string childPath(pathToChild);

    int pid1 = fork();

    if (pid1 < 0){
        perror("fork failed");
        return;
    } else if (pid1 > 0) {
        int pid2 = fork();

        if (pid2 < 0) {
            perror("fork failed");
            return;
        } else if (pid2 > 0) {
            // Here parent routine
            for (std::string line; std::getline(in, line); ) {
                if (line.size() % 2 == 0) {
                    line.push_back('\n');
                    strcpy(memptr1 + cnt1, line.c_str());
                    cnt1 += line.size();
                } else {
                    line.push_back('\n');
                    strcpy(memptr2 + cnt2, line.c_str());
                    cnt2 += line.size();
                }
            }

            sem_post(semptr);
        } else {
            execl(childPath.c_str(), childPath.c_str(), filename2.c_str(), name1, nullptr);
        }
    } else {
        execl(childPath.c_str(), childPath.c_str(), filename1.c_str(), name2, nullptr);
    }

    wait(nullptr);
    wait(nullptr);

    sem_close(semptr);
    sem_unlink(SEM_1);

    shm_unlink("SharedMemory1");
    munmap(memptr1, FILE_SIZE);
    close(shd_fd1);

    shm_unlink("SharedMemory2");
    munmap(memptr2, FILE_SIZE);
    close(shd_fd2);

}
