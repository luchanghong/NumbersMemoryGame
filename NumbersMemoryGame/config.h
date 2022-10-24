/*******************************************************
* 项目配置中心
* 常量前缀：NMG_CFG_
*
* Author:   Lunixy
* Date:     2022-10-22
*******************************************************/

// UI窗口
#define NMG_CFG_WINDOW_WIDTH  800       // 游戏界面的总宽度
#define NMG_CFG_WINDOW_HEIGHT 600       // 游戏界面的总高度 
#define NMG_CFG_GAME_AREA_WIDTH NMG_CFG_WINDOW_HEIGHT       // 游戏区域的宽度
#define NMG_CFG_GAME_AREA_HEIGHT NMG_CFG_WINDOW_HEIGHT      // 游戏区域的高度

// 游戏区域
#define NMG_CFG_START_LEVEL         3       // 游戏起始关数
#define NMG_CFG_CELL_ROW_COUNT      5       // 棋盘每行格子个数
#define NMG_CFG_CELL_COLUMN_COUNT   5       // 棋盘每列格子个数
#define NMG_CFG_CELL_PADDING        20      // 棋盘格子的间距
#define NMG_CFG_CELL_RADIUS         18      // 棋盘格子圆角距离
#define NMG_CFG_CELL_COUNT NMG_CFG_CELL_ROW_COUNT*NMG_CFG_CELL_COLUMN_COUNT     // 棋盘格子总数

#define NMG_CFG_CELL_ORIGIN_WIDTH (NMG_CFG_GAME_AREA_WIDTH - NMG_CFG_CELL_PADDING)/NMG_CFG_CELL_COLUMN_COUNT    // 格子原宽度
#define NMG_CFG_CELL_ORIGIN_HEIGHT (NMG_CFG_GAME_AREA_HEIGHT - NMG_CFG_CELL_PADDING)/NMG_CFG_CELL_ROW_COUNT     // 格子原高度
#define NMG_CFG_CELL_REAL_WIDTH NMG_CFG_CELL_ORIGIN_WIDTH - NMG_CFG_CELL_PADDING        // 格子真实宽度
#define NMG_CFG_CELL_REAL_HEIGHT NMG_CFG_CELL_ORIGIN_HEIGHT - NMG_CFG_CELL_PADDING      // 格子真实高度

#define NMG_CFG_CELL_FONT_MAX_HEIGHT NMG_CFG_CELL_REAL_HEIGHT - 20      // 格子上字体最大高度
#define NMG_CFG_CELL_FONT_MIN_HEIGHT 10                                 // 格子上字体最小高度
#define NMG_CFG_CELL_FONT_HEIGHT_INTVERL 5                              // 格子上字体变化幅度

#define NMG_CFG_CELL_NOTICE_IMG_PADDING 10      // 格子上通知图标和格子的间距
#define NMG_CFG_CELL_NOTICE_IMG_WIDTH NMG_CFG_CELL_REAL_WIDTH - NMG_CFG_CELL_NOTICE_IMG_PADDING * 2         // 格子上通知图标的宽度
#define NMG_CFG_CELL_NOTICE_IMG_HEIGHT NMG_CFG_CELL_REAL_HEIGHT - NMG_CFG_CELL_NOTICE_IMG_PADDING * 2       // 格子上通知图标的高度

// 数据文件
#define NMG_CFG_DATA_FILE_RANK "data_rank.d"
#define NMG_CFG_DATA_FILE_SETTINGS "data_settings.d"