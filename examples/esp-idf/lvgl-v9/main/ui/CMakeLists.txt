SET(SOURCES screens/ui_Screen1.c
    screens/ui_Screen2.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    images/ui_img_background_png.c
    images/ui_img_wifi_png.c
    images/ui_img_back_png.c
    images/ui_img_power_switch_png.c
    images/ui_img_cold_mode_png.c
    images/ui_img_increase_png.c
    images/ui_img_decrease_png.c
    images/ui_img_mode_png.c
    images/ui_img_airflow_png.c
    images/ui_img_wind_direction_png.c
    images/ui_img_settings_png.c
    images/ui_img_background_without_circle_png.c
    images/ui_img_mode_cold_png.c
    images/ui_img_mode_sleep_png.c
    images/ui_img_mode_dry_png.c
    images/ui_img_mode_warm_png.c
    images/ui_img_mode_wind_png.c
    images/ui_img_mode_auto_png.c
    images/ui_img_airflow_small_png.c
    images/ui_img_airflow_middle_png.c
    images/ui_img_airflow_large_png.c
    images/ui_img_decrease_white_png.c
    images/ui_img_increase_white_png.c
    fonts/ui_font_micross100.c
    fonts/ui_font_micross50.c
    fonts/ui_font_simhei30.c
    fonts/ui_font_simhei36.c
    fonts/ui_font_simhei24.c
    fonts/ui_font_simhei46.c)

add_library(ui ${SOURCES})
