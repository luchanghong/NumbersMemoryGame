/*******************************************************
* 设置模块函数
* 函数前缀：NMG_settings_
*
* Author:   Lunixy
* Date:     2022-10-22
*******************************************************/

#include "config.h"
#include "models.h"

extern NMG_MODEL_SETTINGS NMG_data_settings_query();
extern int NMG_data_settings_update(NMG_MODEL_SETTINGS);

/*
* 读取文件 && 获取设置
*/
NMG_MODEL_SETTINGS NMG_settings_list() {
    return NMG_data_settings_query();
}

/*
* 写入文件 && 更新设置
*/
int NMG_settings_update(NMG_MODEL_SETTINGS_OPTION option, NMG_MODEL_SETTINGS_VALUE value) {
    NMG_MODEL_SETTINGS settings = NMG_settings_list();
    switch (option){
    case nmg_settings_game_sound:
        settings.game_sound = value.int_value;
        break;
    case nmg_settings_bgm_sound:
        settings.bgm_sound = value.int_value;
        break;
    case nmg_settings_bg_image_src:
        settings.bg_image_src = value.str_value;
    default:
        break;
    }

    // todo: update
    int res = NMG_data_settings_update(settings);

    return res;
}