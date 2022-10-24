/*******************************************************
* 语言包模块函数
* 函数前缀：NMG_language_
*
* Author:   Lunixy
* Date:     2022-10-22
*******************************************************/

#include "models.h"
#include <stdlib.h>

/*
* 获取语言包列表
*/
NMG_MODEL_SETTINGS_LANGUAGE_TYPE *NMG_language_pack_list() {
    NMG_MODEL_SETTINGS_LANGUAGE_TYPE *list = (NMG_MODEL_SETTINGS_LANGUAGE_TYPE *) calloc(sizeof(NMG_MODEL_SETTINGS_LANGUAGE_TYPE), 2);
    if (list){
        list[0] = { "中文", 0 };
        list[1] = { "English", 1 };
    }
 
    return list;
}

// todo: 多语言数据建立
//typedef struct{
//    char title[40];
//    char message_warn[100];
//} NMG_LANGUAGE_PACK[2];