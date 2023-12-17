#include "include/pi-sin.h"


void information(){
    printf("\n1 - Pi\n2 - sin_integral\n -1 - EXIT\n");
}

int main(){
    int command;
    information();
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
            printf("\nPi = %f\n", Pi(k));
            break;
        case 2:
            printf("\nenter arguments: A B e\n");
            float a, b, e;
            if (scanf("%f %f %f", &a, &b, &e) == EOF){
                printf("\ninvalid arguments\n");
                break; 
            };
            printf("\nintegral of sin(x) on [%f, %f] is %f\n", a, b, sin_integral(a, b, e));
            break;
        default:
            printf("\ninvalid command\n");
            break;
        }
        information();
    }
}