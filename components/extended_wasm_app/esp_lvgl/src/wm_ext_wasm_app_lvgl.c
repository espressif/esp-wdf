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

#include <stdio.h>
#include <stdlib.h>
#include "lvgl.h"
#include "wm_ext_wasm_app_lvgl_func_id.h"

#define LVGL_CALL_FUNC(id, argv) esp_lvgl_call_native_func(id, \
                                                           sizeof(argv) / sizeof(argv[0]), \
                                                           argv)

lv_disp_t *lv_disp_get_next(lv_disp_t *disp)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)disp;
    LVGL_CALL_FUNC(LV_DISP_GET_NEXT, argv);

    return (lv_disp_t *)argv[0];
}

lv_disp_t *lv_disp_get_default(void)
{
    uint32_t argv[1];

    LVGL_CALL_FUNC(LV_DISP_GET_DEFAULT, argv);

    return (lv_disp_t *)argv[0];
}

lv_obj_t *lv_disp_get_scr_act(lv_disp_t *disp)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)disp;
    LVGL_CALL_FUNC(LV_DISP_GET_SCR_ACT, argv);

    return (lv_obj_t *)argv[0];
}

lv_coord_t lv_disp_get_hor_res(lv_disp_t *disp)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)disp;
    LVGL_CALL_FUNC(LV_DISP_GET_HOR_RES, argv);

    return (lv_coord_t)argv[0];
}

lv_coord_t lv_disp_get_ver_res(lv_disp_t *disp)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)disp;
    LVGL_CALL_FUNC(LV_DISP_GET_VER_RES, argv);

    return (lv_coord_t)argv[0];
}

void lv_disp_set_monitor_cb(lv_disp_t *disp, void *cb)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)disp;
    argv[1] = (uint32_t)cb;
    LVGL_CALL_FUNC(LV_DISP_SET_MONITOR_CB, argv);
}

void lv_obj_remove_style(lv_obj_t *obj, lv_style_t *style, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)style;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_REMOVE_STYLE, argv);
}

void lv_obj_set_style_bg_opa(lv_obj_t *obj, lv_opa_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_BG_OPA, argv);
}

void lv_obj_set_pos(lv_obj_t *obj, lv_coord_t x, lv_coord_t y)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)x;
    argv[2] = (uint32_t)y;
    LVGL_CALL_FUNC(LV_OBJ_SET_POS, argv);
}

void lv_obj_align_to(lv_obj_t *obj, const lv_obj_t *base, lv_align_t align, lv_coord_t x_ofs, lv_coord_t y_ofs)
{
    uint32_t argv[5];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)base;
    argv[2] = (uint32_t)align;
    argv[3] = (uint32_t)x_ofs;
    argv[4] = (uint32_t)y_ofs;
    LVGL_CALL_FUNC(LV_OBJ_ALIGN_TO, argv);
}

lv_obj_t *lv_obj_create(lv_obj_t *parent)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)parent;
    LVGL_CALL_FUNC(LV_OBJ_CREATE, argv);

    return (lv_obj_t *)argv[0];
}

lv_coord_t lv_obj_get_width(const lv_obj_t *obj)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)obj;
    LVGL_CALL_FUNC(LV_OBJ_GET_WIDTH, argv);

    return (lv_coord_t)argv[0];
}

lv_coord_t lv_obj_get_height(const lv_obj_t *obj)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)obj;
    LVGL_CALL_FUNC(LV_OBJ_GET_HEIGHT, argv);

    return (lv_coord_t)argv[0];
}

void lv_obj_set_size(lv_obj_t *obj, lv_coord_t w, lv_coord_t h)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)w;
    argv[2] = (uint32_t)h;
    LVGL_CALL_FUNC(LV_OBJ_SET_SIZE, argv);
}

void lv_obj_align(lv_obj_t *obj, lv_align_t align, lv_coord_t x_ofs, lv_coord_t y_ofs)
{
    uint32_t argv[4];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)align;
    argv[2] = (uint32_t)x_ofs;
    argv[3] = (uint32_t)y_ofs;
    LVGL_CALL_FUNC(LV_OBJ_ALIGN, argv);
}

void lv_obj_update_layout(const lv_obj_t *obj)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)obj;
    LVGL_CALL_FUNC(LV_OBJ_UPDATE_LAYOUT, argv);
}

void lv_obj_clean(lv_obj_t *obj)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)obj;
    LVGL_CALL_FUNC(LV_OBJ_CLEAN, argv);
}

void lv_obj_set_flex_flow(lv_obj_t *obj, lv_flex_flow_t flow)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)flow;
    LVGL_CALL_FUNC(LV_OBJ_SET_FLEX_FLOW, argv);
}

lv_coord_t lv_obj_get_content_width(const lv_obj_t *obj)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)obj;
    LVGL_CALL_FUNC(LV_OBJ_GET_CONTENT_WIDTH, argv);

    return (lv_coord_t)argv[0];
}

void lv_obj_set_width(lv_obj_t *obj, lv_coord_t w)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)w;   
    LVGL_CALL_FUNC(LV_OBJ_SET_WIDTH, argv);
}

void lv_obj_set_style_line_color(lv_obj_t *obj, lv_color_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value.full;
    argv[2] = (uint32_t)selector; 
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_LINE_COLOR, argv);
}

void lv_obj_set_style_arc_color(lv_obj_t *obj, lv_color_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value.full;
    argv[2] = (uint32_t)selector; 
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_ARC_COLOR, argv);
}

void lv_obj_set_style_img_recolor(lv_obj_t *obj, lv_color_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value.full;
    argv[2] = (uint32_t)selector; 
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_IMG_RECOLOR, argv);
}

void lv_obj_set_style_text_color(lv_obj_t *obj, lv_color_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value.full;
    argv[2] = (uint32_t)selector; 
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_TEXT_COLOR, argv);
}

void lv_obj_set_x(lv_obj_t *obj, lv_coord_t x)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)x;
    LVGL_CALL_FUNC(LV_OBJ_SET_X, argv);
}

void lv_obj_set_y(lv_obj_t *obj, lv_coord_t y)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)y;
    LVGL_CALL_FUNC(LV_OBJ_SET_Y, argv);
}

void lv_obj_add_style(lv_obj_t *obj, lv_style_t *style, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)style;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_ADD_STYLE, argv);
}

void lv_obj_set_style_bg_color(lv_obj_t *obj, lv_color_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value.full;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_BG_COLOR, argv);
}

void lv_obj_set_style_border_color(lv_obj_t *obj, lv_color_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value.full;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_BORDER_COLOR, argv);
}

void lv_obj_set_style_shadow_color(lv_obj_t *obj, lv_color_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value.full;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_SHADOW_COLOR, argv);
}

lv_obj_t *lv_label_create(lv_obj_t *parent)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)parent;
    LVGL_CALL_FUNC(LV_LABEL_CREATE, argv);

    return (lv_obj_t *)argv[0];
}

void lv_label_set_text(lv_obj_t *obj, const char *txt)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)txt;
    LVGL_CALL_FUNC(LV_LABEL_SET_TEXT, argv);
}

void lv_label_set_text_fmt(lv_obj_t *obj, const char *fmt, ...)
{
    va_list va_arg;
    char *buffer;
    int n = 128;

    va_start(va_arg, fmt);

    while (1) {
        buffer = malloc(n);
        if (!buffer) {
            break;
        }

        int ret = vsnprintf(buffer, n, fmt, va_arg);
        if (ret <= 0) {
            free(buffer);
        } else {
            break;
        }

        n *= 2;
    };

    va_end(va_arg);

    if (buffer) {
        lv_label_set_text(obj, buffer);
        free(buffer);
    }
}

lv_obj_t *lv_table_create(lv_obj_t *parent)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)parent;
    LVGL_CALL_FUNC(LV_TABLE_CREATE, argv);

    return (lv_obj_t *)argv[0];
}

void lv_table_set_col_cnt(lv_obj_t *obj, uint16_t col_cnt) 
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)col_cnt;
    LVGL_CALL_FUNC(LV_TABLE_SET_COL_CNT, argv);
}

void lv_table_set_col_width(lv_obj_t *obj, uint16_t col_id, lv_coord_t w) 
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)col_id;
    argv[2] = (uint32_t)w;
    LVGL_CALL_FUNC(LV_TABLE_SET_COL_WIDTH, argv);
}

void lv_table_add_cell_ctrl(lv_obj_t *obj, uint16_t row, uint16_t col, lv_table_cell_ctrl_t ctrl)
{
    uint32_t argv[4];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)row;
    argv[2] = (uint32_t)col;
    argv[3] = (uint32_t)ctrl;
    LVGL_CALL_FUNC(LV_TABLE_ADD_CELL_CTRL, argv);
}

void lv_table_set_cell_value(lv_obj_t *obj, uint16_t row, uint16_t col, const char *txt)
{
    uint32_t argv[4];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)row;
    argv[2] = (uint32_t)col;
    argv[3] = (uint32_t)txt;
    LVGL_CALL_FUNC(LV_TABLE_SET_CELL_VALUE, argv);
}

lv_timer_t *lv_timer_create(lv_timer_cb_t timer_xcb, uint32_t period, void *user_data)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)timer_xcb;
    argv[1] = (uint32_t)period;
    argv[2] = (uint32_t)user_data;
    LVGL_CALL_FUNC(LV_TIMER_CREATE, argv);

    return (lv_timer_t *)argv[0];   
}

void lv_timer_set_repeat_count(lv_timer_t *timer, int32_t repeat_count)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)timer;
    argv[1] = (uint32_t)repeat_count;
    LVGL_CALL_FUNC(LV_TIMER_SET_REPEAT_COUNT, argv);
}

void lv_style_init(lv_style_t * style)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)style;
    LVGL_CALL_FUNC(LV_STYLE_INIT, argv);
}

void lv_style_reset(lv_style_t *style)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)style;
    LVGL_CALL_FUNC(LV_STYLE_RESET, argv);
}

void lv_style_set_bg_opa(lv_style_t * style, lv_opa_t value)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)style;
    argv[1] = (uint32_t)value;
    LVGL_CALL_FUNC(LV_STYLE_SET_BG_OPA, argv);
}

void lv_style_set_radius(lv_style_t * style, lv_coord_t value)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)style;
    argv[1] = (uint32_t)value;
    LVGL_CALL_FUNC(LV_STYLE_SET_RADIUS, argv);
}

void lv_style_set_border_width(lv_style_t * style, lv_coord_t value)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)style;
    argv[1] = (uint32_t)value;
    LVGL_CALL_FUNC(LV_STYLE_SET_BORDER_WIDTH, argv);
}

void lv_style_set_border_opa(lv_style_t * style, lv_opa_t value)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)style;
    argv[1] = (uint32_t)value;
    LVGL_CALL_FUNC(LV_STYLE_SET_BORDER_OPA, argv);
}

void lv_style_set_border_side(lv_style_t * style, lv_border_side_t value)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)style;
    argv[1] = (uint32_t)value;
    LVGL_CALL_FUNC(LV_STYLE_SET_BORDER_SIDE, argv);
}

void lv_style_set_shadow_opa(lv_style_t * style, lv_opa_t value)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)style;
    argv[1] = (uint32_t)value;
    LVGL_CALL_FUNC(LV_STYLE_SET_SHADOW_OPA, argv);
}

void lv_style_set_shadow_width(lv_style_t * style, lv_coord_t value)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)style;
    argv[1] = (uint32_t)value;
    LVGL_CALL_FUNC(LV_STYLE_SET_SHADOW_WIDTH, argv);
}

void lv_style_set_shadow_ofs_x(lv_style_t * style, lv_coord_t value)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)style;
    argv[1] = (uint32_t)value;
    LVGL_CALL_FUNC(LV_STYLE_SET_SHADOW_OFS_X, argv);
}

void lv_style_set_shadow_ofs_y(lv_style_t * style, lv_coord_t value)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)style;
    argv[1] = (uint32_t)value;
    LVGL_CALL_FUNC(LV_STYLE_SET_SHADOW_OFS_Y, argv);
}

void lv_style_set_shadow_spread(lv_style_t * style, lv_coord_t value)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)style;
    argv[1] = (uint32_t)value;
    LVGL_CALL_FUNC(LV_STYLE_SET_SHADOW_SPREAD, argv);
}

void lv_style_set_img_opa(lv_style_t * style, lv_opa_t value)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)style;
    argv[1] = (uint32_t)value;
    LVGL_CALL_FUNC(LV_STYLE_SET_IMG_OPA, argv);
}

void lv_style_set_img_recolor_opa(lv_style_t * style, lv_opa_t value)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)style;
    argv[1] = (uint32_t)value;
    LVGL_CALL_FUNC(LV_STYLE_SET_IMG_RECOLOR_OPA, argv);
}

void lv_style_set_text_font(lv_style_t * style, const lv_font_t * value)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)style;
    argv[1] = (uint32_t)value;
    LVGL_CALL_FUNC(LV_STYLE_SET_TEXT_FONT, argv);
}

void lv_style_set_text_opa(lv_style_t * style, lv_opa_t value)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)style;
    argv[1] = (uint32_t)value;
    LVGL_CALL_FUNC(LV_STYLE_SET_TEXT_OPA, argv);
}

void lv_style_set_line_width(lv_style_t * style, lv_coord_t value)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)style;
    argv[1] = (uint32_t)value;
    LVGL_CALL_FUNC(LV_STYLE_SET_LINE_WIDTH, argv);
}

void lv_style_set_line_opa(lv_style_t * style, lv_opa_t value)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)style;
    argv[1] = (uint32_t)value;
    LVGL_CALL_FUNC(LV_STYLE_SET_LINE_OPA, argv);
}

void lv_style_set_arc_width(lv_style_t * style, lv_coord_t value)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)style;
    argv[1] = (uint32_t)value;
    LVGL_CALL_FUNC(LV_STYLE_SET_ARC_WIDTH, argv);
}

void lv_style_set_arc_opa(lv_style_t * style, lv_opa_t value)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)style;
    argv[1] = (uint32_t)value;
    LVGL_CALL_FUNC(LV_STYLE_SET_ARC_OPA, argv);
}

void lv_style_set_blend_mode(lv_style_t * style, lv_blend_mode_t value)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)style;
    argv[1] = (uint32_t)value;
    LVGL_CALL_FUNC(LV_STYLE_SET_BLEND_MODE, argv);
}

void lv_style_set_text_color(lv_style_t * style, lv_color_t value)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)style;
    argv[1] = (uint32_t)value.full;
    LVGL_CALL_FUNC(LV_STYLE_SET_TEXT_COLOR, argv);
}

lv_obj_t *lv_line_create(lv_obj_t * parent)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)parent;
    LVGL_CALL_FUNC(LV_LINE_CREATE, argv);

    return (lv_obj_t *)argv[0];
}

void lv_line_set_points(lv_obj_t * obj, const lv_point_t points[], uint16_t point_num)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)points;
    argv[2] = (uint32_t)point_num;
    LVGL_CALL_FUNC(LV_LINE_SET_POINTS, argv);
}

lv_obj_t * lv_arc_create(lv_obj_t * parent)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)parent;
    LVGL_CALL_FUNC(LV_ARC_CREATE, argv);

    return (lv_obj_t *)argv[0];
}

void lv_arc_set_start_angle(lv_obj_t * arc, uint16_t start)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)arc;
    argv[1] = (uint32_t)start;
    LVGL_CALL_FUNC(LV_ARC_SET_START_ANGLE, argv);
}

void lv_arc_set_end_angle(lv_obj_t * arc, uint16_t end)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)arc;
    argv[1] = (uint32_t)end;
    LVGL_CALL_FUNC(LV_ARC_SET_END_ANGLE, argv);
}

lv_obj_t * lv_img_create(lv_obj_t * parent)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)parent;
    LVGL_CALL_FUNC(LV_IMG_CREATE, argv);

    return (lv_obj_t *)argv[0];
}

void lv_img_set_src(lv_obj_t * obj, const void * src)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)src;
    LVGL_CALL_FUNC(LV_IMG_SET_SRC, argv);
}

void lv_img_set_angle(lv_obj_t * obj, int16_t angle)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)angle;
    LVGL_CALL_FUNC(LV_IMG_SET_ANGLE, argv);
}

void lv_img_set_zoom(lv_obj_t * obj, uint16_t zoom)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)zoom;
    LVGL_CALL_FUNC(LV_IMG_SET_ZOOM, argv);
}

void lv_img_set_antialias(lv_obj_t * obj, bool antialias)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)antialias;
    LVGL_CALL_FUNC(LV_IMG_SET_ANTIALIAS, argv);
}

void lv_anim_init(lv_anim_t * a)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)a;
    LVGL_CALL_FUNC(LV_ANIM_INIT, argv);
}

lv_anim_t * lv_anim_start(const lv_anim_t * a)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)a;
    LVGL_CALL_FUNC(LV_ANIM_START, argv);

    return (lv_anim_t *)argv[0];
}

const lv_font_t * lv_theme_get_font_small(lv_obj_t * obj)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)obj;
    LVGL_CALL_FUNC(LV_THEME_GET_FONT_SMALL, argv);

    return (const lv_font_t *)argv[0];
}

const lv_font_t * lv_theme_get_font_normal(lv_obj_t * obj)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)obj;
    LVGL_CALL_FUNC(LV_THEME_GET_FONT_NORMAL, argv);

    return (const lv_font_t *)argv[0];
}

const lv_font_t * lv_theme_get_font_large(lv_obj_t * obj)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)obj;
    LVGL_CALL_FUNC(LV_THEME_GET_FONT_LARGE, argv);

    return (const lv_font_t *)argv[0];
}

lv_theme_t * lv_theme_default_init(lv_disp_t * disp, lv_color_t color_primary, lv_color_t color_secondary, bool dark,
                                   const lv_font_t * font)
{
    uint32_t argv[5];

    argv[0] = (uint32_t)disp;
    argv[1] = (uint32_t)color_primary.full;
    argv[2] = (uint32_t)color_secondary.full;
    argv[3] = (uint32_t)dark;
    argv[4] = (uint32_t)font;
    LVGL_CALL_FUNC(LV_THEME_DEFAULT_INIT, argv);

    return (lv_theme_t *)argv[0];
}

lv_color_t lv_theme_get_color_primary(lv_obj_t * obj)
{
    uint32_t argv[1];
    lv_color_t color;

    argv[0] = (uint32_t)obj;
    LVGL_CALL_FUNC(KV_THEME_GET_COLOR_PRIMARY, argv);

    color.full = (uint32_t)argv[0];

    return color;
}

const uint8_t * lv_font_get_bitmap_fmt_txt(const lv_font_t * font, uint32_t letter)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)font;
    argv[1] = (uint32_t)letter;
    LVGL_CALL_FUNC(LV_FONT_GET_BITMAP_FMT_TXT, argv);

    return (const uint8_t *)argv[0];
}

bool lv_font_get_glyph_dsc_fmt_txt(const lv_font_t * font, lv_font_glyph_dsc_t * dsc_out, uint32_t unicode_letter,
                                   uint32_t unicode_letter_next)
{
    uint32_t argv[4];

    argv[0] = (uint32_t)font;
    argv[1] = (uint32_t)dsc_out;
    argv[2] = unicode_letter;
    argv[3] = unicode_letter_next;
    LVGL_CALL_FUNC(LV_FONT_GET_GLYPH_DSC_FMT_TXT, argv);

    return (bool)argv[0];
}

lv_color_t lv_palette_main(lv_palette_t p)
{
    uint32_t argv[1];
    lv_color_t color;

    argv[0] = (uint32_t)p;
    LVGL_CALL_FUNC(LV_PALETTE_MAIN, argv);

    color.full = (uint32_t)argv[0];

    return color;
}

lv_obj_t * lv_tabview_create(lv_obj_t * parent, lv_dir_t tab_pos, lv_coord_t tab_size)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)parent;
    argv[1] = (uint32_t)tab_pos;
    argv[2] = (uint32_t)tab_size;
    LVGL_CALL_FUNC(LV_TABVIEW_MAIN, argv);

    return (lv_obj_t *)argv[0];
}

void lv_obj_set_style_text_font(lv_obj_t * obj, const lv_font_t * value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_TEXT_FONT, argv);
}

lv_obj_t * lv_tabview_get_tab_btns(lv_obj_t * tv)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)tv;
    LVGL_CALL_FUNC(LV_TABVIEW_GET_TAB_BTNS, argv);

    return (lv_obj_t *)argv[0];
}

void lv_obj_set_style_pad_left(lv_obj_t * obj, lv_coord_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_PAD_LEFT, argv);   
}

lv_obj_t * lv_tabview_add_tab(lv_obj_t * tv, const char * name)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)tv;
    argv[1] = (uint32_t)name;
    LVGL_CALL_FUNC(LV_TABVIEW_ADD_TAB, argv);

    return (lv_obj_t *)argv[0];
}

void lv_obj_set_height(lv_obj_t * obj, lv_coord_t h)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)h;
    LVGL_CALL_FUNC(LV_OBJ_SET_HEIGHT, argv);
}

void lv_label_set_long_mode(lv_obj_t * obj, lv_label_long_mode_t long_mode)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)long_mode;
    LVGL_CALL_FUNC(LV_LABEL_SET_LONG_MODE, argv);
}

lv_obj_t * lv_btn_create(lv_obj_t * parent)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)parent;
    LVGL_CALL_FUNC(LV_BTN_CREATE, argv);

    return (lv_obj_t *)argv[0];
}

void lv_obj_add_state(lv_obj_t * obj, lv_state_t state)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)state;
    LVGL_CALL_FUNC(LV_OBJ_ADD_STATE, argv);
}

lv_obj_t * lv_keyboard_create(lv_obj_t * parent)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)parent;
    LVGL_CALL_FUNC(LV_KEYBOARD_CREATE, argv);

    return (lv_obj_t *)argv[0];
}

void lv_obj_add_flag(lv_obj_t * obj, lv_obj_flag_t f)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)f;
    LVGL_CALL_FUNC(LV_OBJ_ADD_FLAG, argv);
}

lv_obj_t * lv_textarea_create(lv_obj_t * parent)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)parent;
    LVGL_CALL_FUNC(LV_TEXTAREA_CREATE, argv);

    return (lv_obj_t *)argv[0];
}

void lv_textarea_set_one_line(lv_obj_t * obj, bool en)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)en;
    LVGL_CALL_FUNC(LV_TEXTAREA_SET_ONE_LINE, argv);
}

void lv_textarea_set_placeholder_text(lv_obj_t * obj, const char * txt)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)txt;
    LVGL_CALL_FUNC(LV_TEXTAREA_SET_PLACEHOLDER_TEXT, argv);
}

struct _lv_event_dsc_t * lv_obj_add_event_cb(lv_obj_t * obj, lv_event_cb_t event_cb, lv_event_code_t filter,
                                             void * user_data)
{
    uint32_t argv[4];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)event_cb;
    argv[2] = (uint32_t)filter;
    argv[3] = (uint32_t)user_data;
    LVGL_CALL_FUNC(LV_OBJ_ADD_EVENT_CB, argv);

    return (struct _lv_event_dsc_t *)argv[0];
}

void lv_textarea_set_password_mode(lv_obj_t * obj, bool en)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)en;
    LVGL_CALL_FUNC(LV_TEXTAREA_SET_PASSWORD_MODE, argv);
}

lv_obj_t * lv_dropdown_create(lv_obj_t * parent)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)parent;
    LVGL_CALL_FUNC(LV_DROPDOWN_CREATE, argv);

    return (lv_obj_t *)argv[0];
}

void lv_dropdown_set_options_static(lv_obj_t * obj, const char * options)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)options;
    LVGL_CALL_FUNC(LV_DROPDOWN_SET_OPTIONS_STATIC, argv);
}

lv_obj_t * lv_slider_create(lv_obj_t * parent)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)parent;
    LVGL_CALL_FUNC(LV_SLIDER_CREATE, argv);

    return (lv_obj_t *)argv[0];
}

void lv_obj_refresh_ext_draw_size(lv_obj_t * obj)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)obj;
    LVGL_CALL_FUNC(LV_OBJ_REFRESH_EXT_DRAW_SIZE, argv);  
}

lv_obj_t * lv_switch_create(lv_obj_t * parent)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)parent;
    LVGL_CALL_FUNC(LV_SWITCH_CREATE, argv);

    return (lv_obj_t *)argv[0]; 
}

void lv_obj_set_grid_dsc_array(lv_obj_t * obj, const lv_coord_t col_dsc[], const lv_coord_t row_dsc[])
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)col_dsc;
    argv[2] = (uint32_t)row_dsc;
    LVGL_CALL_FUNC(LV_OBJ_SET_GRID_DSC_ARRAY, argv);
}

void lv_obj_set_grid_cell(lv_obj_t * obj, lv_grid_align_t column_align, uint8_t col_pos, uint8_t col_span,
                          lv_grid_align_t row_align, uint8_t row_pos, uint8_t row_span)
{
    uint32_t argv[7];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)column_align;
    argv[2] = (uint32_t)col_pos;
    argv[3] = (uint32_t)col_span;
    argv[4] = (uint32_t)row_align;
    argv[5] = (uint32_t)row_pos;
    argv[6] = (uint32_t)row_span;
    LVGL_CALL_FUNC(LV_OBJ_SET_GRID_CELL, argv);  
}

void lv_obj_set_style_text_align(lv_obj_t * obj, lv_text_align_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_TEXT_ALIGN, argv);
}

void lv_obj_set_flex_grow(lv_obj_t * obj, uint8_t grow)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)grow;
    LVGL_CALL_FUNC(LV_OBJ_SET_FLEX_GROW, argv);  
}

void lv_obj_set_style_max_height(lv_obj_t * obj, lv_coord_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_MAX_HEIGHT, argv);
}

lv_obj_t * lv_chart_create(lv_obj_t * parent)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)parent;
    LVGL_CALL_FUNC(LV_CHART_CREATE, argv);

    return (lv_obj_t *)argv[0];
}

lv_group_t * lv_group_get_default(void)
{
    uint32_t argv[1];

    argv[0] = 0;
    LVGL_CALL_FUNC(LV_GROUP_GET_DEFAULT, argv);

    return (lv_group_t *)argv[0];
}

void lv_group_add_obj(lv_group_t * group, lv_obj_t * obj)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)group;
    argv[1] = (uint32_t)obj;
    LVGL_CALL_FUNC(LV_GROUP_ADD_OBJ, argv); 
}

void lv_chart_set_axis_tick(lv_obj_t * obj, lv_chart_axis_t axis, lv_coord_t major_len, lv_coord_t minor_len,
                            lv_coord_t major_cnt, lv_coord_t minor_cnt, bool label_en, lv_coord_t draw_size)
{
    uint32_t argv[8];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)axis;
    argv[2] = (uint32_t)major_len;
    argv[3] = (uint32_t)minor_len;
    argv[4] = (uint32_t)major_cnt;
    argv[5] = (uint32_t)minor_cnt;
    argv[6] = (uint32_t)label_en;
    argv[7] = (uint32_t)draw_size;
    LVGL_CALL_FUNC(LV_CHART_SET_AXIS_TICK, argv);     
}

void lv_chart_set_div_line_count(lv_obj_t * obj, uint8_t hdiv, uint8_t vdiv)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)hdiv;
    argv[2] = (uint32_t)vdiv;
    LVGL_CALL_FUNC(LV_CHART_SET_DIV_LINE_COUNT, argv);
}

void lv_chart_set_point_count(lv_obj_t * obj, uint16_t cnt)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)cnt;
    LVGL_CALL_FUNC(LV_CHART_SET_POINT_COUNT, argv); 
}

void lv_chart_set_zoom_x(lv_obj_t * obj, uint16_t zoom_x)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)zoom_x;
    LVGL_CALL_FUNC(LV_CHART_SET_ZOOM_X, argv); 
}

void lv_obj_set_style_border_side(lv_obj_t * obj, lv_border_side_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_BORDER_SIDE, argv); 
}

void lv_obj_set_style_radius(lv_obj_t * obj, lv_coord_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_RADIUS, argv); 
}

lv_chart_series_t * lv_chart_add_series(lv_obj_t * obj, lv_color_t color, lv_chart_axis_t axis)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)color.full;
    argv[2] = (uint32_t)axis;
    LVGL_CALL_FUNC(LV_CHART_ADD_SERIES, argv);

    return (lv_chart_series_t *)argv[0];
}

uint32_t lv_rand(uint32_t min, uint32_t max)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)min;
    argv[1] = (uint32_t)max;
    LVGL_CALL_FUNC(LV_RAND, argv);

    return argv[0];
}

void lv_chart_set_next_value(lv_obj_t * obj, lv_chart_series_t * ser, lv_coord_t value)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)ser;
    argv[2] = (uint32_t)value;
    LVGL_CALL_FUNC(LV_CHART_SET_NEXT_VALUE, argv); 
}

void lv_chart_set_type(lv_obj_t * obj, lv_chart_type_t type)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)type;
    LVGL_CALL_FUNC(LV_CHART_SET_TYPE, argv); 
}

void lv_obj_set_style_pad_row(lv_obj_t * obj, lv_coord_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_PAD_ROW, argv); 
}

void lv_obj_set_style_pad_column(lv_obj_t * obj, lv_coord_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_PAD_COLUMN, argv); 
}

lv_color_t lv_palette_lighten(lv_palette_t p, uint8_t lvl)
{
    uint32_t argv[2];
    lv_color_t color;

    argv[0] = (uint32_t)p;
    argv[1] = (uint32_t)lvl;
    LVGL_CALL_FUNC(LV_PALETTE_LIGHTEN, argv);

    color.full = (uint32_t)argv[0];

    return color;
}

lv_obj_t * lv_obj_get_parent(const lv_obj_t *obj)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)obj;
    LVGL_CALL_FUNC(LV_OBJ_GET_PARENT, argv);

    return (lv_obj_t *)argv[0];
}

lv_meter_scale_t * lv_meter_add_scale(lv_obj_t * obj)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)obj;
    LVGL_CALL_FUNC(LV_METER_ADD_SCALE, argv);

    return (lv_meter_scale_t *)argv[0];
}

void lv_meter_set_scale_range(lv_obj_t * obj, lv_meter_scale_t * scale, int32_t min, int32_t max, uint32_t angle_range,
                              uint32_t rotation)
{
    uint32_t argv[6];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)scale;
    argv[2] = (uint32_t)min;
    argv[3] = (uint32_t)max;
    argv[4] = (uint32_t)angle_range;
    argv[5] = (uint32_t)rotation;
    LVGL_CALL_FUNC(LV_METER_SET_SCALE_RANGE, argv);
}

void lv_meter_set_scale_ticks(lv_obj_t * obj, lv_meter_scale_t * scale, uint16_t cnt, uint16_t width, uint16_t len,
                              lv_color_t color)
{
    uint32_t argv[6];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)scale;
    argv[2] = (uint32_t)cnt;
    argv[3] = (uint32_t)width;
    argv[4] = (uint32_t)len;
    argv[5] = (uint32_t)color.full;
    LVGL_CALL_FUNC(LV_METER_SET_SCALE_TICKS, argv);
}

lv_meter_indicator_t * lv_meter_add_arc(lv_obj_t * obj, lv_meter_scale_t * scale, uint16_t width, lv_color_t color,
                                        int16_t r_mod)
{
    uint32_t argv[5];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)scale;
    argv[2] = (uint32_t)width;
    argv[3] = (uint32_t)color.full;
    argv[4] = (uint32_t)r_mod;
    LVGL_CALL_FUNC(LV_METER_ADD_ARC, argv);

    return (lv_meter_indicator_t *)argv[0];
}

void lv_meter_set_indicator_start_value(lv_obj_t * obj, lv_meter_indicator_t * indic, int32_t value)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)indic;
    argv[2] = (uint32_t)value;
    LVGL_CALL_FUNC(LV_METER_SET_INDICATOR_START_VALUE, argv);
}

void lv_meter_set_indicator_end_value(lv_obj_t * obj, lv_meter_indicator_t * indic, int32_t value)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)indic;
    argv[2] = (uint32_t)value;
    LVGL_CALL_FUNC(LV_METER_SET_INDICATOR_END_VALUE, argv);
}

void lv_obj_set_style_pad_right(lv_obj_t * obj, lv_coord_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_PAD_RIGHT, argv);
}

void lv_obj_set_style_width(lv_obj_t * obj, lv_coord_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_WIDTH, argv);
}

void lv_obj_set_style_height(lv_obj_t * obj, lv_coord_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_HEIGHT, argv);
}

lv_color_t lv_palette_darken(lv_palette_t p, uint8_t lvl)
{
    uint32_t argv[2];
    lv_color_t color;

    argv[0] = (uint32_t)p;
    argv[1] = (uint32_t)lvl;
    LVGL_CALL_FUNC(LV_PALETTE_DARKEN, argv);
    color.full = (uint32_t)argv[0];

    return color;
}

void lv_obj_set_style_outline_color(lv_obj_t * obj, lv_color_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value.full;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_OUTLINE_COLOR, argv);
}

void lv_obj_set_style_outline_width(lv_obj_t * obj, lv_coord_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_OUTLINE_WIDTH, argv);
}

void lv_meter_set_scale_major_ticks(lv_obj_t * obj, lv_meter_scale_t * scale, uint16_t nth, uint16_t width,
                                    uint16_t len, lv_color_t color, int16_t label_gap)
{
    uint32_t argv[7];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)scale;
    argv[2] = (uint32_t)nth;
    argv[3] = (uint32_t)width;
    argv[4] = (uint32_t)len;
    argv[5] = (uint32_t)color.full;
    argv[6] = (uint32_t)label_gap;
    LVGL_CALL_FUNC(LV_METER_SET_SCALE_MAJOR_TICKS, argv);
}

lv_meter_indicator_t * lv_meter_add_scale_lines(lv_obj_t * obj, lv_meter_scale_t * scale, lv_color_t color_start,
                                                lv_color_t color_end, bool local, int16_t width_mod)
{
    uint32_t argv[6];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)scale;
    argv[2] = (uint32_t)color_start.full;
    argv[3] = (uint32_t)color_end.full;
    argv[4] = (uint32_t)local;
    argv[5] = (uint32_t)width_mod;
    LVGL_CALL_FUNC(LV_METER_ADD_SCALE_LINES, argv);

    return (lv_meter_indicator_t *)argv[0];
}

void lv_obj_set_style_pad_bottom(lv_obj_t * obj, lv_coord_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_PAD_BOTTOM, argv);
}

lv_coord_t lv_disp_get_dpi(const lv_disp_t * disp)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)disp;
    LVGL_CALL_FUNC(LV_DISP_GET_DPI, argv);

    return (lv_coord_t)argv[0];
}

lv_obj_t * lv_checkbox_create(lv_obj_t * parent)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)parent;
    LVGL_CALL_FUNC(LV_CHECKBOX_CREATE, argv);

    return (lv_obj_t *)argv[0];
}

void lv_checkbox_set_text(lv_obj_t * obj, const char * txt)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)txt;
    LVGL_CALL_FUNC(LV_CHECKBOX_SET_TEXT, argv);
}

void lv_obj_set_flex_align(lv_obj_t * obj, lv_flex_align_t main_place, lv_flex_align_t cross_place,
                           lv_flex_align_t track_cross_place)
{
    uint32_t argv[4];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)main_place;
    argv[2] = (uint32_t)cross_place;
    argv[3] = (uint32_t)track_cross_place;
    LVGL_CALL_FUNC(LV_OBJ_SET_FLEX_ALIGN, argv);
}

void lv_obj_set_style_opa(lv_obj_t * obj, lv_opa_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_OPA, argv);
}

void lv_obj_clear_flag(lv_obj_t * obj, lv_obj_flag_t f)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)f;
    LVGL_CALL_FUNC(LV_OBJ_CLEAR_FLAG, argv);
}

void lv_obj_set_style_pad_top(lv_obj_t * obj, lv_coord_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_PAD_TOP, argv);
}

void lv_obj_set_style_shadow_width(lv_obj_t * obj, lv_coord_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_SHADOW_WIDTH, argv);
}

void lv_obj_set_style_bg_img_src(lv_obj_t * obj, const void * value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_BG_IMG_SRC, argv);
}

lv_event_code_t lv_event_get_code(lv_event_t * e)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)e;
    LVGL_CALL_FUNC(LV_EVENT_GET_CODE, argv);

    return (lv_event_code_t)argv[0];
}

lv_obj_t * lv_event_get_target(lv_event_t * e)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)e;
    LVGL_CALL_FUNC(LV_EVENT_GET_TARGET, argv);

    return (lv_obj_t *)argv[0];
}

void * lv_event_get_user_data(lv_event_t * e)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)e;
    LVGL_CALL_FUNC(LV_EVENT_GET_USER_DATA, argv);

    return (void *)argv[0];
}

lv_indev_t * lv_indev_get_act(void)
{
    uint32_t argv[1];

    argv[0] = 0;
    LVGL_CALL_FUNC(LV_INDEV_GET_ACT, argv);

    return (lv_indev_t *)argv[0];
}

lv_indev_type_t lv_indev_get_type(const lv_indev_t * indev)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)indev;
    LVGL_CALL_FUNC(LV_INDEV_GET_TYPE, argv);

    return (lv_indev_type_t)argv[0];
}

void lv_keyboard_set_textarea(lv_obj_t * kb, lv_obj_t * ta)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)kb;
    argv[1] = (uint32_t)ta;
    LVGL_CALL_FUNC(LV_KEYBOARD_SET_TEXTAREA, argv);
}

void lv_obj_scroll_to_view_recursive(lv_obj_t * obj, lv_anim_enable_t anim_en)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)anim_en;
    LVGL_CALL_FUNC(LV_OBJ_SCROLL_TO_VIEW_RECURSIVE, argv);
}

void lv_indev_reset(lv_indev_t * indev, lv_obj_t * obj)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)indev;
    argv[1] = (uint32_t)obj;
    LVGL_CALL_FUNC(LV_INDEV_RESET, argv);
}

void lv_obj_clear_state(lv_obj_t * obj, lv_state_t state)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)state;
    LVGL_CALL_FUNC(LV_OBJ_CLEAR_STATE, argv);
}

lv_obj_t * lv_disp_get_layer_top(lv_disp_t * disp)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)disp;
    LVGL_CALL_FUNC(LV_DISP_GET_LAYER_TOP, argv);

    return (lv_obj_t *)argv[0];
}

lv_obj_t * lv_calendar_create(lv_obj_t * parent)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)parent;
    LVGL_CALL_FUNC(LV_CALENDAR_CREATE, argv);

    return (lv_obj_t *)argv[0];
}

void lv_calendar_set_showed_date(lv_obj_t * obj, uint32_t year, uint32_t month)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)year;
    argv[2] = (uint32_t)month;
    LVGL_CALL_FUNC(LV_CALENDAR_SET_SHOWED_DATE, argv);
}

lv_obj_t * lv_calendar_header_dropdown_create(lv_obj_t * parent)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)parent;
    LVGL_CALL_FUNC(LV_CALENDAR_HEADER_DROPDOWN_CREATE, argv);

    return (lv_obj_t *)argv[0];
}

void * lv_event_get_param(lv_event_t * e)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)e;
    LVGL_CALL_FUNC(LV_EVENT_GET_PARAM, argv);

    return (void *)argv[0];
}

bool lv_obj_has_state(const lv_obj_t * obj, lv_state_t state)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)state;
    LVGL_CALL_FUNC(LV_OBJ_HAS_STATE, argv);

    return (bool)argv[0];
}

int32_t lv_bar_get_value(const lv_obj_t * obj)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)obj;
    LVGL_CALL_FUNC(LV_BAR_GET_VALUE, argv);

    return (int32_t)argv[0];
}

void lv_txt_get_size(lv_point_t * size_res, const char * text, const lv_font_t * font, lv_coord_t letter_space,
                     lv_coord_t line_space, lv_coord_t max_width, lv_text_flag_t flag)
{
    uint32_t argv[7];

    argv[0] = (uint32_t)size_res;
    argv[1] = (uint32_t)text;
    argv[2] = (uint32_t)font;
    argv[3] = (uint32_t)letter_space;
    argv[4] = (uint32_t)line_space;
    argv[5] = (uint32_t)max_width;
    argv[6] = (uint32_t)flag;
    LVGL_CALL_FUNC(LV_TXT_GET_SIZE, argv);
}

void lv_draw_rect_dsc_init(lv_draw_rect_dsc_t * dsc)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)dsc;
    LVGL_CALL_FUNC(LV_DRAW_RECT_DSC_INIT, argv);
}

void lv_draw_rect(const lv_area_t * coords, const lv_area_t * clip, const lv_draw_rect_dsc_t * dsc)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)coords;
    argv[1] = (uint32_t)clip;
    argv[2] = (uint32_t)dsc;
    LVGL_CALL_FUNC(LV_DRAW_RECT, argv);
}

void lv_draw_label_dsc_init(lv_draw_label_dsc_t * dsc)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)dsc;
    LVGL_CALL_FUNC(LV_DRAW_LABEL_DSC_INIT, argv);
}

void lv_draw_label(const lv_area_t * coords, const lv_area_t * mask,
                   const lv_draw_label_dsc_t * dsc,
                   const char * txt, lv_draw_label_hint_t * hint)
{
    uint32_t argv[5];

    argv[0] = (uint32_t)coords;
    argv[1] = (uint32_t)mask;
    argv[2] = (uint32_t)dsc;
    argv[3] = (uint32_t)txt;
    argv[4] = (uint32_t)hint;
    LVGL_CALL_FUNC(LV_DRAW_LABEL, argv);
}

lv_obj_t * lv_event_get_current_target(lv_event_t * e)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)e;
    LVGL_CALL_FUNC(LV_EVENT_GET_CURRENT_TARGET, argv);

    return (lv_obj_t *)argv[0];
}

lv_res_t lv_calendar_get_pressed_date(const lv_obj_t * calendar, lv_calendar_date_t * date)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)calendar;
    argv[1] = (uint32_t)date;
    LVGL_CALL_FUNC(LV_CALENDAR_GET_PRESSED_DATE, argv);

    return (lv_res_t)argv[0];
}

void lv_textarea_set_text(lv_obj_t * obj, const char * txt)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)txt;
    LVGL_CALL_FUNC(LV_TEXTAREA_SET_TEXT, argv);
}

void lv_obj_del(lv_obj_t * obj)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)obj;
    LVGL_CALL_FUNC(LV_OBJ_DEL, argv);
}

void lv_obj_invalidate(const lv_obj_t * obj)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)obj;
    LVGL_CALL_FUNC(LV_OBJ_INVALIDATE, argv);
}

lv_chart_type_t lv_chart_get_type(const lv_obj_t * obj)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)obj;
    LVGL_CALL_FUNC(LV_CHART_GET_TYPE, argv);

    return (lv_chart_type_t)argv[0];
}

void lv_draw_mask_line_points_init(lv_draw_mask_line_param_t * param, lv_coord_t p1x, lv_coord_t p1y, lv_coord_t p2x,
                                   lv_coord_t p2y, lv_draw_mask_line_side_t side)
{
    uint32_t argv[6];

    argv[0] = (uint32_t)param;
    argv[1] = (uint32_t)p1x;
    argv[2] = (uint32_t)p1y;
    argv[3] = (uint32_t)p2x;
    argv[4] = (uint32_t)p2y;
    argv[5] = (uint32_t)side;
    LVGL_CALL_FUNC(LV_DRAW_MASK_LINE_POINTS_INIT, argv);
}

int16_t lv_draw_mask_add(void * param, void * custom_id)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)param;
    argv[1] = (uint32_t)custom_id;
    LVGL_CALL_FUNC(LV_DRAW_MASK_ADD, argv);

    return (int16_t)argv[0];
}

void lv_draw_mask_fade_init(lv_draw_mask_fade_param_t * param, const lv_area_t * coords, lv_opa_t opa_top,
                            lv_coord_t y_top,
                            lv_opa_t opa_bottom, lv_coord_t y_bottom)
{
    uint32_t argv[6];

    argv[0] = (uint32_t)param;
    argv[1] = (uint32_t)coords;
    argv[2] = (uint32_t)opa_top;
    argv[3] = (uint32_t)y_top;
    argv[4] = (uint32_t)opa_bottom;
    argv[5] = (uint32_t)y_bottom;
    LVGL_CALL_FUNC(LV_DRAW_MASK_FADE_INIT, argv);
}

bool _lv_area_intersect(lv_area_t * res_p, const lv_area_t * a1_p, const lv_area_t * a2_p)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)res_p;
    argv[1] = (uint32_t)a1_p;
    argv[2] = (uint32_t)a2_p;
    LVGL_CALL_FUNC(_LV_AREA_INTERSECT, argv);

    return (bool)argv[0];
}

void * lv_draw_mask_remove_id(int16_t id)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)id;
    LVGL_CALL_FUNC(LV_DRAW_MASK_REMOVE_ID, argv);

    return (void *)argv[0];
}

uint32_t lv_chart_get_pressed_point(const lv_obj_t * obj)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)obj;
    LVGL_CALL_FUNC(LV_CHART_GET_PRESSED_POINT, argv);

    return argv[0];
}

lv_chart_series_t * lv_chart_get_series_next(const lv_obj_t * chart, const lv_chart_series_t * ser)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)chart;
    argv[1] = (uint32_t)ser;
    LVGL_CALL_FUNC(LV_CHART_GET_SERIES_NEXT, argv);

    return (lv_chart_series_t *)argv[0];
}

lv_obj_t * lv_meter_create(lv_obj_t * parent)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)parent;
    LVGL_CALL_FUNC(LV_METER_CREATE, argv);

    return (lv_obj_t *)argv[0];
}

lv_obj_t * lv_obj_get_child(const lv_obj_t * obj, int32_t id)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)id;
    LVGL_CALL_FUNC(LV_OBJ_GET_CHILD, argv);

    return (lv_obj_t *)argv[0];
}

void lv_meter_set_indicator_value(lv_obj_t * obj, lv_meter_indicator_t * indic, int32_t value)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)indic;
    argv[2] = (uint32_t)value;
    LVGL_CALL_FUNC(LV_METER_SET_INDICATOR_VALUE, argv);
}

void lv_chart_set_series_color(lv_obj_t * chart, lv_chart_series_t * series, lv_color_t color)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)chart;
    argv[1] = (uint32_t)series;
    argv[2] = (uint32_t)color.full;
    LVGL_CALL_FUNC(LV_CHART_SET_SERIES_COLOR, argv);
}

int32_t lv_map(int32_t x, int32_t min_in, int32_t max_in, int32_t min_out, int32_t max_out)
{
    uint32_t argv[5];

    argv[0] = (uint32_t)x;
    argv[1] = (uint32_t)min_in;
    argv[2] = (uint32_t)max_in;
    argv[3] = (uint32_t)min_out;
    argv[4] = (uint32_t)max_out;
    LVGL_CALL_FUNC(LV_MAP, argv);

    return (int32_t)argv[0];
}

uint32_t lv_obj_get_child_cnt(const lv_obj_t * obj)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)obj;
    LVGL_CALL_FUNC(LV_OBJ_GET_CHILD_CNT, argv);

    return argv[0];
}

lv_meter_indicator_t * lv_meter_add_needle_line(lv_obj_t * obj, lv_meter_scale_t * scale, uint16_t width,
                                                lv_color_t color, int16_t r_mod)
{
    uint32_t argv[5];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)scale;
    argv[2] = (uint32_t)width;
    argv[3] = (uint32_t)color.full;
    argv[4] = (uint32_t)r_mod;
    LVGL_CALL_FUNC(LV_METER_ADD_NEEDLE_LINE, argv);

    return (lv_meter_indicator_t *)argv[0];
}

lv_res_t lv_mem_test(void)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)0;
    LVGL_CALL_FUNC(LV_MEM_TEST, argv);

    return (lv_res_t)argv[0];
}

void lv_mem_monitor(lv_mem_monitor_t * mon_p)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)mon_p;
    LVGL_CALL_FUNC(LV_MEM_MONITOR, argv);
}

lv_obj_t * lv_colorwheel_create(lv_obj_t * parent, bool knob_recolor)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)parent;
    argv[1] = (uint32_t)knob_recolor;
    LVGL_CALL_FUNC(LV_COLORWHEEL_CREATE, argv);

    return (lv_obj_t *)argv[0];
}

void lv_tabview_set_act(lv_obj_t * obj, uint32_t id, lv_anim_enable_t anim_en)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)id;
    argv[2] = (uint32_t)anim_en;
    LVGL_CALL_FUNC(LV_TABVIEW_SET_ACT, argv);
}

void lv_obj_del_anim_ready_cb(lv_anim_t * a)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)a;
    LVGL_CALL_FUNC(LV_OBJ_DEL_ANIM_READY_CB, argv);
}

void lv_obj_del_async(lv_obj_t * obj)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)obj;
    LVGL_CALL_FUNC(LV_OBJ_DEL_ASYNC, argv);
}

lv_obj_t * lv_bar_create(lv_obj_t * parent)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)parent;
    LVGL_CALL_FUNC(LV_BAR_CREATE, argv);

    return (lv_obj_t *)argv[0];
}

void lv_bar_set_range(lv_obj_t * obj, int32_t min, int32_t max)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)min;
    argv[2] = (uint32_t)max;
    LVGL_CALL_FUNC(LV_BAR_SET_RANGE, argv);
}

void lv_bar_set_value(lv_obj_t * obj, int32_t value, lv_anim_enable_t anim)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)anim;
    LVGL_CALL_FUNC(LV_BAR_SET_VALUE, argv);
}

void lv_bar_set_start_value(lv_obj_t * obj, int32_t start_value, lv_anim_enable_t anim)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)start_value;
    argv[2] = (uint32_t)anim;
    LVGL_CALL_FUNC(LV_BAR_SET_START_VALUE, argv);
}

void lv_obj_set_style_anim_time(lv_obj_t * obj, uint32_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_ANIM_TIME, argv);
}

lv_obj_t * lv_win_create(lv_obj_t * parent, lv_coord_t header_height)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)parent;
    argv[1] = (uint32_t)header_height;
    LVGL_CALL_FUNC(LV_WIN_CREATE, argv);

    return (lv_obj_t *)argv[0];
}

lv_obj_t * lv_win_add_title(lv_obj_t * win, const char * txt)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)win;
    argv[1] = (uint32_t)txt;
    LVGL_CALL_FUNC(LV_WIN_ADD_TITLE, argv);

    return (lv_obj_t *)argv[0];
}

lv_obj_t * lv_win_add_btn(lv_obj_t * win, const void * icon, lv_coord_t btn_w)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)win;
    argv[1] = (uint32_t)icon;
    argv[2] = (uint32_t)btn_w;
    LVGL_CALL_FUNC(LV_WIN_ADD_BTN, argv);

    return (lv_obj_t *)argv[0];
}

lv_obj_t * lv_win_get_content(lv_obj_t * win)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)win;
    LVGL_CALL_FUNC(LV_WIN_GET_CONTENT, argv);

    return (lv_obj_t *)argv[0];
}

void lv_keyboard_set_mode(lv_obj_t * kb, lv_keyboard_mode_t mode)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)kb;
    argv[1] = (uint32_t)mode;
    LVGL_CALL_FUNC(LV_KEYBOARD_SET_MODE, argv);
}

void lv_dropdown_set_options(lv_obj_t * obj, const char * options)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)options;
    LVGL_CALL_FUNC(LV_DROPDOWN_SET_OPTIONS, argv);
}

void lv_dropdown_open(lv_obj_t * dropdown_obj)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)dropdown_obj;
    LVGL_CALL_FUNC(LV_DROPDOWN_OPEN, argv);
}

void lv_dropdown_set_selected(lv_obj_t * obj, uint16_t sel_opt)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)sel_opt;
    LVGL_CALL_FUNC(LV_DROPDOWN_SET_SELECTED, argv);
}

lv_obj_t * lv_roller_create(lv_obj_t * parent)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)parent;
    LVGL_CALL_FUNC(LV_ROLLER_CREATE,argv);

    return (lv_obj_t *)argv[0];
}

void lv_roller_set_options(lv_obj_t * obj, const char * options, lv_roller_mode_t mode)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)options;
    argv[2] = (uint32_t)mode;
    LVGL_CALL_FUNC(LV_ROLLER_SET_OPTIONS, argv);
}

void lv_roller_set_selected(lv_obj_t * obj, uint16_t sel_opt, lv_anim_enable_t anim)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)sel_opt;
    argv[2] = (uint32_t)anim;
    LVGL_CALL_FUNC(LV_ROLLER_SET_SELECTED, argv);
}

lv_obj_t * lv_msgbox_create(lv_obj_t * parent, const char * title, const char * txt, const char * btn_txts[],
                            bool add_close_btn)
{
    uint32_t argv[5];

    argv[0] = (uint32_t)parent;
    argv[1] = (uint32_t)title;
    argv[2] = (uint32_t)txt;
    argv[3] = (uint32_t)btn_txts;
    argv[4] = (uint32_t)add_close_btn;
    LVGL_CALL_FUNC(LV_MSGBOX_CREATE, argv);

    return (lv_obj_t *)argv[0];
}

lv_obj_t * lv_tileview_create(lv_obj_t * parent)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)parent;
    LVGL_CALL_FUNC(LV_TILEVIEW_CREATE, argv);

    return (lv_obj_t *)argv[0];
}

lv_obj_t * lv_tileview_add_tile(lv_obj_t * tv, uint8_t row_id, uint8_t col_id, lv_dir_t dir)
{
    uint32_t argv[4];

    argv[0] = (uint32_t)tv;
    argv[1] = (uint32_t)row_id;
    argv[2] = (uint32_t)col_id;
    argv[3] = (uint32_t)dir;
    LVGL_CALL_FUNC(LV_TILEVIEW_ADD_TILE, argv);

    return (lv_obj_t *)argv[0];
}

void lv_obj_set_tile_id(lv_obj_t * tv, uint32_t col_id, uint32_t row_id, lv_anim_enable_t anim_en)
{
    uint32_t argv[4];

    argv[0] = (uint32_t)tv;
    argv[1] = (uint32_t)col_id;
    argv[2] = (uint32_t)row_id;
    argv[3] = (uint32_t)anim_en;
    LVGL_CALL_FUNC(LV_OBJ_SET_TILE_ID, argv);
}

lv_obj_t * lv_list_create(lv_obj_t * parent)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)parent;
    LVGL_CALL_FUNC(LV_LIST_CREATE, argv);

    return (lv_obj_t *)argv[0];
}

lv_obj_t * lv_list_add_btn(lv_obj_t * list, const char * icon, const char * txt)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)list;
    argv[1] = (uint32_t)icon;
    argv[2] = (uint32_t)txt;
    LVGL_CALL_FUNC(LV_LIST_ADD_BTN, argv);

    return (lv_obj_t *)argv[0];
}

void lv_obj_scroll_to_view(lv_obj_t * obj, lv_anim_enable_t anim_en)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)anim_en;
    LVGL_CALL_FUNC(LV_OBJ_SCROLL_TO_VIEW, argv);
}

void lv_textarea_set_cursor_pos(lv_obj_t * obj, int32_t pos)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)pos;
    LVGL_CALL_FUNC(LV_TEXTAREA_SET_CURSOR_POS, argv);
}

void lv_textarea_add_char(lv_obj_t * obj, uint32_t c)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)c;
    LVGL_CALL_FUNC(LV_TEXTAREA_ADD_CHAR, argv);
}

void lv_textarea_add_text(lv_obj_t * obj, const char * txt)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)txt;
    LVGL_CALL_FUNC(LV_TEXTAREA_ADD_TEXT, argv);
}

lv_obj_t * lv_spinbox_create(lv_obj_t * parent)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)parent;
    LVGL_CALL_FUNC(LV_SPINBOX_CREATE, argv);

    return (lv_obj_t *)argv[0];
}

void lv_spinbox_set_digit_format(lv_obj_t * obj, uint8_t digit_count, uint8_t separator_position)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)digit_count;
    argv[2] = (uint32_t)separator_position;
    LVGL_CALL_FUNC(LV_SPINBOX_SET_DIGIT_FORMAT, argv);
}

void lv_spinbox_set_value(lv_obj_t * obj, int32_t i)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)i;
    LVGL_CALL_FUNC(LV_SPINBOX_SET_VALUE, argv);
}

void lv_spinbox_set_step(lv_obj_t * obj, uint32_t step)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)step;
    LVGL_CALL_FUNC(LV_SPINBOX_SET_STEP, argv);
}

void lv_spinbox_increment(lv_obj_t * obj)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)obj;
    LVGL_CALL_FUNC(LV_SPINBOX_INCREMENT, argv);
}

void lv_obj_scroll_by(lv_obj_t * obj, lv_coord_t x, lv_coord_t y, lv_anim_enable_t anim_en)
{
    uint32_t argv[4];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)x;
    argv[2] = (uint32_t)y;
    argv[3] = (uint32_t)anim_en;
    LVGL_CALL_FUNC(LV_OBJ_SCROLL_BY, argv);
}

void lv_textarea_del_char_forward(lv_obj_t * obj)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)obj;
    LVGL_CALL_FUNC(LV_TEXTAREA_DEL_CHAR_FORWARD, argv);
}

void lv_msgbox_close(lv_obj_t * mbox)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)mbox;
    LVGL_CALL_FUNC(LV_MSGBOX_CLOSE, argv);
}

void lv_style_set_width(lv_style_t * style, lv_coord_t value)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)style;
    argv[1] = (uint32_t)value;
    LVGL_CALL_FUNC(LV_STYLE_SET_WIDTH, argv);
}

void lv_style_set_bg_color(lv_style_t * style, lv_color_t value)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)style;
    argv[1] = (uint32_t)value.full;
    LVGL_CALL_FUNC(LV_STYLE_SET_BG_COLOR, argv);
}

void lv_style_set_pad_right(lv_style_t * style, lv_coord_t value)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)style;
    argv[1] = (uint32_t)value;
    LVGL_CALL_FUNC(LV_STYLE_SET_PAD_RIGHT, argv);
}

void lv_style_set_grid_column_dsc_array(lv_style_t * style, const lv_coord_t value[])
{
    uint32_t argv[2];

    argv[0] = (uint32_t)style;
    argv[1] = (uint32_t)value;
    LVGL_CALL_FUNC(LV_STYLE_SET_GRID_COLUMN_DSC_ARRAY, argv);
}

void lv_style_set_grid_row_dsc_array(lv_style_t * style, const lv_coord_t value[])
{
    uint32_t argv[2];

    argv[0] = (uint32_t)style;
    argv[1] = (uint32_t)value;
    LVGL_CALL_FUNC(LV_STYLE_SET_GRID_ROW_DSC_ARRAY, argv);
}

void lv_style_set_grid_row_align(lv_style_t * style, lv_grid_align_t value)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)style;
    argv[1] = (uint32_t)value;
    LVGL_CALL_FUNC(LV_STYLE_SET_GRID_ROW_ALIGN, argv);
}

void lv_style_set_layout(lv_style_t * style, uint16_t value)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)style;
    argv[1] = (uint32_t)value;
    LVGL_CALL_FUNC(LV_STYLE_SET_LAYOUT, argv);
}

uint32_t lv_obj_get_index(const lv_obj_t * obj)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)obj;
    LVGL_CALL_FUNC(LV_OBJ_GET_INDEX, argv);

    return (uint32_t)argv[0];
}

void lv_obj_set_scroll_snap_y(lv_obj_t * obj, lv_scroll_snap_t align)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)align;
    LVGL_CALL_FUNC(LV_OBJ_SET_SCROLL_SNAP_Y, argv);
}

void lv_obj_set_style_border_width(lv_obj_t * obj, lv_coord_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_BORDER_WIDTH, argv);
}

void lv_obj_set_scroll_dir(lv_obj_t * obj, lv_dir_t dir)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)dir;
    LVGL_CALL_FUNC(LV_OBJ_SET_SCROLL_DIR, argv);
}

lv_obj_t * lv_imgbtn_create(lv_obj_t * parent)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)parent;
    LVGL_CALL_FUNC(LV_IMGBTN_CREATE, argv);

    return (lv_obj_t *)argv[0];
}

void lv_imgbtn_set_src(lv_obj_t * imgbtn, lv_imgbtn_state_t state, const void * src_left, const void * src_mid,
                       const void * src_right)
{
    uint32_t argv[5];

    argv[0] = (uint32_t)imgbtn;
    argv[1] = (uint32_t)state;
    argv[2] = (uint32_t)src_left;
    argv[3] = (uint32_t)src_mid;
    argv[4] = (uint32_t)src_right;
    LVGL_CALL_FUNC(LV_IMGBTN_SET_SRC, argv);
}

void lv_obj_set_style_bg_grad_dir(lv_obj_t * obj, lv_grad_dir_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_BG_GRAD_DIR, argv);
}

void lv_obj_set_style_bg_grad_color(lv_obj_t * obj, lv_color_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value.full;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_BG_GRAD_COLOR, argv);
}

void lv_obj_set_style_grid_row_align(lv_obj_t * obj, lv_grid_align_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_GRID_ROW_ALIGN, argv);
}

void lv_timer_pause(lv_timer_t * timer)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)timer;
    LVGL_CALL_FUNC(LV_TIMER_PAUSE, argv);
}

int32_t lv_anim_path_bounce(const lv_anim_t * a)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)a;
    LVGL_CALL_FUNC(LV_ANIM_PATH_BOUNCE, argv);

    return (int32_t)argv[0];
}

void lv_obj_fade_in(lv_obj_t * obj, uint32_t time, uint32_t delay)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)time;
    argv[2] = (uint32_t)delay;
    LVGL_CALL_FUNC(LV_OBJ_FADE_IN, argv);
}

int32_t lv_anim_path_ease_out(const lv_anim_t * a)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)a;
    LVGL_CALL_FUNC(LV_ANIM_PATH_EASE_OUT, argv);

    return (int32_t)argv[0];
}

void lv_obj_move_to_index(lv_obj_t * obj, int32_t index)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)index;
    LVGL_CALL_FUNC(LV_OBJ_MOVE_TO_INDEX, argv);
}

void lv_obj_set_style_text_line_space(lv_obj_t * obj, lv_coord_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_TEXT_LINE_SPACE, argv);
}

void lv_obj_fade_out(lv_obj_t * obj, uint32_t time, uint32_t delay)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)time;
    argv[2] = (uint32_t)delay;
    LVGL_CALL_FUNC(LV_OBJ_FADE_OUT, argv);
}

void lv_timer_resume(lv_timer_t * timer)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)timer;
    LVGL_CALL_FUNC(LV_TIMER_RESUME, argv);
}

int32_t lv_anim_path_linear(const lv_anim_t * a)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)a;
    LVGL_CALL_FUNC(LV_ANIM_PATH_LINEAR, argv);

    return (int32_t)argv[0];
}

int32_t lv_anim_path_overshoot(const lv_anim_t * a)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)a;
    LVGL_CALL_FUNC(LV_ANIM_PATH_OVERSHOOT, argv);

    return (int32_t)argv[0];
}

bool lv_anim_del(void * var, lv_anim_exec_xcb_t exec_cb)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)var;
    argv[1] = (uint32_t)exec_cb;
    LVGL_CALL_FUNC(LV_ANIM_DEL, argv);

    return (bool)argv[0];
}

void lv_event_set_ext_draw_size(lv_event_t * e, lv_coord_t size)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)e;
    argv[1] = (uint32_t)size;
    LVGL_CALL_FUNC(LV_EVENT_SET_EXT_DRAW_SIZE, argv);
}

void lv_event_set_cover_res(lv_event_t * e, lv_cover_res_t res)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)e;
    argv[1] = (uint32_t)res;
    LVGL_CALL_FUNC(LV_EVENT_SET_COVER_RES, argv);
}

lv_style_value_t lv_obj_get_style_prop(const lv_obj_t * obj, lv_part_t part, lv_style_prop_t prop)
{
    uint32_t argv[3];
    lv_style_value_t ret;

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)part;
    argv[2] = (uint32_t)prop;
    LVGL_CALL_FUNC(LV_OBJ_GET_STYLE_PROP, argv);

    ret.num = (int32_t)argv[0];

    return ret;
}

uint16_t lv_img_get_zoom(lv_obj_t * obj)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)obj;
    LVGL_CALL_FUNC(LV_IMG_GET_ZOOM, argv);

    return (uint16_t)argv[0];
}

int16_t lv_trigo_sin(int16_t angle)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)angle;
    LVGL_CALL_FUNC(LV_TRIGO_SIN, argv);

    return (int16_t)argv[0]; 
}

void lv_draw_polygon(const lv_point_t points[], uint16_t point_cnt, const lv_area_t * mask,
                     const lv_draw_rect_dsc_t * draw_dsc)
{
    uint32_t argv[4];

    argv[0] = (uint32_t)points;
    argv[1] = (uint32_t)point_cnt;
    argv[2] = (uint32_t)mask;
    argv[3] = (uint32_t)draw_dsc;
    LVGL_CALL_FUNC(LV_DRAW_POLYGON, argv);
}

lv_dir_t lv_indev_get_gesture_dir(const lv_indev_t * indev)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)indev;
    LVGL_CALL_FUNC(LV_INDEV_GET_GESTURE_DIR, argv);

    return (lv_dir_t)argv[0];
}

int32_t lv_anim_path_ease_in(const lv_anim_t * a)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)a;
    LVGL_CALL_FUNC(LV_ANIM_PATH_EASE_IN, argv);

    return (int32_t)argv[0];
}

void *lv_timer_get_user_data(lv_timer_t * timer)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)timer;
    LVGL_CALL_FUNC(LV_TIMER_GET_USER_DATA, argv);

    return (void *)argv[0];
}

int lv_obj_get_data(const lv_obj_t *obj, int type, void *pdata, int n)
{
    uint32_t argv[4];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)type;
    argv[2] = (uint32_t)pdata;
    argv[3] = (uint32_t)n;
    LVGL_CALL_FUNC(LV_OBJ_GET_DATA, argv);

    return (int)argv[0];  
}

int lv_obj_draw_part_dsc_get_data(const lv_obj_draw_part_dsc_t *dsc, int type, void *pdata, int n)
{
    uint32_t argv[4];

    argv[0] = (uint32_t)dsc;
    argv[1] = (uint32_t)type;
    argv[2] = (uint32_t)pdata;
    argv[3] = (uint32_t)n;
    LVGL_CALL_FUNC(LV_OBJ_DRAW_PART_DSC_GET_DATA, argv);

    return (int)argv[0];
}

int lv_obj_draw_part_dsc_set_data(lv_obj_draw_part_dsc_t *dsc, int type, const void *pdata, int n)
{
    uint32_t argv[4];

    argv[0] = (uint32_t)dsc;
    argv[1] = (uint32_t)type;
    argv[2] = (uint32_t)pdata;
    argv[3] = (uint32_t)n;
    LVGL_CALL_FUNC(LV_OBJ_DRAW_PART_DSC_SET_DATA, argv);

    return (int)argv[0];
}

int lv_chart_series_get_data(const lv_chart_series_t * ser, int type, void *pdata, int n)
{
    uint32_t argv[4];

    argv[0] = (uint32_t)ser;
    argv[1] = (uint32_t)type;
    argv[2] = (uint32_t)pdata;
    argv[3] = (uint32_t)n;
    LVGL_CALL_FUNC(LV_CHART_SERIES_GET_DATA, argv);

    return (int)argv[0];
}

const lv_font_t *lv_font_get_font(int type)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)type;
    LVGL_CALL_FUNC(LV_FONT_GET_FONT, argv);

    return (const lv_font_t *)argv[0];
}

int lv_font_get_data(const lv_font_t * font, int type, void *pdata, int n)
{
    uint32_t argv[4];

    argv[0] = (uint32_t)font;
    argv[1] = (uint32_t)type;
    argv[2] = (uint32_t)pdata;
    argv[3] = (uint32_t)n;
    LVGL_CALL_FUNC(LV_FONT_GET_DATA, argv);

    return (int)argv[0];
}
