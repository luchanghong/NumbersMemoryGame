/*******************************************************
* 实用函数模块
* 函数前缀：NMG_utils_
*
* Author:   Lunixy
* Date:     2022-10-23
*******************************************************/

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int NMG_utils_is_in_array(int *numbers, int length, int number);

/*
* 随机从两个数直接取不重复的一组随机数
* 
* @param int start  起始数
* @param int end    终止数
* @param int count  随机数个数
* 
* @return int* 数组的指针
*/
int *NMG_utils_rand_numbers(int start, int end, int count) {
    int *numbers = (int *) calloc(sizeof(unsigned int), count);

    if (numbers && count <= end - start){
        int i = 0;
        srand((unsigned int)time(NULL));
        while (i < count){
             int number = rand() % (end - start + 1) + start;
             if (NMG_utils_is_in_array(numbers, i, number) == 0){
                 *(numbers + i) = number;
                 i++;
             }
        }
    }
    return numbers;
}

/*
* 判断元素是否在数组中存在
* 
* @param int* numbers   数组指针
* @param int length     数组元素个数
* @param int number     要查询的元素
* 
* @return enmu{0,1}
*/
int NMG_utils_is_in_array(int *numbers, int length, int number) {
    for (size_t i = 0; i < length; i++){
        if (*(numbers + i) == number){
            return 1;
        }
    }
    return 0;
}