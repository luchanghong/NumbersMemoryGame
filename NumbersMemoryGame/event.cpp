/*******************************************************
* ��ꡢ�����¼����
* ����ǰ׺��NMG_event_
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

// ����������¼�����
static void _NMG_event_mouse_left_down(ExMessage msg) {
    // ��Ϸ�е�״̬�£�ֻ��Ӧ������ӵ��¼�
    if (g_game_status == NMG_GSTS_PLAYING){
        int cell_index = NMG_cell_which_clicked(msg.x, msg.y);
        printf("clicked cell index: %d\n", cell_index);
        // �Ƿ�������
        if (cell_index < 0){
            return;
        }
        // �жϵ��˳��
        int number = NMG_cell_clicked(cell_index);
        if (number == 0){
            // todo: �Ƿ�ֱ�ӽ�������Ϸ
            return;
        }
        // �ؿ���ɣ�������һ��
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

// ����
void NMG_event_listen() {
    ExMessage m;

    while (true){
        // ��ȡһ�����򰴼���Ϣ
        m = getmessage(EX_MOUSE | EX_KEY);

        switch (m.message){
        case WM_MOUSEMOVE:
            // ����ƶ���ʱ�򻭺�ɫ��С��
            putpixel(m.x, m.y, RED);
            break;

        case WM_LBUTTONDOWN:
            _NMG_event_mouse_left_down(m);
            break;

        case WM_KEYDOWN:
            if (m.vkcode == VK_ESCAPE){
                closegraph();	// �� ESC ���˳�����
            }
        }
    }
}