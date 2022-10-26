/*******************************************************
* 游戏模块函数
* 函数前缀：NMG_game_
*
* Author:   Lunixy
* Date:     2022-10-22
*******************************************************/

#include <easyx.h>

#include "models.h"
#include "config.h"

extern int g_game_level;
extern int g_game_play_number;
extern NMG_MODEL_GAME_STATUS g_game_status;

extern void NMG_cell_data_init();
extern void NMG_cell_bind_number();
extern void NMG_cell_unbind_number();

extern void NMG_view_init();
extern void NMG_view_reset();
extern void NMG_view_cells_show_number();
extern void NMG_view_cell_remove_number();
extern void NMG_view_show_countdown();
extern void NMG_view_update_game_level();
extern void NMG_view_pause_button_update(TCHAR label[10]);

extern void NMG_timer_start();
extern void NMG_timer_pause();
extern void NMG_timer_play();
extern void NMG_timer_reset();
extern void NMG_timer_block(int seconds);

// init
static void _NMG_game_init() {
    // 游戏状态初始化
    g_game_status = NMG_GSTS_NO_STARTED;
    g_game_play_number = 0;
    g_game_level = NMG_CFG_START_LEVEL;
    // 格子数据初始化
    NMG_cell_data_init();
}

// 游戏初始化
void NMG_game_init() {
    _NMG_game_init();
    // UI初始化
    NMG_view_init();
}

// 开始一关游戏
void NMG_game_start() {
    if (g_game_status == NMG_GSTS_CAN_PLAY_NEXT || g_game_status == NMG_GSTS_NO_STARTED){
        // 移除格子上的旧数字
        NMG_view_cell_remove_number();
        // 开启计时器
        NMG_timer_start();
        // 解除数据绑定
        NMG_cell_unbind_number();
        // 绑定新数据
        NMG_cell_bind_number();
        // 显示格子上的新数字
        NMG_view_cells_show_number();
        // 预留给玩家的记忆时间
        if (g_game_level > 3){
            Sleep((g_game_level - 3) * 1000);
        }
        // 显示倒计时
        NMG_view_show_countdown();
        // 移除格子上的数字
        NMG_view_cell_remove_number();
        // 清除消息事件
        flushmessage();
        // 改变游戏状态
        g_game_status = NMG_GSTS_PLAYING;
    }
}

// 开启下一关
void NMG_game_next() {
    g_game_level += 1;
    g_game_status = NMG_GSTS_CAN_PLAY_NEXT;
    Sleep(400);
    // 关卡升级
    NMG_view_update_game_level();
    NMG_game_start();
}

// 暂停游戏
void NMG_game_pause() {
    g_game_status = NMG_GSTS_PASUING;
    // 计时器暂停
    NMG_timer_pause();
    // 按钮显示更新
    TCHAR label[10] = L"继续游戏";
    NMG_view_pause_button_update(label);
}

// 继续游戏
void NMG_game_play() {
    g_game_status = NMG_GSTS_PLAYING;
    // 计时器开始
    NMG_timer_play();
    // 按钮显示更新
    TCHAR label[10] = L"暂停游戏";
    NMG_view_pause_button_update(label);
}

// 重置游戏
void NMG_game_reset() {
    // 计时器重置
    NMG_timer_reset();
    // 游戏参数初始化
    _NMG_game_init();
    // UI重载
    NMG_view_reset();
}