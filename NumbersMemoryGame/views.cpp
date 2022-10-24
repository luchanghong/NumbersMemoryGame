/*******************************************************
* 窗口UI绘制
* 函数前缀：NMG_view_
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
* 窗口初始化
* 游戏区初始化
* 功能区初始化
*******************************************************/
void NMG_view_init() {
    initgraph(NMG_CFG_WINDOW_WIDTH, NMG_CFG_WINDOW_HEIGHT, EX_SHOWCONSOLE);

    // 设置背景图，并作为后面绘图的设备
    IMAGE window_bg_img;
    loadimage(&window_bg_img, _T("IMAGE"), _T("WINDOW_BG_1"), NMG_CFG_WINDOW_WIDTH, NMG_CFG_WINDOW_HEIGHT);
    SetWorkingImage(&window_bg_img);

    // 左侧游戏区域
    _NMG_view_left_init();

    // 右侧功能区域 
    rectangle(NMG_CFG_GAME_AREA_WIDTH, 0, NMG_CFG_WINDOW_WIDTH, NMG_CFG_WINDOW_HEIGHT);

    // 把绘图设备重置为窗口，并把背景图输出在窗口内
    SetWorkingImage();
    putimage(0, 0, &window_bg_img);

    // 显示游戏提示欢迎语
    _NMG_view_cell_show_welcome();

    // 事件监听
    NMG_event_listen();
}

// 左侧游戏区域初始化：填满小格子
static void _NMG_view_left_init() {
    // 初步计算格子宽高
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

    // 绘制格子
    _NMG_view_cells_init();
}


/*******************************************************
* 游戏区格子UI操作——cell
* 格子初始化
* 格子显示数字
* 格子隐藏数字
*******************************************************/
static void _NMG_view_cells_init() {
    setfillstyle(BS_DIBPATTERN, NULL, &g_cell_back_image);
    for (int i = 0; i < NMG_CFG_CELL_COUNT; i++){
        NMG_MODEL_CELL cell = g_cell_list[i];
        fillroundrect(cell.left, cell.top, cell.right, cell.bottom, NMG_CFG_CELL_RADIUS, NMG_CFG_CELL_RADIUS);
    }
}

// 单个处理：显示格子上的数字
static void _NMG_view_cell_show_number(int cell_index) {
    NMG_MODEL_CELL cell = g_cell_list[cell_index];
    RECT rect = { cell.left, cell.top, cell.right, cell.bottom };

    // 设置文字背景透明
    setbkmode(TRANSPARENT);

    LOGFONT f;
    gettextstyle(&f);						// 获取当前字体设置
    f.lfHeight = cell.height - 20;			// 设置字体高度为 48
    f.lfWeight = FW_BLACK;                  // 设置字体粗细
    wcscpy_s(f.lfFaceName, _T("黑体"));		// 设置字体为“黑体”
    f.lfQuality = ANTIALIASED_QUALITY;		// 设置正稿质量  
    settextstyle(&f);
    drawtext(cell.bind_number_str, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

// 移除格子上的数字
static void _NMG_view_cell_remove_number(int cell_index) {
    NMG_MODEL_CELL cell = g_cell_list[cell_index];
    clearroundrect(cell.left, cell.top, cell.right, cell.bottom, NMG_CFG_CELL_RADIUS, NMG_CFG_CELL_RADIUS);
    _NMG_view_cells_init();
}

// 显示全部格子的数字
void NMG_view_cells_show_number() {
    for (int i = 0; i < NMG_CFG_CELL_COUNT; i++){
        if (g_cell_list[i].bind_number > 0){
            _NMG_view_cell_show_number(i);
        }
    }
}

// 显示单个格子的数字
void NMG_view_cell_show_number(int cell_index) {
    _NMG_view_cell_show_number(cell_index);
}

// 移除格子上的数字
void NMG_view_cell_remove_number() {
    for (int i = 0; i < NMG_CFG_CELL_COUNT; i++){
        _NMG_view_cell_remove_number(i);
    }
}

// 格子变红，发出警告
void NMG_view_cell_show_warning(int cell_index) {
    NMG_MODEL_CELL cell = g_cell_list[cell_index];
    clearroundrect(cell.left, cell.top, cell.right, cell.bottom, NMG_CFG_CELL_RADIUS, NMG_CFG_CELL_RADIUS);
    // todo: 错误提示
    //fillroundrect(cell.left, cell.top, cell.right, cell.bottom, NMG_CFG_CELL_RADIUS, NMG_CFG_CELL_RADIUS);
}

// 静态函数：格子显示欢迎信息
static void _NMG_view_cell_show_welcome() {
    NMG_cell_init_welcome();
    NMG_view_cells_show_number();
}