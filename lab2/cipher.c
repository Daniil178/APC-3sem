#include "func.h"

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("Incorrect input\nFor example:\n./cipher -m ecb -e -k ffffffff filename > outname\nor\n./cipher --mod=ecb --enc --key=ffffffff filename > outname\n");
        return 0;
    }
    static struct option long_options[] = {
                    {"key", required_argument, 0, 'k'},
                    {"mode", required_argument, 0, 'm'},
                    {"help", no_argument, 0, 'h'},
                    {"version", no_argument, 0, 'v'},
                    {"enc", no_argument, 0, 'e'},
                    {"dec", no_argument, 0, 'd'}, 
                    {"iv", required_argument, 0, 'i'},
                    {"debug", no_argument, 0, 'g'},
                    {"timing", no_argument, 0, 't'},
                    {0, 0, 0, 0}};
    char *path = NULL, t, *info = NULL, *mode = (char *) calloc(3, sizeof(char));
    unsigned long int key = 0, k[3], *p, iv = 0;
    int len, opt = 0, long_index = 0, g = 0, timing = 0, fl = 0;
    srand(time(NULL));
    while ((opt = getopt_long(argc, argv, ":hvedtgk:m:i:", long_options, &long_index)) != -1) {
                    switch (opt) {
                    case 't': timing = 1;
                            break;
                    case 'h': help();
                            //free(mode);
                            return 0;
                    case 'v': printf("Version = 0.1\n");
                            //free(mode);
			    return 0;
                    case 'e': t = 'e';
                            break;
                    case 'd': t = 'd';
                            break;
                    case 'k': if (ASCII_to_hex(optarg, &key) != 0 || strlen(optarg) != 8) {
                                  printf("Error, incorrect key\n");
                                  return -1;
                              }
                            break;
                    case 'm': mode = optarg;
                            if(!((mode[0] == 'e' && mode[1] == 'c' && mode[2] == 'b') || 
                                 (mode[0] == 'c' && mode[1] == 'b' && mode[2] == 'c') || 
                                 (mode[0] == 'o' && mode[1] == 'f' && mode[2] == 'b')))
                            {
                                printf("Error, incorrect mode\n");
                                return -1;
                            }
                            break;
                    case 'i': if (ASCII_to_hex(optarg, &iv) != 0 || strlen(optarg) != 8) {
                                  printf("Error, incorrect IV\n");
                                  return -1;
                              }
                              fl = 1;
                            break;
                    case 'g': g = 1;
                            break;
                    case ':': printf("Error, enter quantity for argument\n");
                            //free(mode);
                            return 1;
                    default: printf("Error, too many argument, please repeat\n");
                            //free(mode);
                            return 1;
                    }
            }
            for (; optind < argc; ++optind) {
                    path = (char *) calloc(strlen(argv[optind]), sizeof(char));
		    path = argv[optind];
            }
    if (path == NULL || (mode[0] == 'c' && mode[1] == 'b' && mode[2] == 'c' && fl == 0) || (mode[0] == 'o' && mode[1] == 'f' && mode[2] == 'b' && fl == 0)) {
	printf("Error, check your filename or exist iv\n");
	//free(mode);
	return 1;
    }
    FILE *f = fopen(path, "r+");
    k[0] = key;
    k[1] = Invers(k[0]);
    k[2] = k[0] ^ k[1];
    if (g == 1) {
        printf("Key[0] = %08lx\nKey[1] = %08lx\nKey[2] = %08lx\n", k[0], k[1], k[2]);
    }
    info = fget_str(f);
    if ((int) strlen(info) % 8 != 0)
        len = (int) strlen(info) / 8 + 1;
    else
        len = (int) strlen(info) / 8;
    p = (unsigned long int *) calloc(len, sizeof(unsigned long int));
    ASCII_to_hex(info, p);
    if (mode[0] == 'c' && mode[1] == 'b' && mode[2] == 'c')
        p = cbc(k, p, len, t, iv, g);
    else if (mode[0] == 'e' && mode[1] == 'c' && mode[2] == 'b')
        p = ecb(k, p, len, t, g);
    else
        p = ofb(k, p, len, iv, g);
    for (int i = 0; i < len; ++i)
        printf("%08lx", p[i]);
    printf("\n"); 
    fclose(f);
    if (timing == 1) {
        cipher_time(k, t, mode, iv);
    }
    //free(p), free(mode), free(path);
    return 0;
}
