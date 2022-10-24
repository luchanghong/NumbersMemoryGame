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
#include <easyx.h>

#include "config.h"

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

// 绘图函数，补充透明度 AA
void drawAlpha(IMAGE *image, int x, int y, int width, int height, int pic_x, int pic_y, double AA = 1) {
	// 变量初始化
	DWORD *dst = GetImageBuffer();			// GetImageBuffer() 函数，用于获取绘图设备的显存指针， EasyX 自带
	DWORD *draw = GetImageBuffer();
	DWORD *src = GetImageBuffer(image);		// 获取 picture 的显存指针
	int imageWidth = image->getwidth();		// 获取图片宽度
	int imageHeight = image->getheight();	// 获取图片宽度
	int dstX = 0;							// 在 绘图区域 显存里像素的角标
	int srcX = 0;							// 在 image 显存里像素的角标

	// 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP ， 贝叶斯定理来进行点颜色的概率计算
	for (int iy = 0; iy < height; iy++){
		for (int ix = 0; ix < width; ix++){
			// 防止越界
			if (ix + pic_x >= 0 && ix + pic_x < imageWidth && iy + pic_y >= 0 && iy + pic_y < imageHeight &&
				ix + x >= 0 && ix + x < NMG_CFG_WINDOW_WIDTH && iy + y >= 0 && iy + y < NMG_CFG_WINDOW_HEIGHT){
				// 获取像素角标
				int srcX = (ix + pic_x) + (iy + pic_y) * imageWidth;
				dstX = (ix + x) + (iy + y) * NMG_CFG_WINDOW_WIDTH;

				int sa = ((src[srcX] & 0xff000000) >> 24) * AA;			// 0xAArrggbb; AA 是透明度
				int sr = ((src[srcX] & 0xff0000) >> 16);				// 获取 RGB 里的 R
				int sg = ((src[srcX] & 0xff00) >> 8);					// G
				int sb = src[srcX] & 0xff;								// B

				// 设置对应的绘图区域像素信息
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //公式： Cp=αp*FP+(1-αp)*BP  ； αp=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //αp=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //αp=sa/255 , FP=sb , BP=db
			}
		}
	}
}
