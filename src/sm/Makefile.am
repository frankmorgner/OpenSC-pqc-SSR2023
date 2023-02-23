# Process this file with automake to create Makefile.in

MAINTAINERCLEANFILES = Makefile.in
EXTRA_DIST = Makefile.mak

noinst_LTLIBRARIES = libsmiso.la libsmeac.la

noinst_HEADERS = \
		 sm-iso-internal.h \
		 sm-iso.h \
		 sslutil.h \
		 sm-eac.h

if ENABLE_OPENSSL
noinst_LTLIBRARIES += libsm.la
endif
noinst_HEADERS += sm-common.h

AM_CFLAGS = $(OPTIONAL_OPENSSL_CFLAGS) $(OPTIONAL_READLINE_CFLAGS)
AM_CPPFLAGS = -I$(top_srcdir)/src -I$(top_builddir)/src/include

libsm_la_SOURCES = sm-common.c sm-common.h

libsmiso_la_SOURCES = sm-iso.c

libsmeac_la_SOURCES = sm-eac.c
libsmeac_la_LIBADD = $(OPENPACE_LIBS) $(OPENSSL_LIBS) libsmiso.la libpqcrystals_dilithium3_ref.la libpqcrystals_kyber1024_ref.la libpqclean.la
libsmeac_la_CFLAGS = $(OPENPACE_CFLAGS) $(OPENSSL_CFLAGS) -I$(top_srcdir)/src -DENABLE_KYBER_REFERENCE=1
#libsmeac_la_CFLAGS = $(OPENPACE_CFLAGS) $(OPENSSL_CFLAGS) -I$(top_srcdir)/src -DENABLE_PQCLEAN=1

lib_LTLIBRARIES =
lib_LTLIBRARIES += libpqcrystals_kyber512_ref.la
lib_LTLIBRARIES += libpqcrystals_kyber768_ref.la
lib_LTLIBRARIES += libpqcrystals_kyber1024_ref.la

SOURCES_KYBER = kyber/ref/kem.c kyber/ref/indcpa.c kyber/ref/polyvec.c kyber/ref/poly.c kyber/ref/reduce.c kyber/ref/ntt.c kyber/ref/cbd.c kyber/ref/verify.c

libpqcrystals_kyber512_ref_la_SOURCES= $(SOURCES_KYBER) kyber/ref/symmetric-shake.c kyber/ref/fips202.c kyber/ref/randombytes.c
libpqcrystals_kyber512_ref_la_CFLAGS= -DKYBER_K=2
libpqcrystals_kyber512_ref_la_LDFLAGS= -export-symbols-regex '^pqcrystals_kyber'

libpqcrystals_kyber768_ref_la_SOURCES= $(SOURCES_KYBER) kyber/ref/symmetric-shake.c kyber/ref/fips202.c kyber/ref/randombytes.c
libpqcrystals_kyber768_ref_la_CFLAGS= -DKYBER_K=3
libpqcrystals_kyber768_ref_la_LDFLAGS= -export-symbols-regex '^pqcrystals_kyber'

libpqcrystals_kyber1024_ref_la_SOURCES= $(SOURCES_KYBER) kyber/ref/symmetric-shake.c kyber/ref/fips202.c kyber/ref/randombytes.c
libpqcrystals_kyber1024_ref_la_CFLAGS= -DKYBER_K=4
libpqcrystals_kyber1024_ref_la_LDFLAGS= -export-symbols-regex '^pqcrystals_kyber'

lib_LTLIBRARIES += libpqcrystals_dilithium2_ref.la
lib_LTLIBRARIES += libpqcrystals_dilithium3_ref.la
lib_LTLIBRARIES += libpqcrystals_dilithium4_ref.la

SOURCES_DILITHIUM = dilithium/ref/sign.c dilithium/ref/packing.c dilithium/ref/polyvec.c dilithium/ref/poly.c dilithium/ref/ntt.c dilithium/ref/reduce.c dilithium/ref/rounding.c

libpqcrystals_dilithium2_ref_la_SOURCES= $(SOURCES_DILITHIUM) dilithium/ref/symmetric-shake.c dilithium/ref/fips202.c dilithium/ref/randombytes.c
libpqcrystals_dilithium2_ref_la_CFLAGS= -DDILITHIUM_MODE=2
libpqcrystals_dilithium2_ref_la_LDFLAGS= -export-symbols-regex '^pqcrystals_dilithium'

libpqcrystals_dilithium3_ref_la_SOURCES= $(SOURCES_DILITHIUM) dilithium/ref/symmetric-shake.c dilithium/ref/fips202.c dilithium/ref/randombytes.c
libpqcrystals_dilithium3_ref_la_CFLAGS= -DDILITHIUM_MODE=3
libpqcrystals_dilithium3_ref_la_LDFLAGS= -export-symbols-regex '^pqcrystals_dilithium'

libpqcrystals_dilithium4_ref_la_SOURCES= $(SOURCES_DILITHIUM) dilithium/ref/symmetric-shake.c dilithium/ref/fips202.c dilithium/ref/randombytes.c
libpqcrystals_dilithium4_ref_la_CFLAGS= -DDILITHIUM_MODE=4
libpqcrystals_dilithium4_ref_la_LDFLAGS= -export-symbols-regex '^pqcrystals_dilithium'

noinst_LTLIBRARIES += libpqclean.la

SOURCES_PQCLEAN = \
				  PQClean/common/randombytes.c \
				  PQClean/common/fips202.c \
				  PQClean/crypto_kem/kyber1024/clean/cbd.c \
				  PQClean/crypto_kem/kyber1024/clean/indcpa.c \
				  PQClean/crypto_kem/kyber1024/clean/kem.c \
				  PQClean/crypto_kem/kyber1024/clean/ntt.c \
				  PQClean/crypto_kem/kyber1024/clean/poly.c \
				  PQClean/crypto_kem/kyber1024/clean/polyvec.c \
				  PQClean/crypto_kem/kyber1024/clean/reduce.c \
				  PQClean/crypto_kem/kyber1024/clean/verify.c \
				  PQClean/crypto_kem/kyber1024/clean/symmetric-fips202.c

#PQClean/crypto_sign/dilithium3/clean/packing.c
#PQClean/crypto_sign/dilithium3/clean/rounding.c
#PQClean/crypto_sign/dilithium3/clean/sign.c

#PQClean/crypto_sign/dilithium3/clean/ntt.c
#PQClean/crypto_sign/dilithium3/clean/poly.c
#PQClean/crypto_sign/dilithium3/clean/polyvec.c
#PQClean/crypto_sign/dilithium3/clean/reduce.c

libpqclean_la_SOURCES = $(SOURCES_PQCLEAN)
libpqclean_la_CPPFLAGS= -IPQClean/crypto_kem/kyber1024/clean -IPQClean/common
