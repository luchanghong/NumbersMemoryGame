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
extern void NMG_cell_bind_number();
extern void NMG_cell_unbind_number();
extern void NMG_view_cells_show_number();
extern void NMG_view_cell_remove_number();

// 游戏初始化
void NMG_game_init() {
    NMG_view_init();
}

// 开始一关游戏
void NMG_game_start() {
    if (g_game_status == NMG_GSTS_CAN_PLAY_NEXT || g_game_status == NMG_GSTS_NO_STARTED){
        // 改变游戏状态
        // 解除数据绑定
        NMG_cell_unbind_number();
        // 移除格子上的旧数字
        NMG_view_cell_remove_number();
        // 绑定新数据
        NMG_cell_bind_number();
        // 显示格子上的新数字
        NMG_view_cells_show_number();

        // 暂停N秒后隐藏数字，玩家开始点击
        // bug: 鼠标点击事件会阻塞
        Sleep(3000);
        NMG_view_cell_remove_number();

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