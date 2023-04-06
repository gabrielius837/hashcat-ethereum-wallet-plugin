#pragma once

#define KECCAK256_LENGTH 32
#define UNCOMPRESSED_KEY_LENGTH 65

#include "keccak256.h"
#include <secp256k1.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  uint8_t *arr;
  size_t count;
} Bytes;

void printHexString(char *prefix, Bytes bytes);

Bytes keccak256(Bytes input);

Bytes generatePublicKey(Bytes privateKey);