#include <stdint.h>
#include <immintrin.h>
#include "params.h"
#include "consts.h"
#include "rejsample.h"

__attribute__((aligned(64)))
static const uint8_t idx[256][8] = {
  {-1, -1, -1, -1, -1, -1, -1, -1},
  { 0, -1, -1, -1, -1, -1, -1, -1},
  { 2, -1, -1, -1, -1, -1, -1, -1},
  { 0,  2, -1, -1, -1, -1, -1, -1},
  { 4, -1, -1, -1, -1, -1, -1, -1},
  { 0,  4, -1, -1, -1, -1, -1, -1},
  { 2,  4, -1, -1, -1, -1, -1, -1},
  { 0,  2,  4, -1, -1, -1, -1, -1},
  { 6, -1, -1, -1, -1, -1, -1, -1},
  { 0,  6, -1, -1, -1, -1, -1, -1},
  { 2,  6, -1, -1, -1, -1, -1, -1},
  { 0,  2,  6, -1, -1, -1, -1, -1},
  { 4,  6, -1, -1, -1, -1, -1, -1},
  { 0,  4,  6, -1, -1, -1, -1, -1},
  { 2,  4,  6, -1, -1, -1, -1, -1},
  { 0,  2,  4,  6, -1, -1, -1, -1},
  { 8, -1, -1, -1, -1, -1, -1, -1},
  { 0,  8, -1, -1, -1, -1, -1, -1},
  { 2,  8, -1, -1, -1, -1, -1, -1},
  { 0,  2,  8, -1, -1, -1, -1, -1},
  { 4,  8, -1, -1, -1, -1, -1, -1},
  { 0,  4,  8, -1, -1, -1, -1, -1},
  { 2,  4,  8, -1, -1, -1, -1, -1},
  { 0,  2,  4,  8, -1, -1, -1, -1},
  { 6,  8, -1, -1, -1, -1, -1, -1},
  { 0,  6,  8, -1, -1, -1, -1, -1},
  { 2,  6,  8, -1, -1, -1, -1, -1},
  { 0,  2,  6,  8, -1, -1, -1, -1},
  { 4,  6,  8, -1, -1, -1, -1, -1},
  { 0,  4,  6,  8, -1, -1, -1, -1},
  { 2,  4,  6,  8, -1, -1, -1, -1},
  { 0,  2,  4,  6,  8, -1, -1, -1},
  {10, -1, -1, -1, -1, -1, -1, -1},
  { 0, 10, -1, -1, -1, -1, -1, -1},
  { 2, 10, -1, -1, -1, -1, -1, -1},
  { 0,  2, 10, -1, -1, -1, -1, -1},
  { 4, 10, -1, -1, -1, -1, -1, -1},
  { 0,  4, 10, -1, -1, -1, -1, -1},
  { 2,  4, 10, -1, -1, -1, -1, -1},
  { 0,  2,  4, 10, -1, -1, -1, -1},
  { 6, 10, -1, -1, -1, -1, -1, -1},
  { 0,  6, 10, -1, -1, -1, -1, -1},
  { 2,  6, 10, -1, -1, -1, -1, -1},
  { 0,  2,  6, 10, -1, -1, -1, -1},
  { 4,  6, 10, -1, -1, -1, -1, -1},
  { 0,  4,  6, 10, -1, -1, -1, -1},
  { 2,  4,  6, 10, -1, -1, -1, -1},
  { 0,  2,  4,  6, 10, -1, -1, -1},
  { 8, 10, -1, -1, -1, -1, -1, -1},
  { 0,  8, 10, -1, -1, -1, -1, -1},
  { 2,  8, 10, -1, -1, -1, -1, -1},
  { 0,  2,  8, 10, -1, -1, -1, -1},
  { 4,  8, 10, -1, -1, -1, -1, -1},
  { 0,  4,  8, 10, -1, -1, -1, -1},
  { 2,  4,  8, 10, -1, -1, -1, -1},
  { 0,  2,  4,  8, 10, -1, -1, -1},
  { 6,  8, 10, -1, -1, -1, -1, -1},
  { 0,  6,  8, 10, -1, -1, -1, -1},
  { 2,  6,  8, 10, -1, -1, -1, -1},
  { 0,  2,  6,  8, 10, -1, -1, -1},
  { 4,  6,  8, 10, -1, -1, -1, -1},
  { 0,  4,  6,  8, 10, -1, -1, -1},
  { 2,  4,  6,  8, 10, -1, -1, -1},
  { 0,  2,  4,  6,  8, 10, -1, -1},
  {12, -1, -1, -1, -1, -1, -1, -1},
  { 0, 12, -1, -1, -1, -1, -1, -1},
  { 2, 12, -1, -1, -1, -1, -1, -1},
  { 0,  2, 12, -1, -1, -1, -1, -1},
  { 4, 12, -1, -1, -1, -1, -1, -1},
  { 0,  4, 12, -1, -1, -1, -1, -1},
  { 2,  4, 12, -1, -1, -1, -1, -1},
  { 0,  2,  4, 12, -1, -1, -1, -1},
  { 6, 12, -1, -1, -1, -1, -1, -1},
  { 0,  6, 12, -1, -1, -1, -1, -1},
  { 2,  6, 12, -1, -1, -1, -1, -1},
  { 0,  2,  6, 12, -1, -1, -1, -1},
  { 4,  6, 12, -1, -1, -1, -1, -1},
  { 0,  4,  6, 12, -1, -1, -1, -1},
  { 2,  4,  6, 12, -1, -1, -1, -1},
  { 0,  2,  4,  6, 12, -1, -1, -1},
  { 8, 12, -1, -1, -1, -1, -1, -1},
  { 0,  8, 12, -1, -1, -1, -1, -1},
  { 2,  8, 12, -1, -1, -1, -1, -1},
  { 0,  2,  8, 12, -1, -1, -1, -1},
  { 4,  8, 12, -1, -1, -1, -1, -1},
  { 0,  4,  8, 12, -1, -1, -1, -1},
  { 2,  4,  8, 12, -1, -1, -1, -1},
  { 0,  2,  4,  8, 12, -1, -1, -1},
  { 6,  8, 12, -1, -1, -1, -1, -1},
  { 0,  6,  8, 12, -1, -1, -1, -1},
  { 2,  6,  8, 12, -1, -1, -1, -1},
  { 0,  2,  6,  8, 12, -1, -1, -1},
  { 4,  6,  8, 12, -1, -1, -1, -1},
  { 0,  4,  6,  8, 12, -1, -1, -1},
  { 2,  4,  6,  8, 12, -1, -1, -1},
  { 0,  2,  4,  6,  8, 12, -1, -1},
  {10, 12, -1, -1, -1, -1, -1, -1},
  { 0, 10, 12, -1, -1, -1, -1, -1},
  { 2, 10, 12, -1, -1, -1, -1, -1},
  { 0,  2, 10, 12, -1, -1, -1, -1},
  { 4, 10, 12, -1, -1, -1, -1, -1},
  { 0,  4, 10, 12, -1, -1, -1, -1},
  { 2,  4, 10, 12, -1, -1, -1, -1},
  { 0,  2,  4, 10, 12, -1, -1, -1},
  { 6, 10, 12, -1, -1, -1, -1, -1},
  { 0,  6, 10, 12, -1, -1, -1, -1},
  { 2,  6, 10, 12, -1, -1, -1, -1},
  { 0,  2,  6, 10, 12, -1, -1, -1},
  { 4,  6, 10, 12, -1, -1, -1, -1},
  { 0,  4,  6, 10, 12, -1, -1, -1},
  { 2,  4,  6, 10, 12, -1, -1, -1},
  { 0,  2,  4,  6, 10, 12, -1, -1},
  { 8, 10, 12, -1, -1, -1, -1, -1},
  { 0,  8, 10, 12, -1, -1, -1, -1},
  { 2,  8, 10, 12, -1, -1, -1, -1},
  { 0,  2,  8, 10, 12, -1, -1, -1},
  { 4,  8, 10, 12, -1, -1, -1, -1},
  { 0,  4,  8, 10, 12, -1, -1, -1},
  { 2,  4,  8, 10, 12, -1, -1, -1},
  { 0,  2,  4,  8, 10, 12, -1, -1},
  { 6,  8, 10, 12, -1, -1, -1, -1},
  { 0,  6,  8, 10, 12, -1, -1, -1},
  { 2,  6,  8, 10, 12, -1, -1, -1},
  { 0,  2,  6,  8, 10, 12, -1, -1},
  { 4,  6,  8, 10, 12, -1, -1, -1},
  { 0,  4,  6,  8, 10, 12, -1, -1},
  { 2,  4,  6,  8, 10, 12, -1, -1},
  { 0,  2,  4,  6,  8, 10, 12, -1},
  {14, -1, -1, -1, -1, -1, -1, -1},
  { 0, 14, -1, -1, -1, -1, -1, -1},
  { 2, 14, -1, -1, -1, -1, -1, -1},
  { 0,  2, 14, -1, -1, -1, -1, -1},
  { 4, 14, -1, -1, -1, -1, -1, -1},
  { 0,  4, 14, -1, -1, -1, -1, -1},
  { 2,  4, 14, -1, -1, -1, -1, -1},
  { 0,  2,  4, 14, -1, -1, -1, -1},
  { 6, 14, -1, -1, -1, -1, -1, -1},
  { 0,  6, 14, -1, -1, -1, -1, -1},
  { 2,  6, 14, -1, -1, -1, -1, -1},
  { 0,  2,  6, 14, -1, -1, -1, -1},
  { 4,  6, 14, -1, -1, -1, -1, -1},
  { 0,  4,  6, 14, -1, -1, -1, -1},
  { 2,  4,  6, 14, -1, -1, -1, -1},
  { 0,  2,  4,  6, 14, -1, -1, -1},
  { 8, 14, -1, -1, -1, -1, -1, -1},
  { 0,  8, 14, -1, -1, -1, -1, -1},
  { 2,  8, 14, -1, -1, -1, -1, -1},
  { 0,  2,  8, 14, -1, -1, -1, -1},
  { 4,  8, 14, -1, -1, -1, -1, -1},
  { 0,  4,  8, 14, -1, -1, -1, -1},
  { 2,  4,  8, 14, -1, -1, -1, -1},
  { 0,  2,  4,  8, 14, -1, -1, -1},
  { 6,  8, 14, -1, -1, -1, -1, -1},
  { 0,  6,  8, 14, -1, -1, -1, -1},
  { 2,  6,  8, 14, -1, -1, -1, -1},
  { 0,  2,  6,  8, 14, -1, -1, -1},
  { 4,  6,  8, 14, -1, -1, -1, -1},
  { 0,  4,  6,  8, 14, -1, -1, -1},
  { 2,  4,  6,  8, 14, -1, -1, -1},
  { 0,  2,  4,  6,  8, 14, -1, -1},
  {10, 14, -1, -1, -1, -1, -1, -1},
  { 0, 10, 14, -1, -1, -1, -1, -1},
  { 2, 10, 14, -1, -1, -1, -1, -1},
  { 0,  2, 10, 14, -1, -1, -1, -1},
  { 4, 10, 14, -1, -1, -1, -1, -1},
  { 0,  4, 10, 14, -1, -1, -1, -1},
  { 2,  4, 10, 14, -1, -1, -1, -1},
  { 0,  2,  4, 10, 14, -1, -1, -1},
  { 6, 10, 14, -1, -1, -1, -1, -1},
  { 0,  6, 10, 14, -1, -1, -1, -1},
  { 2,  6, 10, 14, -1, -1, -1, -1},
  { 0,  2,  6, 10, 14, -1, -1, -1},
  { 4,  6, 10, 14, -1, -1, -1, -1},
  { 0,  4,  6, 10, 14, -1, -1, -1},
  { 2,  4,  6, 10, 14, -1, -1, -1},
  { 0,  2,  4,  6, 10, 14, -1, -1},
  { 8, 10, 14, -1, -1, -1, -1, -1},
  { 0,  8, 10, 14, -1, -1, -1, -1},
  { 2,  8, 10, 14, -1, -1, -1, -1},
  { 0,  2,  8, 10, 14, -1, -1, -1},
  { 4,  8, 10, 14, -1, -1, -1, -1},
  { 0,  4,  8, 10, 14, -1, -1, -1},
  { 2,  4,  8, 10, 14, -1, -1, -1},
  { 0,  2,  4,  8, 10, 14, -1, -1},
  { 6,  8, 10, 14, -1, -1, -1, -1},
  { 0,  6,  8, 10, 14, -1, -1, -1},
  { 2,  6,  8, 10, 14, -1, -1, -1},
  { 0,  2,  6,  8, 10, 14, -1, -1},
  { 4,  6,  8, 10, 14, -1, -1, -1},
  { 0,  4,  6,  8, 10, 14, -1, -1},
  { 2,  4,  6,  8, 10, 14, -1, -1},
  { 0,  2,  4,  6,  8, 10, 14, -1},
  {12, 14, -1, -1, -1, -1, -1, -1},
  { 0, 12, 14, -1, -1, -1, -1, -1},
  { 2, 12, 14, -1, -1, -1, -1, -1},
  { 0,  2, 12, 14, -1, -1, -1, -1},
  { 4, 12, 14, -1, -1, -1, -1, -1},
  { 0,  4, 12, 14, -1, -1, -1, -1},
  { 2,  4, 12, 14, -1, -1, -1, -1},
  { 0,  2,  4, 12, 14, -1, -1, -1},
  { 6, 12, 14, -1, -1, -1, -1, -1},
  { 0,  6, 12, 14, -1, -1, -1, -1},
  { 2,  6, 12, 14, -1, -1, -1, -1},
  { 0,  2,  6, 12, 14, -1, -1, -1},
  { 4,  6, 12, 14, -1, -1, -1, -1},
  { 0,  4,  6, 12, 14, -1, -1, -1},
  { 2,  4,  6, 12, 14, -1, -1, -1},
  { 0,  2,  4,  6, 12, 14, -1, -1},
  { 8, 12, 14, -1, -1, -1, -1, -1},
  { 0,  8, 12, 14, -1, -1, -1, -1},
  { 2,  8, 12, 14, -1, -1, -1, -1},
  { 0,  2,  8, 12, 14, -1, -1, -1},
  { 4,  8, 12, 14, -1, -1, -1, -1},
  { 0,  4,  8, 12, 14, -1, -1, -1},
  { 2,  4,  8, 12, 14, -1, -1, -1},
  { 0,  2,  4,  8, 12, 14, -1, -1},
  { 6,  8, 12, 14, -1, -1, -1, -1},
  { 0,  6,  8, 12, 14, -1, -1, -1},
  { 2,  6,  8, 12, 14, -1, -1, -1},
  { 0,  2,  6,  8, 12, 14, -1, -1},
  { 4,  6,  8, 12, 14, -1, -1, -1},
  { 0,  4,  6,  8, 12, 14, -1, -1},
  { 2,  4,  6,  8, 12, 14, -1, -1},
  { 0,  2,  4,  6,  8, 12, 14, -1},
  {10, 12, 14, -1, -1, -1, -1, -1},
  { 0, 10, 12, 14, -1, -1, -1, -1},
  { 2, 10, 12, 14, -1, -1, -1, -1},
  { 0,  2, 10, 12, 14, -1, -1, -1},
  { 4, 10, 12, 14, -1, -1, -1, -1},
  { 0,  4, 10, 12, 14, -1, -1, -1},
  { 2,  4, 10, 12, 14, -1, -1, -1},
  { 0,  2,  4, 10, 12, 14, -1, -1},
  { 6, 10, 12, 14, -1, -1, -1, -1},
  { 0,  6, 10, 12, 14, -1, -1, -1},
  { 2,  6, 10, 12, 14, -1, -1, -1},
  { 0,  2,  6, 10, 12, 14, -1, -1},
  { 4,  6, 10, 12, 14, -1, -1, -1},
  { 0,  4,  6, 10, 12, 14, -1, -1},
  { 2,  4,  6, 10, 12, 14, -1, -1},
  { 0,  2,  4,  6, 10, 12, 14, -1},
  { 8, 10, 12, 14, -1, -1, -1, -1},
  { 0,  8, 10, 12, 14, -1, -1, -1},
  { 2,  8, 10, 12, 14, -1, -1, -1},
  { 0,  2,  8, 10, 12, 14, -1, -1},
  { 4,  8, 10, 12, 14, -1, -1, -1},
  { 0,  4,  8, 10, 12, 14, -1, -1},
  { 2,  4,  8, 10, 12, 14, -1, -1},
  { 0,  2,  4,  8, 10, 12, 14, -1},
  { 6,  8, 10, 12, 14, -1, -1, -1},
  { 0,  6,  8, 10, 12, 14, -1, -1},
  { 2,  6,  8, 10, 12, 14, -1, -1},
  { 0,  2,  6,  8, 10, 12, 14, -1},
  { 4,  6,  8, 10, 12, 14, -1, -1},
  { 0,  4,  6,  8, 10, 12, 14, -1},
  { 2,  4,  6,  8, 10, 12, 14, -1},
  { 0,  2,  4,  6,  8, 10, 12, 14}
};

#define _mm256_cmpge_epu16(a, b) _mm256_cmpeq_epi16(_mm256_max_epu16(a, b), a)
#define _mm_cmpge_epu16(a, b) _mm_cmpeq_epi16(_mm_max_epu16(a, b), a)

#ifdef KYBER_90S
#define REJ_UNIFORM_BUFLEN 576
#else
#define REJ_UNIFORM_BUFLEN 672
#endif
unsigned int rej_uniform_avx(int16_t * restrict r,
                             const uint8_t * restrict buf)
{
  unsigned int ctr, pos;
  uint16_t val;
  uint32_t good;
  const __m256i bound  = _mm256_set1_epi16((int16_t)(19*KYBER_Q-1));
  const __m256i ones   = _mm256_set1_epi8(1);
  const __m256i kyberq = _mm256_load_si256((__m256i *)&qdata[_16XQ]);
  const __m256i v = _mm256_load_si256((__m256i *)&qdata[_16XV]);
  __m256i f0, f1, g0, g1, g2, g3;
  __m128i f, t, pilo, pihi;

  ctr = 0;
  for(pos = 0; pos < 2*KYBER_N; pos += 64) {
    f0 = _mm256_load_si256((__m256i *)&buf[pos+ 0]);
    f1 = _mm256_load_si256((__m256i *)&buf[pos+32]);

    g0 = _mm256_cmpge_epu16(bound, f0);
    g1 = _mm256_cmpge_epu16(bound, f1);

    g0 = _mm256_packs_epi16(g0, g1);
    good = _mm256_movemask_epi8(g0);

    g0 = _mm256_castsi128_si256(_mm_loadl_epi64((__m128i *)&idx[(good >>  0) & 0xFF]));
    g1 = _mm256_castsi128_si256(_mm_loadl_epi64((__m128i *)&idx[(good >>  8) & 0xFF]));
    g0 = _mm256_inserti128_si256(g0, _mm_loadl_epi64((__m128i *)&idx[(good >> 16) & 0xFF]), 1);
    g1 = _mm256_inserti128_si256(g1, _mm_loadl_epi64((__m128i *)&idx[(good >> 24) & 0xFF]), 1);

    //g0 = _mm256_cvtepu8_epi64(_mm_loadl_epi64((__m128i *)&good));
    //g1 = _mm256_i64gather_epi64((long long *)idx, g0, 8);

    /* Barrett reduction of (still unsigned) values */
    g2 = _mm256_mulhi_epu16(f0, v);
    g3 = _mm256_mulhi_epu16(f1, v);
    g2 = _mm256_srli_epi16(g2, 10);
    g3 = _mm256_srli_epi16(g3, 10);
    g2 = _mm256_mullo_epi16(g2, kyberq);
    g3 = _mm256_mullo_epi16(g3, kyberq);
    f0 = _mm256_sub_epi16(f0, g2);
    f1 = _mm256_sub_epi16(f1, g3);

    g2 = _mm256_add_epi8(g0, ones);
    g3 = _mm256_add_epi8(g1, ones);
    g0 = _mm256_unpacklo_epi8(g0, g2);
    g1 = _mm256_unpacklo_epi8(g1, g3);

    f0 = _mm256_shuffle_epi8(f0, g0);
    f1 = _mm256_shuffle_epi8(f1, g1);

    _mm_storeu_si128((__m128i *)&r[ctr], _mm256_castsi256_si128(f0));
    ctr += _mm_popcnt_u32((good >>  0) & 0xFF);
    _mm_storeu_si128((__m128i *)&r[ctr], _mm256_extracti128_si256(f0, 1));
    ctr += _mm_popcnt_u32((good >> 16) & 0xFF);
    _mm_storeu_si128((__m128i *)&r[ctr], _mm256_castsi256_si128(f1));
    ctr += _mm_popcnt_u32((good >>  8) & 0xFF);
    _mm_storeu_si128((__m128i *)&r[ctr], _mm256_extracti128_si256(f1, 1));
    ctr += _mm_popcnt_u32((good >> 24) & 0xFF);
  }

  while(ctr <= KYBER_N - 8 && pos <= REJ_UNIFORM_BUFLEN - 16) {
    f = _mm_load_si128((__m128i *)&buf[pos]);
    t = _mm_cmpge_epu16(_mm256_castsi256_si128(bound), f);
    good = _mm_movemask_epi8(t);
    good = _pext_u32(good, 0x5555);
    pilo = _mm_loadl_epi64((__m128i *)&idx[good]);
    pihi = _mm_add_epi8(pilo, _mm256_castsi256_si128(ones));
    pilo = _mm_unpacklo_epi8(pilo, pihi);

    /* Barrett reduction */
    t = _mm_mulhi_epu16(f, _mm256_castsi256_si128(v));
    t = _mm_srli_epi16(t, 10);
    t = _mm_mullo_epi16(t, _mm256_castsi256_si128(kyberq));
    f = _mm_sub_epi16(f, t);

    f = _mm_shuffle_epi8(f, pilo);
    _mm_storeu_si128((__m128i *)&r[ctr], f);
    ctr += _mm_popcnt_u32(good);
    pos += 16;
  }

  while(ctr < KYBER_N && pos <= REJ_UNIFORM_BUFLEN - 2) {
    val = buf[pos] | ((uint16_t)buf[pos+1] << 8);
    pos += 2;

    if(val < 19*KYBER_Q) {
      val -= ((int32_t)val*20159 >> 26) * KYBER_Q;
      r[ctr++] = val;
    }
  }

  return ctr;
}