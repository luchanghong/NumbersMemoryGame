/*******************************************************
* ����UI����
* ����ǰ׺��NMG_view_
*
* Author:   Lunixy
* Date:     2022-10-22
*******************************************************/

#include <easyx.h>
#include <conio.h>
#include <stdio.h>

#include "config.h"
#include "models.h"

extern NMG_MODEL_CELL g_cell_list[NMG_CFG_CELL_COUNT];
extern IMAGE g_cell_back_image;

extern void NMG_event_listen();
extern void NMG_cell_init_welcome();

static void _NMG_view_left_init();
static void _NMG_view_cells_init();
static void _NMG_view_cell_show_welcome();

/*******************************************************
* ���ڳ�ʼ��
* ��Ϸ����ʼ��
* ��������ʼ��
*******************************************************/
void NMG_view_init() {
    initgraph(NMG_CFG_WINDOW_WIDTH, NMG_CFG_WINDOW_HEIGHT, EX_SHOWCONSOLE);

    // ���ñ���ͼ������Ϊ�����ͼ���豸
    IMAGE window_bg_img;
    loadimage(&window_bg_img, _T("IMAGE"), _T("WINDOW_BG_1"), NMG_CFG_WINDOW_WIDTH, NMG_CFG_WINDOW_HEIGHT);
    SetWorkingImage(&window_bg_img);

    // �����Ϸ����
    _NMG_view_left_init();

    // �Ҳ๦������ 
    rectangle(NMG_CFG_GAME_AREA_WIDTH, 0, NMG_CFG_WINDOW_WIDTH, NMG_CFG_WINDOW_HEIGHT);

    // �ѻ�ͼ�豸����Ϊ���ڣ����ѱ���ͼ����ڴ�����
    SetWorkingImage();
    putimage(0, 0, &window_bg_img);

    // ��ʾ��Ϸ��ʾ��ӭ��
    _NMG_view_cell_show_welcome();

    // �¼�����
    NMG_event_listen();
}

// �����Ϸ�����ʼ��������С����
static void _NMG_view_left_init() {
    // ����������ӿ��
    int padding = NMG_CFG_CELL_PADDING;
    int size_w = NMG_CFG_CELL_ORIGIN_WIDTH;
    int size_h = NMG_CFG_CELL_ORIGIN_HEIGHT;
    
    for (int i = 0; i < NMG_CFG_CELL_ROW_COUNT; i++){
        for (int j = 0; j < NMG_CFG_CELL_COLUMN_COUNT; j++){
            int left = j * size_w + padding,
                top = i * size_h + padding,
                right = (j + 1) * size_w,
                bottom = (i + 1) * size_h;
            g_cell_list[i * NMG_CFG_CELL_ROW_COUNT + j] = { left, top, right, bottom, size_w - padding, size_h - padding, 0 };
        }
    }

    // ���Ƹ���
    _NMG_view_cells_init();
}


/*******************************************************
* ��Ϸ������UI��������cell
* ���ӳ�ʼ��
* ������ʾ����
* ������������
*******************************************************/
static void _NMG_view_cells_init() {
    setfillstyle(BS_DIBPATTERN, NULL, &g_cell_back_image);
    for (int i = 0; i < NMG_CFG_CELL_COUNT; i++){
        NMG_MODEL_CELL cell = g_cell_list[i];
        fillroundrect(cell.left, cell.top, cell.right, cell.bottom, NMG_CFG_CELL_RADIUS, NMG_CFG_CELL_RADIUS);
    }
}

// ����������ʾ�����ϵ�����
static void _NMG_view_cell_show_number(int cell_index) {
    NMG_MODEL_CELL cell = g_cell_list[cell_index];
    RECT rect = { cell.left, cell.top, cell.right, cell.bottom };

    // �������ֱ���͸��
    setbkmode(TRANSPARENT);

    LOGFONT f;
    gettextstyle(&f);						// ��ȡ��ǰ��������
    f.lfHeight = cell.height - 20;			// ��������߶�Ϊ 48
    f.lfWeight = FW_BLACK;                  // ���������ϸ
    wcscpy_s(f.lfFaceName, _T("����"));		// ��������Ϊ�����塱
    f.lfQuality = ANTIALIASED_QUALITY;		// ������������  
    settextstyle(&f);
    drawtext(cell.bind_number_str, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

// �Ƴ������ϵ�����
static void _NMG_view_cell_remove_number(int cell_index) {
    NMG_MODEL_CELL cell = g_cell_list[cell_index];
    clearroundrect(cell.left, cell.top, cell.right, cell.bottom, NMG_CFG_CELL_RADIUS, NMG_CFG_CELL_RADIUS);
    _NMG_view_cells_init();
}

// ��ʾȫ�����ӵ�����
void NMG_view_cells_show_number() {
    for (int i = 0; i < NMG_CFG_CELL_COUNT; i++){
        if (g_cell_list[i].bind_number > 0){
            _NMG_view_cell_show_number(i);
        }
    }
}

// ��ʾ�������ӵ�����
void NMG_view_cell_show_number(int cell_index) {
    _NMG_view_cell_show_number(cell_index);
}

// �Ƴ������ϵ�����
void NMG_view_cell_remove_number() {
    for (int i = 0; i < NMG_CFG_CELL_COUNT; i++){
        _NMG_view_cell_remove_number(i);
    }
}

// ���ӱ�죬��������
void NMG_view_cell_show_warning(int cell_index) {
    NMG_MODEL_CELL cell = g_cell_list[cell_index];
    clearroundrect(cell.left, cell.top, cell.right, cell.bottom, NMG_CFG_CELL_RADIUS, NMG_CFG_CELL_RADIUS);
    // todo: ������ʾ
    //fillroundrect(cell.left, cell.top, cell.right, cell.bottom, NMG_CFG_CELL_RADIUS, NMG_CFG_CELL_RADIUS);
}

// ��̬������������ʾ��ӭ��Ϣ
static void _NMG_view_cell_show_welcome() {
    NMG_cell_init_welcome();
    NMG_view_cells_show_number();
}