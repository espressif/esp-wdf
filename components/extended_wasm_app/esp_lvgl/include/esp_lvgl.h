// Copyright 2022 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

#define LV_OBJ_COORDS                     0 /*!< type of set/get lv_obj_t->coords */

#define LV_OBJ_DRAW_PART_DSC_TYPE         0 /*!< type of set/get lv_obj_draw_part_dsc_t->type */
#define LV_OBJ_DRAW_PART_DSC_PART         1 /*!< type of set/get lv_obj_draw_part_dsc_t->part */
#define LV_OBJ_DRAW_PART_DSC_ID           2 /*!< type of set/get lv_obj_draw_part_dsc_t->id */
#define LV_OBJ_DRAW_PART_DSC_TEXT         3 /*!< type of set/get lv_obj_draw_part_dsc_t->text */
#define LV_OBJ_DRAW_PART_DSC_VALUE        4 /*!< type of set/get lv_obj_draw_part_dsc_t->value */
#define LV_OBJ_DRAW_PART_DSC_P1           5 /*!< type of set/get lv_obj_draw_part_dsc_t->p1 */
#define LV_OBJ_DRAW_PART_DSC_P2           6 /*!< type of set/get lv_obj_draw_part_dsc_t->p2 */
#define LV_OBJ_DRAW_PART_DSC_CLIP_AREA    7 /*!< type of set/get lv_obj_draw_part_dsc_t->clip_area */
#define LV_OBJ_DRAW_PART_DSC_DRAW_AREA    8 /*!< type of set/get lv_obj_draw_part_dsc_t->draw_area */
#define LV_OBJ_DRAW_PART_DSC_RECT_DSC     9 /*!< type of set/get lv_obj_draw_part_dsc_t->rect_dsc */
#define LV_OBJ_DRAW_PART_DSC_LINE_DSC     10 /*!< type of set/get lv_obj_draw_part_dsc_t->line_dsc */
#define LV_OBJ_DRAW_PART_DSC_SUB_PART_PTR 11 /*!< type of set/get lv_obj_draw_part_dsc_t->sub_part_ptr */

#define LV_CHART_SERIES_COLOR             0 /*!< type of set/get lv_chart_series_t->color */

#define LV_FONT_LINE_HEIGHT               0 /*!< type of set/get lv_font_t->line_height */

#define LV_FONT_MONTSERRAT_8_FONT 0
#define LV_FONT_MONTSERRAT_10_FONT 1
#define LV_FONT_MONTSERRAT_12_FONT 2
#define LV_FONT_MONTSERRAT_14_FONT 3
#define LV_FONT_MONTSERRAT_16_FONT 4
#define LV_FONT_MONTSERRAT_18_FONT 5
#define LV_FONT_MONTSERRAT_20_FONT 6
#define LV_FONT_MONTSERRAT_22_FONT 7
#define LV_FONT_MONTSERRAT_24_FONT 8
#define LV_FONT_MONTSERRAT_26_FONT 9
#define LV_FONT_MONTSERRAT_28_FONT 10
#define LV_FONT_MONTSERRAT_30_FONT 11
#define LV_FONT_MONTSERRAT_32_FONT 12
#define LV_FONT_MONTSERRAT_34_FONT 13
#define LV_FONT_MONTSERRAT_36_FONT 14
#define LV_FONT_MONTSERRAT_38_FONT 15
#define LV_FONT_MONTSERRAT_40_FONT 16
#define LV_FONT_MONTSERRAT_42_FONT 17
#define LV_FONT_MONTSERRAT_44_FONT 18
#define LV_FONT_MONTSERRAT_46_FONT 19
#define LV_FONT_MONTSERRAT_48_FONT 20
#define LV_FONT_MONTSERRAT_28_COMPRESSED_FONT 21
#define LV_FONT_MONTSERRAT_12_SUBPX_FONT 22
#define LV_FONT_UNSCII_8_FONT 23
#define LV_FONT_UNSCII_16_FONT 24
#define LV_FONT_DEJAVU_16_PERSIAN_HEBREW_FONT 25
#define LV_FONT_SIMSUN_16_CJK_FONT 26

/**
  * @brief  Initialize LVGL library and related hardware.
  *
  * @return 0 if success or a negative value if failed.
  */
int lvgl_init(void);

/**
  * @brief  Lock LVGL, and then users can add or remove LVGL controls.
  */
void lvgl_lock(void);

/**
  * @brief  Unlock LVGL, after users add or remove LVGL controls.
  */
void lvgl_unlock(void);

/**
  * @brief  Set LVGL display monitor callback function, it is equal to "disp->driver->monitor_cb = cb".
  *
  * @param  disp display pointer
  * @param  cb monitor callback function
  */
void lv_disp_set_monitor_cb(lv_disp_t *disp, void *cb);

/**
  * @brief  Get user_data of lv_timer_t.
  *
  * @param  timer LV timer pointer
  *
  * @return user_data of lv_timer_t.
  */
void *lv_timer_get_user_data(lv_timer_t * timer);

/**
  * @brief  Get member value of structure of lv_obj_t.
  *
  * @param  obj LV object pointer
  * @param  type type structure member type
  * @param  pdata dst buffer pointer
  * @param  n buffer size
  *
  * @return 0 if success or a negative value if failed.
  */
int lv_obj_get_data(const lv_obj_t *obj, int type, void *pdata, int n);

/**
  * @brief  Get member value of structure of lv_obj_draw_part_dsc_t.
  *         LV_OBJ_DRAW_PART_DSC_TEXT is not supported.
  *
  * @param  dsc LV object draw part descrption pointer
  * @param  type type structure member type
  * @param  pdata dst buffer pointer
  * @param  n buffer size
  *
  * @return 0 if success or a negative value if failed.
  */
int lv_obj_draw_part_dsc_get_data(const lv_obj_draw_part_dsc_t *dsc, int type, void *pdata, int n);

/**
  * @brief  Set member value of structure of lv_obj_draw_part_dsc_t.
  *         Only LV_OBJ_DRAW_PART_DSC_TEXT is supported.
  *
  * @param  dsc LV object draw part descrption pointer
  * @param  type type structure member type
  * @param  pdata dst buffer pointer
  * @param  n buffer size
  *
  * @return 0 if success or a negative value if failed.
  */
int lv_obj_draw_part_dsc_set_data(lv_obj_draw_part_dsc_t *dsc, int type, const void *pdata, int n);

/**
  * @brief  Get member value of structure of lv_chart_series_t.
  *
  * @param  ser LV chart series pointer
  * @param  type type structure member type
  * @param  pdata dst buffer pointer
  * @param  n buffer size
  *
  * @return 0 if success or a negative value if failed.
  */
int lv_chart_series_get_data(const lv_chart_series_t * ser, int type, void *pdata, int n);

/**
  * @brief  Get font pointer
  *
  * @param  type font type
  *
  * @return font pointer if success or NULL if failed.
  */
const lv_font_t *lv_font_get_font(int type);

/**
  * @brief  Get member value of structure of lv_font_t.
  *
  * @param  font LV font pointer
  * @param  type type structure member type
  * @param  pdata dst buffer pointer
  * @param  n buffer size
  *
  * @return 0 if success or a negative value if failed.
  */
int lv_font_get_data(const lv_font_t * font, int type, void *pdata, int n);

#ifdef __cplusplus
}
#endif
