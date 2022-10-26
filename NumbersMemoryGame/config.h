/*******************************************************
* ��Ŀ��������
* ����ǰ׺��NMG_CFG_
*
* Author:   Lunixy
* Date:     2022-10-22
*******************************************************/

// UI����
#define NMG_CFG_WINDOW_WIDTH  800       // ��Ϸ������ܿ��
#define NMG_CFG_WINDOW_HEIGHT 600       // ��Ϸ������ܸ߶� 
#define NMG_CFG_GAME_AREA_WIDTH NMG_CFG_WINDOW_HEIGHT       // ��Ϸ����Ŀ��
#define NMG_CFG_GAME_AREA_HEIGHT NMG_CFG_WINDOW_HEIGHT      // ��Ϸ����ĸ߶�

// ��Ϸ����
#define NMG_CFG_START_LEVEL         3       // ��Ϸ��ʼ����
#define NMG_CFG_CELL_ROW_COUNT      5       // ����ÿ�и��Ӹ���
#define NMG_CFG_CELL_COLUMN_COUNT   5       // ����ÿ�и��Ӹ���
#define NMG_CFG_CELL_PADDING        20      // ���̸��ӵļ��
#define NMG_CFG_CELL_RADIUS         18      // ���̸���Բ�Ǿ���
#define NMG_CFG_CELL_COUNT NMG_CFG_CELL_ROW_COUNT*NMG_CFG_CELL_COLUMN_COUNT     // ���̸�������

#define NMG_CFG_CELL_ORIGIN_WIDTH (NMG_CFG_GAME_AREA_WIDTH - NMG_CFG_CELL_PADDING)/NMG_CFG_CELL_COLUMN_COUNT    // ����ԭ���
#define NMG_CFG_CELL_ORIGIN_HEIGHT (NMG_CFG_GAME_AREA_HEIGHT - NMG_CFG_CELL_PADDING)/NMG_CFG_CELL_ROW_COUNT     // ����ԭ�߶�
#define NMG_CFG_CELL_REAL_WIDTH NMG_CFG_CELL_ORIGIN_WIDTH - NMG_CFG_CELL_PADDING        // ������ʵ���
#define NMG_CFG_CELL_REAL_HEIGHT NMG_CFG_CELL_ORIGIN_HEIGHT - NMG_CFG_CELL_PADDING      // ������ʵ�߶�

#define NMG_CFG_CELL_FONT_MAX_HEIGHT NMG_CFG_CELL_REAL_HEIGHT - 20      // �������������߶�
#define NMG_CFG_CELL_FONT_MIN_HEIGHT 10                                 // ������������С�߶�
#define NMG_CFG_CELL_FONT_HEIGHT_INTVERL 5                              // ����������仯����

#define NMG_CFG_CELL_NOTICE_IMG_PADDING 10      // ������֪ͨͼ��͸��ӵļ��
#define NMG_CFG_CELL_NOTICE_IMG_WIDTH NMG_CFG_CELL_REAL_WIDTH - NMG_CFG_CELL_NOTICE_IMG_PADDING * 2         // ������֪ͨͼ��Ŀ��
#define NMG_CFG_CELL_NOTICE_IMG_HEIGHT NMG_CFG_CELL_REAL_HEIGHT - NMG_CFG_CELL_NOTICE_IMG_PADDING * 2       // ������֪ͨͼ��ĸ߶�

// �����ļ�
#define NMG_CFG_DATA_FILE_RANK "data_rank.d"
#define NMG_CFG_DATA_FILE_SETTINGS "data_settings.d"