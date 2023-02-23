#ifndef PQCLEAN_MCELIECE460896_CLEAN_SK_GEN_H
#define PQCLEAN_MCELIECE460896_CLEAN_SK_GEN_H
/*
  This file is for secret-key generation
*/


#include "gf.h"

#include <stdint.h>

int PQCLEAN_MCELIECE460896_CLEAN_genpoly_gen(gf * /*out*/, gf * /*f*/);
int PQCLEAN_MCELIECE460896_CLEAN_perm_check(const uint32_t * /*p*/);

#endif

