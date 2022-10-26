/*******************************************************
* ��Ŀ�������ļ�
*
* Author:   Lunixy
* Date:     2022-10-22
*******************************************************/
#include <stdio.h>
#include <easyx.h>

#include "config.h"
#include "models.h"

/*
* ȫ�ֱ���
*/
// ��Ϸ�ؿ���
int g_game_level = NMG_CFG_START_LEVEL;
// ��Ϸ״̬
NMG_MODEL_GAME_STATUS g_game_status;
// ��Ϸ�а��յ��˳����ֵ�����
int g_game_play_number = 0;
// ��Ϸ�������еĸ�������
NMG_MODEL_CELL g_cell_list[NMG_CFG_CELL_COUNT];
// ���ӱ���ͼ
IMAGE g_cell_back_image;

extern void NMG_game_init();

int main(int argc, char *argv[])
{
	printf("This is my first gui project.\n");
	// ����ͼƬ
	loadimage(&g_cell_back_image, _T("IMAGE"), _T("CELL_BACK_IMG"), NMG_CFG_CELL_ORIGIN_WIDTH, NMG_CFG_CELL_ORIGIN_HEIGHT);

	// ��Ϸ��ʼ��
	NMG_game_init();

	return 0;
}