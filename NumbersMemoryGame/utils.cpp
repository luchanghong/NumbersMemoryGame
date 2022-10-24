/*******************************************************
* ʵ�ú���ģ��
* ����ǰ׺��NMG_utils_
*
* Author:   Lunixy
* Date:     2022-10-23
*******************************************************/

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int NMG_utils_is_in_array(int *numbers, int length, int number);

/*
* �����������ֱ��ȡ���ظ���һ�������
* 
* @param int start  ��ʼ��
* @param int end    ��ֹ��
* @param int count  ���������
* 
* @return int* �����ָ��
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
* �ж�Ԫ���Ƿ��������д���
* 
* @param int* numbers   ����ָ��
* @param int length     ����Ԫ�ظ���
* @param int number     Ҫ��ѯ��Ԫ��
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