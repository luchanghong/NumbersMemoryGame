/*******************************************************
* ��Ŀ�е�����ģ��
* ����ģ��ǰ׺��NMG_MODEL_
* 
* Author:   Lunixy
* Date:     2022-10-22
*******************************************************/

#include <easyx.h>

/*
* ���а�����ģ��
*/

//struct NMG_model_rank {
//    char nickername[20];
//    int take_time;
//};
// ʹ��typedef�����壬ʹ��ʱ���ӱ��
typedef struct{
    char nickername[20];
    int take_time;
} NMG_MODEL_RANK;

/*
* ��Ϸ�������ģ��
*/
// ���̸���
typedef struct{
    int left;
    int top;
    int right;
    int bottom;
    int width;
    int height;
    int bind_number;
    TCHAR bind_number_str[3];
} NMG_MODEL_CELL;

typedef enum {
    NMG_GSTS_NO_STARTED,		// δ��ʼ
    NMG_GSTS_PLAYING,		    // ������
    NMG_GSTS_CAN_PLAY_NEXT,	    // ���Խ�����һ��
    NMG_GSTS_CLEARANCE,		    // ��ͨ��
} NMG_MODEL_GAME_STATUS;

/*
* ����ѡ������ģ��
*/
typedef struct{
    int game_sound;     // ��Ϸ��Ч����
    int bgm_sound;      // �������ֿ���
    char *bg_image_src; // ����ͼ��ַ
} NMG_MODEL_SETTINGS;

// ������
typedef enum {
    nmg_settings_game_sound,
    nmg_settings_bgm_sound,
    nmg_settings_bg_image_src
} NMG_MODEL_SETTINGS_OPTION;

// �������ֵ�ж����������ͣ�����union��������
typedef union{
    int int_value;      // �������͵�ֵ
    char *str_value;    // �ַ������͵�ֵ
} NMG_MODEL_SETTINGS_VALUE;

/*
* ��������
*/
typedef struct{
    char name[30];
    int code;
} NMG_MODEL_SETTINGS_LANGUAGE_TYPE;