#ifndef PQCLEAN_MCELIECE6960119_SSE_CRYPTO_HASH_H
#define PQCLEAN_MCELIECE6960119_SSE_CRYPTO_HASH_H
#include "fips202.h"

#define crypto_hash_32b(out,in,inlen) shake256(out, 32, in, inlen)

#endif
