#include "ui_app.h"

#include <stdint.h>

#include "ui.h"

typedef enum {
    UI_APP_PAGE_MODE = 0,
    UI_APP_PAGE_AIRFLOW,
    UI_APP_PAGE_SWING,
    UI_APP_PAGE_SETTINGS,
} ui_app_page_t;

#define TEMP_X10_MIN   160
#define TEMP_X10_MAX   300
#define TEMP_X10_STEP  5

#define AIRFLOW_LEVEL_MIN  1
#define AIRFLOW_LEVEL_MAX  5
#define AIRFLOW_OPA_ON     255
#define AIRFLOW_OPA_OFF    100

static int s_temp_x10 = 265;
static int s_airflow_level = 1;

static void bind_click(lv_obj_t *obj, lv_event_cb_t cb, void *user_data)
{
    lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(obj, cb, LV_EVENT_CLICKED, user_data);

    uint32_t child_cnt = lv_obj_get_child_cnt(obj);
    for (uint32_t i = 0; i < child_cnt; i++) {
        lv_obj_t *child = lv_obj_get_child(obj, i);
        if (lv_obj_has_flag(child, LV_OBJ_FLAG_CLICKABLE)) {
            lv_obj_add_event_cb(child, cb, LV_EVENT_CLICKED, user_data);
        }
    }
}

static void update_temp_labels(void)
{
    char buf[8];
    lv_snprintf(buf, sizeof(buf), "%d", s_temp_x10 / 10);
    lv_label_set_text(ui_Label4, buf);
    lv_snprintf(buf, sizeof(buf), ".%d", s_temp_x10 % 10);
    lv_label_set_text(ui_Label5, buf);
}

static void adjust_temp(int delta_x10)
{
    int next = s_temp_x10 + delta_x10;
    if (next < TEMP_X10_MIN) {
        next = TEMP_X10_MIN;
    } else if (next > TEMP_X10_MAX) {
        next = TEMP_X10_MAX;
    }
    if (next == s_temp_x10) {
        return;
    }
    s_temp_x10 = next;
    update_temp_labels();
}

static void update_airflow_ui(void)
{
    lv_obj_t *bars[] = {
        ui_Container38,
        ui_Container42,
        ui_Container43,
        ui_Container44,
        ui_Container45,
    };

    for (int i = 0; i < 5; i++) {
        lv_opa_t opa = ((i + 1) <= s_airflow_level) ? AIRFLOW_OPA_ON : AIRFLOW_OPA_OFF;
        lv_obj_set_style_bg_opa(bars[i], opa, LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    lv_obj_set_style_bg_image_opa(ui_Container39,
                                  (s_airflow_level >= 3) ? AIRFLOW_OPA_ON : AIRFLOW_OPA_OFF,
                                  LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_opa(ui_Container40,
                                  (s_airflow_level >= 5) ? AIRFLOW_OPA_ON : AIRFLOW_OPA_OFF,
                                  LV_PART_MAIN | LV_STATE_DEFAULT);
}

static void adjust_airflow(int delta)
{
    int next = s_airflow_level + delta;
    if (next < AIRFLOW_LEVEL_MIN) {
        next = AIRFLOW_LEVEL_MIN;
    } else if (next > AIRFLOW_LEVEL_MAX) {
        next = AIRFLOW_LEVEL_MAX;
    }
    if (next == s_airflow_level) {
        return;
    }
    s_airflow_level = next;
    update_airflow_ui();
}

static void show_page(ui_app_page_t page)
{
    lv_obj_t *panels[] = {
        ui_Container19,
        ui_Container48,
        ui_Container58,
        ui_Container46,
    };

    for (int i = 0; i < 4; i++) {
        if (i == (int)page) {
            lv_obj_remove_flag(panels[i], LV_OBJ_FLAG_HIDDEN);
        } else {
            lv_obj_add_flag(panels[i], LV_OBJ_FLAG_HIDDEN);
        }
    }
}

static void goto_screen2(ui_app_page_t page)
{
    show_page(page);
    lv_screen_load(ui_Screen2);
}

static void on_temp_inc(lv_event_t *e)
{
    (void)e;
    adjust_temp(TEMP_X10_STEP);
}

static void on_temp_dec(lv_event_t *e)
{
    (void)e;
    adjust_temp(-TEMP_X10_STEP);
}

static void on_open_page(lv_event_t *e)
{
    ui_app_page_t page = (ui_app_page_t)(intptr_t)lv_event_get_user_data(e);
    goto_screen2(page);
}

static void on_switch_page(lv_event_t *e)
{
    ui_app_page_t page = (ui_app_page_t)(intptr_t)lv_event_get_user_data(e);
    show_page(page);
}

static void on_back_screen1(lv_event_t *e)
{
    (void)e;
    lv_screen_load(ui_Screen1);
}

static void on_airflow_inc(lv_event_t *e)
{
    (void)e;
    adjust_airflow(1);
}

static void on_airflow_dec(lv_event_t *e)
{
    (void)e;
    adjust_airflow(-1);
}

void ui_app_init(void)
{
    update_temp_labels();
    update_airflow_ui();

    bind_click(ui_Container5, on_temp_inc, NULL);
    bind_click(ui_Container7, on_temp_dec, NULL);

    bind_click(ui_Container37, on_airflow_inc, NULL);
    bind_click(ui_Container35, on_airflow_dec, NULL);

    bind_click(ui_Container8, on_open_page, (void *)(intptr_t)UI_APP_PAGE_MODE);
    bind_click(ui_Container10, on_open_page, (void *)(intptr_t)UI_APP_PAGE_AIRFLOW);
    bind_click(ui_Container11, on_open_page, (void *)(intptr_t)UI_APP_PAGE_SWING);
    bind_click(ui_Container12, on_open_page, (void *)(intptr_t)UI_APP_PAGE_SETTINGS);

    bind_click(ui_Container15, on_switch_page, (void *)(intptr_t)UI_APP_PAGE_MODE);
    bind_click(ui_Container16, on_switch_page, (void *)(intptr_t)UI_APP_PAGE_AIRFLOW);
    bind_click(ui_Container17, on_switch_page, (void *)(intptr_t)UI_APP_PAGE_SWING);
    bind_click(ui_Container18, on_switch_page, (void *)(intptr_t)UI_APP_PAGE_SETTINGS);

    bind_click(ui_Container14, on_back_screen1, NULL);
}
