#include "main.h"

int main(int argc, char *argv[]){
   int a = 0;
    char s[65];
    char path[100], q[]="/home/daniil/labs/lab1/";
    strcpy(path, q), strcat(path, argv[1]);
    FILE *f = fopen(path, "r+");
    unsigned long int x=0b0;
    while(!feof(f)) {
        fscanf(f, "%s\n", s);
        a = 0, x = 0b0;
        for (int i = 0; s[i] != '\n' && a < 10; i++) {
            if (s[i] == '.' || s[i] == '-' || ((int) s[i] >= (int) ('0') && (int) s[i] <= (int) '9')) {
                ++a;
                x |= ((unsigned long int) 0b1) << (63-i);
            }
        }
        printf("%lx\n", x);
    }
    fclose(f);
    return 0;
}
