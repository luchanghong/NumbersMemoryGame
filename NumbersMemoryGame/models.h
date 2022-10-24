/*******************************************************
* 项目中的数据模型
* 数据模型前缀：NMG_MODEL_
* 
* Author:   Lunixy
* Date:     2022-10-22
*******************************************************/

#include <easyx.h>

/*
* 排行榜数据模型
*/

//struct NMG_model_rank {
//    char nickername[20];
//    int take_time;
//};
// 使用typedef来定义，使用时更加便捷
typedef struct{
    char nickername[20];
    int take_time;
} NMG_MODEL_RANK;

/*
* 游戏相关数据模型
*/
// 棋盘格子
typedef struct{
    int left;
    int top;
    int right;
    int bottom;
    int width;
    int height;
    int bind_number;
    TCHAR bind_number_str[3];
} NMG_MODEL_CELL;

typedef enum {
    NMG_GSTS_NO_STARTED,		// 未开始
    NMG_GSTS_PLAYING,		    // 进行中
    NMG_GSTS_CAN_PLAY_NEXT,	    // 可以进行下一关
    NMG_GSTS_CLEARANCE,		    // 已通关
} NMG_MODEL_GAME_STATUS;

/*
* 设置选项数据模型
*/
typedef struct{
    int game_sound;     // 游戏音效开关
    int bgm_sound;      // 背景音乐开关
    char *bg_image_src; // 背景图地址
} NMG_MODEL_SETTINGS;

// 设置项
typedef enum {
    nmg_settings_game_sound,
    nmg_settings_bgm_sound,
    nmg_settings_bg_image_src
} NMG_MODEL_SETTINGS_OPTION;

// 设置项的值有多种数据类型，采用union构造类型
typedef union{
    int int_value;      // 整数类型的值
    char *str_value;    // 字符串类型的值
} NMG_MODEL_SETTINGS_VALUE;

/*
* 语言种类
*/
typedef struct{
    char name[30];
    int code;
} NMG_MODEL_SETTINGS_LANGUAGE_TYPE;