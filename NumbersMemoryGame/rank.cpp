/*******************************************************
* 排行榜模块函数
* 函数前缀：NMG_rank_
*
* Author:   Lunixy
* Date:     2022-10-22
*******************************************************/

#include <stdlib.h>
#include "models.h"

extern NMG_MODEL_RANK *NMG_data_rank_query();
extern int NMG_data_rank_update(NMG_MODEL_RANK *list);

/*
* 读取文件 && 获取排行榜TOP10
* 
* 返回排行榜数组指针
*/
NMG_MODEL_RANK *NMG_rank_top_10() {
    return NMG_data_rank_query();
}

/*
* 排行榜插入一条数据 && 写入文件
* 
* 返回新的排行榜数组指针
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