#include "definitions.h"
#include "keccak256.h"

void printHexString(char *prefix, Bytes bytes) {
  printf("%s: 0x", prefix);
  for (size_t i = 0; i < bytes.count; i++)
    printf("%02x", bytes.arr[i]);
  printf("\n");
}

Bytes keccak256(Bytes input) {
  SHA3_CTX ctx;
  keccak_init(&ctx);
  keccak_update(&ctx, input.arr, input.count);
  uint8_t *output = malloc(KECCAK256_LENGTH);
  keccak_final(&ctx, output);
  Bytes result = { output, KECCAK256_LENGTH };
  return result;
}