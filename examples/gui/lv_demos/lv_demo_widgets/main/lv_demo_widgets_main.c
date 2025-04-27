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

#include <unistd.h>
#include <stdio.h>
#include "lv_demo_widgets.h"
#include "esp_lvgl.h"

void on_init(void)
{
    int ret;

    ret = lvgl_init();
    if (ret != 0) {
        printf("Faield to lvgl_init ret=%d\n", ret);
        return;
    }

    lvgl_lock();
    lv_demo_widgets();
    lvgl_unlock();
}

void on_destroy()
{
    if (!lvgl_is_inited()) {
        return;
    }

    int ret;

    printf("Close LVGL widgets demo\n");
    lvgl_lock();
    lv_demo_widgets_close();
    lvgl_unlock();

    ret = lvgl_deinit();
    if (ret != 0) {
        printf("Faield to lvgl_deinit ret=%d\n", ret);
    }
}

int main(void)
{
    on_init();

    if (!lvgl_is_inited()) {
        return -1;
    }

    while (1) {
        sleep(3600);
    }

    return 0;
}
