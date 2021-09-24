#include <stdio.h>
#include <string.h>

unsigned long long int search_1 (char s[65]) {
    int c = 0, n = 0, t, k = (int) strlen(s) - 1; //c - количество найденных разделителей, n - цифр, t - тип разделителя
    char a[10];
    unsigned long long int x = 0;
        for (int i = 0; i <= k; ++i) {
        if ((int) s[i] >= (int) '0' && (int) s[i] <= (int) '9') {
            if (n < 2 && c == 0) {
                if (n == 0 && (int) s[i] < (int) '4') {
                    x |= ((unsigned long long int) 1) << (k - i);
                    a[n + c] = s[i];
                    ++n;
                }
                else if (n == 1 && (((int) a[0] < (int) '3' && a[0] != '0') ||
                (a[0] == '3' && (int) s[i] <= (int) '1') || (a[0] == '0' && s[i] != '0'))) {
                    x |= ((unsigned long long int) 1) << (k - i);
                    a[n + c] = s[i];
                    ++n;
                }
            }
            else if (n >= 2 && n < 4 && c == 1) {
                if (n == 2 && (int) s[i] < (int) '2') {
                    x |= ((unsigned long long int) 1) << (k - i);
                    a[n + c] = s[i];
                    ++n;
                }
                else if (n == 3 && ((int) a[0] < (int) '2' || (a[0] == '2' && (int) a[1] <= (int) '8')) && a[3] == '0' && s[i] == '2') {
                    x |= ((unsigned long long int) 1) << (k - i);
                    a[n + c] = s[i];
                    ++n;
                }
                else if (n == 3 && ((a[3] == '0' && (int) s[i] > (int) '0' && s[i] != '2') || (a[3] == '1' && (int) s[i] < (int) '3'))) {
                    x |= ((unsigned long long int) 1) << (k - i);
                    a[n + c] = s[i];
                    ++n;
                }
                else if (n == 3 && a[0] == '3' &&  a[1] == '1' &&
                ((a[3] == '0' && (s[i] == '1' || s[i] == '3' || s[i] == '5' || s[i] == '7' || s[i] == '8'))
                        || (a[3] == '1' && (s[i] == '0' || s[i] == '2')))) {
                    x |= ((unsigned long long int) 1) << (k - i);
                    a[n + c] = s[i];
                    ++n;
                }
            }
            else if (n >= 4 && n < 8 && c == 2) {
                if (n == 4 && (int) s[i] > (int) '0') {
                    x |= ((unsigned long long int) 1) << (k - i);
                    a[n + c] = s[i];
                    ++n;
                }
                else if (n >= 5) {
                    x |= ((unsigned long long int) 1) << (k - i);
                    a[n + c] = s[i];
                    ++n;
                }
            }
        }
        else if (n == 2 && c == 0 && (s[i] == '.' || s[i] == '-')) {
            x |= ((unsigned long long int) 1) << (k - i);
            a[n] = s[i];
            ++c;
            if (s[i] == '.')
                t = 0;
            else
                t = 1;
        }
        else if (n == 4 && c == 1) {
            if ((s[i] == '.' && t == 0) || (s[i] == '-' && t == 1)) {
                x |= ((unsigned long long int) 1) << (k - i);
                a[n + c] = s[i];
                ++c;
            }
        }
    }
    if (n != 8 || c != 2)
        x = 0;
    return x;
}

unsigned long long int search_2 (char s[65]) {
    int n = 0, k = (int) strlen(s) - 1; //n - цифр
    char a[8];
    unsigned long long int x = 0;
    for (int i = 0; i <= k; ++i) {
        if ((int) s[i] >= (int) '0' && (int) s[i] <= (int) '9') {
            if (n == 0 && (int) s[i] > (int) '0') {
                x |= ((unsigned long long int) 1) << (k - i);
                a[n] = s[i];
                ++n;
            }
            else if (n >= 1 && n < 4) {
                x |= ((unsigned long long int) 1) << (k - i);
                a[n] = s[i];
                ++n;
            }
            else if (n == 4 && (int) s[i] < (int) '2') {
                x |= ((unsigned long long int) 1) << (k - i);
                a[n] = s[i];
                ++n;
            }
            else if (n == 5 && ((a[4] == '0' && (int) s[i] > (int) '0') || (a[4] == '1' && (int) s[i] < (int) '3'))) {
                x |= ((unsigned long long int) 1) << (k - i);
                a[n] = s[i];
                ++n;
            }
            else if (n == 6 && ((a[4] == '0' && a[5] == '2' && (int) s[i] < (int) '3') ||
            ((a[4] != '0' || a[5] != '2') && (int) s[i] < (int) '4'))) {
                x |= ((unsigned long long int) 1) << (k - i);
                a[n] = s[i];
                ++n;
            }
            else if (n == 7) {
                if (a[4] == '0' && a[5] == '2' && ((a[6] == '2' && (int) s[i] < (int) '9') || (a[6] == '0' && s[i] != '0')
                || (a[6] == '1'))) {
                    x |= ((unsigned long long int) 1) << (k - i);
                    a[n] = s[i];
                    ++n;
                }
                else if ((a[4] != '0' || a[5] != '2') && (a[6] != '0' || s[i] != '0')) {
                    if ((int) a[6] < (int) '3' || (a[6] == '3' && s[i] == '0')) {
                        x |= ((unsigned long long int) 1) << (k - i);
                        a[n] = s[i];
                        ++n;
                    }
                    else if (a[6] == '3' && s[i] == '1' &&
                    ((a[4] == '0' && (a[5] == '1' || a[5] == '3' || a[5] == '5' || a[5] == '7' || a[5] == '8'))
                              || (a[4] == '1' && (a[5] == '0' || a[5] == '2')))) {
                        x |= ((unsigned long long int) 1) << (k - i);
                        a[n] = s[i];
                        ++n;
                    }
                }
            }
        }
    }
    if (n != 8)
        x = 0;
    return x;
}

int main (int argc, char *argv[]) {
    char s[65];
    if (!argv[1])
        printf("Error, please enter file path\n");
    else {
        FILE *f = fopen (argv[1], "r+");
        unsigned long long int x, y;
        printf("len_dd.mm.yyyy_yyyymmdd\n");
        while (!feof(f)) {
            fscanf(f, "%s\n", s);
            x = search_1(s);
            y = search_2(s);
            printf("%ld_%llx_%llx\n",strlen(s), x, y);
        }
        fclose(f);
    }
    return 0;
}
