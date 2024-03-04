#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>     
#include <fcntl.h>
#include <unistd.h>
#include <semaphore.h>

sem_t *CreateSemaphore(const char *name, int value);
int CreateShm(const char* name);
char* MapSharedMemory(const int size, int fd);
int CreateFork();

constexpr const char *SEM_1 = "SEM_1";

const int FILE_SIZE = 1024;