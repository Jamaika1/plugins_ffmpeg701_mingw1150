/*
 * primitives.h
 *
 * Description of this file:
 *    function handles initialize functions definition of the xavs2 library
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

#ifndef XAVS2_PRIMITIVES_H
#define XAVS2_PRIMITIVES_H

#include "pixel.h"

/**
 * ===========================================================================
 * function definitions and structures
 * ===========================================================================
 */


/**
 * ===========================================================================
 * type defines
 * ===========================================================================
 */

typedef void *(*memcpy_t)(void *dst, const void *src, size_t n);

/* ---------------------------------------------------------------------------
 * inter prediction
 */
typedef void(*block_copy8_t   )(xavs2_t *bb, pel8_t *dst, intptr_t i_dst, pel8_t *src, intptr_t i_src, int w, int h);
typedef void(*block_copy10_t   )(xavs2_t *bb, pel10_t *dst, intptr_t i_dst, pel10_t *src, intptr_t i_src, int w, int h);
typedef void(*plane_copy8_di_t)(xavs2_t *bb, pel8_t *dstu, intptr_t i_dstu, pel8_t *dstv, intptr_t i_dstv, pel8_t *src, intptr_t i_src, int w, int h);
typedef void(*plane_copy10_di_t)(xavs2_t *bb, pel10_t *dstu, intptr_t i_dstu, pel10_t *dstv, intptr_t i_dstv, pel10_t *src, intptr_t i_src, int w, int h);
typedef void(*intpl8_t        )(xavs2_t *h, pel8_t *dst, int i_dst, pel8_t *src, int i_src, int width, int height, const int8_t *coeff);
typedef void(*intpl10_t        )(xavs2_t *h, pel10_t *dst, int i_dst, pel10_t *src, int i_src, int width, int height, const int8_t *coeff);
typedef void(*intpl8_ext_t    )(xavs2_t *h, pel8_t *dst, int i_dst, pel8_t *src, int i_src, int width, int height, const int8_t *coeff_x, const int8_t *coeff_y);
typedef void(*intpl10_ext_t    )(xavs2_t *h, pel10_t *dst, int i_dst, pel10_t *src, int i_src, int width, int height, const int8_t *coeff_x, const int8_t *coeff_y);

typedef void(*intpl_luma8_hor_t)(xavs2_t *h, pel8_t *dst, int i_dst, mct_t *tmp, int i_tmp, pel8_t *src, int i_src, int width, int height, const int8_t *coeff);
typedef void(*intpl_luma10_hor_t)(xavs2_t *h, pel10_t *dst, int i_dst, mct_t *tmp, int i_tmp, pel10_t *src, int i_src, int width, int height, const int8_t *coeff);
typedef void(*intpl_luma8_ext_t)(xavs2_t *h, pel8_t *dst, int i_dst, mct_t *tmp, int i_tmp, int width, int height, const int8_t *coeff);
typedef void(*intpl_luma10_ext_t)(xavs2_t *h, pel10_t *dst, int i_dst, mct_t *tmp, int i_tmp, int width, int height, const int8_t *coeff);
typedef void(*intpl_luma8_ver_t)(xavs2_t *h, pel8_t *dst, int i_dst, pel8_t *src, int i_src, int width, int height, int8_t const *coeff);
typedef void(*intpl_luma10_ver_t)(xavs2_t *h, pel10_t *dst, int i_dst, pel10_t *src, int i_src, int width, int height, int8_t const *coeff);

typedef void(*intpl_luma8_ver_x3_t)(xavs2_t *h, pel8_t *const dst[3], int i_dst, pel8_t *src, int i_src, int width, int height, int8_t const **coeff);
typedef void(*intpl_luma10_ver_x3_t)(xavs2_t *h, pel10_t *const dst[3], int i_dst, pel10_t *src, int i_src, int width, int height, int8_t const **coeff);
typedef void(*intpl_luma8_hor_x3_t)(xavs2_t *h, pel8_t *const dst[3], int i_dst, mct_t *const tmp[3], int i_tmp, pel8_t *src, int i_src, int width, int height, const int8_t **coeff);
typedef void(*intpl_luma10_hor_x3_t)(xavs2_t *h, pel10_t *const dst[3], int i_dst, mct_t *const tmp[3], int i_tmp, pel10_t *src, int i_src, int width, int height, const int8_t **coeff);
typedef void(*intpl_luma8_ext_x3_t)(xavs2_t *h, pel8_t *const dst[3], int i_dst, mct_t *tmp, int i_tmp, int width, int height, const int8_t **coeff);
typedef void(*intpl_luma10_ext_x3_t)(xavs2_t *h, pel10_t *const dst[3], int i_dst, mct_t *tmp, int i_tmp, int width, int height, const int8_t **coeff);

typedef void (*filter_pp8_t)    (const pel8_t   *src, intptr_t srcStride, pel8_t   *dst, intptr_t dstStride, int coeffIdx);
typedef void (*filter_pp10_t)    (const pel10_t   *src, intptr_t srcStride, pel10_t   *dst, intptr_t dstStride, int coeffIdx);
typedef void (*filter_hps8_t)   (const pel8_t   *src, intptr_t srcStride, int16_t *dst, intptr_t dstStride, int coeffIdx, int isRowExt);
typedef void (*filter_hps10_t)   (const pel10_t   *src, intptr_t srcStride, int16_t *dst, intptr_t dstStride, int coeffIdx, int isRowExt);
typedef void (*filter_ps8_t)    (const pel8_t   *src, intptr_t srcStride, int16_t *dst, intptr_t dstStride, int coeffIdx);
typedef void (*filter_ps10_t)    (const pel10_t   *src, intptr_t srcStride, int16_t *dst, intptr_t dstStride, int coeffIdx);
typedef void (*filter_sp8_t)    (const int16_t *src, intptr_t srcStride, pel8_t   *dst, intptr_t dstStride, int coeffIdx);
typedef void (*filter_sp10_t)    (const int16_t *src, intptr_t srcStride, pel10_t   *dst, intptr_t dstStride, int coeffIdx);
typedef void (*filter_ss_t)    (const int16_t *src, intptr_t srcStride, int16_t *dst, intptr_t dstStride, int coeffIdx);
typedef void (*filter_hv_pp8_t) (const pel8_t   *src, intptr_t srcStride, pel8_t   *dst, intptr_t dstStride, int idxX, int idxY);
typedef void (*filter_hv_pp10_t) (const pel10_t   *src, intptr_t srcStride, pel10_t   *dst, intptr_t dstStride, int idxX, int idxY);
typedef void (*filter_p2s8_t)   (const pel8_t   *src, intptr_t srcStride, int16_t *dst, intptr_t dstStride);
typedef void (*filter_p2s10_t)   (const pel10_t   *src, intptr_t srcStride, int16_t *dst, intptr_t dstStride);

/* ---------------------------------------------------------------------------
 * intra prediction
 */
typedef void(*intra8_pred_t)(xavs2_t *h, pel8_t *src, pel8_t *dst, int i_dst, int dir_mode, int bsx, int bsy);
typedef void(*intra10_pred_t)(xavs2_t *h, pel10_t *src, pel10_t *dst, int i_dst, int dir_mode, int bsx, int bsy);
typedef void(*fill_edge8_t) (xavs2_t *h, const pel8_t *p_topleft, int i_topleft, const pel8_t *p_lcu_ep, pel8_t *ep, uint32_t i_avail, int bsx, int bsy);
typedef void(*fill_edge10_t) (xavs2_t *h, const pel10_t *p_topleft, int i_topleft, const pel10_t *p_lcu_ep, pel10_t *ep, uint32_t i_avail, int bsx, int bsy);
typedef void(*fill_ref_samples_t)(xavs2_t *h, cu_t *p_cu, int img_x, int img_y, int block_x, int block_y, int bsx, int bsy);


/* ---------------------------------------------------------------------------
 * transform and quantization functions
 */
typedef void(*dct_t)(xavs2_t *h, const coeff_t *src, coeff_t *dst, int i_src);

/* ---------------------------------------------------------------------------
 * coefficient scan
 */
typedef void(*coeff_scan_t)(coeff_t *dst, const coeff_t *src, int i_src_shift);
typedef void(*coeff_scan4x4_t)(coeff_t *dst, uint64_t r1, uint64_t r2, uint64_t r3, uint64_t r4);


typedef struct {
    /* dct */
    dct_t         dct[NUM_PU_SIZES];
    dct_t        idct[NUM_PU_SIZES];
    dct_t        dct_half[NUM_PU_SIZES];   // 只求解DCT矩阵的低频系数

    /* 2nd transform */
    void(*transform_4x4_2nd)    (xavs2_t *h, coeff_t *coeff, int i_coeff);
    void(*inv_transform_4x4_2nd)(xavs2_t *h, coeff_t *coeff, int i_coeff);
    void(*transform_2nd)        (coeff_t *coeff, int i_coeff, int i_mode, int b_top, int b_left);
    void(*inv_transform_2nd)    (coeff_t *coeff, int i_coeff, int i_mode, int b_top, int b_left);

    /* quant */
    void(*abs_coeff)(coeff_t *coef, const coeff_t *src, const int i_coef);
    int (*add_sign) (coeff_t *coef, const coeff_t *abs_val, const int i_coef);
    int(*quant)   (coeff_t *coef, const int i_coef, const int scale, const int shift, const int add);
    void(*dequant)(coeff_t *coef, const int i_coef, const int scale, const int shift);
    int(*wquant)  (coeff_t *coef, const int i_coef, const int scale, const int shift, const int add, int *levelscale);
} dct_funcs_t;


/* SAO filter function */
typedef void(*sao_flt8_t)(xavs2_t* h,pel8_t *p_dst, int i_dst, pel8_t *p_src, int i_src,
                         int i_block_w, int i_block_h,
                         int *lcu_avail, SAOBlkParam *sao_param);
typedef void(*sao_flt10_t)(xavs2_t* h,pel10_t *p_dst, int i_dst, pel10_t *p_src, int i_src,
                         int i_block_w, int i_block_h,
                         int *lcu_avail, SAOBlkParam *sao_param);

/* ---------------------------------------------------------------------------
 */
typedef struct intrinsic_func_t {
    ALIGN32(uint32_t    cpuid);
    memcpy_t            fast_memcpy;
    memcpy_t            memcpy_aligned;
    void*(*fast_memzero)(void *dst, size_t n);
    void*(*memzero_aligned)(void *dst, size_t n);
    void*(*fast_memset)(void *dst, int val, size_t n);
    void (*mem_repeat_i)(void *dst, int val, size_t count);
    void*(*mem_repeat_p)(void *dst, int val, size_t count);
    void (*lowres_filter8)(xavs2_t *h, pel8_t *src, int i_src, pel8_t *dst, int i_dst, int width, int height);
    void (*lowres_filter10)(xavs2_t *h, pel10_t *src, int i_src, pel10_t *dst, int i_dst, int width, int height);

    pixel_funcs_t       pixf;

    /* ---------------------------------------------------------------------------
     * block copy
     */
    /* align copy */
    block_copy8_t        align_copy8;
    block_copy10_t        align_copy10;

    /* plane copy */
    block_copy8_t        plane_copy8;
    block_copy10_t        plane_copy10;
    plane_copy8_di_t     plane_copy8_deinterleave;
    plane_copy10_di_t     plane_copy10_deinterleave;

    /* ---------------------------------------------------------------------------
     * Motion Compensation
     */
    intpl_luma8_hor_t    intpl_luma8_hor;
    intpl_luma10_hor_t    intpl_luma10_hor;
    intpl_luma8_ver_t    intpl_luma8_ver;
    intpl_luma10_ver_t    intpl_luma10_ver;
    intpl_luma8_ext_t    intpl_luma8_ext;
    intpl_luma10_ext_t    intpl_luma10_ext;

    intpl_luma8_ver_x3_t intpl_luma8_ver_x3;
    intpl_luma10_ver_x3_t intpl_luma10_ver_x3;
    intpl_luma8_hor_x3_t intpl_luma8_hor_x3;
    intpl_luma10_hor_x3_t intpl_luma10_hor_x3;
    intpl_luma8_ext_x3_t intpl_luma8_ext_x3;
    intpl_luma10_ext_x3_t intpl_luma10_ext_x3;

    intpl8_t             intpl_luma8_block_hor;
    intpl10_t             intpl_luma10_block_hor;
    intpl8_t             intpl_luma8_block_ver;
    intpl10_t             intpl_luma10_block_ver;
    intpl8_ext_t         intpl_luma8_block_ext;
    intpl10_ext_t         intpl_luma10_block_ext;

    intpl8_t             intpl_chroma8_block_hor;
    intpl10_t             intpl_chroma10_block_hor;
    intpl8_t             intpl_chroma8_block_ver;
    intpl10_t             intpl_chroma10_block_ver;
    intpl8_ext_t         intpl_chroma8_block_ext;
    intpl10_ext_t         intpl_chroma10_block_ext;

    struct inter_pred8_t {
        filter_pp8_t     luma_hpp8;    // 8-tap luma motion compensation interpolation filters
        filter_hps8_t    luma_hps8;
        filter_pp8_t     luma_vpp8;
        filter_ps8_t     luma_vps8;
        filter_sp8_t     luma_vsp8;
        filter_ss_t     luma_vss8;
        filter_hv_pp8_t  luma_hvpp8;   // combines hps + vsp
    } intpl8[NUM_PU_SIZES];

    struct inter_pred10_t {
        filter_pp10_t     luma_hpp10;    // 8-tap luma motion compensation interpolation filters
        filter_hps10_t    luma_hps10;
        filter_pp10_t     luma_vpp10;
        filter_ps10_t     luma_vps10;
        filter_sp10_t     luma_vsp10;
        filter_ss_t     luma_vss10;
        filter_hv_pp10_t  luma_hvpp10;   // combines hps + vsp
    } intpl10[NUM_PU_SIZES];

    /* ---------------------------------------------------------------------------
     * intra prediction
     */
    intra8_pred_t        intraf8[NUM_INTRA_MODE];
    intra10_pred_t        intraf10[NUM_INTRA_MODE];
    fill_edge8_t         fill_edge8_f[4];   /* 0, x, y, xy */
    fill_edge10_t         fill_edge10_f[4];   /* 0, x, y, xy */
    fill_ref_samples_t  fill_ref_luma[2]; /* 0: CU inside picture; 1: on right/bottom */

    /* ---------------------------------------------------------------------------
     * transform and quantization
     */
    dct_funcs_t     dctf;

    coeff_scan_t    transpose_coeff_scan[NUM_PU_SIZES][2];  /* [TU size][0: no transpose; 1: transpose] */

    coeff_scan4x4_t transpose_coeff_4x4[2];  /* [TU size][0: no transpose; 1: transpose] */

    /* ---------------------------------------------------------------------------
     * In-loop filter
     */
    void(*deblock_luma8[2])(xavs2_t *, pel8_t *, int, int, int, uint8_t*);
    void(*deblock_chroma8[2])(xavs2_t *, pel8_t *, pel8_t *, int, int, int, uint8_t*);
    void(*deblock_luma10[2])(xavs2_t *, pel10_t *, int, int, int, uint8_t*);
    void(*deblock_chroma10[2])(xavs2_t *, pel10_t *, pel10_t *, int, int, int, uint8_t*);

    void(*deblock_luma8_double[2])  (pel8_t *src, int stride, int alpha, int beta, uint8_t *flt_flag);
    void(*deblock_chroma8_double[2])(pel8_t *src_u, pel8_t *src_v, int stride, int alpha, int beta, uint8_t *flt_flag);
    void(*deblock_luma10_double[2])  (pel10_t *src, int stride, int alpha, int beta, uint8_t *flt_flag);
    void(*deblock_chroma10_double[2])(pel10_t *src_u, pel10_t *src_v, int stride, int alpha, int beta, uint8_t *flt_flag);

    sao_flt8_t       sao_block8;          /* filter for SAO */
    sao_flt10_t       sao_block10;          /* filter for SAO */

    /* function handles */
    void(*alf_flt8[2])(xavs2_t *h, pel8_t *p_dst, int i_dst, pel8_t *p_src, int i_src,
                      int lcu_pix_x, int lcu_pix_y, int lcu_width, int lcu_height,
                      int *alf_coeff, int b_top_avail, int b_down_avail);

    void(*alf_flt10[2])(xavs2_t *h, pel10_t *p_dst, int i_dst, pel10_t *p_src, int i_src,
                      int lcu_pix_x, int lcu_pix_y, int lcu_width, int lcu_height,
                      int *alf_coeff, int b_top_avail, int b_down_avail);

    /* -----------------------------------------------------------------------
     * RDO procedure
     */
    int (*get_skip_mv_predictors[SLICE_TYPE_NUM])(xavs2_t *h, cu_t *p_cu);  /* get MVs for skip/direct mode */
    rdcost_t (*compress_ctu[SLICE_TYPE_NUM])(xavs2_t *h, aec_t *p_aec, cu_t *p_cu, int i_level,
            int i_min_level, int i_max_level, rdcost_t cost_limit);
} intrinsic_func_t;

extern intrinsic_func_t g_funcs;

/**
 * ===========================================================================
 * interface function declares
 * ===========================================================================
 */
#define xavs2_mem_oper_init FPFX(mem_oper_init)
void xavs2_mem_oper_init    (xavs2_param_t* param, uint32_t cpuid, intrinsic_func_t *pf);

#define xavs2_mc_init FPFX(mc_init)
void xavs2_mc_init          (xavs2_param_t* param, uint32_t cpuid, intrinsic_func_t *pf);

#define xavs2_intra_pred_init FPFX(intra_pred_init)
void xavs2_intra_pred_init  (xavs2_param_t* param, uint32_t cpuid, intrinsic_func_t *pf);

#define xavs2_dct_init FPFX(dct_init)
void xavs2_dct_init         (uint32_t cpuid, dct_funcs_t *dctf);

#define xavs2_quant_init FPFX(quant_init)
void xavs2_quant_init       (uint32_t cpuid, dct_funcs_t *quantf);

#define xavs2_cg_scan_init FPFX(cg_scan_init)
void xavs2_cg_scan_init     (uint32_t cpuid, intrinsic_func_t *pf);

#define xavs2_deblock_init FPFX(deblock_init)
void xavs2_deblock_init     (xavs2_param_t* param, uint32_t cpuid, intrinsic_func_t* lf);

#define xavs2_sao_init FPFX(sao_init)
void xavs2_sao_init         (xavs2_param_t* param, uint32_t cpuid, intrinsic_func_t *pf);

#define xavs2_alf_init FPFX(alf_init)
void xavs2_alf_init         (xavs2_param_t* param, uint32_t cpuid, intrinsic_func_t *pf);

#define xavs2_rdo_init FPFX(rdo_init)
void xavs2_rdo_init         (uint32_t cpuid, intrinsic_func_t *pf);

#define xavs2_init_all_primitives FPFX(init_all_primitives)
void xavs2_init_all_primitives    (xavs2_param_t* param, intrinsic_func_t *p_funcs);

#endif  // XAVS2_PRIMITIVES_H
