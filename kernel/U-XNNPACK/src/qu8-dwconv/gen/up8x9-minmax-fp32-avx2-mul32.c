// Auto-generated file. Do not edit!
//   Template: src/qs8-dwconv/unipass-avx2-mul32.c.in
//   Generator: tools/xngen
//
// Copyright 2020 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <immintrin.h>

#include <xnnpack/dwconv.h>


void xnn_qu8_dwconv_minmax_fp32_ukernel_up8x9__avx2_mul32(
    size_t channels,
    size_t output_width,
    const uint8_t** input,
    const void* weights,
    uint8_t* output,
    size_t input_stride,
    size_t output_increment,
    size_t input_offset,
    const uint8_t* zero,
    const union xnn_qu8_conv_minmax_params params[restrict XNN_MIN_ELEMENTS(1)]) XNN_DISABLE_TSAN XNN_DISABLE_MSAN
{
  assert(channels != 0);
  assert(output_width != 0);

  const __m256i vk_zero_point = _mm256_cvtepu16_epi32(_mm_load_si128((const __m128i*) params->fp32_avx2.kernel_zero_point));
  do {
    const uint8_t* i0 = input[0];
    assert(i0 != NULL);
    if XNN_UNPREDICTABLE(i0 != zero) {
      i0 = (const uint8_t*) ((uintptr_t) i0 + input_offset);
    }
    const uint8_t* i1 = input[1];
    assert(i1 != NULL);
    if XNN_UNPREDICTABLE(i1 != zero) {
      i1 = (const uint8_t*) ((uintptr_t) i1 + input_offset);
    }
    const uint8_t* i2 = input[2];
    assert(i2 != NULL);
    if XNN_UNPREDICTABLE(i2 != zero) {
      i2 = (const uint8_t*) ((uintptr_t) i2 + input_offset);
    }
    const uint8_t* i3 = input[3];
    assert(i3 != NULL);
    if XNN_UNPREDICTABLE(i3 != zero) {
      i3 = (const uint8_t*) ((uintptr_t) i3 + input_offset);
    }
    const uint8_t* i4 = input[4];
    assert(i4 != NULL);
    if XNN_UNPREDICTABLE(i4 != zero) {
      i4 = (const uint8_t*) ((uintptr_t) i4 + input_offset);
    }
    const uint8_t* i5 = input[5];
    assert(i5 != NULL);
    if XNN_UNPREDICTABLE(i5 != zero) {
      i5 = (const uint8_t*) ((uintptr_t) i5 + input_offset);
    }
    const uint8_t* i6 = input[6];
    assert(i6 != NULL);
    if XNN_UNPREDICTABLE(i6 != zero) {
      i6 = (const uint8_t*) ((uintptr_t) i6 + input_offset);
    }
    const uint8_t* i7 = input[7];
    assert(i7 != NULL);
    if XNN_UNPREDICTABLE(i7 != zero) {
      i7 = (const uint8_t*) ((uintptr_t) i7 + input_offset);
    }
    const uint8_t* i8 = input[8];
    assert(i8 != NULL);
    if XNN_UNPREDICTABLE(i8 != zero) {
      i8 = (const uint8_t*) ((uintptr_t) i8 + input_offset);
    }
    input = (const uint8_t**) ((uintptr_t) input + input_stride);

    size_t c = channels;
    const void* w = weights;
    for (; c >= 8; c -= 8) {
      __m256i vacc01234567 = _mm256_loadu_si256((const __m256i*) w);


      const __m256i vi0x01234567 = _mm256_cvtepu8_epi32(_mm_loadl_epi64((const __m128i*) i0));
      const __m256i vk0x01234567 = _mm256_sub_epi32(_mm256_cvtepu8_epi32(_mm_loadl_epi64((const __m128i*) ((uintptr_t) w + 8 * sizeof(int32_t) + 0 * sizeof(uint8_t)))), vk_zero_point);
      i0 += 8;

      vacc01234567 = _mm256_add_epi32(vacc01234567, _mm256_mullo_epi32(vi0x01234567, vk0x01234567));

      const __m256i vi1x01234567 = _mm256_cvtepu8_epi32(_mm_loadl_epi64((const __m128i*) i1));
      const __m256i vk1x01234567 = _mm256_sub_epi32(_mm256_cvtepu8_epi32(_mm_loadl_epi64((const __m128i*) ((uintptr_t) w + 8 * sizeof(int32_t) + 8 * sizeof(uint8_t)))), vk_zero_point);
      i1 += 8;

      vacc01234567 = _mm256_add_epi32(vacc01234567, _mm256_mullo_epi32(vi1x01234567, vk1x01234567));

      const __m256i vi2x01234567 = _mm256_cvtepu8_epi32(_mm_loadl_epi64((const __m128i*) i2));
      const __m256i vk2x01234567 = _mm256_sub_epi32(_mm256_cvtepu8_epi32(_mm_loadl_epi64((const __m128i*) ((uintptr_t) w + 8 * sizeof(int32_t) + 16 * sizeof(uint8_t)))), vk_zero_point);
      i2 += 8;

      vacc01234567 = _mm256_add_epi32(vacc01234567, _mm256_mullo_epi32(vi2x01234567, vk2x01234567));

      const __m256i vi3x01234567 = _mm256_cvtepu8_epi32(_mm_loadl_epi64((const __m128i*) i3));
      const __m256i vk3x01234567 = _mm256_sub_epi32(_mm256_cvtepu8_epi32(_mm_loadl_epi64((const __m128i*) ((uintptr_t) w + 8 * sizeof(int32_t) + 24 * sizeof(uint8_t)))), vk_zero_point);
      i3 += 8;

      vacc01234567 = _mm256_add_epi32(vacc01234567, _mm256_mullo_epi32(vi3x01234567, vk3x01234567));

      const __m256i vi4x01234567 = _mm256_cvtepu8_epi32(_mm_loadl_epi64((const __m128i*) i4));
      const __m256i vk4x01234567 = _mm256_sub_epi32(_mm256_cvtepu8_epi32(_mm_loadl_epi64((const __m128i*) ((uintptr_t) w + 8 * sizeof(int32_t) + 32 * sizeof(uint8_t)))), vk_zero_point);
      i4 += 8;

      vacc01234567 = _mm256_add_epi32(vacc01234567, _mm256_mullo_epi32(vi4x01234567, vk4x01234567));

      const __m256i vi5x01234567 = _mm256_cvtepu8_epi32(_mm_loadl_epi64((const __m128i*) i5));
      const __m256i vk5x01234567 = _mm256_sub_epi32(_mm256_cvtepu8_epi32(_mm_loadl_epi64((const __m128i*) ((uintptr_t) w + 8 * sizeof(int32_t) + 40 * sizeof(uint8_t)))), vk_zero_point);
      i5 += 8;

      vacc01234567 = _mm256_add_epi32(vacc01234567, _mm256_mullo_epi32(vi5x01234567, vk5x01234567));

      const __m256i vi6x01234567 = _mm256_cvtepu8_epi32(_mm_loadl_epi64((const __m128i*) i6));
      const __m256i vk6x01234567 = _mm256_sub_epi32(_mm256_cvtepu8_epi32(_mm_loadl_epi64((const __m128i*) ((uintptr_t) w + 8 * sizeof(int32_t) + 48 * sizeof(uint8_t)))), vk_zero_point);
      i6 += 8;

      vacc01234567 = _mm256_add_epi32(vacc01234567, _mm256_mullo_epi32(vi6x01234567, vk6x01234567));

      const __m256i vi7x01234567 = _mm256_cvtepu8_epi32(_mm_loadl_epi64((const __m128i*) i7));
      const __m256i vk7x01234567 = _mm256_sub_epi32(_mm256_cvtepu8_epi32(_mm_loadl_epi64((const __m128i*) ((uintptr_t) w + 8 * sizeof(int32_t) + 56 * sizeof(uint8_t)))), vk_zero_point);
      i7 += 8;

      vacc01234567 = _mm256_add_epi32(vacc01234567, _mm256_mullo_epi32(vi7x01234567, vk7x01234567));

      const __m256i vi8x01234567 = _mm256_cvtepu8_epi32(_mm_loadl_epi64((const __m128i*) i8));
      const __m256i vk8x01234567 = _mm256_sub_epi32(_mm256_cvtepu8_epi32(_mm_loadl_epi64((const __m128i*) ((uintptr_t) w + 8 * sizeof(int32_t) + 64 * sizeof(uint8_t)))), vk_zero_point);
      i8 += 8;

      vacc01234567 = _mm256_add_epi32(vacc01234567, _mm256_mullo_epi32(vi8x01234567, vk8x01234567));

      w = (const void*) ((uintptr_t) w + 8 * sizeof(int32_t) + 72 * sizeof(uint8_t));

      __m256 vscaled01234567 = _mm256_cvtepi32_ps(vacc01234567);

      const __m256 vscale = _mm256_load_ps(params->fp32_avx2.scale);
      vscaled01234567 = _mm256_mul_ps(vscaled01234567, vscale);

      vacc01234567 = _mm256_cvtps_epi32(vscaled01234567);

      const __m128i voutput_zero_point = _mm_load_si128((const __m128i*) params->fp32_avx2.output_zero_point);
      __m128i vout01234567 = _mm_adds_epi16(_mm_packs_epi32(_mm256_castsi256_si128(vacc01234567), _mm256_extracti128_si256(vacc01234567, 1)), voutput_zero_point);

      __m128i vout0123456701234567 = _mm_packus_epi16(vout01234567, vout01234567);

      const __m128i voutput_min = _mm_load_si128((const __m128i*) params->fp32_avx2.output_min);
      vout0123456701234567 = _mm_max_epu8(vout0123456701234567, voutput_min);

      const __m128i voutput_max = _mm_load_si128((const __m128i*) params->fp32_avx2.output_max);
      vout0123456701234567 = _mm_min_epu8(vout0123456701234567, voutput_max);

      _mm_storel_epi64((__m128i*) output, vout0123456701234567);
      output += 8;
    }
    if XNN_UNLIKELY(c != 0) {
      {
        __m256i vacc01234567 = _mm256_loadu_si256((const __m256i*) w);


        const __m256i vi0x01234567 = _mm256_cvtepu8_epi32(_mm_loadl_epi64((const __m128i*) i0));
        const __m256i vk0x01234567 = _mm256_sub_epi32(_mm256_cvtepu8_epi32(_mm_loadl_epi64((const __m128i*) ((uintptr_t) w + 8 * sizeof(int32_t) + 0 * sizeof(uint8_t)))), vk_zero_point);

        vacc01234567 = _mm256_add_epi32(vacc01234567, _mm256_mullo_epi32(vi0x01234567, vk0x01234567));

        const __m256i vi1x01234567 = _mm256_cvtepu8_epi32(_mm_loadl_epi64((const __m128i*) i1));
        const __m256i vk1x01234567 = _mm256_sub_epi32(_mm256_cvtepu8_epi32(_mm_loadl_epi64((const __m128i*) ((uintptr_t) w + 8 * sizeof(int32_t) + 8 * sizeof(uint8_t)))), vk_zero_point);

        vacc01234567 = _mm256_add_epi32(vacc01234567, _mm256_mullo_epi32(vi1x01234567, vk1x01234567));

        const __m256i vi2x01234567 = _mm256_cvtepu8_epi32(_mm_loadl_epi64((const __m128i*) i2));
        const __m256i vk2x01234567 = _mm256_sub_epi32(_mm256_cvtepu8_epi32(_mm_loadl_epi64((const __m128i*) ((uintptr_t) w + 8 * sizeof(int32_t) + 16 * sizeof(uint8_t)))), vk_zero_point);

        vacc01234567 = _mm256_add_epi32(vacc01234567, _mm256_mullo_epi32(vi2x01234567, vk2x01234567));

        const __m256i vi3x01234567 = _mm256_cvtepu8_epi32(_mm_loadl_epi64((const __m128i*) i3));
        const __m256i vk3x01234567 = _mm256_sub_epi32(_mm256_cvtepu8_epi32(_mm_loadl_epi64((const __m128i*) ((uintptr_t) w + 8 * sizeof(int32_t) + 24 * sizeof(uint8_t)))), vk_zero_point);

        vacc01234567 = _mm256_add_epi32(vacc01234567, _mm256_mullo_epi32(vi3x01234567, vk3x01234567));

        const __m256i vi4x01234567 = _mm256_cvtepu8_epi32(_mm_loadl_epi64((const __m128i*) i4));
        const __m256i vk4x01234567 = _mm256_sub_epi32(_mm256_cvtepu8_epi32(_mm_loadl_epi64((const __m128i*) ((uintptr_t) w + 8 * sizeof(int32_t) + 32 * sizeof(uint8_t)))), vk_zero_point);

        vacc01234567 = _mm256_add_epi32(vacc01234567, _mm256_mullo_epi32(vi4x01234567, vk4x01234567));

        const __m256i vi5x01234567 = _mm256_cvtepu8_epi32(_mm_loadl_epi64((const __m128i*) i5));
        const __m256i vk5x01234567 = _mm256_sub_epi32(_mm256_cvtepu8_epi32(_mm_loadl_epi64((const __m128i*) ((uintptr_t) w + 8 * sizeof(int32_t) + 40 * sizeof(uint8_t)))), vk_zero_point);

        vacc01234567 = _mm256_add_epi32(vacc01234567, _mm256_mullo_epi32(vi5x01234567, vk5x01234567));

        const __m256i vi6x01234567 = _mm256_cvtepu8_epi32(_mm_loadl_epi64((const __m128i*) i6));
        const __m256i vk6x01234567 = _mm256_sub_epi32(_mm256_cvtepu8_epi32(_mm_loadl_epi64((const __m128i*) ((uintptr_t) w + 8 * sizeof(int32_t) + 48 * sizeof(uint8_t)))), vk_zero_point);

        vacc01234567 = _mm256_add_epi32(vacc01234567, _mm256_mullo_epi32(vi6x01234567, vk6x01234567));

        const __m256i vi7x01234567 = _mm256_cvtepu8_epi32(_mm_loadl_epi64((const __m128i*) i7));
        const __m256i vk7x01234567 = _mm256_sub_epi32(_mm256_cvtepu8_epi32(_mm_loadl_epi64((const __m128i*) ((uintptr_t) w + 8 * sizeof(int32_t) + 56 * sizeof(uint8_t)))), vk_zero_point);

        vacc01234567 = _mm256_add_epi32(vacc01234567, _mm256_mullo_epi32(vi7x01234567, vk7x01234567));

        const __m256i vi8x01234567 = _mm256_cvtepu8_epi32(_mm_loadl_epi64((const __m128i*) i8));
        const __m256i vk8x01234567 = _mm256_sub_epi32(_mm256_cvtepu8_epi32(_mm_loadl_epi64((const __m128i*) ((uintptr_t) w + 8 * sizeof(int32_t) + 64 * sizeof(uint8_t)))), vk_zero_point);

        vacc01234567 = _mm256_add_epi32(vacc01234567, _mm256_mullo_epi32(vi8x01234567, vk8x01234567));


        __m256 vscaled01234567 = _mm256_cvtepi32_ps(vacc01234567);
        vscaled01234567 = _mm256_mul_ps(vscaled01234567, _mm256_load_ps(params->fp32_avx2.scale));
        vacc01234567 = _mm256_cvtps_epi32(vscaled01234567);


        const __m128i voutput_zero_point = _mm_load_si128((const __m128i*) params->fp32_avx2.output_zero_point);
        __m128i vout01234567 = _mm_adds_epi16(_mm_packs_epi32(_mm256_castsi256_si128(vacc01234567), _mm256_extracti128_si256(vacc01234567, 1)), voutput_zero_point);

        __m128i vout0123456701234567 = _mm_packus_epi16(vout01234567, vout01234567);

        const __m128i voutput_max = _mm_load_si128((const __m128i*) params->fp32_avx2.output_max);
        vout0123456701234567 = _mm_min_epu8(vout0123456701234567, voutput_max);

        const __m128i voutput_min = _mm_load_si128((const __m128i*) params->fp32_avx2.output_min);
        vout0123456701234567 = _mm_max_epu8(vout0123456701234567, voutput_min);

        if (c & 4) {
          *((uint32_t*) output) = (uint32_t) _mm_cvtsi128_si32(vout0123456701234567);
          vout0123456701234567 = _mm_srli_epi64(vout0123456701234567, 32);
          output += 4;
        }
        if (c & 2) {
          *((uint16_t*) output) = (uint16_t) _mm_extract_epi16(vout0123456701234567, 0);
          vout0123456701234567 = _mm_srli_epi32(vout0123456701234567, 16);
          output += 2;
        }
        if (c & 1) {
          *output = (uint8_t) _mm_extract_epi8(vout0123456701234567, 0);
          output += 1;
        }
      }
    }

    output = (uint8_t*) ((uintptr_t) output + output_increment);
  } while (--output_width != 0);
}