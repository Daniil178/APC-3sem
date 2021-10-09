#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include <time.h>

char *fget_str(FILE *f);
void help();
void ASCII_to_hex(char *s, unsigned long int *x);
unsigned long int *gen_text(unsigned long int *p);
void cipher_time(unsigned long int key[3], char t, char mode[3], unsigned long int iv);

unsigned long int Invers(unsigned long int k0);
unsigned long int SubBytes(unsigned long int p, char t);
unsigned long int ShiftRows(unsigned long int p);
unsigned long int AddRoundKey(unsigned long int p, unsigned long int key);
unsigned long int *ecb(unsigned long int key[3], unsigned long int *p, int len, char t, int g);
unsigned long int *cbc(unsigned long int key[3], unsigned long int *p, int len, char t, unsigned long int iv, int g);
