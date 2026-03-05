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
#include "esp_lvgl.h"
#include "wm_ext_wasm_app_lvgl_func_id.h"

#define LV_VERSION_VAL(major, minor, patch) ((major << 16) | (minor << 8) | (patch))
#define LV_VERSION  LV_VERSION_VAL(WM_LV_VERSION_MAJOR, \
                                   WM_LV_VERSION_MINOR, \
                                   WM_LV_VERSION_PATCH)

#define LVGL_CALL_FUNC(id, argv) esp_lvgl_call_native_func(id, \
                                                           sizeof(argv) / sizeof(argv[0]), \
                                                           argv)
#define ESP_BROOKESIA_SELECTOR_TRANS_VALUE             0xFFFFFFFF

static bool is_lvgl_init = false;
static char *s_lv_textarea_got_text = NULL;
static char *s_lv_label_got_text = NULL;

lv_display_t *lv_display_get_next(lv_display_t *disp)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)disp;
    LVGL_CALL_FUNC(LV_DISP_GET_NEXT, argv);

    return (lv_display_t *)argv[0];
}

lv_display_t *lv_display_get_default(void)
{
    uint32_t argv[1];

    LVGL_CALL_FUNC(LV_DISP_GET_DEFAULT, argv);

    return (lv_display_t *)argv[0];
}

lv_obj_t *lv_display_get_screen_active(lv_display_t *disp)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)disp;
    LVGL_CALL_FUNC(LV_DISP_GET_SCR_ACT, argv);

    return (lv_obj_t *)argv[0];
}

int32_t lv_display_get_horizontal_resolution(const lv_display_t * disp)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)disp;
    LVGL_CALL_FUNC(LV_DISP_GET_HOR_RES, argv);

    return (int32_t)argv[0];
}

int32_t lv_display_get_vertical_resolution(const lv_display_t * disp)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)disp;
    LVGL_CALL_FUNC(LV_DISP_GET_VER_RES, argv);

    return (int32_t)argv[0];
}

#if 0
void lv_disp_set_monitor_cb(lv_display_t *disp, void *cb)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)disp;
    argv[1] = (uint32_t)cb;
    LVGL_CALL_FUNC(LV_DISP_SET_MONITOR_CB, argv);
}
#endif

lv_observer_t * lv_subject_add_observer_obj(lv_subject_t * subject, lv_observer_cb_t cb, lv_obj_t * obj,
                                            void * user_data)
{
    uint32_t argv[4];

    argv[0] = (uint32_t)subject;
    argv[1] = (uint32_t)cb;
    argv[2] = (uint32_t)obj;
    argv[3] = (uint32_t)user_data;
    LVGL_CALL_FUNC(LV_SUBJECT_ADD_OBSERVER_OBJ, argv);

    return (lv_observer_t *)argv[0];   
}

void lv_obj_remove_style(lv_obj_t * obj, const lv_style_t * style, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)style;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_REMOVE_STYLE, argv);
}

void lv_obj_set_style_bg_opa(lv_obj_t * obj, lv_opa_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_BG_OPA, argv);
}

void lv_obj_set_pos(lv_obj_t *obj, int32_t x, int32_t y)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)x;
    argv[2] = (uint32_t)y;
    LVGL_CALL_FUNC(LV_OBJ_SET_POS, argv);
}

void lv_obj_align_to(lv_obj_t *obj, const lv_obj_t *base, lv_align_t align, int32_t x_ofs, int32_t y_ofs)
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

int32_t lv_obj_get_width(const lv_obj_t *obj)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)obj;
    LVGL_CALL_FUNC(LV_OBJ_GET_WIDTH, argv);

    return (int32_t)argv[0];
}

int32_t lv_obj_get_height(const lv_obj_t *obj)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)obj;
    LVGL_CALL_FUNC(LV_OBJ_GET_HEIGHT, argv);

    return (int32_t)argv[0];
}

void lv_obj_set_size(lv_obj_t *obj, int32_t w, int32_t h)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)w;
    argv[2] = (uint32_t)h;
    LVGL_CALL_FUNC(LV_OBJ_SET_SIZE, argv);
}

void lv_obj_align(lv_obj_t *obj, lv_align_t align, int32_t x_ofs, int32_t y_ofs)
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

int32_t lv_obj_get_content_width(const lv_obj_t *obj)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)obj;
    LVGL_CALL_FUNC(LV_OBJ_GET_CONTENT_WIDTH, argv);

    return (int32_t)argv[0];
}

void lv_obj_set_width(lv_obj_t *obj, int32_t w)
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
    argv[1] = (uint32_t)((value.red << 16) | (value.green << 8) | value.blue);
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_LINE_COLOR, argv);
}

void lv_obj_set_style_arc_color(lv_obj_t *obj, lv_color_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)((value.red << 16) | (value.green << 8) | value.blue);
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_ARC_COLOR, argv);
}

void lv_obj_set_style_image_recolor(lv_obj_t *obj, lv_color_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)((value.red << 16) | (value.green << 8) | value.blue);
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_IMG_RECOLOR, argv);
}

void lv_obj_set_style_text_color(lv_obj_t *obj, lv_color_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)((value.red << 16) | (value.green << 8) | value.blue);
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_TEXT_COLOR, argv);
}

void lv_obj_set_x(lv_obj_t *obj, int32_t x)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)x;
    LVGL_CALL_FUNC(LV_OBJ_SET_X, argv);
}

void lv_obj_set_y(lv_obj_t *obj, int32_t y)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)y;
    LVGL_CALL_FUNC(LV_OBJ_SET_Y, argv);
}

void lv_obj_add_style(lv_obj_t * obj, const lv_style_t * style, lv_style_selector_t selector)
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
    argv[1] = (uint32_t)((value.red << 16) | (value.green << 8) | value.blue);
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_BG_COLOR, argv);
}

void lv_obj_set_style_border_color(lv_obj_t *obj, lv_color_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)((value.red << 16) | (value.green << 8) | value.blue);
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_BORDER_COLOR, argv);
}

void lv_obj_set_style_shadow_color(lv_obj_t *obj, lv_color_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)((value.red << 16) | (value.green << 8) | value.blue);
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

void lv_table_set_column_count(lv_obj_t *obj, uint32_t col_cnt) 
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)col_cnt;
    LVGL_CALL_FUNC(LV_TABLE_SET_COL_CNT, argv);
}

void lv_table_set_column_width(lv_obj_t *obj, uint32_t col_id, int32_t w) 
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)col_id;
    argv[2] = (uint32_t)w;
    LVGL_CALL_FUNC(LV_TABLE_SET_COL_WIDTH, argv);
}

void lv_table_set_cell_ctrl(lv_obj_t *obj, uint32_t row, uint32_t col, lv_table_cell_ctrl_t ctrl)
{
    uint32_t argv[4];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)row;
    argv[2] = (uint32_t)col;
    argv[3] = (uint32_t)ctrl;
    LVGL_CALL_FUNC(LV_TABLE_ADD_CELL_CTRL, argv);
}

void lv_table_set_cell_value(lv_obj_t *obj, uint32_t row, uint32_t col, const char *txt)
{
    uint32_t argv[4];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)row;
    argv[2] = (uint32_t)col;
    argv[3] = (uint32_t)txt;
    LVGL_CALL_FUNC(LV_TABLE_SET_CELL_VALUE, argv);
}

void lv_table_set_cell_value_fmt(lv_obj_t * obj, uint32_t row, uint32_t col, const char * fmt, ...)
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
        lv_table_set_cell_value(obj, row, col, buffer);
        free(buffer);
    }
}

void lv_table_set_row_count(lv_obj_t * obj, uint32_t row_cnt)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)row_cnt;
    LVGL_CALL_FUNC(LV_TABLE_SET_ROW_CNT, argv);
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

void lv_style_set_radius(lv_style_t * style, int32_t value)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)style;
    argv[1] = (uint32_t)value;
    LVGL_CALL_FUNC(LV_STYLE_SET_RADIUS, argv);
}

void lv_style_set_border_width(lv_style_t * style, int32_t value)
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

void lv_style_set_shadow_width(lv_style_t * style, int32_t value)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)style;
    argv[1] = (uint32_t)value;
    LVGL_CALL_FUNC(LV_STYLE_SET_SHADOW_WIDTH, argv);
}

void lv_style_set_shadow_offset_x(lv_style_t * style, int32_t value)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)style;
    argv[1] = (uint32_t)value;
    LVGL_CALL_FUNC(LV_STYLE_SET_SHADOW_OFS_X, argv);
}

void lv_style_set_shadow_offset_y(lv_style_t * style, int32_t value)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)style;
    argv[1] = (uint32_t)value;
    LVGL_CALL_FUNC(LV_STYLE_SET_SHADOW_OFS_Y, argv);
}

void lv_style_set_shadow_spread(lv_style_t * style, int32_t value)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)style;
    argv[1] = (uint32_t)value;
    LVGL_CALL_FUNC(LV_STYLE_SET_SHADOW_SPREAD, argv);
}

void lv_style_set_image_opa(lv_style_t * style, lv_opa_t value)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)style;
    argv[1] = (uint32_t)value;
    LVGL_CALL_FUNC(LV_STYLE_SET_IMG_OPA, argv);
}

void lv_style_set_image_recolor_opa(lv_style_t * style, lv_opa_t value)
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

void lv_style_set_line_width(lv_style_t * style, int32_t value)
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

void lv_style_set_arc_width(lv_style_t * style, int32_t value)
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
    argv[1] = (uint32_t)((value.red << 16) | (value.green << 8) | value.blue);
    LVGL_CALL_FUNC(LV_STYLE_SET_TEXT_COLOR, argv);
}

lv_obj_t *lv_line_create(lv_obj_t * parent)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)parent;
    LVGL_CALL_FUNC(LV_LINE_CREATE, argv);

    return (lv_obj_t *)argv[0];
}

void lv_line_set_points(lv_obj_t * obj, const lv_point_precise_t points[], uint32_t point_num)
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

void lv_arc_set_start_angle(lv_obj_t * arc, lv_value_precise_t start)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)arc;
    argv[1] = (uint32_t)start;
    LVGL_CALL_FUNC(LV_ARC_SET_START_ANGLE, argv);
}

void lv_arc_set_end_angle(lv_obj_t * arc, lv_value_precise_t end)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)arc;
    argv[1] = (uint32_t)end;
    LVGL_CALL_FUNC(LV_ARC_SET_END_ANGLE, argv);
}

lv_obj_t * lv_image_create(lv_obj_t * parent)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)parent;
    LVGL_CALL_FUNC(LV_IMG_CREATE, argv);

    return (lv_obj_t *)argv[0];
}

void lv_image_set_src(lv_obj_t * obj, const void * src)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)src;
    LVGL_CALL_FUNC(LV_IMG_SET_SRC, argv);
}

void lv_image_set_rotation(lv_obj_t * obj, int32_t angle)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)angle;
    LVGL_CALL_FUNC(LV_IMG_SET_ANGLE, argv);
}

void lv_image_set_scale(lv_obj_t * obj, uint32_t zoom)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)zoom;
    LVGL_CALL_FUNC(LV_IMG_SET_ZOOM, argv);
}

void lv_image_set_antialias(lv_obj_t * obj, bool antialias)
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

lv_theme_t * lv_theme_default_init(lv_display_t * disp, lv_color_t color_primary, lv_color_t color_secondary, bool dark,
                                   const lv_font_t * font)
{
    uint32_t argv[5];

    argv[0] = (uint32_t)disp;
    argv[1] = (uint32_t)((color_primary.red << 16) | (color_primary.green << 8) | color_primary.blue);
    argv[2] = (uint32_t)((color_secondary.red << 16) | (color_secondary.green << 8) | color_secondary.blue);
    argv[3] = (uint32_t)dark;
    argv[4] = (uint32_t)font;
    LVGL_CALL_FUNC(LV_THEME_DEFAULT_INIT, argv);

    return (lv_theme_t *)argv[0];
}

lv_color_t lv_theme_get_color_primary(lv_obj_t * obj)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)obj;
    LVGL_CALL_FUNC(KV_THEME_GET_COLOR_PRIMARY, argv);

    lv_color_t color = {
        .blue = argv[0] & 0xFF,
        .green = (argv[0] >> 8) & 0xFF,
        .red = (argv[0] >> 16) & 0xFF
    };

    return color;
}

const void * lv_font_get_bitmap_fmt_txt(lv_font_glyph_dsc_t * g_dsc, lv_draw_buf_t * draw_buf)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)g_dsc;
    argv[1] = (uint32_t)draw_buf;
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

    argv[0] = (uint32_t)p;
    LVGL_CALL_FUNC(LV_PALETTE_MAIN, argv);

    lv_color_t color = {
        .blue = argv[0] & 0xFF,
        .green = (argv[0] >> 8) & 0xFF,
        .red = (argv[0] >> 16) & 0xFF
    };

    return color;
}

lv_obj_t * lv_tabview_create(lv_obj_t * parent)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)parent;
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

lv_obj_t * lv_tabview_get_tab_bar(lv_obj_t * tv)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)tv;
    LVGL_CALL_FUNC(LV_TABVIEW_GET_TAB_BTNS, argv);

    return (lv_obj_t *)argv[0];
}

void lv_obj_set_style_pad_left(lv_obj_t * obj, int32_t value, lv_style_selector_t selector)
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

void lv_obj_set_height(lv_obj_t * obj, int32_t h)
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

lv_obj_t * lv_button_create(lv_obj_t * parent)
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

void lv_obj_set_grid_dsc_array(lv_obj_t * obj, const int32_t col_dsc[], const int32_t row_dsc[])
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)col_dsc;
    argv[2] = (uint32_t)row_dsc;
    LVGL_CALL_FUNC(LV_OBJ_SET_GRID_DSC_ARRAY, argv);
}

void lv_obj_set_grid_cell(lv_obj_t * obj, lv_grid_align_t x_align, int32_t col_pos, int32_t col_span,
                          lv_grid_align_t y_align, int32_t row_pos, int32_t row_span)
{
    uint32_t argv[7];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)x_align;
    argv[2] = (uint32_t)col_pos;
    argv[3] = (uint32_t)col_span;
    argv[4] = (uint32_t)y_align;
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

void lv_obj_set_style_max_height(lv_obj_t * obj, int32_t value, lv_style_selector_t selector)
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

#if 0
void lv_chart_set_axis_tick(lv_obj_t * obj, lv_chart_axis_t axis, int32_t major_len, int32_t minor_len,
                            int32_t major_cnt, int32_t minor_cnt, bool label_en, int32_t draw_size)
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
#endif

void lv_chart_set_div_line_count(lv_obj_t * obj, uint8_t hdiv, uint8_t vdiv)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)hdiv;
    argv[2] = (uint32_t)vdiv;
    LVGL_CALL_FUNC(LV_CHART_SET_DIV_LINE_COUNT, argv);
}

void lv_chart_set_point_count(lv_obj_t * obj, uint32_t cnt)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)cnt;
    LVGL_CALL_FUNC(LV_CHART_SET_POINT_COUNT, argv); 
}

#if 0
void lv_chart_set_zoom_x(lv_obj_t * obj, uint16_t zoom_x)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)zoom_x;
    LVGL_CALL_FUNC(LV_CHART_SET_ZOOM_X, argv); 
}
#endif

void lv_obj_set_style_border_side(lv_obj_t * obj, lv_border_side_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_BORDER_SIDE, argv); 
}

void lv_obj_set_style_radius(lv_obj_t * obj, int32_t value, lv_style_selector_t selector)
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
    argv[1] = (uint32_t)((color.red << 16) | (color.green << 8) | color.blue);
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

void lv_chart_set_next_value(lv_obj_t * obj, lv_chart_series_t * ser, int32_t value)
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

void lv_obj_set_style_pad_row(lv_obj_t * obj, int32_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_PAD_ROW, argv); 
}

void lv_obj_set_style_pad_column(lv_obj_t * obj, int32_t value, lv_style_selector_t selector)
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

    argv[0] = (uint32_t)p;
    argv[1] = (uint32_t)lvl;
    LVGL_CALL_FUNC(LV_PALETTE_LIGHTEN, argv);

    lv_color_t color = {
        .blue = argv[0] & 0xFF,
        .green = (argv[0] >> 8) & 0xFF,
        .red = (argv[0] >> 16) & 0xFF
    };

    return color;
}

lv_obj_t * lv_obj_get_parent(const lv_obj_t *obj)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)obj;
    LVGL_CALL_FUNC(LV_OBJ_GET_PARENT, argv);

    return (lv_obj_t *)argv[0];
}

#if 0
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
#endif

void lv_obj_set_style_pad_right(lv_obj_t * obj, int32_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_PAD_RIGHT, argv);
}

void lv_obj_set_style_width(lv_obj_t * obj, int32_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_WIDTH, argv);
}

void lv_obj_set_style_height(lv_obj_t * obj, int32_t value, lv_style_selector_t selector)
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

    argv[0] = (uint32_t)p;
    argv[1] = (uint32_t)lvl;
    LVGL_CALL_FUNC(LV_PALETTE_DARKEN, argv);

    lv_color_t color = {
        .blue = argv[0] & 0xFF,
        .green = (argv[0] >> 8) & 0xFF,
        .red = (argv[0] >> 16) & 0xFF
    };

    return color;
}

void lv_obj_set_style_outline_color(lv_obj_t * obj, lv_color_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)((value.red << 16) | (value.green << 8) | value.blue);
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_OUTLINE_COLOR, argv);
}

void lv_obj_set_style_outline_width(lv_obj_t * obj, int32_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_OUTLINE_WIDTH, argv);
}

#if 0
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
#endif

void lv_obj_set_style_pad_bottom(lv_obj_t * obj, int32_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_PAD_BOTTOM, argv);
}

int32_t lv_display_get_dpi(const lv_display_t * disp)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)disp;
    LVGL_CALL_FUNC(LV_DISP_GET_DPI, argv);

    return (int32_t)argv[0];
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

void lv_obj_remove_flag(lv_obj_t * obj, lv_obj_flag_t f)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)f;
    LVGL_CALL_FUNC(LV_OBJ_CLEAR_FLAG, argv);
}

void lv_obj_set_style_pad_top(lv_obj_t * obj, int32_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_PAD_TOP, argv);
}

void lv_obj_set_style_shadow_width(lv_obj_t * obj, int32_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_SHADOW_WIDTH, argv);
}

#if CONFIG_ESP_BROOKESIA_GUI_ENABLE_SQUARELINE
uint32_t lv_brookesia_selector_trans(lv_style_selector_t selector)
{
    if (!selector) {
        selector = ESP_BROOKESIA_SELECTOR_TRANS_VALUE;
    }

    return selector;
}
#endif

void lv_obj_set_style_bg_image_src(lv_obj_t * obj, const void * value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
#if CONFIG_ESP_BROOKESIA_GUI_ENABLE_SQUARELINE
    argv[2] = lv_brookesia_selector_trans(selector);
#else
    argv[2] = (uint32_t)selector;
#endif
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_BG_IMG_SRC, argv);
}

lv_event_code_t lv_event_get_code(lv_event_t * e)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)e;
    LVGL_CALL_FUNC(LV_EVENT_GET_CODE, argv);

    return (lv_event_code_t)argv[0];
}

void * lv_event_get_target(lv_event_t * e)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)e;
    LVGL_CALL_FUNC(LV_EVENT_GET_TARGET, argv);

    return (void *)argv[0];
}

void * lv_event_get_user_data(lv_event_t * e)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)e;
    LVGL_CALL_FUNC(LV_EVENT_GET_USER_DATA, argv);

    return (void *)argv[0];
}

lv_indev_t * lv_indev_active(void)
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

void lv_obj_remove_state(lv_obj_t * obj, lv_state_t state)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)state;
    LVGL_CALL_FUNC(LV_OBJ_CLEAR_STATE, argv);
}

lv_obj_t * lv_display_get_layer_top(lv_display_t * disp)
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

void lv_calendar_set_month_shown(lv_obj_t * obj, uint32_t year, uint32_t month)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)year;
    argv[2] = (uint32_t)month;
    LVGL_CALL_FUNC(LV_CALENDAR_SET_SHOWED_DATE, argv);
}

lv_obj_t * lv_calendar_add_header_dropdown(lv_obj_t * parent)
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

void lv_text_get_size(lv_point_t * size_res, const char * text, const lv_font_t * font, int32_t letter_space,
                      int32_t line_space, int32_t max_width, lv_text_flag_t flag)
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

void lv_draw_rect(lv_layer_t * layer, const lv_draw_rect_dsc_t * dsc, const lv_area_t * coords)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)layer;
    argv[1] = (uint32_t)dsc;
    argv[2] = (uint32_t)coords;
    LVGL_CALL_FUNC(LV_DRAW_RECT, argv);
}

void lv_draw_label_dsc_init(lv_draw_label_dsc_t * dsc)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)dsc;
    LVGL_CALL_FUNC(LV_DRAW_LABEL_DSC_INIT, argv);
}

void lv_draw_label(lv_layer_t * layer, const lv_draw_label_dsc_t * dsc,
                   const lv_area_t * coords)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)layer;
    argv[1] = (uint32_t)dsc;
    argv[2] = (uint32_t)coords;
    LVGL_CALL_FUNC(LV_DRAW_LABEL, argv);
}

void * lv_event_get_current_target(lv_event_t * e)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)e;
    LVGL_CALL_FUNC(LV_EVENT_GET_CURRENT_TARGET, argv);

    return (void *)argv[0];
}

lv_result_t lv_calendar_get_pressed_date(const lv_obj_t * calendar, lv_calendar_date_t * date)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)calendar;
    argv[1] = (uint32_t)date;
    LVGL_CALL_FUNC(LV_CALENDAR_GET_PRESSED_DATE, argv);

    return (lv_result_t)argv[0];
}

void lv_textarea_set_text(lv_obj_t * obj, const char * txt)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)txt;
    LVGL_CALL_FUNC(LV_TEXTAREA_SET_TEXT, argv);
}

void lv_obj_delete(lv_obj_t * obj)
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

#if 0
void lv_draw_mask_line_points_init(lv_draw_mask_line_param_t * param, int32_t p1x, int32_t p1y, int32_t p2x,
                                   int32_t p2y, lv_draw_mask_line_side_t side)
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
                            int32_t y_top,
                            lv_opa_t opa_bottom, int32_t y_bottom)
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
#endif

bool lv_area_intersect(lv_area_t * res_p, const lv_area_t * a1_p, const lv_area_t * a2_p)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)res_p;
    argv[1] = (uint32_t)a1_p;
    argv[2] = (uint32_t)a2_p;
    LVGL_CALL_FUNC(_LV_AREA_INTERSECT, argv);

    return (bool)argv[0];
}

#if 0
void * lv_draw_mask_remove_id(int16_t id)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)id;
    LVGL_CALL_FUNC(LV_DRAW_MASK_REMOVE_ID, argv);

    return (void *)argv[0];
}
#endif

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

#if 0
lv_obj_t * lv_meter_create(lv_obj_t * parent)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)parent;
    LVGL_CALL_FUNC(LV_METER_CREATE, argv);

    return (lv_obj_t *)argv[0];
}
#endif

lv_obj_t * lv_obj_get_child(const lv_obj_t * obj, int32_t id)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)id;
    LVGL_CALL_FUNC(LV_OBJ_GET_CHILD, argv);

    return (lv_obj_t *)argv[0];
}

#if 0
void lv_meter_set_indicator_value(lv_obj_t * obj, lv_meter_indicator_t * indic, int32_t value)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)indic;
    argv[2] = (uint32_t)value;
    LVGL_CALL_FUNC(LV_METER_SET_INDICATOR_VALUE, argv);
}
#endif

void lv_chart_set_series_color(lv_obj_t * chart, lv_chart_series_t * series, lv_color_t color)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)chart;
    argv[1] = (uint32_t)series;
    argv[2] = (uint32_t)((color.red << 16) | (color.green << 8) | color.blue);
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

uint32_t lv_obj_get_child_count(const lv_obj_t * obj)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)obj;
    LVGL_CALL_FUNC(LV_OBJ_GET_CHILD_CNT, argv);

    return argv[0];
}

#if 0
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
#endif

lv_result_t lv_mem_test(void)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)0;
    LVGL_CALL_FUNC(LV_MEM_TEST, argv);

    return (lv_result_t)argv[0];
}

void lv_mem_monitor(lv_mem_monitor_t * mon_p)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)mon_p;
    LVGL_CALL_FUNC(LV_MEM_MONITOR, argv);
}

#if 0
lv_obj_t * lv_colorwheel_create(lv_obj_t * parent, bool knob_recolor)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)parent;
    argv[1] = (uint32_t)knob_recolor;
    LVGL_CALL_FUNC(LV_COLORWHEEL_CREATE, argv);

    return (lv_obj_t *)argv[0];
}
#endif

void lv_tabview_set_active(lv_obj_t * obj, uint32_t id, lv_anim_enable_t anim_en)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)id;
    argv[2] = (uint32_t)anim_en;
    LVGL_CALL_FUNC(LV_TABVIEW_SET_ACT, argv);
}

#if 0
void lv_obj_del_anim_ready_cb(lv_anim_t * a)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)a;
    LVGL_CALL_FUNC(LV_OBJ_DEL_ANIM_READY_CB, argv);
}
#endif

void lv_obj_delete_async(lv_obj_t * obj)
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

void lv_obj_set_style_anim_duration(lv_obj_t * obj, uint32_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_ANIM_TIME, argv);
}

lv_obj_t * lv_win_create(lv_obj_t * parent)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)parent;
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

lv_obj_t * lv_win_add_button(lv_obj_t * win, const void * icon, int32_t btn_w)
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

void lv_dropdown_set_selected(lv_obj_t * obj, uint32_t sel_opt)
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

void lv_roller_set_selected(lv_obj_t * obj, uint32_t sel_opt, lv_anim_enable_t anim)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)sel_opt;
    argv[2] = (uint32_t)anim;
    LVGL_CALL_FUNC(LV_ROLLER_SET_SELECTED, argv);
}

lv_obj_t * lv_msgbox_create(lv_obj_t * parent)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)parent;
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

void lv_tileview_set_tile_by_index(lv_obj_t * tv, uint32_t col_id, uint32_t row_id, lv_anim_enable_t anim_en)
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

lv_obj_t * lv_list_add_button(lv_obj_t * list, const void * icon, const char * txt)
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

void lv_spinbox_set_digit_format(lv_obj_t * obj, uint32_t digit_count, uint32_t separator_position)
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

void lv_obj_scroll_by(lv_obj_t * obj, int32_t x, int32_t y, lv_anim_enable_t anim_en)
{
    uint32_t argv[4];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)x;
    argv[2] = (uint32_t)y;
    argv[3] = (uint32_t)anim_en;
    LVGL_CALL_FUNC(LV_OBJ_SCROLL_BY, argv);
}

#if 0
void lv_textarea_del_char_forward(lv_obj_t * obj)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)obj;
    LVGL_CALL_FUNC(LV_TEXTAREA_DEL_CHAR_FORWARD, argv);
}
#endif

void lv_msgbox_close(lv_obj_t * mbox)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)mbox;
    LVGL_CALL_FUNC(LV_MSGBOX_CLOSE, argv);
}

void lv_style_set_width(lv_style_t * style, int32_t value)
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
    argv[1] = (uint32_t)((value.red << 16) | (value.green << 8) | value.blue);
    LVGL_CALL_FUNC(LV_STYLE_SET_BG_COLOR, argv);
}

void lv_style_set_pad_right(lv_style_t * style, int32_t value)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)style;
    argv[1] = (uint32_t)value;
    LVGL_CALL_FUNC(LV_STYLE_SET_PAD_RIGHT, argv);
}

void lv_style_set_grid_column_dsc_array(lv_style_t * style, const int32_t * value)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)style;
    argv[1] = (uint32_t)value;
    LVGL_CALL_FUNC(LV_STYLE_SET_GRID_COLUMN_DSC_ARRAY, argv);
}

void lv_style_set_grid_row_dsc_array(lv_style_t * style, const int32_t * value)
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

int32_t lv_obj_get_index(const lv_obj_t * obj)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)obj;
    LVGL_CALL_FUNC(LV_OBJ_GET_INDEX, argv);

    return (int32_t)argv[0];
}

void lv_obj_set_scroll_snap_y(lv_obj_t * obj, lv_scroll_snap_t align)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)align;
    LVGL_CALL_FUNC(LV_OBJ_SET_SCROLL_SNAP_Y, argv);
}

void lv_obj_set_style_border_width(lv_obj_t * obj, int32_t value, lv_style_selector_t selector)
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

lv_obj_t * lv_imagebutton_create(lv_obj_t * parent)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)parent;
    LVGL_CALL_FUNC(LV_IMGBTN_CREATE, argv);

    return (lv_obj_t *)argv[0];
}

void lv_imagebutton_set_src(lv_obj_t * obj, lv_imagebutton_state_t state, const void * src_left, const void * src_mid,
                            const void * src_right)
{
    uint32_t argv[5];

    argv[0] = (uint32_t)obj;
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
    argv[1] = (uint32_t)((value.red << 16) | (value.green << 8) | value.blue);
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

void lv_obj_set_style_text_line_space(lv_obj_t * obj, int32_t value, lv_style_selector_t selector)
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

bool lv_anim_delete(void * var, lv_anim_exec_xcb_t exec_cb)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)var;
    argv[1] = (uint32_t)exec_cb;
    LVGL_CALL_FUNC(LV_ANIM_DEL, argv);

    return (bool)argv[0];
}

void lv_event_set_ext_draw_size(lv_event_t * e, int32_t size)
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

int32_t lv_image_get_scale(lv_obj_t * obj)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)obj;
    LVGL_CALL_FUNC(LV_IMG_GET_ZOOM, argv);

    return (int32_t)argv[0];
}

int32_t lv_trigo_sin(int16_t angle)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)angle;
    LVGL_CALL_FUNC(LV_TRIGO_SIN, argv);

    return (int32_t)argv[0]; 
}

#if 0
void lv_draw_polygon(struct _lv_layer_t * draw_ctx, const lv_draw_rect_dsc_t * draw_dsc,
                     const lv_point_precise_t points[], uint16_t point_cnt)
{
    uint32_t argv[4];

    argv[0] = (uint32_tlv_indev_get_gesture_dir)draw_ctx;
    argv[1] = (uint32_t)draw_dsc;
    argv[2] = (uint32_t)points;
    argv[3] = (uint32_t)point_cnt;
    LVGL_CALL_FUNC(LV_DRAW_POLYGON, argv);
}
#endif

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

int lv_draw_rect_dsc_get_data(lv_draw_rect_dsc_t *dsc, int type, void *pdata, int n)
{
    uint32_t argv[4];

    argv[0] = (uint32_t)dsc;
    argv[1] = (uint32_t)type;
    argv[2] = (uint32_t)pdata;
    argv[3] = (uint32_t)n;
    LVGL_CALL_FUNC(LV_OBJ_DRAW_PART_DSC_GET_DATA, argv);

    return (int)argv[0];
}

int lv_draw_rect_dsc_set_data(lv_draw_rect_dsc_t *dsc, int type, const void *pdata, int n)
{
    uint32_t argv[4];

    argv[0] = (uint32_t)dsc;
    argv[1] = (uint32_t)type;
    argv[2] = (uint32_t)pdata;
    argv[3] = (uint32_t)n;
    LVGL_CALL_FUNC(LV_OBJ_DRAW_PART_DSC_SET_DATA, argv);

    return (int)argv[0];
}

#if 0
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
#endif

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

void lv_label_set_text_static(lv_obj_t * obj, const char * text)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)text;
    LVGL_CALL_FUNC(LV_LABEL_SET_TEXT_STATIC, argv);
}

void lv_style_set_border_color(lv_style_t * style, lv_color_t value)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)style;
    argv[1] = (uint32_t)((value.red << 16) | (value.green << 8) | value.blue);
    LVGL_CALL_FUNC(LV_STYLE_SET_BORDER_COLOR, argv);
}

void lv_style_set_shadow_color(lv_style_t * style, lv_color_t value)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)style;
    argv[1] = (uint32_t)((value.red << 16) | (value.green << 8) | value.blue);
    LVGL_CALL_FUNC(LV_STYLE_SET_SHADOW_COLOR, argv);
}

void lv_style_set_outline_color(lv_style_t * style, lv_color_t value)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)style;
    argv[1] = (uint32_t)((value.red << 16) | (value.green << 8) | value.blue);
    LVGL_CALL_FUNC(LV_STYLE_SET_OUTLINE_COLOR, argv);
}

void lv_style_set_outline_width(lv_style_t * style, int32_t value)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)style;
    argv[1] = (uint32_t)value;
    LVGL_CALL_FUNC(LV_STYLE_SET_OUTLINE_WIDTH, argv);
}

lv_indev_t * lv_indev_get_next(lv_indev_t * indev)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)indev;
    LVGL_CALL_FUNC(LV_INDEV_GET_NEXT, argv);

    return (lv_indev_t *)argv[0];
}

lv_group_t * lv_group_create(void)
{
    uint32_t argv[1];

    argv[0] = 0;
    LVGL_CALL_FUNC(LV_GROUP_CREATE, argv);

    return (lv_group_t *)argv[0];
}

void lv_indev_set_group(lv_indev_t * indev, lv_group_t * group)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)indev;
    argv[1] = (uint32_t)group;
    LVGL_CALL_FUNC(LV_INDEV_SET_GROUP, argv);
}

void lv_obj_set_style_shadow_opa(lv_obj_t * obj, lv_opa_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_SHADOW_OPA, argv);
}

void lv_indev_enable(lv_indev_t * indev, bool en)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)indev;
    argv[1] = (uint32_t)en;
    LVGL_CALL_FUNC(LV_INDEV_ENABLE, argv);
}

bool lv_obj_has_flag(const lv_obj_t * obj, lv_obj_flag_t f)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)f;
    LVGL_CALL_FUNC(LV_OBJ_HAS_FLAG, argv);

    return (bool)argv[0];
}

void lv_arc_set_bg_angles(lv_obj_t * obj, lv_value_precise_t start, lv_value_precise_t end)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)start;
    argv[2] = (uint32_t)end;
    LVGL_CALL_FUNC(LV_ARC_SET_BG_ANGLES, argv);
}

void lv_arc_set_value(lv_obj_t * obj, int32_t value)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    LVGL_CALL_FUNC(LV_ARC_SET_VALUE, argv);
}

void lv_obj_set_style_arc_width(lv_obj_t * obj, int32_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_ARC_WIDTH, argv);
}

void lv_arc_set_rotation(lv_obj_t * obj, int32_t rotation)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)rotation;
    LVGL_CALL_FUNC(LV_ARC_SET_ROTATION, argv);
}

void lv_obj_set_style_image_opa(lv_obj_t * obj, lv_opa_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_IMG_OPA, argv);
}

void lv_timer_delete(lv_timer_t * timer)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)timer;
    LVGL_CALL_FUNC(LV_TIMER_DEL, argv);
}

void *lv_obj_get_user_data(lv_obj_t * obj)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)obj;
    LVGL_CALL_FUNC(LV_OBJ_GET_USER_DATA, argv);

    return (void *)argv[0];
}

void lv_obj_set_user_data(lv_obj_t * obj, void * user_data)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)user_data;
    LVGL_CALL_FUNC(LV_OBJ_SET_USER_DATA, argv);
}

void lv_obj_set_scrollbar_mode(lv_obj_t * obj, lv_scrollbar_mode_t mode)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)mode;
    LVGL_CALL_FUNC(LV_OBJ_SET_SCROLLBAR_MODE, argv);
}

void lv_group_remove_all_objs(lv_group_t * group)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)group;
    LVGL_CALL_FUNC(LV_GROUP_REMOVE_ALL_OBJS, argv);
}

void lv_label_set_recolor(lv_obj_t * obj, bool en)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)en;
    LVGL_CALL_FUNC(LV_LABEL_SET_RECOLOR, argv);
}

uint32_t lv_tabview_get_tab_active(lv_obj_t * obj)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)obj;
    LVGL_CALL_FUNC(LV_TABVIEW_GET_TAB_ACT, argv);

    return (uint16_t)argv[0];
}

void lv_obj_set_style_shadow_offset_x(lv_obj_t * obj, int32_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_SHADOW_OFS_X, argv);
}

void lv_obj_set_style_shadow_offset_y(lv_obj_t * obj, int32_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_SHADOW_OFS_Y, argv);
}

lv_obj_t * lv_led_create(lv_obj_t * parent)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)parent;
    LVGL_CALL_FUNC(LV_LED_CREATE, argv);

    return (lv_obj_t *)argv[0];
}

void lv_led_off(lv_obj_t * led)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)led;
    LVGL_CALL_FUNC(LV_LED_OFF, argv);
}

void lv_led_on(lv_obj_t * led)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)led;
    LVGL_CALL_FUNC(LV_LED_ON, argv);
}

void lv_obj_get_click_area(const lv_obj_t * obj, lv_area_t * area)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)area;
    LVGL_CALL_FUNC(LV_OBJ_GET_CLICK_AREA, argv);
}

void lv_indev_set_button_points(lv_indev_t * indev, const lv_point_t points[])
{
    uint32_t argv[2];

    argv[0] = (uint32_t)indev;
    argv[1] = (uint32_t)points;
    LVGL_CALL_FUNC(LV_INDEV_SET_BUTTON_POINTS, argv);
}

lv_obj_t * lv_qrcode_create(lv_obj_t * parent)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)parent;
    LVGL_CALL_FUNC(LV_QRCODE_CREATE, argv);

    return (lv_obj_t *)argv[0];
}

lv_result_t lv_qrcode_update(lv_obj_t * obj, const void * data, uint32_t data_len)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)data;
    argv[2] = (uint32_t)data_len;
    LVGL_CALL_FUNC(LV_QRCODE_UPDATE, argv);

    return (lv_result_t)argv[0];
}

void lv_group_focus_obj(lv_obj_t * obj)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)obj;
    LVGL_CALL_FUNC(LV_GROUP_FOCUS_OBJ, argv);
}

void lv_group_focus_freeze(lv_group_t * group, bool en)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)group;
    argv[1] = (uint32_t)en;
    LVGL_CALL_FUNC(LV_GROUP_FOCUS_FREEZE, argv);
}

lv_timer_t *lv_display_get_refr_timer(lv_display_t *disp)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)disp;
    LVGL_CALL_FUNC(LV_DISP_GET_REFR_TIMER, argv);

    return (lv_timer_t *)argv[0];
}

void lv_timer_set_period(lv_timer_t * timer, uint32_t period)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)timer;
    argv[1] = (uint32_t)period;
    LVGL_CALL_FUNC(LV_TIMER_SET_PERIOD, argv);
}

lv_timer_t * lv_anim_get_timer(void)
{
    uint32_t argv[1];

    LVGL_CALL_FUNC(LV_ANIM_GET_TIMER, argv);

    return (lv_timer_t *)argv[0];
}

#if 0
int lv_disp_get_data(lv_display_t *disp, void *pdata, int n)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)disp;
    argv[1] = (uint32_t)pdata;
    argv[2] = (uint32_t)n;
    LVGL_CALL_FUNC(LV_DISP_GET_DATA, argv);

    return (int)argv[0];
}
#endif

int lv_anim_timer_get_data(lv_timer_t *anim_timer, void *pdata, int n)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)anim_timer;
    argv[1] = (uint32_t)pdata;
    argv[2] = (uint32_t)n;
    LVGL_CALL_FUNC(LV_ANIM_TIMER_GET_DATA, argv);

    return (int)argv[0];
}

lv_opa_t lv_obj_get_style_opa_recursive(const lv_obj_t * obj, lv_part_t part)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)part;
    LVGL_CALL_FUNC(LV_OBJ_GET_STYLE_OPA_RECURSIVE, argv);

    return (lv_opa_t)argv[0];
}

int lv_timer_ctx_get_data(const timer_context_t *dsc, int type, void *pdata, int n)
{
    uint32_t argv[4];

    argv[0] = (uint32_t)dsc;
    argv[1] = (uint32_t)type;
    argv[2] = (uint32_t)pdata;
    argv[3] = (uint32_t)n;
    LVGL_CALL_FUNC(LV_TIMER_CTX_GET_DATA, argv);

    return (int)argv[0];
}

int lv_timer_ctx_set_data(timer_context_t *dsc, int type, const void *pdata, int n)
{
    uint32_t argv[4];

    argv[0] = (uint32_t)dsc;
    argv[1] = (uint32_t)type;
    argv[2] = (uint32_t)pdata;
    argv[3] = (uint32_t)n;
    LVGL_CALL_FUNC(LV_TIMER_CTX_SET_DATA, argv);

    return (int)argv[0];
}

void lv_timer_ready(lv_timer_t * timer)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)timer;
    LVGL_CALL_FUNC(LV_TIMER_READY, argv);
}

lv_obj_t * lv_screen_active(void)
{
    uint32_t argv[1];

    LVGL_CALL_FUNC(LV_SCREEN_ACTIVE, argv);

    return (lv_obj_t *)argv[0];
}

void lv_tabview_set_tab_bar_size(lv_obj_t * obj, int32_t size)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)size;
    LVGL_CALL_FUNC(LV_TABVIEW_SET_TAB_BAR_SIZE, argv);
}

void lv_anim_set_var(lv_anim_t * a, void * var)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)a;
    argv[1] = (uint32_t)var;
    LVGL_CALL_FUNC(LV_ANIM_SET_VAR, argv);
}

void lv_anim_set_duration(lv_anim_t * a, uint32_t duration)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)a;
    argv[1] = (uint32_t)duration;
    LVGL_CALL_FUNC(LV_ANIM_SET_DURATION, argv);
}

void lv_anim_set_delay(lv_anim_t * a, uint32_t delay)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)a;
    argv[1] = (uint32_t)delay;
    LVGL_CALL_FUNC(LV_ANIM_SET_DELAY, argv);
}

void lv_anim_set_completed_cb(lv_anim_t * a, lv_anim_completed_cb_t completed_cb)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)a;
    argv[1] = (uint32_t)completed_cb;
    LVGL_CALL_FUNC(LV_ANIM_SET_COMPLETED_CB, argv);
}

void lv_anim_set_exec_cb(lv_anim_t * a, lv_anim_exec_xcb_t exec_cb)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)a;
    argv[1] = (uint32_t)exec_cb;
    LVGL_CALL_FUNC(LV_ANIM_SET_EXEC_CB, argv);
}

void lv_anim_set_path_cb(lv_anim_t * a, lv_anim_path_cb_t path_cb)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)a;
    argv[1] = (uint32_t)path_cb;
    LVGL_CALL_FUNC(LV_ANIM_SET_PATH_CB, argv);
}

void lv_anim_set_values(lv_anim_t * a, int32_t start, int32_t end)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)a;
    argv[1] = (uint32_t)start;
    argv[2] = (uint32_t)end;
    LVGL_CALL_FUNC(LV_ANIM_SET_VALUES, argv);
}

void lv_anim_set_reverse_duration(lv_anim_t * a, uint32_t duration)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)a;
    argv[1] = (uint32_t)duration;
    LVGL_CALL_FUNC(LV_ANIM_SET_REVERSE_DURATION, argv);
}

void lv_anim_set_repeat_count(lv_anim_t * a, uint32_t cnt)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)a;
    argv[1] = (uint32_t)cnt;
    LVGL_CALL_FUNC(LV_ANIM_SET_REPEAT_COUNT, argv);
}

lv_obj_t * lv_scale_create(lv_obj_t * parent)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)parent;
    LVGL_CALL_FUNC(LV_SCALE_CREATE, argv);

    return (lv_obj_t *)argv[0];
}

void lv_scale_set_mode(lv_obj_t * obj, lv_scale_mode_t mode)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)mode;
    LVGL_CALL_FUNC(LV_SCALE_SET_MODE, argv);
}

void lv_scale_set_angle_range(lv_obj_t * obj, uint32_t angle_range)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)angle_range;
    LVGL_CALL_FUNC(LV_SCALE_SET_ANGLE_RANGE, argv);
}

void lv_scale_set_text_src(lv_obj_t * obj, const char * txt_src[])
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)txt_src;
    LVGL_CALL_FUNC(LV_SCALE_SET_TEXT_SRC, argv);
}

void lv_scale_set_total_tick_count(lv_obj_t * obj, uint32_t total_tick_count)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)total_tick_count;
    LVGL_CALL_FUNC(LV_SCALE_SET_TOTAL_TICK_COUNT, argv);
}

void lv_scale_set_major_tick_every(lv_obj_t * obj, uint32_t major_tick_every)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)major_tick_every;
    LVGL_CALL_FUNC(LV_SCALE_SET_MAJOR_TICK_EVERY, argv);
}

void lv_scale_set_range(lv_obj_t * obj, int32_t min, int32_t max)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)min;
    argv[2] = (uint32_t)max;
    LVGL_CALL_FUNC(LV_SCALE_SET_RANGE, argv);
}

void lv_scale_set_rotation(lv_obj_t * obj, int32_t rotation)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)rotation;
    LVGL_CALL_FUNC(LV_SCALE_SET_ROTATION, argv);
}

lv_scale_section_t * lv_scale_add_section(lv_obj_t * obj)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)obj;
    LVGL_CALL_FUNC(LV_SCALE_ADD_SECTION, argv);

    return (lv_scale_section_t *)argv[0];
}

void lv_scale_set_section_range(lv_obj_t * scale, lv_scale_section_t * section, int32_t min, int32_t max)
{
    uint32_t argv[4];

    argv[0] = (uint32_t)scale;
    argv[1] = (uint32_t)section;
    argv[2] = (uint32_t)min;
    argv[3] = (uint32_t)max;
    LVGL_CALL_FUNC(LV_SCALE_SET_SECTION_RANGE, argv);
}

void lv_scale_set_section_style_main(lv_obj_t * scale, lv_scale_section_t * section, const lv_style_t * style)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)scale;
    argv[1] = (uint32_t)section;
    argv[2] = (uint32_t)style;
    LVGL_CALL_FUNC(LV_SCALE_SET_SECTION_STYLE_MAIN, argv);
}

void lv_scale_set_section_style_indicator(lv_obj_t * scale, lv_scale_section_t * section, const lv_style_t * style)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)scale;
    argv[1] = (uint32_t)section;
    argv[2] = (uint32_t)style;
    LVGL_CALL_FUNC(LV_SCALE_SET_SECTION_STYLE_INDICATOR, argv);
}

void lv_scale_set_section_style_items(lv_obj_t * scale, lv_scale_section_t * section, const lv_style_t * style)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)scale;
    argv[1] = (uint32_t)section;
    argv[2] = (uint32_t)style;
    LVGL_CALL_FUNC(LV_SCALE_SET_SECTION_STYLE_ITEMS, argv);
}

void lv_scale_set_image_needle_value(lv_obj_t * obj, lv_obj_t * needle_img, int32_t value)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)needle_img;
    argv[2] = (uint32_t)value;
    LVGL_CALL_FUNC(LV_SCALE_SET_IMAGE_NEEDLE_VALUE, argv);

}

void lv_scale_set_post_draw(lv_obj_t * obj, bool en)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)en;
    LVGL_CALL_FUNC(LV_SCALE_SET_POST_DRAW, argv);
}

lv_obj_t * lv_msgbox_add_title(lv_obj_t * obj, const char * title)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)title;
    LVGL_CALL_FUNC(LV_MSGBOX_ADD_TITLE, argv);

    return (lv_obj_t *)argv[0];
}

lv_obj_t * lv_msgbox_add_header_button(lv_obj_t * obj, const void * icon)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)icon;
    LVGL_CALL_FUNC(LV_MSGBOX_ADD_HEADER_BUTTON, argv);

    return (lv_obj_t *)argv[0];
}

lv_obj_t * lv_msgbox_add_text(lv_obj_t * obj, const char * text)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)text;
    LVGL_CALL_FUNC(LV_MSGBOX_ADD_TEXT, argv);

    return (lv_obj_t *)argv[0];
}

lv_obj_t * lv_msgbox_add_footer_button(lv_obj_t * obj, const char * text)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)text;
    LVGL_CALL_FUNC(LV_MSGBOX_ADD_FOOTER_BUTTON, argv);

    return (lv_obj_t *)argv[0];
}

void lv_textarea_delete_char_forward(lv_obj_t * obj)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)obj;
    LVGL_CALL_FUNC(LV_TEXTAREA_DELETE_CHAR_FORWARD, argv);
}

lv_obj_t * lv_layer_top(void)
{
    uint32_t argv[1];

    LVGL_CALL_FUNC(LV_LAYER_TOP, argv);

    return (lv_obj_t *)argv[0];
}

lv_draw_task_type_t lv_draw_task_get_type(const lv_draw_task_t * t)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)t;
    LVGL_CALL_FUNC(LV_DRAW_TASK_GET_TYPE, argv);

    return (lv_draw_task_type_t)argv[0];
}

int lv_draw_dsc_base_get_data(lv_draw_dsc_base_t *dsc, int type, void *pdata, int n)
{
    uint32_t argv[4];

    argv[0] = (uint32_t)dsc;
    argv[1] = (uint32_t)type;
    argv[2] = (uint32_t)pdata;
    argv[3] = (uint32_t)n;
    LVGL_CALL_FUNC(LV_DRAW_DSC_BASE_GET_DATA, argv);

    return (int)argv[0];
}

int lv_draw_dsc_base_set_data(lv_draw_dsc_base_t *dsc, int type, const void *pdata, int n)
{
    uint32_t argv[4];

    argv[0] = (uint32_t)dsc;
    argv[1] = (uint32_t)type;
    argv[2] = (uint32_t)pdata;
    argv[3] = (uint32_t)n;
    LVGL_CALL_FUNC(LV_DRAW_DSC_BASE_SET_DATA, argv);

    return (int)argv[0];
}

int lv_draw_line_dsc_get_data(lv_draw_line_dsc_t *dsc, int type, void *pdata, int n)
{
    uint32_t argv[4];

    argv[0] = (uint32_t)dsc;
    argv[1] = (uint32_t)type;
    argv[2] = (uint32_t)pdata;
    argv[3] = (uint32_t)n;
    LVGL_CALL_FUNC(LV_DRAW_LINE_DSC_GET_DATA, argv);

    return (int)argv[0];
}

int lv_draw_line_dsc_set_data(lv_draw_line_dsc_t *dsc, int type, const void *pdata, int n)
{
    uint32_t argv[4];

    argv[0] = (uint32_t)dsc;
    argv[1] = (uint32_t)type;
    argv[2] = (uint32_t)pdata;
    argv[3] = (uint32_t)n;
    LVGL_CALL_FUNC(LV_DRAW_LINE_DSC_SET_DATA, argv);

    return (int)argv[0];
}

int lv_draw_fill_dsc_get_data(const lv_draw_fill_dsc_t * dsc, int type, void *pdata, int n)
{
    uint32_t argv[4];

    argv[0] = (uint32_t)dsc;
    argv[1] = (uint32_t)type;
    argv[2] = (uint32_t)pdata;
    argv[3] = (uint32_t)n;
    LVGL_CALL_FUNC(LV_DRAW_FILL_DSC_GET_DATA, argv);

    return (int)argv[0];
}

void * lv_draw_task_get_draw_dsc(const lv_draw_task_t * t)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)t;
    LVGL_CALL_FUNC(LV_DRAW_TASK_GET_DRAW_DSC, argv);

    return (void *)argv[0];
}

void lv_draw_task_get_area(const lv_draw_task_t * t, lv_area_t * area)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)t;
    argv[1] = (uint32_t)area;
    LVGL_CALL_FUNC(LV_DRAW_TASK_GET_AREA, argv);
}

lv_draw_line_dsc_t * lv_draw_task_get_line_dsc(lv_draw_task_t * task)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)task;
    LVGL_CALL_FUNC(LV_DRAW_TASK_GET_LINE_DSC, argv);

    return (lv_draw_line_dsc_t *)argv[0];
}

lv_draw_fill_dsc_t * lv_draw_task_get_fill_dsc(lv_draw_task_t * task)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)task;
    LVGL_CALL_FUNC(LV_DRAW_TASK_GET_FILL_DSC, argv);

    return (lv_draw_fill_dsc_t *)argv[0];
}

lv_draw_label_dsc_t * lv_draw_task_get_label_dsc(lv_draw_task_t * task)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)task;
    LVGL_CALL_FUNC(LV_DRAW_TASK_GET_LABEL_DSC, argv);

    return (lv_draw_label_dsc_t *)argv[0];
}

lv_draw_border_dsc_t * lv_draw_task_get_border_dsc(lv_draw_task_t * task)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)task;
    LVGL_CALL_FUNC(LV_DRAW_TASK_GET_BORDER_DSC, argv);

    return (lv_draw_border_dsc_t *)argv[0];
}

void lv_draw_triangle_dsc_init(lv_draw_triangle_dsc_t * dsc)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)dsc;
    LVGL_CALL_FUNC(LV_DRAW_TRIANGLE_DSC_INIT, argv);
}

void lv_draw_triangle(lv_layer_t * layer, const lv_draw_triangle_dsc_t * dsc)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)layer;
    argv[1] = (uint32_t)dsc;
    LVGL_CALL_FUNC(LV_DRAW_TRIANGLE, argv);
}

int32_t lv_pct(int32_t x)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)x;
    LVGL_CALL_FUNC(LV_AREA_PCT, argv);

    return (int32_t)argv[0];
}

int32_t lv_chart_get_first_point_center_offset(lv_obj_t * obj)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)obj;
    LVGL_CALL_FUNC(LV_CHART_GET_FIRST_POINT_CENTER_OFFSET, argv);

    return (int32_t)argv[0];
}

lv_color_t lv_chart_get_series_color(lv_obj_t * chart, const lv_chart_series_t * series)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)chart;
    argv[1] = (uint32_t)series;
    LVGL_CALL_FUNC(LV_CHART_GET_SERIES_COLOR, argv);

    lv_color_t color = {
        .blue = argv[0] & 0xFF,
        .green = (argv[0] >> 8) & 0xFF,
        .red = (argv[0] >> 16) & 0xFF
    };

    return color;
}

int32_t * lv_chart_get_series_y_array(const lv_obj_t * obj, lv_chart_series_t * ser)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)ser;
    LVGL_CALL_FUNC(LV_CHART_GET_SERIES_Y_ARRAY, argv);

    return (int32_t *)argv[0];
}

void lv_obj_center(lv_obj_t * obj)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)obj;
    LVGL_CALL_FUNC(LV_OBJ_CENTER, argv);
}

void lv_obj_delete_anim_completed_cb(lv_anim_t * a)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)a;
    LVGL_CALL_FUNC(LV_OBJ_DELETE_ANIM_COMPLETED_CB, argv);
}

lv_obj_t * lv_obj_get_sibling(const lv_obj_t * obj, int32_t idx)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)idx;
    LVGL_CALL_FUNC(LV_OBJ_GET_SIBLING, argv);

    return (lv_obj_t *)argv[0];
}

void lv_obj_set_style_arc_opa(lv_obj_t * obj, lv_opa_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_ARC_OPA, argv);
}

void lv_obj_set_style_margin_left(lv_obj_t * obj, int32_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_MARGIN_LEFT, argv);
}

void lv_obj_set_style_margin_right(lv_obj_t * obj, int32_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_MARGIN_RIGHT, argv);
}

void lv_obj_set_style_margin_top(lv_obj_t * obj, int32_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_MARGIN_TOP, argv);
}

void lv_obj_set_style_margin_bottom(lv_obj_t * obj, int32_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_MARGIN_BOTTOM, argv);
}

void lv_obj_set_style_length(lv_obj_t * obj, int32_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_LENGTH, argv);
}

void lv_obj_set_style_arc_rounded(lv_obj_t * obj, bool value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_ARC_ROUNDED, argv);
}

void lv_obj_get_coords(const lv_obj_t * obj, lv_area_t * coords)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)coords;
    LVGL_CALL_FUNC(LV_OBJ_GET_COORDS, argv);
}

void lv_obj_remove_style_all(lv_obj_t * obj)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)obj;
    LVGL_CALL_FUNC(LV_OBJ_REMOVE_STYLE_ALL, argv);
}

void lv_obj_set_layout(lv_obj_t * obj, uint32_t layout)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)layout;
    LVGL_CALL_FUNC(LV_OBJ_SET_LAYOUT, argv);
}

int32_t lv_obj_get_content_height(const lv_obj_t * obj)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)obj;
    LVGL_CALL_FUNC(LV_OBJ_GET_CONTENT_HEIGHT, argv);

    return (int32_t)argv[0];
}

int32_t lv_obj_get_scroll_bottom(const lv_obj_t * obj)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)obj;
    LVGL_CALL_FUNC(LV_OBJ_GET_SCROLL_BOTTOM, argv);

    return (int32_t)argv[0];
}

void lv_obj_set_style_opa_layered(lv_obj_t * obj, lv_opa_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_OPA_LAYERED, argv);
}

void lv_obj_scroll_to_y(lv_obj_t * obj, int32_t y, lv_anim_enable_t anim_en)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)y;
    argv[2] = (uint32_t)anim_en;
    LVGL_CALL_FUNC(LV_OBJ_SCROLL_TO_Y, argv);
}

void lv_obj_set_style_translate_y(lv_obj_t * obj, int32_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_TRANSLATE_Y, argv);   
}

void lv_style_set_arc_color(lv_style_t * style, lv_color_t value)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)style;
    argv[1] = (uint32_t)((value.red << 16) | (value.green << 8) | value.blue);
    LVGL_CALL_FUNC(LV_STYLE_SET_ARC_COLOR, argv);
}

void lv_style_set_line_color(lv_style_t * style, lv_color_t value)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)style;
    argv[1] = (uint32_t)((value.red << 16) | (value.green << 8) | value.blue);
    LVGL_CALL_FUNC(LV_STYLE_SET_LINE_COLOR, argv);
}

lv_color_t lv_color_white(void)
{
    uint32_t argv[1];

    LVGL_CALL_FUNC(LV_COLOR_WHITE, argv);
    lv_color_t color = {
        .blue = argv[0] & 0xFF,
        .green = (argv[0] >> 8) & 0xFF,
        .red = (argv[0] >> 16) & 0xFF
    };

    return color;
}

lv_color_t lv_color_black(void)
{
    uint32_t argv[1];

    LVGL_CALL_FUNC(LV_COLOR_BLACK, argv);
    lv_color_t color = {
        .blue = argv[0] & 0xFF,
        .green = (argv[0] >> 8) & 0xFF,
        .red = (argv[0] >> 16) & 0xFF
    };

    return color;
}

lv_color_t lv_color_hex(uint32_t c)
{
    lv_color_t ret;
    ret.red = (c >> 16) & 0xff;
    ret.green = (c >> 8) & 0xff;
    ret.blue = (c >> 0) & 0xff;
    return ret;
}

lv_color_t lv_color_make(uint8_t r, uint8_t g, uint8_t b)
{
    lv_color_t ret;
    ret.red = r;
    ret.green = g;
    ret.blue = b;
    return ret;
}

lv_color_t lv_color_hex3(uint32_t c)
{
    uint32_t argv[1];

    argv[0] = c;
    LVGL_CALL_FUNC(LV_COLOR_HEX3, argv);
    lv_color_t color = {
        .blue = argv[0] & 0xFF,
        .green = (argv[0] >> 8) & 0xFF,
        .red = (argv[0] >> 16) & 0xFF
    };

    return color;
}

lv_color_t lv_color_mix(lv_color_t c1, lv_color_t c2, uint8_t mix)
{
    lv_color_t ret;

    ret.red = LV_UDIV255((uint16_t)c1.red * mix + c2.red * (255 - mix) + LV_COLOR_MIX_ROUND_OFS);
    ret.green = LV_UDIV255((uint16_t)c1.green * mix + c2.green * (255 - mix) + LV_COLOR_MIX_ROUND_OFS);
    ret.blue = LV_UDIV255((uint16_t)c1.blue * mix + c2.blue * (255 - mix) + LV_COLOR_MIX_ROUND_OFS);
    return ret;
}

void lv_image_set_pivot(lv_obj_t * obj, int32_t x, int32_t y)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)x;
    argv[2] = (uint32_t)y;
    LVGL_CALL_FUNC(LV_IMAGE_SET_PIVOT, argv);
}

void lv_image_set_inner_align(lv_obj_t * obj, lv_image_align_t align)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)align;
    LVGL_CALL_FUNC(LV_IMAGE_SET_INNER_ALIGN, argv);
}

void lv_indev_wait_release(lv_indev_t * indev)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)indev;
    LVGL_CALL_FUNC(LV_INDEV_WAIT_RELEASE, argv);
}

void lv_slider_set_value(lv_obj_t * obj, int32_t value, lv_anim_enable_t anim)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)anim;
    LVGL_CALL_FUNC(LV_SLIDER_SET_VALUE, argv);
}

void lv_slider_set_range(lv_obj_t * obj, int32_t min, int32_t max)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)min;
    argv[2] = (uint32_t)max;
    LVGL_CALL_FUNC(LV_SLIDER_SET_RANGE, argv);
}

int32_t lv_slider_get_value(const lv_obj_t * obj)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)obj;
    LVGL_CALL_FUNC(LV_SLIDER_GET_VALUE, argv);

    return (int32_t)argv[0];
}

int32_t lv_area_get_width(const lv_area_t * area_p)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)area_p;
    LVGL_CALL_FUNC(LV_AREA_GET_WIDTH, argv);

    return (int32_t)argv[0];
}

int32_t lv_area_get_height(const lv_area_t * area_p)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)area_p;
    LVGL_CALL_FUNC(LV_AREA_GET_HEIGHT, argv);

    return (int32_t)argv[0];
}

void lv_arc_set_angles(lv_obj_t * obj, lv_value_precise_t start, lv_value_precise_t end)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)start;
    argv[2] = (uint32_t)end;
    LVGL_CALL_FUNC(LV_ARC_SET_ANGLES, argv);
}

lv_draw_task_t * lv_event_get_draw_task(lv_event_t * e)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)e;
    LVGL_CALL_FUNC(LV_EVENT_GET_DRAW_TASK, argv);

    return (lv_draw_task_t *)argv[0];
}

lv_layer_t * lv_event_get_layer(lv_event_t * e)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)e;
    LVGL_CALL_FUNC(LV_EVENT_GET_LAYER, argv);

    return (lv_layer_t *)argv[0];
}

lv_obj_t * lv_tabview_get_content(lv_obj_t * tv)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)tv;
    LVGL_CALL_FUNC(LV_TABVIEW_GET_CONTENT, argv);

    return (lv_obj_t *)argv[0];
}

uint32_t lv_anim_speed(uint32_t speed)
{
    uint32_t argv[1];

    argv[0] = speed;
    LVGL_CALL_FUNC(LV_ANIM_SPEED, argv);

    return argv[0];
}

int lv_obj_get_obs_data(lv_display_t *disp, int type, void *pdata, int n)
{
    uint32_t argv[4];

    argv[0] = (uint32_t)disp;
    argv[1] = (uint32_t)type;
    argv[2] = (uint32_t)pdata;
    argv[3] = (uint32_t)n;
    LVGL_CALL_FUNC(LV_OBJ_GET_OBS_DATA, argv);

    return (int)argv[0];
}

int lv_draw_task_get_data(lv_draw_task_t *disp, int type, void *pdata, int n)
{
    uint32_t argv[4];

    argv[0] = (uint32_t)disp;
    argv[1] = (uint32_t)type;
    argv[2] = (uint32_t)pdata;
    argv[3] = (uint32_t)n;
    LVGL_CALL_FUNC(LV_DRAW_TASK_GET_DATA, argv);

    return (int)argv[0];
}

int lv_draw_fill_dsc_set_data(lv_draw_fill_dsc_t *dsc, int type, const void *pdata, int n)
{
    uint32_t argv[4];

    argv[0] = (uint32_t)dsc;
    argv[1] = (uint32_t)type;
    argv[2] = (uint32_t)pdata;
    argv[3] = (uint32_t)n;
    LVGL_CALL_FUNC(LV_DRAW_FILL_DSC_SET_DATA, argv);

    return (int)argv[0];
}

int lv_draw_label_dsc_set_data(lv_draw_label_dsc_t *dsc, int type, const void *pdata, int n)
{
    uint32_t argv[4];

    argv[0] = (uint32_t)dsc;
    argv[1] = (uint32_t)type;
    argv[2] = (uint32_t)pdata;
    argv[3] = (uint32_t)n;
    LVGL_CALL_FUNC(LV_DRAW_LABEL_DSC_SET_DATA, argv);

    return (int)argv[0];
}

int lv_draw_border_dsc_set_data(lv_draw_border_dsc_t *dsc, int type, const void *pdata, int n)
{
    uint32_t argv[4];

    argv[0] = (uint32_t)dsc;
    argv[1] = (uint32_t)type;
    argv[2] = (uint32_t)pdata;
    argv[3] = (uint32_t)n;
    LVGL_CALL_FUNC(LV_DRAW_BORDER_DSC_SET_DATA, argv);

    return (int)argv[0];
}

int32_t lv_font_get_line_height(const lv_font_t * font)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)font;
    LVGL_CALL_FUNC(LV_FONT_GET_LINE_HEIGHT, argv);

    return (int32_t)argv[0];
}

int32_t lv_trigo_cos(int16_t angle)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)angle;
    LVGL_CALL_FUNC(LV_TRIGO_COS, argv);

    return (int32_t)argv[0];
}

#if LV_USE_PERF_MONITOR
int lv_get_sys_perf_data(const lv_sysmon_perf_info_t *info, int type, void *pdata, int n)
{
    uint32_t argv[4];

    argv[0] = (uint32_t)info;
    argv[1] = (uint32_t)type;
    argv[2] = (uint32_t)pdata;
    argv[3] = (uint32_t)n;
    LVGL_CALL_FUNC(LV_GET_SYS_PERF_DATA, argv);

    return (int)argv[0];
}
#endif

lv_obj_t * lv_buttonmatrix_create(lv_obj_t * parent)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)parent;
    LVGL_CALL_FUNC(LV_BUTTONMATRIX_CREATE, argv);

    return (lv_obj_t *)argv[0];
}

void lv_buttonmatrix_set_map(lv_obj_t * obj, const char * const map[])
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)map;
    LVGL_CALL_FUNC(LV_BUTTONMATRIX_SET_MAP, argv);
}

void lv_buttonmatrix_set_button_width(lv_obj_t * obj, uint32_t btn_id, uint32_t width)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)btn_id;
    argv[2] = (uint32_t)width;
    LVGL_CALL_FUNC(LV_BUTTONMATRIX_SET_BUTTON_WIDTH, argv);
}

void lv_buttonmatrix_set_button_ctrl(lv_obj_t * obj, uint32_t btn_id, lv_buttonmatrix_ctrl_t ctrl)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)btn_id;
    argv[2] = (uint32_t)ctrl;
    LVGL_CALL_FUNC(LV_BUTTONMATRIX_SET_BUTTON_CTRL, argv);
}

uint32_t lv_buttonmatrix_get_selected_button(const lv_obj_t * obj)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)obj;
    LVGL_CALL_FUNC(LV_BUTTONMATRIX_GET_SELECTED_BUTTON, argv);

    return argv[0];
}

const char * lv_buttonmatrix_get_button_text(const lv_obj_t * obj, uint32_t btn_id)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)btn_id;
    LVGL_CALL_FUNC(LV_BUTTONMATRIX_GET_BUTTON_TEXT, argv);

    return (const char *)argv[0];
}

void lv_label_cut_text(lv_obj_t * obj, uint32_t pos, uint32_t cnt)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)pos;
    argv[2] = (uint32_t)cnt;
    LVGL_CALL_FUNC(LV_LABEL_CUT_TEXT, argv);
}

void lv_label_ins_text(lv_obj_t * obj, uint32_t pos, const char * txt)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)pos;
    argv[2] = (uint32_t)txt;
    LVGL_CALL_FUNC(LV_LABEL_INS_TEXT, argv);
}

char * lv_label_get_text2(const lv_obj_t * obj)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)obj;
    LVGL_CALL_FUNC(LV_LABEL_GET_TEXT, argv);

    return (char *)argv[0];
}

char * lv_textarea_get_text2(const lv_obj_t * obj)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)obj;
    LVGL_CALL_FUNC(LV_TEXTAREA_GET_TEXT, argv);

    return (char *)argv[0];
}

char * lv_label_get_text(const lv_obj_t * obj)
{    
    if (s_lv_label_got_text) {
        free(s_lv_label_got_text);
        s_lv_label_got_text = NULL;
    }

    char *text = lv_label_get_text2(obj);
    if (text) {
        s_lv_label_got_text = text;
    }

    return text;
}

const char * lv_textarea_get_text(const lv_obj_t * obj)
{    
    if (s_lv_textarea_got_text) {
        free(s_lv_textarea_got_text);
        s_lv_textarea_got_text = NULL;
    }

    char *text = lv_textarea_get_text2(obj);
    if (text) {
        s_lv_textarea_got_text = text;
    }

    return (const char *)text;
}

const void * lv_subject_get_pointer(lv_subject_t * subject)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)subject;
    LVGL_CALL_FUNC(LV_SUBJECT_GET_POINTER, argv);

    return (const void *)argv[0];  
}

void * lv_observer_get_target(lv_observer_t * observer)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)observer;
    LVGL_CALL_FUNC(LV_OBSERVER_GET_TARGET, argv);

    return (void *)argv[0];  
}

int32_t lv_obj_get_x(const lv_obj_t * obj)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)obj;
    LVGL_CALL_FUNC(LV_OBJ_GET_X, argv);

    return (int32_t)argv[0];
}

int32_t lv_obj_get_y(const lv_obj_t * obj)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)obj;
    LVGL_CALL_FUNC(LV_OBJ_GET_Y, argv);

    return (int32_t)argv[0];
}

void lv_obj_set_style_grid_column_dsc_array(lv_obj_t * obj, const int32_t * value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_GRID_COLUMN_DSC_ARRAY, argv);
}

void lv_obj_set_style_grid_row_dsc_array(lv_obj_t * obj, const int32_t * value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_GRID_ROW_DSC_ARRAY, argv);
}

void lv_obj_set_grid_align(lv_obj_t * obj, lv_grid_align_t column_align, lv_grid_align_t row_align)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)column_align;
    argv[2] = (uint32_t)row_align;
    LVGL_CALL_FUNC(LV_OBJ_SET_GRID_ALIGN, argv);
}

void lv_screen_load_anim(lv_obj_t * scr, lv_screen_load_anim_t anim_type, uint32_t time, uint32_t delay,
                         bool auto_del)
{
    uint32_t argv[5];

    argv[0] = (uint32_t)scr;
    argv[1] = (uint32_t)anim_type;
    argv[2] = (uint32_t)time;
    argv[3] = (uint32_t)delay;
    argv[4] = (uint32_t)auto_del;
    LVGL_CALL_FUNC(LV_SCREEN_LOAD_ANIM, argv);
}

void lv_screen_load(lv_obj_t * scr)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)scr;
    LVGL_CALL_FUNC(LV_SCREEN_LOAD, argv);
}

lv_theme_t * lv_theme_simple_init(lv_display_t * disp)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)disp;
    LVGL_CALL_FUNC(LV_THEME_SIMPLE_INIT, argv);

    return (lv_theme_t *)argv[0];
}

void lv_display_set_theme(lv_display_t * disp, lv_theme_t * th)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)disp;
    argv[1] = (uint32_t)th;
    LVGL_CALL_FUNC(LV_DISPLAY_SET_THEME, argv);
}

void lv_obj_set_align(lv_obj_t * obj, lv_align_t align)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)align;
    LVGL_CALL_FUNC(LV_OBJ_SET_ALIGN, argv);
}

void lv_obj_set_style_text_opa(lv_obj_t * obj, lv_opa_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_TEXT_OPA, argv);
}

lv_result_t lv_obj_send_event(lv_obj_t * obj, lv_event_code_t event_code, void * param)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)event_code;
    argv[2] = (uint32_t)param;
    LVGL_CALL_FUNC(LV_OBJ_SEND_EVENT, argv);

    return (lv_result_t)argv[0];
}

void lv_obj_set_style_bg_image_tiled(lv_obj_t * obj, bool value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_BG_IMAGE_TILED, argv);
}

void lv_obj_set_style_border_opa(lv_obj_t * obj, lv_opa_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_BORDER_OPA, argv);
}

void lv_obj_set_style_shadow_spread(lv_obj_t * obj, int32_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_SHADOW_SPREAD, argv);
}

void lv_obj_set_style_image_recolor_opa(lv_obj_t * obj, lv_opa_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_IMAGE_RECOLOR_OPA, argv);
}

int32_t lv_obj_get_y_aligned(const lv_obj_t * obj)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)obj;
    LVGL_CALL_FUNC(LV_OBJ_GET_Y_ALIGNED, argv);

    return (int32_t)argv[0];
}

void * lv_malloc(size_t size)
{
    return malloc(size);
}

void lv_free(void * data)
{
    free(data);
}

void lv_anim_set_user_data(lv_anim_t * a, void * user_data)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)a;
    argv[1] = (uint32_t)user_data;
    LVGL_CALL_FUNC(LV_ANIM_SET_USER_DATA, argv);
}

void lv_anim_set_custom_exec_cb(lv_anim_t * a, lv_anim_custom_exec_cb_t exec_cb)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)a;
    argv[1] = (uint32_t)exec_cb;
    LVGL_CALL_FUNC(LV_ANIM_SET_CUSTOM_EXEC_CB, argv);
}

void lv_anim_set_deleted_cb(lv_anim_t * a, lv_anim_deleted_cb_t deleted_cb)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)a;
    argv[1] = (uint32_t)deleted_cb;
    LVGL_CALL_FUNC(LV_ANIM_SET_DELETED_CB, argv);
}

void lv_anim_set_reverse_delay(lv_anim_t * a, uint32_t delay)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)a;
    argv[1] = (uint32_t)delay;
    LVGL_CALL_FUNC(LV_ANIM_SET_REVERSE_DELAY, argv);
}

void lv_anim_set_repeat_delay(lv_anim_t * a, uint32_t delay)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)a;
    argv[1] = (uint32_t)delay;
    LVGL_CALL_FUNC(LV_ANIM_SET_REPEAT_DELAY, argv);
}

void lv_anim_set_early_apply(lv_anim_t * a, bool en)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)a;
    argv[1] = (uint32_t)en;
    LVGL_CALL_FUNC(LV_ANIM_SET_EARLY_APPLY, argv);
}

void lv_anim_set_get_value_cb(lv_anim_t * a, lv_anim_get_value_cb_t get_value_cb)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)a;
    argv[1] = (uint32_t)get_value_cb;
    LVGL_CALL_FUNC(LV_ANIM_SET_GET_VALUE_CB, argv);
}

int32_t lv_arc_get_value(const lv_obj_t * obj)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)obj;
    LVGL_CALL_FUNC(LV_ARC_GET_VALUE, argv);

    return (int32_t)argv[0];
}

void lv_obj_set_style_transform_scale_x(lv_obj_t * obj, int32_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_TRANSFORM_SCALE_X, argv);
}

void lv_obj_set_style_transform_scale_y(lv_obj_t * obj, int32_t value, lv_style_selector_t selector)
{
    uint32_t argv[3];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)value;
    argv[2] = (uint32_t)selector;
    LVGL_CALL_FUNC(LV_OBJ_SET_STYLE_TRANSFORM_SCALE_Y, argv);
}

lv_result_t lv_async_call(lv_async_cb_t async_xcb, void * user_data)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)async_xcb;
    argv[1] = (uint32_t)user_data;
    LVGL_CALL_FUNC(LV_ASYNC_CALL, argv);

    return (lv_result_t)argv[0];
}

lv_subject_t *lv_obj_get_subject(void)
{
    uint32_t argv[1];

    LVGL_CALL_FUNC(LV_OBJ_GET_SUBJECT, argv);

    return (lv_subject_t *)argv[0];
}


void lv_obj_refr_pos(lv_obj_t * obj)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)obj;
    LVGL_CALL_FUNC(LV_OBJ_REFR_POS, argv); 
}

void lv_image_set_offset_x(lv_obj_t * obj, int32_t x)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)x;
    LVGL_CALL_FUNC(LV_IMAGE_SET_OFFSET_X, argv);
}

void lv_anim_delete_all(void)
{
    uint32_t argv[1];

    LVGL_CALL_FUNC(LV_ANIM_DELETE_ALL, argv);
}

void lv_obj_set_parent(lv_obj_t * obj, lv_obj_t * parent)
{
    uint32_t argv[2];

    argv[0] = (uint32_t)obj;
    argv[1] = (uint32_t)parent;
    LVGL_CALL_FUNC(LV_OBJ_SET_PARENT, argv); 
}

uint32_t lv_tick_get(void)
{
    uint32_t argv[1];

    LVGL_CALL_FUNC(LV_TICK_GET, argv);

    return argv[0];
}

uint32_t lv_tick_elaps(uint32_t prev_tick)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)prev_tick;
    LVGL_CALL_FUNC(LV_TICK_ELAPS, argv);

    return argv[0];
}

void * lv_anim_get_user_data(const lv_anim_t * a)
{
    uint32_t argv[1];

    argv[0] = (uint32_t)a;
    LVGL_CALL_FUNC(LV_ANIM_GET_USER_DATA, argv);

    return (void *)argv[0];
}

int lvgl_init(void)
{
    int ret = esp_lvgl_init(LV_VERSION);
    if (!ret) {
        is_lvgl_init = true;
    } else {
        is_lvgl_init = false;
    }

    return ret;
}

int lvgl_deinit(void)
{
    return esp_lvgl_deinit();
}

bool lvgl_is_inited(void)
{
    return is_lvgl_init;
}
