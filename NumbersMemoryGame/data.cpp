/*******************************************************
* �ļ���дģ�麯��
* ����ǰ׺��NMG_data_
*
* Author:   Lunixy
* Date:     2022-10-22
*******************************************************/

#include <stdlib.h>
#include "config.h"
#include "models.h"

/*
* ���а����ݶ�д
*/
// ��ȡ���а�
NMG_MODEL_RANK *NMG_data_rank_query() {
    NMG_MODEL_RANK *list = (NMG_MODEL_RANK *) calloc(sizeof(NMG_MODEL_RANK), 10);
    // todo: use fread to query

    return list;
}

// �������а�
int NMG_data_rank_update(NMG_MODEL_RANK *list) {
    // todo: use fwrite to update

    return 1;
}

/*
* �û��������ݶ�д
*/
// ��ȡ�û�����
NMG_MODEL_SETTINGS NMG_data_settings_query() {
    NMG_MODEL_SETTINGS settings = {};
    // todo: use fread to query
    return settings;
}

// �����û�����
int NMG_data_settings_update(NMG_MODEL_SETTINGS settings) {
    // todo: use fwrite to update

    return 1;
}