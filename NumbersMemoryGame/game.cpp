/*******************************************************
* ��Ϸģ�麯��
* ����ǰ׺��NMG_game_
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
    // ��Ϸ״̬��ʼ��
    g_game_status = NMG_GSTS_NO_STARTED;
    g_game_play_number = 0;
    g_game_level = NMG_CFG_START_LEVEL;
    // �������ݳ�ʼ��
    NMG_cell_data_init();
}

// ��Ϸ��ʼ��
void NMG_game_init() {
    _NMG_game_init();
    // UI��ʼ��
    NMG_view_init();
}

// ��ʼһ����Ϸ
void NMG_game_start() {
    if (g_game_status == NMG_GSTS_CAN_PLAY_NEXT || g_game_status == NMG_GSTS_NO_STARTED){
        // �Ƴ������ϵľ�����
        NMG_view_cell_remove_number();
        // ������ʱ��
        NMG_timer_start();
        // ������ݰ�
        NMG_cell_unbind_number();
        // ��������
        NMG_cell_bind_number();
        // ��ʾ�����ϵ�������
        NMG_view_cells_show_number();
        // Ԥ������ҵļ���ʱ��
        if (g_game_level > 3){
            Sleep((g_game_level - 3) * 1000);
        }
        // ��ʾ����ʱ
        NMG_view_show_countdown();
        // �Ƴ������ϵ�����
        NMG_view_cell_remove_number();
        // �����Ϣ�¼�
        flushmessage();
        // �ı���Ϸ״̬
        g_game_status = NMG_GSTS_PLAYING;
    }
}

// ������һ��
void NMG_game_next() {
    g_game_level += 1;
    g_game_status = NMG_GSTS_CAN_PLAY_NEXT;
    Sleep(400);
    // �ؿ�����
    NMG_view_update_game_level();
    NMG_game_start();
}

// ��ͣ��Ϸ
void NMG_game_pause() {
    g_game_status = NMG_GSTS_PASUING;
    // ��ʱ����ͣ
    NMG_timer_pause();
    // ��ť��ʾ����
    TCHAR label[10] = L"������Ϸ";
    NMG_view_pause_button_update(label);
}

// ������Ϸ
void NMG_game_play() {
    g_game_status = NMG_GSTS_PLAYING;
    // ��ʱ����ʼ
    NMG_timer_play();
    // ��ť��ʾ����
    TCHAR label[10] = L"��ͣ��Ϸ";
    NMG_view_pause_button_update(label);
}

// ������Ϸ
void NMG_game_reset() {
    // ��ʱ������
    NMG_timer_reset();
    // ��Ϸ������ʼ��
    _NMG_game_init();
    // UI����
    NMG_view_reset();
}