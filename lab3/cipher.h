#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include <time.h>

void help();
unsigned char *ASCII_to_hhx(char *s, unsigned char *x);
unsigned char it_reg1(unsigned char *reg);
unsigned char it_reg2(unsigned char *reg);
unsigned char it_reg3(unsigned char *reg);
unsigned char func(unsigned char a, unsigned char b, unsigned char c);
void ciphering(unsigned char *reg1, unsigned char *reg2, unsigned char *reg3, char *filepath);
