#include "main.h"


void perebor(int a, int A[10], FILE *q, char s[65]){
    char B[]= {'0','1','2','3','4','5','6','7','8','9'}, C[]= {'.', '-'};
    if (a == 8) {
        for (int i = 0; i < 10; ++i) {
            s[A[0]] = B[i];
            for (int j = 0; j < 10; ++j) {
                s[A[1]] = B[j];
                for (int k = 0; k < 10; ++k) {
                    s[A[2]] = B[k];
                    for (int h = 0; h < 10; ++h) {
                        s[A[3]] = B[h];
                        for (int g = 0; g < 2; ++g) {
                            s[A[4]] = B[g];
                            for (int v = 0; v < 10; ++v) {
                                if (g == 0 && v > 0)
                                    s[A[5]] = B[v];
                                else if (g == 1 && v < 3)
                                    s[A[5]] = B[v];
                                for (int c = 0; c < 4; ++c) {
                                    if (g == 0 && v == 2 && c < 3) {
                                        s[A[6]] = B[c];
                                        for (int n = 0; n < 9; ++n) {
                                            if ((c == 0 && n > 0) || c > 0) {
                                                s[A[7]] = B[n];
                                                fprintf(q, "%s\n", s);
                                            }
                                        }
                                    } else {
                                        s[A[6]] = B[c];
                                        if (c < 3)
                                            for (int n = 0; n < 10; ++n) {
                                                if ((c == 0 && n > 0) || c > 0) {
                                                    s[A[7]] = B[n];
                                                    fprintf(q, "%s\n", s);
                                                }
                                            }
                                        else {
                                            s[A[7]] = '0';
                                            fprintf(q, "%s\n", s);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    else {
        for(int p=0; p<4; ++p){
            s[A[0]] = B[p];
            for(int l=0; l<10; ++l){
                if((p== 0 && l>0) || p>0){
                    if(p==3 && l==0)
                        s[A[1]] = '0';
                    else if(p!=3)
                        s[A[1]] = B[l];
                    for(int z=0; z<2; ++z){
                        s[A[2]] = C[z], s[A[5]] = C[z];
                        for(int m=0; m<2; ++m){
                            s[A[3]] = B[m];
                            for(int u=0; u<10; ++u){
                                if((m==0 && u>0 && u!=2) || (m==1 && u<3) || (m==0 && u==2 && p<3)){
                                    s[A[4]] = B[u];
                                    for (int i = 0; i < 10; ++i) {
                                        s[A[6]] = B[i];
                                        for (int j = 0; j < 10; ++j) {
                                            s[A[7]] = B[j];
                                            for (int k = 0; k < 10; ++k) {
                                                s[A[8]] = B[k];
                                                for (int h = 0; h < 10; ++h) {
                                                    s[A[9]] = B[h];
                                                    fprintf(q, "%s\n", s);
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

int main(int argc, char *argv[]){
    char path[100], Q[]="/home/daniil/labs/lab1.2/";
    int a = 0, i = 0, A[10];
    char s[65];
    strcpy(path, Q), strcat(path, argv[1]);
    FILE *f = fopen(path, "r+");
    FILE *q = fopen("/home/daniil/labs/lab1.2/output.txt", "w+");
    unsigned long long int x = 0b0, y = 0b0;
    while (!feof(f)) {
        a = 0, y = 0b0;
        fscanf(f, "%llx\n", &x);
        for (i = 0; i < 64; ++i) {
            if ((x & ((unsigned long long int) 0b1 << (63 - i))) > 0) {
                y |= (unsigned long long int) 0b1 << (63 - i);
                A[a] = i;
                ++a;
            } else {
                s[i] = '*';
            }
        }
	printf("64_%llx\n", y);
        perebor(a, A, q, s);
    }
        fclose(f);
        fclose(q);
    return 0;
}
