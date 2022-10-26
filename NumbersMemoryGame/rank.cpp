/*******************************************************
* ���а�ģ�麯��
* ����ǰ׺��NMG_rank_
*
* Author:   Lunixy
* Date:     2022-10-22
*******************************************************/

#include <stdlib.h>
#include "models.h"

extern NMG_MODEL_RANK *NMG_data_rank_query();
extern int NMG_data_rank_update(NMG_MODEL_RANK *list);

/*
* ��ȡ�ļ� && ��ȡ���а�TOP10
* 
* �������а�����ָ��
*/
NMG_MODEL_RANK *NMG_rank_top_10() {
    return NMG_data_rank_query();
}

/*
* ���а����һ������ && д���ļ�
* 
* �����µ����а�����ָ��
*/
NMG_MODEL_RANK *NMG_rank_insert(NMG_MODEL_RANK rank) {
    NMG_MODEL_RANK *list = (NMG_MODEL_RANK *) calloc(sizeof(NMG_MODEL_RANK), 10);
    list = NMG_rank_top_10();
    // todo: insert && update

    int res = NMG_data_rank_update(list);
    if (res){
        return list;
    }

    return nullptr;
}