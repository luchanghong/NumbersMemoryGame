/*******************************************************
* 项目主函数文件
*
* Author:   Lunixy
* Date:     2022-10-22
*******************************************************/
#include <stdio.h>
#include <easyx.h>

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
int g_game_play_number = 0;
// 游戏区域所有的格子数组
NMG_MODEL_CELL g_cell_list[NMG_CFG_CELL_COUNT];
// 格子背景图
IMAGE g_cell_back_image;

extern void NMG_game_init();

int main(int argc, char *argv[])
{
	printf("This is my first gui project.\n");
	// 加载图片
	loadimage(&g_cell_back_image, _T("IMAGE"), _T("CELL_BACK_IMG"), NMG_CFG_CELL_ORIGIN_WIDTH, NMG_CFG_CELL_ORIGIN_HEIGHT);

	// 游戏初始化
	NMG_game_init();

	return 0;
}