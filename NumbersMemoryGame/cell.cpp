/*******************************************************
* ���̸���ģ��
* ����ǰ׺��NMG_cell_
*
* Author:   Lunixy
* Date:     2022-10-23
*******************************************************/

#include <stdio.h>
#include <easyx.h>

#include "config.h"
#include "models.h"

extern int g_game_level;
extern int g_game_play_number;
extern NMG_MODEL_CELL g_cell_list[NMG_CFG_CELL_COUNT];

extern int *NMG_utils_rand_numbers(int start, int end, int count);
extern void NMG_view_cells_show_number();
extern void NMG_view_cell_show_number(int cell_index);
extern void NMG_view_cell_show_warning(int cell_index);

// ���ӳ�ʼ��
void NMG_cell_data_init() {
	for (int i = 0; i < NMG_CFG_CELL_ROW_COUNT; i++){
		for (int j = 0; j < NMG_CFG_CELL_COLUMN_COUNT; j++){
			int left = j * NMG_CFG_CELL_ORIGIN_WIDTH + NMG_CFG_CELL_PADDING,
				top = i * NMG_CFG_CELL_ORIGIN_HEIGHT + NMG_CFG_CELL_PADDING,
				right = (j + 1) * NMG_CFG_CELL_ORIGIN_WIDTH,
				bottom = (i + 1) * NMG_CFG_CELL_ORIGIN_HEIGHT;
			g_cell_list[i * NMG_CFG_CELL_ROW_COUNT + j] = {
				left, top, right, bottom,
				NMG_CFG_CELL_REAL_WIDTH, NMG_CFG_CELL_REAL_HEIGHT, 0
			};
		}
	}
}

// ��ʼ����ӭ��
void NMG_cell_init_welcome() {
	struct {
		TCHAR s[3];
		int n;
	} welcome[12] = {
		{ _T("��"), 1 },
		{ _T("��"), 1 },
		{ _T("��"), 1 },
		{ _T("��"), 1 },
		{ _T("��"), 1 },
		{ _T("��"), 1 },
		{ _T("��"), 1 },
		{ _T("ʼ"), 1 },
		{ _T("��"), 1 },
		{ _T("Ϸ"), 1 },
	};
	for (int i = 0; i < 12; i++){
		g_cell_list[i].bind_number = welcome[i].n;
		wcscpy_s(g_cell_list[i].bind_number_str, welcome[i].s);
	}
}

// �ѹؿ����ֺ͸��Ӱ�
void NMG_cell_bind_number() {
	int *numbers = NMG_utils_rand_numbers(0, NMG_CFG_CELL_COUNT - 1, g_game_level);
	for (int i = 0; i < g_game_level; i++){
		printf("cell[%d] bind number: %d\n", *numbers, i + 1);

		int bind_number = i + 1;
		// ������ת���ɶ�Ӧ���ַ���
		g_cell_list[*numbers].bind_number = bind_number;
		_stprintf_s(g_cell_list[*numbers].bind_number_str, 3, _T("%d"), bind_number);
		numbers++;
	}
}

// �ѹؿ����ֺ͸��ӽ��
void NMG_cell_unbind_number() {
	for (int i = 0; i < NMG_CFG_CELL_COUNT; i++){
		g_cell_list[i].bind_number = 0;
		wcscpy_s(g_cell_list[i].bind_number_str, _T(""));
	}
}

// ��Ѱ�ĸ����ӱ����
int NMG_cell_which_clicked(int x, int y) {
	for (int i = 0; i < NMG_CFG_CELL_COUNT; i++){
		NMG_MODEL_CELL cell = g_cell_list[i];
		if (cell.left <= x && cell.right >= x && cell.top <= y && cell.bottom >= y){
			return i;
		}
	}

	return -1;
}

// �жϵ������˳��
int NMG_cell_clicked(int cell_index) {
	NMG_MODEL_CELL cell = g_cell_list[cell_index];
	int number = cell.bind_number;
	if (g_game_play_number + 1 == number){
		// �����ȷ����ʾ��������
		NMG_view_cell_show_number(cell_index);
		return number;
	}

	// ������󣬷�������/��ʾ
	NMG_view_cell_show_warning(cell_index);
	return 0;
}