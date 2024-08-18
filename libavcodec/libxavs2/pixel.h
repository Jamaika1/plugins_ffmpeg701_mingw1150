/*
 * pixel.h
 *
 * Description of this file:
 *    Pixel processing functions definition of the xavs2 library
 *
 * --------------------------------------------------------------------------
 *
 *    xavs2 - video encoder of AVS2/IEEE1857.4 video coding standard
 *    Copyright (C) 2018~ VCL, NELVT, Peking University
 *
 *    Authors: Falei LUO <falei.luo@gmail.com>
 *             etc.
 *
 *    Homepage1: http://vcl.idm.pku.edu.cn/xavs2
 *    Homepage2: https://github.com/pkuvcl/xavs2
 *    Homepage3: https://gitee.com/pkuvcl/xavs2
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02111, USA.
 *
 *    This program is also available under a commercial proprietary license.
 *    For more information, contact us at sswang @ pku.edu.cn.
 */

#ifndef XAVS2_PIXEL_H
#define XAVS2_PIXEL_H


/**
 * ===========================================================================
 * type defines
 * ===========================================================================
 */

/* ---------------------------------------------------------------------------
 * Luma PU partition
 */
enum LumaPU {
    /* square (the first 5 PUs match the block sizes) */
    LUMA_4x4,   LUMA_8x8, LUMA_16x16, LUMA_32x32, LUMA_64x64,
    /* rectangular */
    LUMA_8x4,   LUMA_4x8,
    LUMA_16x8,  LUMA_8x16,
    LUMA_32x16, LUMA_16x32,
    LUMA_64x32, LUMA_32x64,
    /* asymmetrical (0.75, 0.25) */
    LUMA_16x12, LUMA_12x16, LUMA_16x4,  LUMA_4x16,
    LUMA_32x24, LUMA_24x32, LUMA_32x8,  LUMA_8x32,
    LUMA_64x48, LUMA_48x64, LUMA_64x16, LUMA_16x64,
    /* number */
    NUM_PU_SIZES,                /* total number of PU sizes */
    LUMA_INVALID = 255
};

/* ---------------------------------------------------------------------------
 * Luma CU sizes, can be indexed using log2n(width)-2
 */
enum LumaCU {
    BLOCK_4x4,
    BLOCK_8x8,
    BLOCK_16x16,
    BLOCK_32x32,
    BLOCK_64x64,
    NUM_CU_SIZES                /* total number of CU sizes */
};

/* ---------------------------------------------------------------------------
 * TU sizes
 */
enum TransUnit {
    /* square */
    TU_4x4, TU_8x8, TU_16x16, TU_32x32, TU_64x64,
    /* asymmetrical */
    TU_16x4,  TU_4x16,
    TU_32x8,  TU_8x32,
    TU_64x16, TU_16x64,
    /* number */
    NUM_TU_SIZES                /* total number of TU sizes */
};

/* ---------------------------------------------------------------------------
 * Chroma (only for 4:2:0) partition sizes.
 * These enum are only a convenience for indexing into the chroma primitive
 * arrays when instantiating macros or templates. The chroma function tables
 * should always be indexed by a LumaPU enum when used.
 */
enum ChromaPU {
    /* square */
    CHROMA_2x2, CHROMA_4x4, CHROMA_8x8, CHROMA_16x16, CHROMA_32x32,
    /* rectangular */
    CHROMA_4x2,   CHROMA_2x4,
    CHROMA_8x4,   CHROMA_4x8,
    CHROMA_16x8,  CHROMA_8x16,
    CHROMA_32x16, CHROMA_16x32,
    /* asymmetrical (0.75, 0.25) */
    CHROMA_8x6,   CHROMA_6x8,   CHROMA_8x2,  CHROMA_2x8,
    CHROMA_16x12, CHROMA_12x16, CHROMA_16x4, CHROMA_4x16,
    CHROMA_32x24, CHROMA_24x32, CHROMA_32x8, CHROMA_8x32,
};

/* ---------------------------------------------------------------------------
 */
enum ChromaCU {
    BLOCK_C_2x2,
    BLOCK_C_4x4,
    BLOCK_C_8x8,
    BLOCK_C_16x16,
    BLOCK_C_32x32
};


typedef cmp_dist_t(*pixel8_cmp_t)(const pel8_t *pix1, intptr_t i_pix1, const pel8_t *pix2, intptr_t i_pix2);
typedef cmp_dist_t(*pixel10_cmp_t)(const pel10_t *pix1, intptr_t i_pix1, const pel10_t *pix2, intptr_t i_pix2);
typedef dist_t(*pixel8_ssd_t)(const pel8_t *pix1, intptr_t i_pix1, const pel8_t *pix2, intptr_t i_pix2);
typedef dist_t(*pixel10_ssd_t)(const pel10_t *pix1, intptr_t i_pix1, const pel10_t *pix2, intptr_t i_pix2);
typedef dist_t(*pixel8_ssd2_t)(const pel8_t *pix1, intptr_t i_pix1, const pel8_t *pix2, intptr_t i_pix2, int width, int height);
typedef dist_t(*pixel10_ssd2_t)(const pel10_t *pix1, intptr_t i_pix1, const pel10_t *pix2, intptr_t i_pix2, int width, int height);
typedef void(*pixel8_cmp_x3_t)(const pel8_t *fenc, const pel8_t *pix0, const pel8_t *pix1, const pel8_t *pix2,                    intptr_t i_stride, int scores[3]);
typedef void(*pixel10_cmp_x3_t)(const pel10_t *fenc, const pel10_t *pix0, const pel10_t *pix1, const pel10_t *pix2,                    intptr_t i_stride, int scores[3]);
typedef void(*pixel8_cmp_x4_t)(const pel8_t *fenc, const pel8_t *pix0, const pel8_t *pix1, const pel8_t *pix2, const pel8_t *pix3, intptr_t i_stride, int scores[4]);
typedef void(*pixel10_cmp_x4_t)(const pel10_t *fenc, const pel10_t *pix0, const pel10_t *pix1, const pel10_t *pix2, const pel10_t *pix3, intptr_t i_stride, int scores[4]);

typedef void(*copy_pp8_t)(pel8_t* dst, intptr_t dstStride, const pel8_t* src, intptr_t srcStride); // dst is aligned
typedef void(*copy_pp10_t)(pel10_t* dst, intptr_t dstStride, const pel10_t* src, intptr_t srcStride); // dst is aligned
typedef void(*copy_sp8_t)(pel8_t* dst, intptr_t dstStride, const coeff_t* src, intptr_t srcStride);
typedef void(*copy_sp10_t)(pel10_t* dst, intptr_t dstStride, const coeff_t* src, intptr_t srcStride);
typedef void(*copy_ps8_t)(coeff_t* dst, intptr_t dstStride, const pel8_t* src, intptr_t srcStride);
typedef void(*copy_ps10_t)(coeff_t* dst, intptr_t dstStride, const pel10_t* src, intptr_t srcStride);
typedef void(*copy_ss8_t)(coeff_t* dst, intptr_t dstStride, const coeff_t* src, intptr_t srcStride);
typedef void(*copy_ss10_t)(coeff_t* dst, intptr_t dstStride, const coeff_t* src, intptr_t srcStride);

typedef void(*pixel_sub_ps8_t)(coeff_t* dst, intptr_t dstride, const pel8_t* src0, const pel8_t* src1, intptr_t sstride0, intptr_t sstride1);
typedef void(*pixel_sub_ps10_t)(coeff_t* dst, intptr_t dstride, const pel10_t* src0, const pel10_t* src1, intptr_t sstride0, intptr_t sstride1);
typedef void(*pixel_add_ps8_t)(xavs2_t *h, pel8_t* a, intptr_t dstride, const pel8_t* b0, const coeff_t* b1, intptr_t sstride0, intptr_t sstride1);
typedef void(*pixel_add_ps10_t)(xavs2_t *h, pel10_t* a, intptr_t dstride, const pel10_t* b0, const coeff_t* b1, intptr_t sstride0, intptr_t sstride1);
typedef void(*pixel_avg_pp8_t)(pel8_t* dst, intptr_t dstride, const pel8_t* src0, intptr_t sstride0, const pel8_t* src1, intptr_t sstride1, int weight);
typedef void(*pixel_avg_pp10_t)(pel10_t* dst, intptr_t dstride, const pel10_t* src0, intptr_t sstride0, const pel10_t* src1, intptr_t sstride1, int weight);

typedef int(*mad_funcs8_t)(pel8_t *p_src, int i_src, int cu_size);
typedef int(*mad_funcs10_t)(pel10_t *p_src, int i_src, int cu_size);

typedef struct {

    pixel8_cmp_t     sad8    [NUM_PU_SIZES];
    pixel10_cmp_t     sad10   [NUM_PU_SIZES];
    pixel8_cmp_t     satd8   [NUM_PU_SIZES];
    pixel10_cmp_t     satd10   [NUM_PU_SIZES];
    pixel8_cmp_t     sa8d8   [NUM_PU_SIZES];
    pixel10_cmp_t     sa8d10   [NUM_PU_SIZES];
    pixel8_ssd_t     ssd8    [NUM_PU_SIZES];
    pixel10_ssd_t     ssd10    [NUM_PU_SIZES];
    pixel8_cmp_x3_t  sad8_x3 [NUM_PU_SIZES];
    pixel10_cmp_x3_t  sad10_x3 [NUM_PU_SIZES];
    pixel8_cmp_x4_t  sad8_x4 [NUM_PU_SIZES];
    pixel10_cmp_x4_t  sad10_x4 [NUM_PU_SIZES];

    pixel_sub_ps8_t  sub_ps8 [NUM_PU_SIZES];
    pixel_sub_ps10_t  sub_ps10 [NUM_PU_SIZES];
    pixel_add_ps8_t  add_ps8 [NUM_PU_SIZES];
    pixel_add_ps10_t  add_ps10 [NUM_PU_SIZES];
    copy_sp8_t       copy_sp8[NUM_PU_SIZES];
    copy_sp10_t       copy_sp10[NUM_PU_SIZES];
    copy_ps8_t       copy_ps8[NUM_PU_SIZES];
    copy_ps10_t       copy_ps10[NUM_PU_SIZES];
    copy_ss8_t       copy_ss8[NUM_PU_SIZES];
    copy_ss10_t       copy_ss10[NUM_PU_SIZES];
    copy_pp8_t       copy_pp8[NUM_PU_SIZES];
    copy_pp10_t       copy_pp10[NUM_PU_SIZES];
    pixel_avg_pp8_t  avg8    [NUM_PU_SIZES];
    pixel_avg_pp10_t  avg10    [NUM_PU_SIZES];

    pixel8_cmp_t    *intra8_cmp;  /* either satd or sad for intra mode prediction */
    pixel10_cmp_t    *intra10_cmp;  /* either satd or sad for intra mode prediction */
    pixel8_cmp_t    *fpel8_cmp;   /* either satd or sad for fractional pixel comparison in ME */
    pixel10_cmp_t    *fpel10_cmp;   /* either satd or sad for fractional pixel comparison in ME */

    mad_funcs8_t     madf8[CTU_DEPTH];
    mad_funcs10_t     madf10[CTU_DEPTH];

    pixel8_ssd2_t    ssd_block8;
    pixel10_ssd2_t    ssd_block10;
    /* block average */
    void (*average8)(pel8_t *dst, int i_dst, pel8_t *src1, int i_src1, pel8_t *src2, int i_src2, int width, int height);
    void (*average10)(pel10_t *dst, int i_dst, pel10_t *src1, int i_src1, pel10_t *src2, int i_src2, int width, int height);
} pixel_funcs_t;


/**
 * ===========================================================================
 * global variables
 * ===========================================================================
 */

/* get partition index for the given size */
#define g_partition_map_tab FPFX(g_partition_map_tab)
extern const uint8_t g_partition_map_tab[];
#define PART_INDEX(w, h)    (g_partition_map_tab[((((w) >> 2) - 1) << 4) + ((h) >> 2) - 1])


/**
 * ===========================================================================
 * function declares
 * ===========================================================================
 */

#define xavs2_pixel_init FPFX(pixel_init)
void xavs2_pixel_init(xavs2_param_t* param, uint32_t cpu, pixel_funcs_t* pixf);

#define xavs2_pixel_ssd8_wxh FPFX(xpixel_ssd8_wxh)
uint64_t xavs2_pixel_ssd8_wxh(pixel_funcs_t *pf,
                             pel8_t *p_pix1, intptr_t i_pix1,
                             pel8_t *p_pix2, intptr_t i_pix2,
                             int i_width, int i_height,
                             int inout_shift);
#define xavs2_pixel_ssd10_wxh FPFX(xpixel_ssd10_wxh)
uint64_t xavs2_pixel_ssd10_wxh(pixel_funcs_t *pf,
                             pel10_t *p_pix1, intptr_t i_pix1,
                             pel10_t *p_pix2, intptr_t i_pix2,
                             int i_width, int i_height,
                             int inout_shift);


#define xavs2_mad8_init FPFX(mad8_init)
void xavs2_mad8_init(uint32_t cpu, mad_funcs8_t *madf8);

#define xavs2_mad10_init FPFX(mad10_init)
void xavs2_mad10_init(uint32_t cpu, mad_funcs10_t *madf10);

#endif  // XAVS2_PIXEL_H
