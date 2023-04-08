#include "definitions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printHexString(char *prefix, Bytes bytes) {
  printf("%s: 0x", prefix);
  for (size_t i = 0; i < bytes.count; i++)
    printf("%02x", bytes.arr[i]);
  printf("\n");
}

int keccak256(Bytes *input, Bytes *output) {
  // no possible indication if something went wrong...
  SHA3_CTX ctx;
  keccak_init(&ctx);
  keccak_update(&ctx, input->arr, input->count);
  uint8_t *digest = malloc(KECCAK256_LENGTH);
  if (!digest) {
    fprintf(stderr, "failed to allocate bytes for keccak256\n");
    return 1;
  }
  keccak_final(&ctx, digest);
  output->arr = digest;
  output->count = KECCAK256_LENGTH;
  return 0;
}

int generatePublicKey(Bytes *input, Bytes *output) {
  secp256k1_context *ctx;
  secp256k1_pubkey pubkey;

  // Create a new secp256k1 context object
  ctx = secp256k1_context_create(SECP256K1_CONTEXT_SIGN |
                                 SECP256K1_CONTEXT_VERIFY);
  if (ctx == NULL) {
    fprintf(stderr, "failed to create secp256k1 context object\n");
    return 1;
  }

  // Compute the public key from the private key
  if (secp256k1_ec_pubkey_create(ctx, &pubkey, input->arr) != 1) {
    fprintf(stderr, "failed to compute public key from private key\n");
    secp256k1_context_destroy(ctx);
    return 1;
  }

  // Convert the public key to a binary format
  size_t outputLength = UNCOMPRESSED_KEY_LENGTH;
  uint8_t *outputArr = malloc(UNCOMPRESSED_KEY_LENGTH);
  if (secp256k1_ec_pubkey_serialize(ctx, outputArr, &outputLength, &pubkey,
                                    SECP256K1_EC_UNCOMPRESSED) != 1) {
    printf("failed to serialize public key\n");
    secp256k1_context_destroy(ctx);
    free(outputArr);
    return 1;
  }

  output->arr = outputArr + 1;
  output->count = outputLength - 1;

  int statusCode;
  Bytes digest;
  if ((statusCode = keccak256(output, &digest)) != 0) {
    free(outputArr);
    return statusCode;
  }

  uint8_t *address = malloc(ADDRESS_LENGTH);
  if (!address) {
    free(outputArr);
    free(digest.arr);
    fprintf(stderr, "failed to allocate bytes for address");
    return 1;
  }

  memcpy(address, (digest.arr + 12), ADDRESS_LENGTH);

  free(outputArr);
  free(digest.arr);

  output->arr = address;
  output->count = ADDRESS_LENGTH;

  return 0;
}