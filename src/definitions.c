#include "definitions.h"
#include <stdlib.h>

void printHexString(char *prefix, Bytes bytes) {
  printf("%s: 0x", prefix);
  for (size_t i = 0; i < bytes.count; i++)
    printf("%02x", bytes.arr[i]);
  printf("\n");
}

Bytes keccak256(Bytes input) {
  uint8_t *output = malloc(KECCAK256_LENGTH);
  wc_Sha3_256Hash(input.arr, input.count, output);
  Bytes result = { output, KECCAK256_LENGTH };
  return result;
}