/*******************************************************
* 文件读写模块函数
* 函数前缀：NMG_data_
*
* Author:   Lunixy
* Date:     2022-10-22
*******************************************************/

#include <stdlib.h>
#include "config.h"
#include "models.h"

/*
* 排行榜数据读写
*/
// 读取排行榜
NMG_MODEL_RANK *NMG_data_rank_query() {
    NMG_MODEL_RANK *list = (NMG_MODEL_RANK *) calloc(sizeof(NMG_MODEL_RANK), 10);
    // todo: use fread to query

    return list;
}

// 更新排行榜
int NMG_data_rank_update(NMG_MODEL_RANK *list) {
    // todo: use fwrite to update

    return 1;
}

/*
* 用户设置数据读写
*/
// 读取用户设置
NMG_MODEL_SETTINGS NMG_data_settings_query() {
    NMG_MODEL_SETTINGS settings = {};
    // todo: use fread to query
    return settings;
}

// 更新用户设置
int NMG_data_settings_update(NMG_MODEL_SETTINGS settings) {
    // todo: use fwrite to update

    return 1;
}