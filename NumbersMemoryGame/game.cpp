/*******************************************************
* ��Ϸģ�麯��
* ����ǰ׺��NMG_game_
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

// ��Ϸ��ʼ��
void NMG_game_init() {
    NMG_view_init();
}

// ��ʼһ����Ϸ
void NMG_game_start() {
    if (g_game_status == NMG_GSTS_CAN_PLAY_NEXT || g_game_status == NMG_GSTS_NO_STARTED){
        // �ı���Ϸ״̬
        // ������ݰ�
        NMG_cell_unbind_number();
        // �Ƴ������ϵľ�����
        NMG_view_cell_remove_number();
        // ��������
        NMG_cell_bind_number();
        // ��ʾ�����ϵ�������
        NMG_view_cells_show_number();

        // ��ͣN����������֣���ҿ�ʼ���
        // bug: ������¼�������
        Sleep(3000);
        NMG_view_cell_remove_number();

        g_game_status = NMG_GSTS_PLAYING;
        //g_game_level += 1;
    }
}

// ������һ��
void NMG_game_next() {
    g_game_level += 1;
    g_game_status = NMG_GSTS_CAN_PLAY_NEXT;
    Sleep(400);
    NMG_game_start();
}