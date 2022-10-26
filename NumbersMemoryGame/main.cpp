/*******************************************************
* 项目主函数文件
*
* Author:   Lunixy
* Date:     2022-10-22
*******************************************************/
#include <stdio.h>
#include <easyx.h>
#include <process.h>

#include "config.h"
#include "models.h"

/*
* 全局变量
*/
// 游戏关卡数
int g_game_level = NMG_CFG_START_LEVEL;
// 游戏状态
NMG_MODEL_GAME_STATUS g_game_status;
// 游戏中按照点击顺序出现的数字
int g_game_play_number;
// 游戏区域所有的格子数组
NMG_MODEL_CELL g_cell_list[NMG_CFG_CELL_COUNT];
// 格子背景图
IMAGE g_cell_back_image;
// 全局按钮数组
NMG_MODEL_BUTTON g_buttons[10];

extern void NMG_game_init();
extern void NMG_event_listen();
extern void NMG_timer_update(void *);

int main(int argc, char *argv[]) {
	initgraph(NMG_CFG_WINDOW_WIDTH, NMG_CFG_WINDOW_HEIGHT, EX_SHOWCONSOLE);

	// 加载图片
	loadimage(&g_cell_back_image, _T("IMAGE"), _T("CELL_BACK_IMG"), NMG_CFG_CELL_ORIGIN_WIDTH, NMG_CFG_CELL_ORIGIN_HEIGHT);

	// 游戏初始化
	NMG_game_init();

	// 单独开启线程用来更新计时器
	_beginthread(NMG_timer_update, 0, NULL);
	//DWORD thread_id;
	//CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)NMG_timer_update, NULL, 0, &thread_id);

	while (true){
		// 事件监听
		NMG_event_listen();
	}

	return 0;
}