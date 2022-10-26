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
#include <easyx.h>

#include "config.h"

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

// ��ͼ����������͸���� AA
void drawAlpha(IMAGE *image, int x, int y, int width, int height, int pic_x, int pic_y, double AA = 1) {
	// ������ʼ��
	DWORD *dst = GetImageBuffer();			// GetImageBuffer() ���������ڻ�ȡ��ͼ�豸���Դ�ָ�룬 EasyX �Դ�
	DWORD *draw = GetImageBuffer();
	DWORD *src = GetImageBuffer(image);		// ��ȡ picture ���Դ�ָ��
	int imageWidth = image->getwidth();		// ��ȡͼƬ���
	int imageHeight = image->getheight();	// ��ȡͼƬ���
	int dstX = 0;							// �� ��ͼ���� �Դ������صĽǱ�
	int srcX = 0;							// �� image �Դ������صĽǱ�

	// ʵ��͸����ͼ ��ʽ�� Cp=��p*FP+(1-��p)*BP �� ��Ҷ˹���������е���ɫ�ĸ��ʼ���
	for (int iy = 0; iy < height; iy++){
		for (int ix = 0; ix < width; ix++){
			// ��ֹԽ��
			if (ix + pic_x >= 0 && ix + pic_x < imageWidth && iy + pic_y >= 0 && iy + pic_y < imageHeight &&
				ix + x >= 0 && ix + x < NMG_CFG_WINDOW_WIDTH && iy + y >= 0 && iy + y < NMG_CFG_WINDOW_HEIGHT){
				// ��ȡ���ؽǱ�
				int srcX = (ix + pic_x) + (iy + pic_y) * imageWidth;
				dstX = (ix + x) + (iy + y) * NMG_CFG_WINDOW_WIDTH;

				int sa = ((src[srcX] & 0xff000000) >> 24) * AA;			// 0xAArrggbb; AA ��͸����
				int sr = ((src[srcX] & 0xff0000) >> 16);				// ��ȡ RGB ��� R
				int sg = ((src[srcX] & 0xff00) >> 8);					// G
				int sb = src[srcX] & 0xff;								// B

				// ���ö�Ӧ�Ļ�ͼ����������Ϣ
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //��ʽ�� Cp=��p*FP+(1-��p)*BP  �� ��p=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //��p=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //��p=sa/255 , FP=sb , BP=db
			}
		}
	}
}
