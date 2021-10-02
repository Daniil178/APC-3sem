#include "func.h"

int main(int argc, char *argv[]) {
    static struct option long_options[] = {
                    {"key", required_argument, 0, 'k'},
                    {"mode", required_argument, 0, 'm'},
                    {"help", no_argument, 0, 'h'},
                    {"version", no_argument, 0, 'v'},
                    {"enc", no_argument, 0, 'e'},
                    {"dec", no_argument, 0, 'd'}, 
                    {"iv", required_argument, 0, 'i'},
                    {"debug", no_argument, 0, 'g'},
                    {0, 0, 0, 0}};
    char *path = NULL, t, *info = NULL, *mode = (char *) calloc(3, sizeof(char));
    unsigned long int key = 0, k[3], *p, iv = 0;
    int len, opt = 0, long_index = 0, g = 0;
    while ((opt = getopt_long(argc, argv, ":hvedgk:m:i:", long_options, &long_index)) != -1) {
                    switch (opt) {
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
                    case 'k': ASCII_to_hex(optarg, &key);
                            break;
                    case 'm': mode = optarg;
                            break;
                    case 'i': ASCII_to_hex(optarg, &iv);
                            break;
                    case 'g': g = 1;
                            break;
                    case ':': printf("Error, enter quantity for argument\n");
                            //free(mode);
                            return 1;
                    default: printf("Error, please repeat\n");
                            //free(mode);
                            return 1;
                    }
            }
            for (; optind < argc; ++optind) {
                    path = (char *) calloc(strlen(argv[optind]), sizeof(char));
		    path = argv[optind];
            }
    if (path == NULL || key == 0 || (mode[0] == 'c' && mode[1] == 'b' && mode[2] == 'c' && iv == 0)) {
	printf("Error, please, repeat\n");
	//free(mode);
	return 1;
    }
    FILE *f = fopen(path, "r+");
    k[0] = key;
    k[1] = Invers(k[0]);
    k[2] = k[0] ^ k[1];
    if (g == 1) {
        printf("Key[0] = %lx\nKey[1] = %lx\nKey[2] = %lx\n", k[0], k[1], k[2]);
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
    else
        p = ecb(k, p, len, t, g);
    for (int i = 0; i < len; ++i)
        printf("%lx", p[i]);
    printf("\n"); 
    fclose(f);
    //free(info), free(p), free(mode), free(path);
    return 0;
}
