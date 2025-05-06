/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

/*********************
 *      INCLUDES
 *********************/
#include <math.h>
#include "esp_lvgl.h"

#ifndef PI
#define PI  (3.14159f)
#endif

#if 0
#define LV_WRAPPER_DEBUG() \
    printf("line=%d failed to get o=%p t=%d &p=%p s=%ld\n", __LINE__, o, t, &p, sizeof(p));
#else
#define LV_WRAPPER_DEBUG()
#endif

#define LV_TIMER_CTX_GET_DATA(o, t, p)                                          \
({                                                                               \
    int _ret = lv_timer_ctx_get_data(o, t, &p, sizeof(p));                       \
    if (_ret) {                                                                 \
        LV_WRAPPER_DEBUG();                                                                \
    }                                                                           \
    _ret; \
})

#define LV_TIMER_CTX_SET_DATA(o, t, p)                                          \
({                                                                               \
    int _ret = lv_timer_ctx_set_data(o, t, &p, sizeof(p));                      \
    if (_ret) {                                                                 \
        LV_WRAPPER_DEBUG();    \
    }                                                                           \
    _ret; \
})

// LVGL image declare
LV_IMG_DECLARE(esp_logo)
LV_IMG_DECLARE(esp_text)

static lv_obj_t *arc[3];
static lv_obj_t *img_logo;
static lv_obj_t *img_text;
static lv_color_t arc_color[] = {
    LV_COLOR_MAKE(232, 87, 116),
    LV_COLOR_MAKE(126, 87, 162),
    LV_COLOR_MAKE(90, 202, 228),
};

static lv_obj_t *g_scr;
static lv_timer_t *ui_test_timer;

static void anim_timer_cb(lv_timer_t *timer)
{
    timer_context_t *timer_ctx = (timer_context_t *)lv_timer_get_user_data(timer);
    int count;
    LV_TIMER_CTX_GET_DATA(timer_ctx, LV_TIMER_CTX_COUNT_VAL, count);
    lv_obj_t *scr = timer_ctx->scr;

    // Play arc animation
    if (count < 90) {
        lv_coord_t arc_start = count > 0 ? (1 - cosf(count / 180.0f * PI)) * 270 : 0;
        lv_coord_t arc_len = (sinf(count / 180.0f * PI) + 1) * 135;

        for (size_t i = 0; i < sizeof(arc) / sizeof(arc[0]); i++) {
            lv_arc_set_bg_angles(arc[i], arc_start, arc_len);
            lv_arc_set_rotation(arc[i], (count + 120 * (i + 1)) % 360);
        }
    }

    // Delete arcs when animation finished
    if (count == 90) {
        for (size_t i = 0; i < sizeof(arc) / sizeof(arc[0]); i++) {
            lv_obj_del(arc[i]);
        }

        // Create new image and make it transparent
        img_text = lv_img_create(scr);
        lv_img_set_src(img_text, &esp_text);
        lv_obj_set_style_img_opa(img_text, 0, 0);
    }

    // Move images when arc animation finished
    if ((count >= 100) && (count <= 180)) {
        float test = (count - 140) * 2.25f / 90.0f;
        int32_t offset = (sinf(test) + 1) * 20.0f;
        lv_obj_align(img_logo, LV_ALIGN_CENTER, 0, -offset);
        lv_obj_align(img_text, LV_ALIGN_CENTER, 0, 2 * offset);
        lv_obj_set_style_img_opa(img_text, offset / 40.0f * 255, 0);
    }

    // Delete timer when all animation finished
    if ((count += 5) == 220) {
        lv_timer_del(timer);
    } else {
        LV_TIMER_CTX_SET_DATA(timer_ctx, LV_TIMER_CTX_COUNT_VAL, count);
    }
}

void lv_start_ui(lv_obj_t *scr)
{
    // Create image
    img_logo = lv_img_create(scr);
    lv_img_set_src(img_logo, &esp_logo);
    lv_obj_center(img_logo);

    // Create arcs
    for (size_t i = 0; i < sizeof(arc) / sizeof(arc[0]); i++) {
        arc[i] = lv_arc_create(scr);

        // Set arc caption
        lv_obj_set_size(arc[i], 220 - 30 * i, 220 - 30 * i);
        lv_arc_set_bg_angles(arc[i], 120 * i, 10 + 120 * i);
        lv_arc_set_value(arc[i], 0);

        // Set arc style
        lv_obj_remove_style(arc[i], NULL, LV_PART_KNOB);
        lv_obj_set_style_arc_width(arc[i], 10, 0);
        lv_obj_set_style_arc_color(arc[i], arc_color[i], 0);

        // Make arc center
        lv_obj_center(arc[i]);
    }

    // Create timer for animation
    static timer_context_t my_tim_ctx = {
        .count_val = -90,
    };
    my_tim_ctx.scr = scr;
    ui_test_timer = lv_timer_create(anim_timer_cb, 20, &my_tim_ctx);
}

void lv_demo_ui(void)
{
    g_scr = lv_disp_get_scr_act(NULL);
    lv_start_ui(g_scr);
}

void lv_demo_ui_close(void)
{
    lv_obj_clean(g_scr);
}

