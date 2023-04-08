#include "definitions.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getSeed(int argc, char **argv, Bytes *output) {
  if (argc != 2) {
    fprintf(stderr, "defaulting to empty seed\n");
    uint8_t *arr = malloc(0);
    output->arr = arr;
    output->count = 0;
    return 0;
  }

  char *str = argv[1];
  int length = strlen(str);
  if (length % 2 != 0 || length < 2) {
    fprintf(stderr, "expecting non empty even length seed, instead got %s\n",
            str);
    return 1;
  }

  int offset = str[0] == '0' && str[1] == 'x' ? 2 : 0;
  size_t count = (length - offset) / 2;
  uint8_t *arr = malloc(count);
  if (!arr) {
    fprintf(stderr, "failed to allocate memory for seed.\n");
    return 1;
  }

  for (int i = offset; i < length; i += 2) {
    uint32_t byte;
    if (sscanf(&str[i], "%2x", &byte) != 1) {
      fprintf(stderr, "Invalid hex string.\n");
      free(arr);
      return 1;
    }
    arr[(i - offset) / 2] = (uint8_t)byte;
  }

  output->arr = arr;
  output->count = count;
  return 0;
}

int main(int argc, char **argv) {
  Bytes seed;
  int statusCode;

  if ((statusCode = getSeed(argc, argv, &seed)) != 0) {
    return statusCode;
  }
  printHexString("seed", seed);

  Bytes privateKey;
  if ((statusCode = keccak256(&seed, &privateKey)) != 0) {
    free(seed.arr);
    return statusCode;
  }
  printHexString("private key", privateKey);

  Bytes publicKey;
  if ((statusCode = generatePublicKey(&privateKey, &publicKey)) != 0) {
    free(seed.arr);
    free(privateKey.arr);
    return statusCode;
  }
  printHexString("public key", publicKey);

  free(seed.arr);
  free(privateKey.arr);
  free(publicKey.arr);

  return 0;
}