/**
* Description: Implements functions from header file
*
* @author Wihebrink
* @version 9/1/2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PpmProcessor.h"
#include "PixelProcessor.h"


/**
 * read PPM header of a file. Useful for converting files from BMP to PPM.
 *
 * @param  file: A pointer to the file being read or written
 * @param  header: Pointer to the destination PPM header
 */
void readPPMHeader(FILE* file, struct PPM_Header* header) {
	fread(&header->magicNum, sizeof(char)*2, 1, file);
	fread(&header->height, sizeof(int), 1, file);
	fread(&header->width, sizeof(int), 1, file);
	fread(&header->maxValue, sizeof(int), 1, file);
}

/**
 * write PPM header of a file. Useful for converting files from BMP to PPM.
 *
 * @param  file: A pointer to the file being read or written
 * @param  header: The header made by makePPMHeader function

 */
void writePPMHeader(FILE* file, struct PPM_Header* header) {
	fwrite(&header->magicNum, sizeof(char)*2, 1, file);
	fwrite(&header->height, sizeof(int), 1, file);
	fwrite(&header->width, sizeof(int), 1, file);
	fwrite(&header->maxValue, sizeof(int), 1, file);
}

/**
 * make PPM header based on width and height. Useful for converting files from BMP to PPM.
 *
 * @param  header: Pointer to the destination PPM header
 * @param  width: Width of the image that this header is for
 * @param  height: Height of the image that this header is for
 */
void makePPMHeader(struct PPM_Header* header, int width, int height) {
	header->magicNum[0] = 'P';
	header->magicNum[1] = '6';
	header->height = height;
	header->width = width;
	header->maxValue = 255;
}

/**
 * read Pixels from PPM file based on width and height.
 *
 * @param  file: A pointer to the file being read or written
 * @param  pArr: Pixel array of the image that this header is for 
 * @param  width: Width of the image that this header is for
 * @param  height: Height of the image that this header is for
 */
void readPixelsPPM(FILE* file, struct Pixel** pArr, int width, int height) {
	int i, j;
	int padding = (width%4);
	for (i = 0; i < width; i++) {
		for (j = 0; j < height; j++) {
			unsigned char r, g, b;
			fread(&r, sizeof(unsigned char), 1, file);
			fread(&g, sizeof(unsigned char), 1, file);
			fread(&b, sizeof(unsigned char), 1, file);
			pArr[i][j].R = r;
			pArr[i][j].G = g;
			pArr[i][j].B = b;	
			if (j == height - 1) {
				fseek(file, sizeof(char)*padding, SEEK_CUR);
			}
		}
	}
}

/**
 * write Pixels from PPM file based on width and height.
 *
 * @param  file: A pointer to the file being read or written
 * @param  pArr: Pixel array of the image that this header is for
 * @param  width: Width of the image that this header is for
 * @param  height: Height of the image that this header is for
 */
void writePixelsPPM(FILE* file, struct Pixel** pArr, int width, int height) {
	int i, j;	
	int padding = width%4;
	for (i = 0; i < width; i++) {
		for (j = 0; j < height; j++) {
			fwrite(&pArr[i][j].R, sizeof(char), 1, file);
			fwrite(&pArr[i][j].G, sizeof(char), 1, file);
			fwrite(&pArr[i][j].B, sizeof(char), 1, file);
			if (j == (height - 1)) {
				fseek(file, sizeof(char)*padding, SEEK_CUR);
			}
		}
	}
	char file_end = 0x00;
	fwrite(&file_end, sizeof(char), 1, file);	
}


