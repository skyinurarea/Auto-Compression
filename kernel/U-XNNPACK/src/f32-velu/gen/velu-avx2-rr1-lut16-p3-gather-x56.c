// Auto-generated file. Do not edit!
//   Template: src/f32-velu/avx2-rr1-lut16-p3-gather.c.in
//   Generator: tools/xngen
//
// Copyright 2020 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <immintrin.h>

#include <xnnpack/common.h>
#include <xnnpack/vunary.h>


extern XNN_INTERNAL const int xnn_table_exp2minus_k_over_16[16];

static const int32_t mask_table[14] = {-1, -1, -1, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0};

void xnn_f32_velu_ukernel__avx2_rr1_lut16_p3_gather_x56(
    size_t n,
    const float* x,
    float* y,
    const union xnn_f32_elu_params params[restrict XNN_MIN_ELEMENTS(1)])
{
  assert(n % sizeof(float) == 0);

  const __m256 vprescale = _mm256_broadcast_ps((const __m128*) params->sse.prescale);
  const __m256 valpha = _mm256_broadcast_ps((const __m128*) params->sse.alpha);
  const __m256 vbeta = _mm256_broadcast_ps((const __m128*) params->sse.beta);

  const __m256 vsat_cutoff = _mm256_set1_ps(-0x1.154246p+4f);
  const __m256 vmagic_bias = _mm256_set1_ps(0x1.800000p19f);
  const __m256 vlog2e = _mm256_set1_ps(0x1.715476p+0f);
  const __m256i vindex_mask = _mm256_set1_epi32(0xF);
  const __m256 vminus_ln2 = _mm256_set1_ps(-0x1.62E43p-1f);
  const __m256 vc3 = _mm256_set1_ps(0x1.55561Cp-3f);
  const __m256 vc2 = _mm256_set1_ps(0x1.0001ECp-1f);

  for (; n >= 56 * sizeof(float); n -= 56 * sizeof(float)) {
    __m256 vx0 = _mm256_loadu_ps(x);
    __m256 vx1 = _mm256_loadu_ps(x + 8);
    __m256 vx2 = _mm256_loadu_ps(x + 16);
    __m256 vx3 = _mm256_loadu_ps(x + 24);
    __m256 vx4 = _mm256_loadu_ps(x + 32);
    __m256 vx5 = _mm256_loadu_ps(x + 40);
    __m256 vx6 = _mm256_loadu_ps(x + 48);
    x += 56;

    const __m256 vz0 = _mm256_max_ps(vsat_cutoff, _mm256_mul_ps(vx0, vprescale));
    const __m256 vz1 = _mm256_max_ps(vsat_cutoff, _mm256_mul_ps(vx1, vprescale));
    const __m256 vz2 = _mm256_max_ps(vsat_cutoff, _mm256_mul_ps(vx2, vprescale));
    const __m256 vz3 = _mm256_max_ps(vsat_cutoff, _mm256_mul_ps(vx3, vprescale));
    const __m256 vz4 = _mm256_max_ps(vsat_cutoff, _mm256_mul_ps(vx4, vprescale));
    const __m256 vz5 = _mm256_max_ps(vsat_cutoff, _mm256_mul_ps(vx5, vprescale));
    const __m256 vz6 = _mm256_max_ps(vsat_cutoff, _mm256_mul_ps(vx6, vprescale));

    __m256 vn0 = _mm256_fmadd_ps(vz0, vlog2e, vmagic_bias);
    __m256 vn1 = _mm256_fmadd_ps(vz1, vlog2e, vmagic_bias);
    __m256 vn2 = _mm256_fmadd_ps(vz2, vlog2e, vmagic_bias);
    __m256 vn3 = _mm256_fmadd_ps(vz3, vlog2e, vmagic_bias);
    __m256 vn4 = _mm256_fmadd_ps(vz4, vlog2e, vmagic_bias);
    __m256 vn5 = _mm256_fmadd_ps(vz5, vlog2e, vmagic_bias);
    __m256 vn6 = _mm256_fmadd_ps(vz6, vlog2e, vmagic_bias);

    const __m256i vidx0 = _mm256_and_si256(_mm256_castps_si256(vn0), vindex_mask);
    const __m256i vl0 = _mm256_i32gather_epi32(xnn_table_exp2minus_k_over_16, vidx0, sizeof(float));
    const __m256i vidx1 = _mm256_and_si256(_mm256_castps_si256(vn1), vindex_mask);
    const __m256i vl1 = _mm256_i32gather_epi32(xnn_table_exp2minus_k_over_16, vidx1, sizeof(float));
    const __m256i vidx2 = _mm256_and_si256(_mm256_castps_si256(vn2), vindex_mask);
    const __m256i vl2 = _mm256_i32gather_epi32(xnn_table_exp2minus_k_over_16, vidx2, sizeof(float));
    const __m256i vidx3 = _mm256_and_si256(_mm256_castps_si256(vn3), vindex_mask);
    const __m256i vl3 = _mm256_i32gather_epi32(xnn_table_exp2minus_k_over_16, vidx3, sizeof(float));
    const __m256i vidx4 = _mm256_and_si256(_mm256_castps_si256(vn4), vindex_mask);
    const __m256i vl4 = _mm256_i32gather_epi32(xnn_table_exp2minus_k_over_16, vidx4, sizeof(float));
    const __m256i vidx5 = _mm256_and_si256(_mm256_castps_si256(vn5), vindex_mask);
    const __m256i vl5 = _mm256_i32gather_epi32(xnn_table_exp2minus_k_over_16, vidx5, sizeof(float));
    const __m256i vidx6 = _mm256_and_si256(_mm256_castps_si256(vn6), vindex_mask);
    const __m256i vl6 = _mm256_i32gather_epi32(xnn_table_exp2minus_k_over_16, vidx6, sizeof(float));

    const __m256i ven0 = _mm256_slli_epi32(_mm256_castps_si256(vn0), 19);
    vn0 = _mm256_sub_ps(vn0, vmagic_bias);
    const __m256i ven1 = _mm256_slli_epi32(_mm256_castps_si256(vn1), 19);
    vn1 = _mm256_sub_ps(vn1, vmagic_bias);
    const __m256i ven2 = _mm256_slli_epi32(_mm256_castps_si256(vn2), 19);
    vn2 = _mm256_sub_ps(vn2, vmagic_bias);
    const __m256i ven3 = _mm256_slli_epi32(_mm256_castps_si256(vn3), 19);
    vn3 = _mm256_sub_ps(vn3, vmagic_bias);
    const __m256i ven4 = _mm256_slli_epi32(_mm256_castps_si256(vn4), 19);
    vn4 = _mm256_sub_ps(vn4, vmagic_bias);
    const __m256i ven5 = _mm256_slli_epi32(_mm256_castps_si256(vn5), 19);
    vn5 = _mm256_sub_ps(vn5, vmagic_bias);
    const __m256i ven6 = _mm256_slli_epi32(_mm256_castps_si256(vn6), 19);
    vn6 = _mm256_sub_ps(vn6, vmagic_bias);

    __m256 vs0 = _mm256_castsi256_ps(_mm256_add_epi32(vl0, ven0));
    __m256 vt0 = _mm256_fmadd_ps(vn0, vminus_ln2, vz0);
    __m256 vs1 = _mm256_castsi256_ps(_mm256_add_epi32(vl1, ven1));
    __m256 vt1 = _mm256_fmadd_ps(vn1, vminus_ln2, vz1);
    __m256 vs2 = _mm256_castsi256_ps(_mm256_add_epi32(vl2, ven2));
    __m256 vt2 = _mm256_fmadd_ps(vn2, vminus_ln2, vz2);
    __m256 vs3 = _mm256_castsi256_ps(_mm256_add_epi32(vl3, ven3));
    __m256 vt3 = _mm256_fmadd_ps(vn3, vminus_ln2, vz3);
    __m256 vs4 = _mm256_castsi256_ps(_mm256_add_epi32(vl4, ven4));
    __m256 vt4 = _mm256_fmadd_ps(vn4, vminus_ln2, vz4);
    __m256 vs5 = _mm256_castsi256_ps(_mm256_add_epi32(vl5, ven5));
    __m256 vt5 = _mm256_fmadd_ps(vn5, vminus_ln2, vz5);
    __m256 vs6 = _mm256_castsi256_ps(_mm256_add_epi32(vl6, ven6));
    __m256 vt6 = _mm256_fmadd_ps(vn6, vminus_ln2, vz6);

    __m256 vp0 = _mm256_fmadd_ps(vc3, vt0, vc2);
    __m256 vp1 = _mm256_fmadd_ps(vc3, vt1, vc2);
    __m256 vp2 = _mm256_fmadd_ps(vc3, vt2, vc2);
    __m256 vp3 = _mm256_fmadd_ps(vc3, vt3, vc2);
    __m256 vp4 = _mm256_fmadd_ps(vc3, vt4, vc2);
    __m256 vp5 = _mm256_fmadd_ps(vc3, vt5, vc2);
    __m256 vp6 = _mm256_fmadd_ps(vc3, vt6, vc2);

    vp0 = _mm256_mul_ps(vp0, vt0);
    vt0 = _mm256_mul_ps(vt0, vs0);
    vp1 = _mm256_mul_ps(vp1, vt1);
    vt1 = _mm256_mul_ps(vt1, vs1);
    vp2 = _mm256_mul_ps(vp2, vt2);
    vt2 = _mm256_mul_ps(vt2, vs2);
    vp3 = _mm256_mul_ps(vp3, vt3);
    vt3 = _mm256_mul_ps(vt3, vs3);
    vp4 = _mm256_mul_ps(vp4, vt4);
    vt4 = _mm256_mul_ps(vt4, vs4);
    vp5 = _mm256_mul_ps(vp5, vt5);
    vt5 = _mm256_mul_ps(vt5, vs5);
    vp6 = _mm256_mul_ps(vp6, vt6);
    vt6 = _mm256_mul_ps(vt6, vs6);

    vs0 = _mm256_fmsub_ps(vs0, valpha, valpha);
    vp0 = _mm256_fmadd_ps(vp0, vt0, vt0);
    vs1 = _mm256_fmsub_ps(vs1, valpha, valpha);
    vp1 = _mm256_fmadd_ps(vp1, vt1, vt1);
    vs2 = _mm256_fmsub_ps(vs2, valpha, valpha);
    vp2 = _mm256_fmadd_ps(vp2, vt2, vt2);
    vs3 = _mm256_fmsub_ps(vs3, valpha, valpha);
    vp3 = _mm256_fmadd_ps(vp3, vt3, vt3);
    vs4 = _mm256_fmsub_ps(vs4, valpha, valpha);
    vp4 = _mm256_fmadd_ps(vp4, vt4, vt4);
    vs5 = _mm256_fmsub_ps(vs5, valpha, valpha);
    vp5 = _mm256_fmadd_ps(vp5, vt5, vt5);
    vs6 = _mm256_fmsub_ps(vs6, valpha, valpha);
    vp6 = _mm256_fmadd_ps(vp6, vt6, vt6);

    const __m256 ve0 = _mm256_fmadd_ps(vp0, valpha, vs0);
    vx0 = _mm256_mul_ps(vx0, vbeta);
    const __m256 ve1 = _mm256_fmadd_ps(vp1, valpha, vs1);
    vx1 = _mm256_mul_ps(vx1, vbeta);
    const __m256 ve2 = _mm256_fmadd_ps(vp2, valpha, vs2);
    vx2 = _mm256_mul_ps(vx2, vbeta);
    const __m256 ve3 = _mm256_fmadd_ps(vp3, valpha, vs3);
    vx3 = _mm256_mul_ps(vx3, vbeta);
    const __m256 ve4 = _mm256_fmadd_ps(vp4, valpha, vs4);
    vx4 = _mm256_mul_ps(vx4, vbeta);
    const __m256 ve5 = _mm256_fmadd_ps(vp5, valpha, vs5);
    vx5 = _mm256_mul_ps(vx5, vbeta);
    const __m256 ve6 = _mm256_fmadd_ps(vp6, valpha, vs6);
    vx6 = _mm256_mul_ps(vx6, vbeta);

    const __m256 vy0 = _mm256_blendv_ps(vx0, ve0, vx0);
    const __m256 vy1 = _mm256_blendv_ps(vx1, ve1, vx1);
    const __m256 vy2 = _mm256_blendv_ps(vx2, ve2, vx2);
    const __m256 vy3 = _mm256_blendv_ps(vx3, ve3, vx3);
    const __m256 vy4 = _mm256_blendv_ps(vx4, ve4, vx4);
    const __m256 vy5 = _mm256_blendv_ps(vx5, ve5, vx5);
    const __m256 vy6 = _mm256_blendv_ps(vx6, ve6, vx6);

    _mm256_storeu_ps(y, vy0);
    _mm256_storeu_ps(y + 8, vy1);
    _mm256_storeu_ps(y + 16, vy2);
    _mm256_storeu_ps(y + 24, vy3);
    _mm256_storeu_ps(y + 32, vy4);
    _mm256_storeu_ps(y + 40, vy5);
    _mm256_storeu_ps(y + 48, vy6);
    y += 56;
  }
  for (; n >= 8 * sizeof(float); n -= 8 * sizeof(float)) {
    __m256 vx = _mm256_loadu_ps(x);
    x += 8;

    const __m256 vz = _mm256_max_ps(vsat_cutoff, _mm256_mul_ps(vx, vprescale));

    __m256 vn = _mm256_fmadd_ps(vz, vlog2e, vmagic_bias);
    const __m256i vidx = _mm256_and_si256(_mm256_castps_si256(vn), vindex_mask);
    const __m256i vl = _mm256_i32gather_epi32(xnn_table_exp2minus_k_over_16, vidx, sizeof(float));

    const __m256i ven = _mm256_slli_epi32(_mm256_castps_si256(vn), 19);
    vn = _mm256_sub_ps(vn, vmagic_bias);

    __m256 vs = _mm256_castsi256_ps(_mm256_add_epi32(vl, ven));
    __m256 vt = _mm256_fmadd_ps(vn, vminus_ln2, vz);

    __m256 vp = _mm256_fmadd_ps(vc3, vt, vc2);
    vp = _mm256_mul_ps(vp, vt);

    vt = _mm256_mul_ps(vt, vs);
    vs = _mm256_fmsub_ps(vs, valpha, valpha);
    vp = _mm256_fmadd_ps(vp, vt, vt);
    const __m256 ve = _mm256_fmadd_ps(vp, valpha, vs);

    vx = _mm256_mul_ps(vx, vbeta);
    const __m256 vy = _mm256_blendv_ps(vx, ve, vx);

    _mm256_storeu_ps(y, vy);
    y += 8;
  }
  if XNN_UNLIKELY(n != 0) {
    assert(n >= 1 * sizeof(float));
    assert(n <= 7 * sizeof(float));
    __m256i vmask = _mm256_loadu_si256((const __m256i*) ((uintptr_t) &mask_table[7] - n));

    __m256 vx = _mm256_maskload_ps(x, vmask);

    const __m256 vz = _mm256_max_ps(vsat_cutoff, _mm256_mul_ps(vx, vprescale));

    __m256 vn = _mm256_fmadd_ps(vz, vlog2e, vmagic_bias);
    const __m256i vidx = _mm256_and_si256(_mm256_castps_si256(vn), vindex_mask);
    const __m256i vl = _mm256_i32gather_epi32(xnn_table_exp2minus_k_over_16, vidx, sizeof(float));

    const __m256i ven = _mm256_slli_epi32(_mm256_castps_si256(vn), 19);
    vn = _mm256_sub_ps(vn, vmagic_bias);

    __m256 vs = _mm256_castsi256_ps(_mm256_add_epi32(vl, ven));
    __m256 vt = _mm256_fmadd_ps(vn, vminus_ln2, vz);

    __m256 vp = _mm256_fmadd_ps(vc3, vt, vc2);
    vp = _mm256_mul_ps(vp, vt);

    vt = _mm256_mul_ps(vt, vs);
    vs = _mm256_fmsub_ps(vs, valpha, valpha);
    vp = _mm256_fmadd_ps(vp, vt, vt);
    const __m256 ve = _mm256_fmadd_ps(vp, valpha, vs);

    vx = _mm256_mul_ps(vx, vbeta);
    const __m256 vy = _mm256_blendv_ps(vx, ve, vx);

    // _mm256_maskstore_ps(y, vmask, vf) could be used here, but triggers msan failures (probably an msan bug).
    __m128 vy_lo = _mm256_castps256_ps128(vy);
    if (n & (4 * sizeof(float))) {
      _mm_storeu_ps(y, vy_lo);
      vy_lo = _mm256_extractf128_ps(vy, 1);
      y += 4;
    }
    if (n & (2 * sizeof(float))) {
      _mm_storel_pi((__m64*) y, vy_lo);
      vy_lo = _mm_movehl_ps(vy_lo, vy_lo);
      y += 2;
    }
    if (n & (1 * sizeof(float))) {
      _mm_store_ss(y, vy_lo);
    }
  }
}
