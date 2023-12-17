#include "parent.hpp"

int fork_process(){
    pid_t pid = fork();
    if (pid == -1){
        perror("Fork error!\n");
        exit(-1);
    }
    return pid;
}

void * create_MMF(void *addr, size_t len, int prot, int flags, int fd, off_t offset){
    void * dst = mmap(addr, len, prot, flags, fd, offset);
    if (dst == MAP_FAILED){
        perror("mmap error!\n");
        exit(-1);
    }
    return dst;
}

void delete_MMF(void *addr, size_t len){
    if (munmap(addr, len) != 0){
        perror("munmap error!\n");
        exit(-1);
    }
}

int create_shm(const char * name, int oflag, mode_t mode){
    int fd = shm_open(name, oflag, mode);
    if (fd == -1){
        perror("shm_open error!");
        exit(-1);
    }
    return fd;
}

void file_truncate(int fd, off_t length){
    if(ftruncate(fd, length) != 0){
        perror("ftruncate error!");
        exit(-1);
    }
}

void remove_shm(const char * name){
    if (shm_unlink(name) != 0){
        perror("shm_unlink error!");
        exit(-1);
    }
}

std::string validInputToString(std::istream &input){
    std::string s;
    getline(input, s);
    int thereIsNumbers = 0;
    int minusCounter = 0;
    for (char c : s){
        if (c != '-' and !isdigit(c) and c != ' '){
            perror("Invalid input!");
            exit(-1);
        } else if (c == '-'){
            minusCounter++;
        } else if (c == ' '){
            if (minusCounter){
                perror("Invalid input!");
                exit(-1);
            }
        } else{
            minusCounter = 0;
            thereIsNumbers = 1;
        }
    }
    if (!thereIsNumbers){
        perror("Invalid input!");
        exit(-1);
    }
    return s;
}

void extend_capacity_MMF(MMF * mem, int new_size){
    file_truncate(mem->fd, sizeof(int) * new_size);
    int * addr = (int *)create_MMF(nullptr, sizeof(int) * new_size, PROT_WRITE, MAP_SHARED, mem->fd, 0);
    for(int i = 0; i < mem->addr[0]; i++){
        addr[i] = mem->addr[i];
    }
    delete_MMF(mem->addr, mem->capacity);
    mem->addr = addr;
}

void push_MMF(MMF * mem, int num){
    if (mem->addr[0] + 1 == mem->capacity - 1){
        extend_capacity_MMF(mem, mem->capacity * 2);
    }
    mem->addr[mem->addr[0] + 1] = num;
    mem->addr[0]++;
}

void processes(std::istream &input){
    const char* pathToChild = getenv("PATH_TO_CHILD");
    std::string f;
    input >> f;
    std::istringstream buf(validInputToString(input));
    std::istream validInput(buf.rdbuf());
    pid_t child = fork_process();
    if (child == 0){
        execl(pathToChild, pathToChild, f.c_str(), nullptr);
    } else{
        int number;
        int fd = create_shm("MMF", O_CREAT | O_RDWR, 0666);
        file_truncate(fd, sizeof(int) * 2);
        int * ptr = (int *)create_MMF(nullptr, sizeof(int) * 2, PROT_WRITE, MAP_SHARED, fd, 0);
        MMF mem = {ptr, 2, fd};
        mem.addr[0] = 0;
        while(validInput >> number){
            push_MMF(&mem, number);
        }
        wait(nullptr);
        delete_MMF(ptr, mem.capacity);
    }
}