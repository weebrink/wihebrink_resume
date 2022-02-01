/**
* Description: Implementation of header file
*
* @author Wihebrink
* @version 9/1/2021
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BmpProcessor.h"
#include "PixelProcessor.h"

/**
 * read BMP header of a file. Useful for converting files from PPM to BMP.
 *
 * @param  file: A pointer to the file being read or written
 * @param  header: Pointer to the destination BMP header
 */
void readBMPHeader(FILE* file, struct BMP_Header* header) {
	fread(&header->signature, sizeof(char)*2, 1, file);
	fread(&header->size, sizeof(int), 1, file);
	fread(&header->reserved1, sizeof(short), 1, file);
	fread(&header->reserved2, sizeof(short), 1, file);
	fread(&header->offset_pixel_array, sizeof(int), 1, file);
}

/**
 * write BMP header of a file. Useful for converting files from PPM to BMP.
 *
 * @param  file: A pointer to the file being read or written
 * @param  header: The header made by makeBMPHeader function
 */
void writeBMPHeader(FILE* file, struct BMP_Header* header) {
	fwrite(&header->signature, sizeof(char)*2, 1, file);
	fwrite(&header->size, sizeof(int), 1, file);
	fwrite(&header->reserved1, sizeof(short), 1, file);
	fwrite(&header->reserved2, sizeof(short), 1, file);
	fwrite(&header->offset_pixel_array, sizeof(int), 1, file);
}

/**
 * read DIB header from a file. Useful for converting files from PPM to BMP.
 *
 * @param  file: A pointer to the file being read or written
 * @param  header: Pointer to the destination DIB header
 */
void readDIBHeader(FILE* file, struct DIB_Header* header) {
	fread(&header->DIB_size, sizeof(int), 1, file);
	fread(&header->width, sizeof(int), 1, file);
	fread(&header->height, sizeof(int), 1, file);
	fread(&header->bits_per_pixel, sizeof(short), 1, file);
	fread(&header->compression, sizeof(int), 1, file);
	fread(&header->image_size, sizeof(int), 1, file);
	fread(&header->pixelsX, sizeof(int), 1, file);
	fread(&header->pixelsY, sizeof(int), 1, file);
	fread(&header->color, sizeof(int), 1, file);
}

/**
 * write DIB header of a file. Useful for converting files from PPM to BMP.
 *
 * @param  file: A pointer to the file being read or written
 * @param  header: The header made by makeDIBHeader function
 */
void writeDIBHeader(FILE* file, struct DIB_Header* header) {
	fwrite(&header->DIB_size, sizeof(int), 1, file);
	fwrite(&header->width, sizeof(int), 1, file);
	fwrite(&header->height, sizeof(int), 1, file);
	fwrite(&header->bits_per_pixel, sizeof(short), 1, file);
	fwrite(&header->compression, sizeof(int), 1, file);
	fwrite(&header->image_size, sizeof(int), 1, file);
	fwrite(&header->pixelsX, sizeof(int), 1, file);
	fwrite(&header->pixelsY, sizeof(int), 1, file);
	fwrite(&header->color, sizeof(int), 1, file);
}

/**
 * make BMP header based on width and height. 
 * The purpose of this is to create a new BMPHeader struct using the information 
 * from a PPMHeader when converting from PPM to BMP.
 *
 * @param  header: Pointer to the destination DIB header
 * @param  width: Width of the image that this header is for
 * @param  height: Height of the image that this header is for
 */
void makeBMPHeader(struct BMP_Header* header, int width, int height) {
	header->signature[0] = 0x42;
	header->signature[1] = 0x4D;
	header->reserved1 = 0x00;
	header->reserved2 = 0x00;
	header->offset_pixel_array = 54;
	header->size = (54+(height*(width+(width%4)))*3);
}


 /**
 * Makes new DIB header based on width and height. Useful for converting files from PPM to BMP.
 *
 * @param  header: Pointer to the destination DIB header
 * @param  width: Width of the image that this header is for
 * @param  height: Height of the image that this header is for
 */
void makeDIBHeader(struct DIB_Header* header, int width, int height) {
	header->DIB_size = 40;
	header->width = width;
	header->height = height;
	header->bits_per_pixel = 24;
	header->planes = 1;
	header->compression = 0;
	header->image_size = height*(width+(width%4))*(3);
	header->pixelsX = 0;
	header->pixelsY = 0;
	header->color = 0;
	header->importantColor = 0;
}


/**
 * read Pixels from BMP file based on width and height.
 *
 * @param  file: A pointer to the file being read or written
 * @param  pArr: Pixel array of the image that this header is for
 * @param  width: Width of the image that this header is for
 * @param  height: Height of the image that this header is for
 */
void readPixelsBMP(FILE* file, struct Pixel** pArr, int width, int height) {
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
 * write Pixels from BMP file based on width and height.
 *
 * @param  file: A pointer to the file being read or written
 * @param  pArr: Pixel array of the image that this header is for
 * @param  width: Width of the image that this header is for
 * @param  height: Height of the image that this header is for
 */
void writePixelsBMP(FILE* file, struct Pixel** pArr, int width, int height) {
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

