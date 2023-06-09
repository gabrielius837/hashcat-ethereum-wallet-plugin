#pragma once

#define KECCAK256_LENGTH 32
#define UNCOMPRESSED_KEY_LENGTH 65
#define ADDRESS_LENGTH 20

#include "secp256k1.h"
#include "keccak/KeccakHash.h"
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  uint8_t *arr;
  size_t count;
} Bytes;

void printHexString(char *prefix, Bytes bytes);

int keccak256(Bytes *input, Bytes *output);

int generatePublicKey(Bytes *input, Bytes *output);