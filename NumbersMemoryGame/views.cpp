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

extern int g_game_level;
extern IMAGE g_cell_back_image;
extern NMG_MODEL_BUTTON g_buttons[10];
extern NMG_MODEL_CELL g_cell_list[NMG_CFG_CELL_COUNT];

extern void NMG_cell_init_welcome();
extern void NMG_utils_draw_button(int x1, int y1, int x2, int y2, TCHAR *label, NMG_CFG_BUTTON_TYPE type);
extern void NMG_utils_draw_alpha_image(IMAGE *image, int x, int y, int width, int height, int pic_x, int pic_y, double AA = 1);

static void _NMG_view_left_init();
static void _NMG_view_right_init();
static void _NMG_view_cells_init();
static void _NMG_view_show_game_level();
void NMG_view_cell_show_welcome();
void NMG_view_show_game_timer(int hour, int min, int sec);
void NMG_view_show_buttons();

static IMAGE game_area_img(NMG_CFG_GAME_AREA_WIDTH, NMG_CFG_GAME_AREA_HEIGHT);
/*******************************************************
* 窗口初始化
* 游戏区初始化
* 功能区初始化
*******************************************************/
static void _NMG_view_attributes() {
    // 设置窗口标题
    HWND win_handle = GetHWnd();
    SetWindowText(win_handle, L"数字记忆游戏");
}

void NMG_view_init() {
    // 窗口属性设置
    _NMG_view_attributes();

    // 设置绘制区域为默认窗口
    SetWorkingImage();

    // 设置背景图，并作为后面绘图的设备
    IMAGE window_bg_img;
    loadimage(&window_bg_img, _T("IMAGE"), _T("WINDOW_BG_1"), NMG_CFG_WINDOW_WIDTH, NMG_CFG_WINDOW_HEIGHT);
    putimage(0, 0, &window_bg_img);

    // 右侧功能区域
    _NMG_view_right_init();

    // 左侧游戏区域，设置绘制区域为游戏区
    SetWorkingImage(&game_area_img);
    putimage(0, 0, &window_bg_img);
    _NMG_view_left_init();

    // 设置绘制区域为窗口
    SetWorkingImage();
    putimage(0, 0, &game_area_img);

    // 显示游戏提示欢迎语，切换游戏绘制区域为游戏区
    NMG_view_cell_show_welcome();
}

void NMG_view_reset() {
    _NMG_view_cells_init();
    NMG_view_cell_show_welcome();
}

// 左侧游戏区域初始化：填满小格子
static void _NMG_view_left_init() {
    // 绘制格子
    _NMG_view_cells_init();
}

// 右侧区域初始化
static void _NMG_view_right_init() {
    //setfillstyle(BS_HATCHED, HS_CROSS);
    //rectangle(NMG_CFG_GAME_AREA_WIDTH, 0, NMG_CFG_WINDOW_WIDTH, NMG_CFG_WINDOW_HEIGHT);

    _NMG_view_show_game_level();
    NMG_view_show_game_timer(0, 0, 0);
    NMG_view_show_buttons();
}

/*******************************************************
* 右侧区域UI
* 关卡
* 倒计时
* 排行榜
* 设置中心
*******************************************************/
// 关卡展示
static void _NMG_view_show_game_level() {
    // 关卡区域坐标
    int rect_left = NMG_CFG_GAME_AREA_WIDTH + NMG_CFG_RIGHT_AREA_PADDING,
        rect_top = NMG_CFG_RIGHT_AREA_PADDING,
        rect_right = NMG_CFG_WINDOW_WIDTH - NMG_CFG_RIGHT_AREA_PADDING,
        rect_bottom = NMG_CFG_CELL_REAL_HEIGHT + NMG_CFG_RIGHT_AREA_PADDING;
    int width = rect_right - rect_left,
        height = rect_bottom - rect_top;

    setfillstyle(0);
    setbkmode(TRANSPARENT);
    setfillcolor(RGB(200, 30, 90));
    solidroundrect(rect_left, rect_top, rect_right, rect_bottom, 20, 20);
    
    // 分割线
    line(rect_right - 30, rect_top, rect_left + 30, rect_bottom);
    // 当前关卡区域和总关卡数量区域
    RECT rect1 = { rect_left, rect_top, rect_right - width / 2, rect_bottom - 10 };
    RECT rect2 = { rect_left + width / 2, rect_top, rect_right, rect_bottom - 10 };
    TCHAR current_level[3];
    _stprintf_s(current_level, 3, _T("%d"), g_game_level); 

    LOGFONT font;
    gettextstyle(&font);						// 获取当前字体设置
    font.lfWeight = FW_BLACK;                   // 设置字体粗细
    font.lfQuality = ANTIALIASED_QUALITY;		// 设置正稿质量
    wcscpy_s(font.lfFaceName, _T("黑体"));		// 设置字体为“黑体”
    // 输出当前关卡文字
    font.lfHeight = height / 2;
    settextcolor(WHITE);
    settextstyle(&font);
    drawtext(current_level, &rect1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    // 输出总关卡文字
    font.lfHeight = height / 3;
    settextcolor(LIGHTGRAY);
    settextstyle(&font);
    drawtext(L"20关", &rect2, DT_CENTER | DT_BOTTOM | DT_SINGLELINE);
}

// 计时器展示
void NMG_view_show_game_timer(int hour, int min, int sec) {
    int rect_left = NMG_CFG_GAME_AREA_WIDTH + NMG_CFG_RIGHT_AREA_PADDING,
        rect_top = NMG_CFG_CELL_REAL_HEIGHT + 2 * NMG_CFG_RIGHT_AREA_PADDING,
        rect_right = NMG_CFG_WINDOW_WIDTH - NMG_CFG_RIGHT_AREA_PADDING,
        rect_bottom = 2 * (NMG_CFG_CELL_REAL_HEIGHT + NMG_CFG_RIGHT_AREA_PADDING);
    int height = rect_bottom - rect_top;

    TCHAR timer_string[9];
    _stprintf_s(timer_string, 9, _T("%02d:%02d:%02d"), hour, min, sec);
    NMG_utils_draw_button(rect_left, rect_top, rect_right, rect_bottom, timer_string, NMG_CFG_BUTTON_SUCESS);
}

// 功能按钮展示
void NMG_view_show_buttons() {
    int rect_left = NMG_CFG_GAME_AREA_WIDTH + NMG_CFG_RIGHT_AREA_PADDING,
        rect_top = 2 * NMG_CFG_CELL_REAL_HEIGHT + 2 * NMG_CFG_RIGHT_AREA_PADDING,
        rect_right = NMG_CFG_WINDOW_WIDTH - NMG_CFG_RIGHT_AREA_PADDING,
        rect_bottom = 3 * (NMG_CFG_CELL_REAL_HEIGHT + NMG_CFG_RIGHT_AREA_PADDING);
     int height = rect_bottom - rect_top;

    TCHAR pause[10] = L"暂停游戏";
    g_buttons[0] = { "pause", RECT{rect_left, rect_top, rect_right, rect_bottom - height / 2 - 5}};
    NMG_utils_draw_button(rect_left, rect_top, rect_right, rect_bottom - height / 2 - 5, pause, NMG_CFG_BUTTON_WARNING);
    TCHAR reset[10] = L"重新开始";
    g_buttons[1] = { "reset", RECT{rect_left, rect_top + height / 2 + 5, rect_right, rect_bottom}};

    NMG_utils_draw_button(rect_left, rect_top + height / 2 + 5, rect_right, rect_bottom, reset, NMG_CFG_BUTTON_DANGER);
}

// 暂停按钮更新
void NMG_view_pause_button_update(TCHAR label[10]) {
    NMG_MODEL_BUTTON button = g_buttons[0];
    NMG_utils_draw_button(button.rect.left, button.rect.top, button.rect.right, button.rect.bottom, label, NMG_CFG_BUTTON_WARNING);
}

// 关卡更新
void NMG_view_update_game_level() {
    _NMG_view_show_game_level();
}

/*******************************************************
* 游戏区格子UI操作——cell
* 格子初始化
* 格子显示数字
* 格子隐藏数字
*******************************************************/
static LOGFONT _NMG_view_cell_number_font() {
    // 设置文字背景透明
    setbkmode(TRANSPARENT);
    settextcolor(WHITE);

    LOGFONT font;
    gettextstyle(&font);						// 获取当前字体设置
    font.lfWeight = FW_BLACK;                   // 设置字体粗细
    font.lfQuality = ANTIALIASED_QUALITY;		// 设置正稿质量  
    wcscpy_s(font.lfFaceName, _T("黑体"));		// 设置字体为“黑体”
    return font;
}

static void _NMG_view_cells_init() {
    setfillstyle(BS_DIBPATTERN, NULL, &g_cell_back_image);
    for (int i = 0; i < NMG_CFG_CELL_COUNT; i++){
        NMG_MODEL_CELL cell = g_cell_list[i];
        solidroundrect(cell.left, cell.top, cell.right, cell.bottom, NMG_CFG_CELL_RADIUS, NMG_CFG_CELL_RADIUS);
    }
}

// 根据序号初始化一个格子
static void _NMG_view_cell_init(int cell_index) {
    NMG_MODEL_CELL cell = g_cell_list[cell_index];

    setfillstyle(BS_DIBPATTERN, NULL, &g_cell_back_image);
    solidroundrect(cell.left, cell.top, cell.right, cell.bottom, NMG_CFG_CELL_RADIUS, NMG_CFG_CELL_RADIUS);
}

// 显示格子上的数字
static void _NMG_view_cell_show_number(int cell_index, int with_animation = 1) {
    NMG_MODEL_CELL cell = g_cell_list[cell_index];
    LOGFONT font = _NMG_view_cell_number_font();
    RECT rect = { cell.left, cell.top, cell.right, cell.bottom };

    // 不需要过度动画
    if (!with_animation){
        font.lfHeight = NMG_CFG_CELL_FONT_MAX_HEIGHT;
        settextstyle(&font);
        drawtext(cell.bind_number_str, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        return;
    }

    // 过度动画，由小变大
    BeginBatchDraw();
    for (int height = NMG_CFG_CELL_FONT_MIN_HEIGHT; height < NMG_CFG_CELL_FONT_MAX_HEIGHT; height += 5){
        _NMG_view_cell_init(cell_index);

        font.lfHeight = height;
        settextstyle(&font);
        drawtext(cell.bind_number_str, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        FlushBatchDraw();
        Sleep(1);
    }
    font.lfHeight = NMG_CFG_CELL_FONT_MAX_HEIGHT;
    settextstyle(&font);
    drawtext(cell.bind_number_str, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    EndBatchDraw();
}

// 移除格子上的数字
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
        Sleep(1);
    }
    // 真正移除数字
    _NMG_view_cell_init(cell_index);
    EndBatchDraw();
}

// 显示全部格子的数字
void NMG_view_cells_show_number() {
    for (int i = 0; i < NMG_CFG_CELL_COUNT; i++){
        if (g_cell_list[i].bind_number > 0){
            _NMG_view_cell_show_number(i);
        }
    }
}

// 显示全部格子的数字
void NMG_view_cells_show_number_no_animation() {
    for (int i = 0; i < NMG_CFG_CELL_COUNT; i++){
        if (g_cell_list[i].bind_number > 0){
            _NMG_view_cell_show_number(i, 0);
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
        if (g_cell_list[i].bind_number > 0){
            _NMG_view_cell_remove_number(i);
        }
    }
}

// 格子显示错误提示图标
void NMG_view_cell_show_warning(int cell_index) {
    NMG_MODEL_CELL cell = g_cell_list[cell_index];
    IMAGE wrong_image;
    BeginBatchDraw();
    for (int padding = cell.width / 2; padding >= NMG_CFG_CELL_NOTICE_IMG_PADDING; padding -= 3){
        int img_width = cell.width - 2 * padding;
        int img_height = cell.height - 2 * padding;
        // 格子初始化，图标消失
        _NMG_view_cell_init(cell_index);
        loadimage(&wrong_image, _T("images\\wrong_face.png"), img_width, img_height);
        NMG_utils_draw_alpha_image(&wrong_image, cell.left + padding, cell.top + padding, img_width, img_height, 0, 0);
        Sleep(20);
        FlushBatchDraw();
    }
    EndBatchDraw();
    Sleep(200);
    _NMG_view_cell_init(cell_index);
}

// 静态函数：格子显示欢迎信息
void NMG_view_cell_show_welcome() {
    NMG_cell_init_welcome();
    NMG_view_cells_show_number();
}

/*******************************************************
* 游戏区UI
* 倒计时
*******************************************************/
static LOGFONT _NMG_view_countdown_font() {
    setbkmode(TRANSPARENT);
    settextcolor(YELLOW);

    LOGFONT font;
    gettextstyle(&font);						// 获取当前字体设置
    font.lfWeight = FW_BLACK;                   // 设置字体粗细
    wcscpy_s(font.lfFaceName, _T("Consolas"));		// 设置字体为“黑体”
    font.lfQuality = ANTIALIASED_QUALITY;		// 设置正稿质量
    return font;
}

// 显示倒计时
void NMG_view_show_countdown() {
    LOGFONT font = _NMG_view_countdown_font();
    RECT rect = { 0, 0, NMG_CFG_GAME_AREA_WIDTH, NMG_CFG_GAME_AREA_HEIGHT };

    int sleep_time = 1000;      // 延迟的毫秒时间
    int end_height = 40;        // 字体最小粗细值
    int height_interval = 10;   // 字体粗细值衰减幅度

    BeginBatchDraw();
    for (int i = 3; i > 0; i--){
        int start_height = NMG_CFG_GAME_AREA_HEIGHT / 2;
        int sleep_interval = sleep_time / ((start_height - end_height) / height_interval);

        while (start_height > end_height){
            // 重绘游戏区背景图以及显示的数字
            putimage(0, 0, &game_area_img);
            NMG_view_cells_show_number_no_animation();
            // 输出倒计时数字
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
    // 重绘游戏区背景图以及显示的数字
    putimage(0, 0, &game_area_img);
    NMG_view_cells_show_number_no_animation();
    EndBatchDraw();
}