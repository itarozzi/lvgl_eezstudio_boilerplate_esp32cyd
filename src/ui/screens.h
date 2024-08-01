#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *page2;
    lv_obj_t *btn_change_page;
    lv_obj_t *btn_increment;
    lv_obj_t *btn_reset;
    lv_obj_t *obj0;
    lv_obj_t *obj1;
    lv_obj_t *obj2;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_MAIN = 1,
    SCREEN_ID_PAGE2 = 2,
};

void create_screen_main();
void tick_screen_main();

void create_screen_page2();
void tick_screen_page2();

void create_screens();
void tick_screen(int screen_index);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/