/**
* Description: Implementation of header file
*
* @author Wihebrink
* @version 09/1/2021
*/

#include <stdio.h>
#include "PixelProcessor.h"

void colorShiftPixels(struct Pixel** pArr, int width, int height, int rShift, int gShift, int bShift) {
	int i, j;
	for (i = 0; i < width; i++) {
		for (j = 0; j < height; j++) {
			pArr[i][j].R += rShift;
			pArr[i][j].G += gShift;
			pArr[i][j].B += bShift;
		}
	}
}
