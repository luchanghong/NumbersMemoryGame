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

extern int g_game_level;
extern IMAGE g_cell_back_image;
extern NMG_MODEL_CELL g_cell_list[NMG_CFG_CELL_COUNT];

extern void NMG_event_listen();
extern void NMG_cell_init_welcome();
extern void drawAlpha(IMAGE *image, int x, int y, int width, int height, int pic_x, int pic_y, double AA = 1);

static void _NMG_view_left_init();
static void _NMG_view_cells_init();
static void _NMG_view_cell_show_welcome();

static IMAGE game_area_img(NMG_CFG_GAME_AREA_WIDTH, NMG_CFG_GAME_AREA_HEIGHT);
/*******************************************************
* ���ڳ�ʼ��
* ��Ϸ����ʼ��
* ��������ʼ��
*******************************************************/
void NMG_view_init() {
    initgraph(NMG_CFG_WINDOW_WIDTH, NMG_CFG_WINDOW_HEIGHT, EX_SHOWCONSOLE);
    // ���û�������ΪĬ�ϴ���
    SetWorkingImage();

    // ���ñ���ͼ������Ϊ�����ͼ���豸
    IMAGE window_bg_img;
    loadimage(&window_bg_img, _T("IMAGE"), _T("WINDOW_BG_1"), NMG_CFG_WINDOW_WIDTH, NMG_CFG_WINDOW_HEIGHT);
    putimage(0, 0, &window_bg_img);

    // �Ҳ๦������
    //setfillstyle(BS_HATCHED, HS_CROSS);
    rectangle(NMG_CFG_GAME_AREA_WIDTH, 0, NMG_CFG_WINDOW_WIDTH, NMG_CFG_WINDOW_HEIGHT);

    // �����Ϸ�������û�������Ϊ��Ϸ��
    SetWorkingImage(&game_area_img);
    putimage(0, 0, &window_bg_img);
    _NMG_view_left_init();

    // ���û�������Ϊ����
    SetWorkingImage();
    putimage(0, 0, &game_area_img);

    // ��ʾ��Ϸ��ʾ��ӭ��л���Ϸ��������Ϊ��Ϸ��
    _NMG_view_cell_show_welcome();

    // �¼�����
    NMG_event_listen();

    //EndBatchDraw();
}

// �����Ϸ�����ʼ��������С����
static void _NMG_view_left_init() {
    // ���Ƹ���
    _NMG_view_cells_init();
}


/*******************************************************
* ��Ϸ������UI��������cell
* ���ӳ�ʼ��
* ������ʾ����
* ������������
*******************************************************/
static LOGFONT _NMG_view_cell_number_font() {
    // �������ֱ���͸��
    setbkmode(TRANSPARENT);
    settextcolor(WHITE);

    LOGFONT font;
    gettextstyle(&font);						// ��ȡ��ǰ��������
    font.lfWeight = FW_BLACK;                   // ���������ϸ
    font.lfQuality = ANTIALIASED_QUALITY;		// ������������  
    wcscpy_s(font.lfFaceName, _T("����"));		// ��������Ϊ�����塱
    return font;
}

static void _NMG_view_cells_init() {
    setfillstyle(BS_DIBPATTERN, NULL, &g_cell_back_image);
    for (int i = 0; i < NMG_CFG_CELL_COUNT; i++){
        NMG_MODEL_CELL cell = g_cell_list[i];
        fillroundrect(cell.left, cell.top, cell.right, cell.bottom, NMG_CFG_CELL_RADIUS, NMG_CFG_CELL_RADIUS);
    }
}

// ������ų�ʼ��һ������
static void _NMG_view_cell_init(int cell_index) {
    NMG_MODEL_CELL cell = g_cell_list[cell_index];
    setfillstyle(BS_DIBPATTERN, NULL, &g_cell_back_image);
    fillroundrect(cell.left, cell.top, cell.right, cell.bottom, NMG_CFG_CELL_RADIUS, NMG_CFG_CELL_RADIUS);
}

// ��ʾ�����ϵ�����
static void _NMG_view_cell_show_number(int cell_index, int with_animation = 1) {
    NMG_MODEL_CELL cell = g_cell_list[cell_index];
    LOGFONT font = _NMG_view_cell_number_font();
    RECT rect = { cell.left, cell.top, cell.right, cell.bottom };

    // ����Ҫ���ȶ���
    if (!with_animation){
        font.lfHeight = NMG_CFG_CELL_FONT_MAX_HEIGHT;
        settextstyle(&font);
        drawtext(cell.bind_number_str, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        return;
    }

    // ���ȶ�������С���
    BeginBatchDraw();
    for (int height = NMG_CFG_CELL_FONT_MIN_HEIGHT; height < NMG_CFG_CELL_FONT_MAX_HEIGHT; height += 5){
        _NMG_view_cell_init(cell_index);

        font.lfHeight = height;
        settextstyle(&font);
        drawtext(cell.bind_number_str, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        FlushBatchDraw();
        Sleep(10);
    }
    font.lfHeight = NMG_CFG_CELL_FONT_MAX_HEIGHT;
    settextstyle(&font);
    drawtext(cell.bind_number_str, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    EndBatchDraw();
}

// �Ƴ������ϵ�����
static void _NMG_view_cell_remove_number(int cell_index) {
    NMG_MODEL_CELL cell = g_cell_list[cell_index];
    LOGFONT font = _NMG_view_cell_number_font();
    RECT rect = { cell.left, cell.top, cell.right, cell.bottom };

    BeginBatchDraw();
    for (int height = NMG_CFG_CELL_FONT_MAX_HEIGHT; height >= 0; height -= NMG_CFG_CELL_FONT_HEIGHT_INTVERL){
        _NMG_view_cell_init(cell_index);
        font.lfHeight = height;
        settextstyle(&font);
        drawtext(cell.bind_number_str, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        FlushBatchDraw();
        Sleep(10);
    }
    // �����Ƴ�����
    clearroundrect(cell.left, cell.top, cell.right, cell.bottom, NMG_CFG_CELL_RADIUS, NMG_CFG_CELL_RADIUS);
    _NMG_view_cell_init(cell_index);
    EndBatchDraw();
}

// ��ʾȫ�����ӵ�����
void NMG_view_cells_show_number() {
    for (int i = 0; i < NMG_CFG_CELL_COUNT; i++){
        if (g_cell_list[i].bind_number > 0){
            _NMG_view_cell_show_number(i);
        }
    }
}

// ��ʾȫ�����ӵ�����
void NMG_view_cells_show_number_no_animation() {
    for (int i = 0; i < NMG_CFG_CELL_COUNT; i++){
        if (g_cell_list[i].bind_number > 0){
            _NMG_view_cell_show_number(i, 0);
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
        if (g_cell_list[i].bind_number > 0){
            _NMG_view_cell_remove_number(i);
        }
    }
}

// ������ʾ������ʾͼ��
void NMG_view_cell_show_warning(int cell_index) {
    NMG_MODEL_CELL cell = g_cell_list[cell_index];
    IMAGE wrong_image;
    BeginBatchDraw();
    for (int padding = cell.width / 2; padding >= NMG_CFG_CELL_NOTICE_IMG_PADDING; padding -= 3){
        int img_width = cell.width - 2 * padding;
        int img_height = cell.height - 2 * padding;
        // ���ӳ�ʼ����ͼ����ʧ
        _NMG_view_cell_init(cell_index);
        loadimage(&wrong_image, _T("images\\wrong_face.png"), img_width, img_height);
        drawAlpha(&wrong_image, cell.left + padding, cell.top + padding, img_width, img_height, 0, 0);
        Sleep(20);
        FlushBatchDraw();
    }
    EndBatchDraw();
    Sleep(200);
    _NMG_view_cell_init(cell_index);
}

// ��̬������������ʾ��ӭ��Ϣ
static void _NMG_view_cell_show_welcome() {
    NMG_cell_init_welcome();
    NMG_view_cells_show_number();
}

/*******************************************************
* ��Ϸ��UI
* ����ʱ
*******************************************************/
static LOGFONT _NMG_view_countdown_font() {
    setbkmode(TRANSPARENT);
    settextcolor(YELLOW);

    LOGFONT font;
    gettextstyle(&font);						// ��ȡ��ǰ��������
    font.lfWeight = FW_BLACK;                   // ���������ϸ
    wcscpy_s(font.lfFaceName, _T("����"));		// ��������Ϊ�����塱
    font.lfQuality = ANTIALIASED_QUALITY;		// ������������
    return font;
}

// ��ʾ����ʱ
void NMG_view_show_countdown() {
    LOGFONT font = _NMG_view_countdown_font();
    RECT rect = { 0, 0, NMG_CFG_GAME_AREA_WIDTH, NMG_CFG_GAME_AREA_HEIGHT };

    int sleep_time = 1000;      // �ӳٵĺ���ʱ��
    int end_height = 40;        // ������С��ϸֵ
    int height_interval = 10;   // �����ϸֵ˥������

    // ���3���ٿ�ʼ��ʾ����ʱ
    if (g_game_level > 3){
        Sleep(1000 *(g_game_level - 3));
    }

    BeginBatchDraw();
    for (int i = 3; i > 0; i--){
        int start_height = NMG_CFG_GAME_AREA_WIDTH / 2;

        int sleep_interval = sleep_time / ((start_height - end_height) / height_interval);

        while (start_height > end_height){
            // �ػ���Ϸ������ͼ�Լ���ʾ������
            putimage(0, 0, &game_area_img);
            NMG_view_cells_show_number_no_animation();
            // �������ʱ����
            TCHAR number_str[3];
            _stprintf_s(number_str, 3, _T("%d"), i);
            font.lfHeight = start_height;
            settextcolor(YELLOW);
            settextstyle(&font);
            drawtext(number_str, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
            start_height -= height_interval;
            Sleep(sleep_interval);
            FlushBatchDraw();
        }
    }
    // �ػ���Ϸ������ͼ�Լ���ʾ������
    putimage(0, 0, &game_area_img);
    NMG_view_cells_show_number_no_animation();
    EndBatchDraw();
}