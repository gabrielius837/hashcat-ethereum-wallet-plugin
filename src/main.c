#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "definitions.h"


Bytes getSeed(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "defaulting to empty seed\n");
    uint8_t *arr = malloc(0);
    Bytes seed = {arr, 0};
    return seed;
  }

  char *str = argv[1];
  int length = strlen(str);
  if (length % 2 != 0 || length < 2) {
    fprintf(stderr, "expecting non empty even length seed, instead got %s\n",
            str);
    exit(1);
  }

  int offset = str[0] == '0' && str[1] == 'x' ? 2 : 0;
  size_t count = (length - offset) / 2;
  uint8_t *arr = malloc(count);
  if (!arr) {
    fprintf(stderr, "failed to allocate memory.\n");
    exit(1);
  }

  for (int i = offset; i < length; i += 2) {
    uint32_t byte;
    if (sscanf(&str[i], "%2x", &byte) != 1) {
      fprintf(stderr, "Invalid hex string.\n");
      exit(1);
    }
    arr[(i - offset) / 2] = (uint8_t)byte;
  }

  Bytes bytes = {arr, count};
  return bytes;
}

int main(int argc, char **argv) {
  Bytes seed = getSeed(argc, argv);
  printHexString("seed", seed);
  Bytes privateKey = keccak256(seed);
  printHexString("private key", privateKey);
  Bytes publicKey = generatePublicKey(privateKey);
  printHexString("uncompressed key", publicKey);
  return 0;
}