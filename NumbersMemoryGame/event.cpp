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
extern NMG_MODEL_BUTTON g_buttons[10];
extern NMG_MODEL_GAME_STATUS g_game_status;

extern void NMG_game_start();
extern void NMG_game_next();
extern void NMG_game_pause();
extern void NMG_game_play();
extern void NMG_game_reset();
extern int NMG_cell_clicked(int cell_index);
extern int NMG_cell_which_clicked(int x, int y);

static int _NMG_event_click_button(int x, int y) {
    
    for (int i = 0; i < 10; i++){
        NMG_MODEL_BUTTON button = g_buttons[i];
        if (button.rect.left < x && button.rect.right > x && button.rect.top < y && button.rect.bottom > y){
            return i;
        }
    }
    return -1;
}

// 鼠标左键点击事件处理
static void _NMG_event_mouse_left_down(ExMessage msg) {
    int button_index = _NMG_event_click_button(msg.x, msg.y);
    // 暂停按钮点击
    if (button_index == 0){
        if (g_game_status == NMG_GSTS_PLAYING){
            NMG_game_pause();
        } else if (g_game_status == NMG_GSTS_PASUING){
            NMG_game_play();
        }
        return;
    }

    // 重置按钮点击
    if (button_index == 1){
        if (g_game_status != NMG_GSTS_NO_STARTED){
            NMG_game_reset();
            return;
        }
    }

    // 游戏中的状态下，只响应点击格子的事件
    int cell_index = NMG_cell_which_clicked(msg.x, msg.y);
    if (g_game_status == NMG_GSTS_PLAYING){
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
    } else if (g_game_status == NMG_GSTS_NO_STARTED){
        if (cell_index >= 0){
            NMG_game_start();
        }
    }
}

// 监听
void NMG_event_listen() {
    ExMessage m;
    // 获取一条鼠标或按键消息
    if (!peekmessage(&m, EX_MOUSE)){
        return;
    }

    switch (m.message){
    case WM_MOUSEMOVE:
        // 鼠标移动的时候画红色的小点
        // putpixel(m.x, m.y, RED);
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