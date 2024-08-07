#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

objects_t objects;
lv_obj_t *tick_value_change_obj;

static void event_handler_cb_main_btn_change_page(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_CLICKED) {
        flowPropagateValue(flowState, 2, 0);
    }
}

static void event_handler_cb_main_btn_reset(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_CLICKED) {
        flowPropagateValue(flowState, 4, 0);
    }
}

static void event_handler_cb_main_btn_increment(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_CLICKED) {
        flowPropagateValue(flowState, 6, 0);
    }
    if (event == LV_EVENT_LONG_PRESSED_REPEAT) {
        flowPropagateValue(flowState, 6, 1);
    }
}

static void event_handler_cb_main_obj1(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
}

static void event_handler_cb_page2_obj2(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_CLICKED) {
        flowPropagateValue(flowState, 2, 0);
    }
}

static void event_handler_cb_page2_obj4(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_arc_get_value(ta);
            if (tick_value_change_obj != ta) {
                assignIntegerProperty(flowState, 5, 3, value, "Failed to assign Value in Arc widget");
            }
        }
    }
}

static void event_handler_cb_page2_obj5(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 6, 3, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_page2_obj6(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
}

static void event_handler_cb_page2_obj7(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_arc_get_value(ta);
            if (tick_value_change_obj != ta) {
                assignIntegerProperty(flowState, 8, 3, value, "Failed to assign Value in Arc widget");
            }
        }
    }
}

void create_screen_main() {
    void *flowState = getFlowState(0, 0);
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 16, 15);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "EEZ-Studio LVGL");
        }
        {
            // btnChangePage
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.btn_change_page = obj;
            lv_obj_set_pos(obj, 205, 189);
            lv_obj_set_size(obj, 100, 41);
            lv_obj_add_event_cb(obj, event_handler_cb_main_btn_change_page, LV_EVENT_ALL, flowState);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "next page");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // btnReset
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.btn_reset = obj;
            lv_obj_set_pos(obj, 16, 61);
            lv_obj_set_size(obj, 51, 50);
            lv_obj_add_event_cb(obj, event_handler_cb_main_btn_reset, LV_EVENT_ALL, flowState);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "rst");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // btnIncrement
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.btn_increment = obj;
            lv_obj_set_pos(obj, 254, 62);
            lv_obj_set_size(obj, 51, 50);
            lv_obj_add_event_cb(obj, event_handler_cb_main_btn_increment, LV_EVENT_ALL, flowState);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "inc");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj0 = obj;
            lv_obj_set_pos(obj, 110, 77);
            lv_obj_set_size(obj, 100, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "");
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_bar_create(parent_obj);
            objects.obj1 = obj;
            lv_obj_set_pos(obj, 86, 115);
            lv_obj_set_size(obj, 150, 10);
            lv_bar_set_range(obj, 0, 255);
            lv_obj_add_event_cb(obj, event_handler_cb_main_obj1, LV_EVENT_ALL, flowState);
        }
        {
            lv_obj_t *obj = lv_img_create(parent_obj);
            lv_obj_set_pos(obj, 224, 11);
            lv_obj_set_size(obj, 100, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_logo_lvgl);
            lv_img_set_pivot(obj, 110, 0);
            lv_img_set_zoom(obj, 90);
        }
    }
}

void tick_screen_main() {
    void *flowState = getFlowState(0, 0);
    {
        const char *new_val = evalTextProperty(flowState, 8, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj0);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj0;
            lv_label_set_text(objects.obj0, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = evalIntegerProperty(flowState, 9, 3, "Failed to evaluate Value in Bar widget");
        int32_t cur_val = lv_bar_get_value(objects.obj1);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj1;
            lv_bar_set_value(objects.obj1, new_val, LV_ANIM_OFF);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_page2() {
    void *flowState = getFlowState(0, 1);
    lv_obj_t *obj = lv_obj_create(0);
    objects.page2 = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 47, 143);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "counter");
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj2 = obj;
            lv_obj_set_pos(obj, 256, 196);
            lv_obj_set_size(obj, 61, 36);
            lv_obj_add_event_cb(obj, event_handler_cb_page2_obj2, LV_EVENT_ALL, flowState);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "back");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj3 = obj;
            lv_obj_set_pos(obj, 26, 71);
            lv_obj_set_size(obj, 100, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "");
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.obj4 = obj;
            lv_obj_set_pos(obj, 8, 20);
            lv_obj_set_size(obj, 136, 123);
            lv_arc_set_range(obj, 0, 255);
            lv_arc_set_bg_end_angle(obj, 60);
            lv_obj_add_event_cb(obj, event_handler_cb_page2_obj4, LV_EVENT_ALL, flowState);
        }
        {
            lv_obj_t *obj = lv_switch_create(parent_obj);
            objects.obj5 = obj;
            lv_obj_set_pos(obj, 135, 200);
            lv_obj_set_size(obj, 50, 25);
            lv_obj_add_event_cb(obj, event_handler_cb_page2_obj5, LV_EVENT_ALL, flowState);
        }
        {
            lv_obj_t *obj = lv_led_create(parent_obj);
            objects.obj6 = obj;
            lv_obj_set_pos(obj, 144, 164);
            lv_obj_set_size(obj, 32, 32);
            lv_led_set_color(obj, lv_color_hex(4280171468));
            lv_obj_add_event_cb(obj, event_handler_cb_page2_obj6, LV_EVENT_ALL, flowState);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
        }
        {
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.obj7 = obj;
            lv_obj_set_pos(obj, 176, 20);
            lv_obj_set_size(obj, 136, 123);
            lv_arc_set_range(obj, 0, 50);
            lv_arc_set_bg_end_angle(obj, 60);
            lv_obj_add_event_cb(obj, event_handler_cb_page2_obj7, LV_EVENT_ALL, flowState);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 197, 143);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "temperature");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj8 = obj;
            lv_obj_set_pos(obj, 187, 72);
            lv_obj_set_size(obj, 100, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "");
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
}

void tick_screen_page2() {
    void *flowState = getFlowState(0, 1);
    {
        const char *new_val = evalTextProperty(flowState, 4, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj3);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj3;
            lv_label_set_text(objects.obj3, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = evalIntegerProperty(flowState, 5, 3, "Failed to evaluate Value in Arc widget");
        int32_t cur_val = lv_arc_get_value(objects.obj4);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj4;
            lv_arc_set_value(objects.obj4, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 6, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj5, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj5;
            if (new_val) lv_obj_add_state(objects.obj5, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj5, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 7, 3, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.obj6, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj6;
            if (new_val) lv_obj_add_state(objects.obj6, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.obj6, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = evalIntegerProperty(flowState, 7, 4, "Failed to evaluate Brightness in Led widget");
        if (new_val < 0) new_val = 0;
        else if (new_val > 255) new_val = 255;
        int32_t cur_val = lv_led_get_brightness(objects.obj6);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj6;
            lv_led_set_brightness(objects.obj6, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = evalIntegerProperty(flowState, 8, 3, "Failed to evaluate Value in Arc widget");
        int32_t cur_val = lv_arc_get_value(objects.obj7);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj7;
            lv_arc_set_value(objects.obj7, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 10, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj8);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj8;
            lv_label_set_text(objects.obj8, new_val);
            tick_value_change_obj = NULL;
        }
    }
}


void create_screens() {
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_main();
    create_screen_page2();
}

typedef void (*tick_screen_func_t)();

tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
    tick_screen_page2,
};

void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
