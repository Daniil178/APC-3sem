#include "func.h"
int main(int argc, char *argv[]) {
	if (argc != 4) {
		printf("Error, check your argument\nExample: ./gen 0a0b0cff md5 3des\n");
		return 1;
	}
	srand(time(NULL));
	char *hash = argv[2], *cipher = argv[3];
	char *passw = argv[1], end[] = ".enc";
	unsigned char opentext[] = "00000000You have successfully decrypted this text";
	unsigned char nonce[64], *iv, *password = calloc(4, 1), *key, type_c, type_h;
	int len = len_find(cipher, hash, &type_c, &type_h);
	iv = calloc(len, 1);
	key = calloc(len, 1);
	unsigned char *c_text = calloc(49, 1);	
	password = ASCII_to_hhx(passw, password);
	gen_text(nonce, 64);
	gen_text(iv, len);
	create_key(password, nonce, len, cipher, key);
	encrypt_text(opentext, 49, iv, key, len, c_text);
	
	char *filepath = calloc(strlen(hash) + strlen(cipher) + strlen(passw) + 6, 1);
	memcpy(filepath, hash, strlen(hash));
	filepath[strlen(hash)] = '_';
	memcpy(filepath + strlen(hash) + 1, cipher, strlen(cipher));
	filepath[strlen(hash) + 1 + strlen(cipher)] = '_';
	memcpy(filepath + strlen(hash) + 1 + strlen(cipher) + 1, passw, 8);
	memcpy(filepath + strlen(hash) + 1 + strlen(cipher) + 1 + 8, end, 4);
	
	FILE *f = fopen(filepath, "wb");
	fprintf(f, "ENC%c%c%s%s%s", type_h, type_c, nonce, iv, c_text);
	fclose(f);
	free(password), free(iv), free(key), free(filepath), free(c_text);
	return 0;
}
