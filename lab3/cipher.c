#include "cipher.h"

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("Incorrect input\nFor example:\n./cipher -k path_to_file_with_key.txt path_to_file_with_ciphertext.txt\nor\n./cipher --key=path_to_file_with_key.txt path_to_file_with_ciphertext.txt\n");
return 1;
}
    static struct option long_options[] = {
        {"key", required_argument, 0, 'k'},
        {"help", no_argument, 0, 'h'},
        {0, 0, 0, 0}};
    FILE *f; 
    int opt = 0, long_index = 0;
    char key[55], key1[15], key2[19], key3[23], *path = NULL, *key_path = NULL;
    unsigned char *reg1 = calloc(7, sizeof(unsigned char)), *reg2 = calloc(9, sizeof(unsigned char)), *reg3 = calloc(11, sizeof(unsigned char));
    while ((opt = getopt_long(argc, argv, ":hk:", long_options, &long_index)) != -1) {
    	switch (opt) {
    	case 'h': help();
			return 0;
    	case 'k':
		key_path = (char *) calloc(strlen(optarg), sizeof(char));
		key_path = optarg;
		break;
    	case ':': printf("Error, enter quantity for argument\n");
                              return 1;
    	default: printf("Error, too many argument, please repeat\n");
                              return 1;
    	}
    }
    for (; optind < argc; ++optind) {
         path = (char *) calloc(strlen(argv[optind]), sizeof(char));
         path = argv[optind];
    }
    if ((f = fopen(key_path, "r+")) == NULL) {
		printf("Error, file don`t exist\n");
		return 1;
    }
    fscanf(f, "%s", key);
    fclose(f);
    if (strlen(key) < 54) {
        printf("Error incorrect len of key\n");
        return 1;
    }
    for(int i = 0; i < 14; key1[i] = key[i], ++i);
    for(int i = 14; i < 32; key2[i - 14] = key[i], ++i);
    for(int i = 32; i < 54; key3[i - 32] = key[i], ++i);
    key1[14] = '\0', key2[18] = '\0', key3[22] = '\0';
    ASCII_to_hhx(key1, reg1);
    ASCII_to_hhx(key2, reg2);
    ASCII_to_hhx(key3, reg3);
    ciphering(reg1, reg2, reg3, path);
    return 0;
}
