#pragma once

#include <iostream>
#include <unistd.h>
#include <fstream>
#include <sys/types.h>
#include <sys/wait.h>
#include <sstream>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h> 
#include <pthread.h>
struct MMF{
    int * addr;
    int capacity;
    int fd;
};
int fork_process();
void * create_MMF(void *addr, size_t len, int prot, int flags, int fd, off_t offset);
void delete_MMF(void *addr, size_t len);
int create_shm(const char * name, int oflag, mode_t mode);
void file_truncate(int fd, off_t length);
void remove_shm(const char * name);
std::string validInputToString(std::istream &input);
void extend_capacity_MMF(MMF * mem, int new_size);
void push_MMF(MMF * mem, int num);
void processes(std::istream &input);