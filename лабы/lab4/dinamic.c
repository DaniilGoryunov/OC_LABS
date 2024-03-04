#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>

void* Handle = NULL;

float (*Pi)(int) = NULL;
float (*sin_integral)(float, float, float) = NULL;


int mode = 1;


void load_lib(){
    switch (mode){
        case 1:
	        Handle = dlopen("../build/liblib1.dylib", RTLD_LAZY);
	        break;
        case 2:
	        Handle = dlopen("../build/liblib2.dylib", RTLD_LAZY);
	        break;
        default:
            printf("invalid mode");
            return;
    }
    if (Handle == NULL){
	    perror("dlopen");
	    exit(-1);
    }
}

void load_contract(){
    load_lib();
    Pi = dlsym(Handle, "Pi");
    sin_integral = dlsym(Handle, "sin_integral");
}

void swap_contract(){
    dlclose(Handle);
    if(mode == 1){
        mode = 2;
    } 
    else {
        mode = 1;
    }
    load_contract();
}

void information(){
    printf("\n1 - Pi\n2 - sin_integral\n3 - swap contract\n -1 - EXIT\n");
}


int main(){
    int command;
    information();
    load_contract();
    while(scanf("%d", &command) != EOF){
        switch (command){
        case -1:
            return 0;
        case 1:
            printf("\nenter lenght of series\n");
            int k;
            if (scanf("%d", &k) == EOF){
                printf("\ninvalid argument\n");
                break; 
            };
            printf("\nPi = %f\n", (*Pi)(k));
            break;
        case 2:
            printf("\nenter arguments: A B e\n");
            float a, b, e;
            if (scanf("%f %f %f", &a, &b, &e) == EOF){
                printf("\ninvalid arguments\n");
                break; 
            };
            printf("\nintegral of sin(x) on [%f, %f] is %f\n", a, b, (*sin_integral)(a, b, e));
            break;
        case 3:
            swap_contract();
            printf("\nswap\n");
            break;
        default:
            printf("\ninvalid command\n");
            break;
        }
        information();
    }
    dlclose(Handle);
}
