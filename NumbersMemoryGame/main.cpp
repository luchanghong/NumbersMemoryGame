/*******************************************************
* ��Ŀ�������ļ�
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
* ȫ�ֱ���
*/
// ��Ϸ�ؿ���
int g_game_level = NMG_CFG_START_LEVEL;
// ��Ϸ״̬
NMG_MODEL_GAME_STATUS g_game_status;
// ��Ϸ�а��յ��˳����ֵ�����
int g_game_play_number;
// ��Ϸ�������еĸ�������
NMG_MODEL_CELL g_cell_list[NMG_CFG_CELL_COUNT];
// ���ӱ���ͼ
IMAGE g_cell_back_image;
// ȫ�ְ�ť����
NMG_MODEL_BUTTON g_buttons[10];

extern void NMG_game_init();
extern void NMG_event_listen();
extern void NMG_timer_update(void *);

int main(int argc, char *argv[]) {
	initgraph(NMG_CFG_WINDOW_WIDTH, NMG_CFG_WINDOW_HEIGHT, EX_SHOWCONSOLE);

	// ����ͼƬ
	loadimage(&g_cell_back_image, _T("IMAGE"), _T("CELL_BACK_IMG"), NMG_CFG_CELL_ORIGIN_WIDTH, NMG_CFG_CELL_ORIGIN_HEIGHT);

	// ��Ϸ��ʼ��
	NMG_game_init();

	// ���������߳��������¼�ʱ��
	_beginthread(NMG_timer_update, 0, NULL);
	//DWORD thread_id;
	//CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)NMG_timer_update, NULL, 0, &thread_id);

	while (true){
		// �¼�����
		NMG_event_listen();
	}

	return 0;
}