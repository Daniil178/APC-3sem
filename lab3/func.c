#include "cipher.h"

unsigned char *ASCII_to_hhx(char *s, unsigned char *x) {
    int len = (int) strlen(s), j = 0;
    for (int i = len - 1; i > 0; --i) {
        if ((int) s[i] >= '0' && (int) s[i] <= '9') {
            x[((len / 2) - 1) - j] |= ((unsigned char) ((int) s[i] - '0')) << (((i + 1) % 2) * 4);
        }
        if((int) s[i] >= 'a' && (int) s[i] <= 'f') {
            x[((len / 2) - 1) - j] |= ((unsigned char) ((int) s[i] - ('a' - 10))) << (((i + 1) % 2) * 4);
        }
        if (i % 2 == 0)
            ++j;
    }
    return x;
}

unsigned char it_reg1(unsigned char *reg) {
    unsigned char res = reg[0], new = reg[0] ^ reg[2] ^ reg[4] ^ 0x1;
    for(int i = 0; i < 6; ++i)
        reg[i] = reg[i + 1];
    reg[6] = new;

    return res;
}

unsigned char it_reg2(unsigned char *reg) {
    unsigned char res = reg[0], new = reg[2] ^ reg[4] ^ reg[6] ^ 0x1;
    for(int i = 0; i < 8; ++i)
        reg[i] = reg[i + 1];
    reg[8] = new;
    return res;
}

unsigned char it_reg3(unsigned char *reg) {
    unsigned char res = reg[0], new = reg[4] ^ reg[6] ^ reg[8] ^ 0x1;
    for(int i = 0; i < 10; ++i)
        reg[i] = reg[i + 1];
    reg[10] = new;
    return res;
}

unsigned char func(unsigned char a, unsigned char b, unsigned char c) {
    return (unsigned char) (((a*b*c) % 256 + (a*b) % 256 + (a*c) % 256 + 1) % 256);
}

void ciphering(unsigned char *reg1, unsigned char *reg2, unsigned char *reg3, char *filepath) {
    char inp1, inp2;
    unsigned char p, a, b, c;
    FILE *txt; 
    if ((txt = fopen(filepath, "r+")) == NULL) {
        printf("Error, file don`t exist\n");
        return;
    }
    while(fscanf(txt, "%c", &inp1) != EOF && fscanf(txt, "%c", &inp2) != EOF) {
        p = 0x0;
        if ((int) inp1 > 47 && (int) inp1 < 58) {
            p |= ((unsigned char) ((int) inp1 - 48)) << 4;
        }
        else if((int) inp1 > 96 && (int) inp1 < 103) {
            p |= ((unsigned char) ((int) inp1 - 87)) << 4;
        }
        if ((int) inp2 > 47 && (int) inp2 < 58) {
            p |= ((unsigned char) ((int) inp2 - 48));
        }
        else if((int) inp2 > 96 && (int) inp2 < 103) {
            p |= ((unsigned char) ((int) inp2 - 87));
        }
        a = it_reg1(reg1);
        b = it_reg2(reg2);
        c = it_reg3(reg3);
        printf("%02hhx", (unsigned char) (p ^ func(a, b, c)));
    }
    fclose(txt);
    printf("\n");
}

void help() {
    printf("-h, --help: for help with argument;\n-k, --key=[value]: path to the key;\nFor example\n./cipher -k path_to_file_with_key.txt path_to_file_with_ciphertext.txt\nor\n./cipher --key=path_to_file_with_key.txt path_to_file_with_ciphertext.txt\n");
}
