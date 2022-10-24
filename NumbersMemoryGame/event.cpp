/*******************************************************
* 鼠标、键盘事件监测
* 函数前缀：NMG_event_
*
* Author:   Lunixy
* Date:     2022-10-24
*******************************************************/

#include <easyx.h>
#include <stdio.h>

#include "models.h"

extern int g_game_level;
extern int g_game_play_number;
extern NMG_MODEL_GAME_STATUS g_game_status;

extern void NMG_game_start();
extern void NMG_game_next();
extern int NMG_cell_clicked(int cell_index);
extern int NMG_cell_which_clicked(int x, int y);

// 鼠标左键点击事件处理
static void _NMG_event_mouse_left_down(ExMessage msg) {
    // 游戏中的状态下，只响应点击格子的事件
    if (g_game_status == NMG_GSTS_PLAYING){
        int cell_index = NMG_cell_which_clicked(msg.x, msg.y);
        printf("clicked cell index: %d\n", cell_index);
        // 是否点击格子
        if (cell_index < 0){
            return;
        }
        // 判断点击顺序
        int number = NMG_cell_clicked(cell_index);
        if (number == 0){
            // todo: 是否直接结束掉游戏
            return;
        }
        // 关卡完成，触发下一关
        if (number == g_game_level){
            g_game_play_number = 0;
            NMG_game_next();
        } else if (number > 0){
            g_game_play_number = number;
        }
        return;
    }
    NMG_game_start();
}

// 监听
void NMG_event_listen() {
    ExMessage m;

    while (true){
        // 获取一条鼠标或按键消息
        m = getmessage(EX_MOUSE | EX_KEY);

        switch (m.message){
        case WM_MOUSEMOVE:
            // 鼠标移动的时候画红色的小点
            putpixel(m.x, m.y, RED);
            break;

        case WM_LBUTTONDOWN:
            _NMG_event_mouse_left_down(m);
            break;

        case WM_KEYDOWN:
            if (m.vkcode == VK_ESCAPE){
                closegraph();	// 按 ESC 键退出程序
            }
        }
    }
}