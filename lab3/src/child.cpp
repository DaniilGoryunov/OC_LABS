#include "parent.hpp"

int main(int argc, char* argv[]){
    if (argc < 2){
        perror("Too few arguments");
        exit(1);
    }
    std::ofstream res;
    res.open(argv[1]);
    int sum = 0;
    int fd = create_shm("MMF", O_RDONLY, 0666);
    int * ptr = (int *)create_MMF(nullptr, sizeof(int) * 2, PROT_READ, MAP_SHARED, fd, 0);
    for (int i = 1; i <= ptr[0]; i++){
        sum += ptr[i];
    }
    delete_MMF(ptr, ptr[0]);
    remove_shm("MMF");
    res << sum;
    return 0;
}