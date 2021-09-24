#include <stdio.h>

void perebor_2(int A[10], char *s, int len, int n){
    if (n == len) {
        printf("%s\n", s);
        return;
    }
    else if (s[n] == '.' || s[n] == '-' || s[n] == '*')
        perebor_2(A, s, len, n + 1);
    for (int i = 0; i < 10; ++i) {
        if (n == A[0] && i < 4) {
            s[n] = (char) (48 + i);
        }
        else if (n == A[1]) {
            if (s[A[0]] == '0' && i < 9) {
                s[n] = (char) (49 + i);
            }
            else if (s[A[0]] == '1' || s[A[0]] == '2') {
                s[n] = (char) (48 + i);
            }
            else if (s[A[0]] == '3' && i < 2) {
                s[n] = (char) (48 + i);
            }
        }
        else if (n == A[3] && i < 2) {
                s[n] = (char) (48 + i);
        }
        else if (n == A[4] && s[A[3]] != '0' && i < 3) {
            if (s[A[0]] == '3' && s[A[1]] == '1' && (s[A[3]] == '1' && (i == 0 || i == 2))) {
                s[n] = (char) (48 + i);
            } else if (s[A[0]] != '3') {
                s[n] = (char) (48 + i);
            }
        }
        else if (n == A[4] && s[A[3]] == '0' && i < 9){
                if (s[A[0]] == '3'  && s[A[1]] == '0' && i != 1)
                    s[n] = (char) (49 + i);
                else if (s[A[0]] == '3'  && s[A[1]] == '1'
                         && (i == 0 || i == 2 || i == 4 || i == 6 || i == 7)) {
                    s[n] = (char) (49 + i);
                }
                else if (s[A[0]] != '3') {
                    s[n] = (char) (49 + i);
                }
            }
        else if (n == A[6] && i < 9) {
                s[n] = (char) (49 + i);
        }
        else if (n == A[7] || n == A[8] || n == A[9]) {
            s[n] = (char) (48 + i);
        }
        else
            break;
        perebor_2(A, s, len, n + 1);
    }
}

void perebor_1(int A[10], char *s, int len, int n) {
    if (n == len) {
        printf("%s\n", s);
        return;
    }
    else if (s[n] == '*')
        perebor_1(A, s, len, n + 1);
    for (int i = 0; i < 10; ++i) {
        if (n == A[0] && i < 9) {
            s[n] = (char) (49 + i);
        }
        else if (n == A[1] || n == A[2] || n == A[3]) {
            s[n] = (char) (48 + i);
        }
        else if (n == A[4] && i < 2) {
            s[n] = (char) (48 + i);
        }
        else if (n == A[5] && s[A[4]] == '0' && i < 9) {
            s[n] = (char) (49 + i);
        }
        else if (n == A[5] && s[A[4]] == '1' && i < 3) {
            s[n] = (char) (48 + i);
        }
        else if (n == A[6] && i < 4) {
            if (s[A[4]] == '0' && s[A[5]] == '2' && i < 3)
                s[n] = (char) (48 + i);
            else
                s[n] = (char) (48 + i);
        }
        else if (n == A[7] && s[A[6]] == '0' && i < 9)
            s[n] = (char) (49 + i);
        else if (n == A[7] && s[A[6]] != '3' && s[A[6]] != '0') {
            if (s[A[4]] == '0' && s[A[5]] == '2' && s[A[6]] == '2' && i < 9)
                s[n] = (char) (48 + i);
            else if (s[A[6]] == '1' || s[A[6]] == '2')
                s[n] = (char) (48 + i);
        }
        else if (n == A[7] && s[A[6]] == '3' && i == 0 && ((s[A[4]] == '0' && (s[A[5]] == '4' || s[A[5]] == '6' || s[A[5]] == '9'))
            || (s[A[4]] == '1' && s[A[5]] == '1')))
                s[n] = (char) (48 + i);
        else if (n == A[7] && s[A[6]] == '3' && i < 2 &&
        ((s[A[4]] == '0' && (s[A[5]] == '1' || s[A[5]] == '3' || s[A[5]] == '5' || s[A[5]] == '7' || s[A[5]] == '8'))
        || (s[A[4]] == '1' && (s[A[5]] == '0' || s[A[5]] == '2'))))
            s[n] = (char) (48 + i);
        else
            break;
        perebor_1(A, s, len, n + 1);
    }
}


int main(int argc, char *argv[]) {
    int a = 0, i = 0, A[10], len;
    char s[65];
    if (argc == 1) 
	    printf("Error, don`t have path\n");
    FILE *f = fopen(argv[1], "r+");
    unsigned long long int x = 0b0, y = 0b0;
    while (!feof(f)) {
        a = 0, y = 0b0;
        fscanf(f, "%d_%llx\n",&len, &x);
        for (i = 0; i < len; ++i) {
            if ((x & ((unsigned long long int) 1 << (len - 1 - i))) > 0) {
                y |= (unsigned long long int) 1 << (len - 1 - i);
                A[a] = i;
                ++a;
                s[i] = '0';
            }
            else {
                s[i] = '*';
            }
        }
        s[len] = '\0';
        if (a == 10) {
            s[A[2]] = '.', s[A[5]] = '.';
            perebor_2(A, s, len, 0);
            s[A[2]] = '-', s[A[5]] = '-';
            perebor_2(A, s, len, 0);
        }
        else if (a == 8) {
            perebor_1(A, s, len, 0);
        }
        else
            printf("%s\n", s);
    }
    fclose(f);
    return 0;
}
