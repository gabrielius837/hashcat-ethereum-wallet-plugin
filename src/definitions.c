#include "definitions.h"
#include <stdio.h>

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
  Bytes result = {output, KECCAK256_LENGTH};
  return result;
}

Bytes generatePublicKey(Bytes privateKey) {
  // fallback if privateKey is malformed (not 32 bytes)?

  // Initialize a secp256k1 context
  secp256k1_context *ctx = secp256k1_context_create(SECP256K1_CONTEXT_SIGN);

  // Compute the corresponding public key
  secp256k1_pubkey pubkey;
  int result = secp256k1_ec_pubkey_create(ctx, &pubkey, privateKey.arr);
  if (result != 0) {
    printf("fail\n");
    Bytes result = { NULL, 0 };
    return result;
  }

  // Serialize the public key to an uncompressed format
  size_t uncompressedKeyLength = UNCOMPRESSED_KEY_LENGTH;
  uint8_t *digest = malloc(uncompressedKeyLength);
  Bytes publicKey = {digest, uncompressedKeyLength};
  // resolve
  secp256k1_ec_pubkey_serialize(ctx, digest, &uncompressedKeyLength, &pubkey,
                                SECP256K1_EC_UNCOMPRESSED);
  secp256k1_context_destroy(ctx);
  Bytes test = {&pubkey, 64};
  printHexString("wtf", test);
  return publicKey;
}