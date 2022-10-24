/*******************************************************
* 游戏模块函数
* 函数前缀：NMG_game_
*
* Author:   Lunixy
* Date:     2022-10-22
*******************************************************/

#include <easyx.h>

#include "models.h"

extern int g_game_level;
extern NMG_MODEL_GAME_STATUS g_game_status;

extern void NMG_view_init();
extern void NMG_cell_data_init();
extern void NMG_cell_bind_number();
extern void NMG_cell_unbind_number();
extern void NMG_view_cells_show_number();
extern void NMG_view_cell_remove_number();
extern void NMG_view_show_countdown();

// 游戏初始化
void NMG_game_init() {
    // 游戏状态初始化
    g_game_status = NMG_GSTS_NO_STARTED;
    // 格子数据初始化
    NMG_cell_data_init();
    // UI初始化
    NMG_view_init();
}

// 开始一关游戏
void NMG_game_start() {
    if (g_game_status == NMG_GSTS_CAN_PLAY_NEXT || g_game_status == NMG_GSTS_NO_STARTED){
        // 移除格子上的旧数字
        NMG_view_cell_remove_number();
        // 解除数据绑定
        NMG_cell_unbind_number();
        // 绑定新数据
        NMG_cell_bind_number();
        // 显示格子上的新数字
        NMG_view_cells_show_number();
        // 显示倒计时
        NMG_view_show_countdown();
        // 移除格子上的数字
        NMG_view_cell_remove_number();
        // 清除消息事件
        flushmessage();
        // 改变游戏状态
        g_game_status = NMG_GSTS_PLAYING;
        //g_game_level += 1;
    }
}

// 开启下一关
void NMG_game_next() {
    g_game_level += 1;
    g_game_status = NMG_GSTS_CAN_PLAY_NEXT;
    Sleep(400);
    NMG_game_start();
}