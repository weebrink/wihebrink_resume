/**
* Blurs BMP files with a Box Blurring technique. Also tries to attempts
* to use swiss cheese technique on images as well.
*
* Completion time: 23 hours
*
* @author Wihebrink
* @version 9/15/2021
*/

////////////////////////////////////////////////////////////////////////////////
//INCLUDES
#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include "BmpProcessor.h"
#include "PixelProcessor.h"


////////////////////////////////////////////////////////////////////////////////
//MACRO DEFINITIONS

#define BMP_HEADER_SIZE 14
#define BMP_DIB_HEADER_SIZE 40
#define MAXIMUM_IMAGE_SIZE 4096
#define THREAD_COUNT 4

////////////////////////////////////////////////////////////////////////////////
//DATA STRUCTURES

struct BMP_Header {
	char signature[2];
	int size;
	short reserved1;
	short reserved2;
	int offset_pixel_arr;
}

typedef struct DIB_Header {
	int size;
	int width;
	int height;
	short planes;
	short bitsPerPixel;
	int compression;
	int imageSizeBytes;
	int pixelsPerMeterHorizontal;
	int pixelsPerMeterVertical;
	int colorUsed;
	int colorImp;
}BM_INFO_HEADER;

typedef struct {
	unsigned char R,G,B;
}RGB_INDEX;

RGB_INDEX rgb_index[MAXIMUM_IMAGE_SIZE][MAXIMUM_IMAGE_SIZE];
RGB_INDEX blurred_rgb_index[MAXIMUM_IMAGE_SIZE][MAXIMUM_IMAGE_SIZE];

typedef enum color_pallet {
	RED = 0,
	GREEN = 1,
	BLUE = 2;
	YELLOW = 3;
	BLACK = 4;
}COLORS;

unsigned char blurred_rgb(int i, int j, COLORS rgb);
unsigned char swiss_cheese_rgb(int i, int j, COLORS rgb);

int GLOBAL_HEIGHT = 0;
int GLOBAL_WIDTH = 0;

////////////////////////////////////////////////////////////////////////////////
//MAIN PROGRAM CODE

unsigned char blurred_rgb(int i, int j, COLORS rgb) {

	int p,q;
	switch(rgb) {
		case RED: {
			int sum = 0;
			int counter = 0;
			int average = 0;

			for(p = i-1; p <= i + 1; p++) {
				if(p < 0 || p >= GLOBAL_HEIGHT) {
					continue;
				}
				for(q = j-1; q <= j + 1; q++) {
					if(q < 0 || q >= GLOBAL_WIDTH) {
						continue;
					}
					sum = sum + rgb_index[p][q].R;
					counter++;
				}
			}
			if(count) {
				average = sum/counter;
			}
			return average;
		}break;

		case GREEN: {
			int sum = 0;
			int counter = 0;
			int average = 0;

			for(p = i-1; p <= i + 1; p++) {
				if(p < 0 || p >= GLOBAL_HEIGHT) {
					continue;
				}
				for(q = j-1; q <= j + 1; q++) {
					if(q < 0 || q >= GLOBAL_WIDTH) {
						continue;
					}
					sum = sum + rgb_index[p][q].G;
					counter++;
				}
			}
			if(count) {
				average = sum/counter;
			}
			return average;
		}break;

		case BLUE: {
			int sum = 0;
			int counter = 0;
			int average = 0;
	
			for(p = i-1; p <= i + 1; p++) {
				if(p < 0 || p >= GLOBAL_HEIGHT) {
					continue;
				}
				for(q = j-1; q <= j + 1; q++) {
					if(q < 0 || q >= GLOBAL_WIDTH) {
						continue;
					}
					sum = sum + rgb_index[p][q].B;
					counter++;
				}
			}
			if(count) {	
				average = sum/counter;
			}
			return average;
		}break;
	}
}

unsigned char swiss_cheese_rgb(int i, int j, COLORS rgb) {
	int p,q;
	switch(rgb) {
		case RED: {
			int sum = 0;
			int counter = 0;
			int average = 0;

			for(p = i-1; p <= i + 1; p++) {
				if(p < 0 || p >= GLOBAL_HEIGHT) {
					continue;
				}
				for(q = j-1; q <= j + 1; q++) {
					if(q < 0 || q >= GLOBAL_WIDTH) {
						continue;
					}
					sum = sum + rgb_index[p][q].R;
					counter++;
				}
			}
			if(count) {
				average = sum/counter;
			}
			return average;
		}break;

		case GREEN: {
			int sum = 0;
			int counter = 0;
			int average = 0;

			for(p = i-1; p <= i + 1; p++) {
				if(p < 0 || p >= GLOBAL_HEIGHT) {
					continue;
				}
				for(q = j-1; q <= j + 1; q++) {
					if(q < 0 || q >= GLOBAL_WIDTH) {
						continue;
					}
					sum = sum + rgb_index[p][q].G;
					counter++;
				}
			}
			if(count) {
				average = sum/counter;
			}
			return average;
		}break;

		case BLUE: {
			int sum = 0;
			int counter = 0;
			int average = 0;
	
			for(p = i-1; p <= i + 1; p++) {
				if(p < 0 || p >= GLOBAL_HEIGHT) {
					continue;
				}
				for(q = j-1; q <= j + 1; q++) {
					if(q < 0 || q >= GLOBAL_WIDTH) {
						continue;
					}
					sum = sum - rgb_index[p][q].B; // Shift to slight yellow
					counter++;
				}
			}
			if(count) {	
				average = sum/counter;
			}
			return average;
		}break;
	}
}

void* top_left_blur(void* image) {
	int i,j;
	int height = (GLOBAL_HEIGHT + 1)/2;
	int width = (GLOBAL_WIDTH + 1)/2;
	for(i=0; i < width; i++) {
		for(j=0; j < height; j++) {
			blurred_rgb_index[i][j].R = blurred_rgb(i,j,RED);
			blurred_rgb_index[i][j].G = blurred_rgb(i,j,GREEN);
			blurred_rgb_index[i][j].B = blurred_rgb(i,j,BLUE);
		}
	}
}

void* top_right_blur(void* image) {
	int i,j;
	int height = (GLOBAL_HEIGHT + 1)/2;
	int width = GLOBAL_WIDTH;
	for(i=0; i < width; i++) {
		for(j=0; j < height; j++) {
			blurred_rgb_index[i][j].R = blurred_rgb(i,j,RED);
			blurred_rgb_index[i][j].G = blurred_rgb(i,j,GREEN);
			blurred_rgb_index[i][j].B = blurred_rgb(i,j,BLUE);
		}
	}
}

void* bot_left_blur(void* image) {
	int i,j;
	int height = GLOBAL_HEIGHT;
	int width = (GLOBAL_WIDTH + 1)/2;
	for(i=0; i < width; i++) {
		for(j=0; j < height; j++) {
			blurred_rgb_index[i][j].R = blurred_rgb(i,j,RED);
			blurred_rgb_index[i][j].G = blurred_rgb(i,j,GREEN);
			blurred_rgb_index[i][j].B = blurred_rgb(i,j,BLUE);
		}
	}
}

void* bot_right_blur(void* image) {
	int i,j;
	int height = GLOBAL_HEIGHT;
	int width = GLOBAL_WIDTH;
	for(i=0; i < width; i++) {
		for(j=0; j < height; j++) {
			blurred_rgb_index[i][j].R = blurred_rgb(i,j,RED);
			blurred_rgb_index[i][j].G = blurred_rgb(i,j,GREEN);
			blurred_rgb_index[i][j].B = blurred_rgb(i,j,BLUE);
		}
	}
}

void* top_left_swiss(void* image) {
	int i,j;
	int height = (GLOBAL_HEIGHT + 1)/2;
	int width = (GLOBAL_WIDTH + 1)/2;
	for(i=0; i < width; i++) {
		for(j=0; j < height; j++) {
			blurred_rgb_index[i][j].R = swiss_cheese_rgb(i,j,RED);
			blurred_rgb_index[i][j].G = swiss_cheese_rgb(i,j,GREEN);
			blurred_rgb_index[i][j].B = swiss_cheese_rgb(i,j,BLUE);
		}
	}
}

void* top_right_swiss(void* image) {
	int i,j;
	int height = (GLOBAL_HEIGHT + 1)/2;
	int width = GLOBAL_WIDTH;
	for(i=0; i < width; i++) {
		for(j=0; j < height; j++) {
			blurred_rgb_index[i][j].R = swiss_cheese_rgb(i,j,RED);
			blurred_rgb_index[i][j].G = swiss_cheese_rgb(i,j,GREEN);
			blurred_rgb_index[i][j].B = swiss_cheese_rgb(i,j,BLUE);
		}
	}
}

void* bot_left_swiss(void* image) {
	int i,j;
	int height = GLOBAL_HEIGHT;
	int width = (GLOBAL_WIDTH + 1)/2;
	for(i=0; i < width; i++) {
		for(j=0; j < height; j++) {
			blurred_rgb_index[i][j].R = swiss_cheese_rgb(i,j,RED);
			blurred_rgb_index[i][j].G = swiss_cheese_rgb(i,j,GREEN);
			blurred_rgb_index[i][j].B = swiss_cheese_rgb(i,j,BLUE);
		}
	}
}

void* bot_right_swiss(void* image) {
	int i,j;
	int height = GLOBAL_HEIGHT;
	int width = GLOBAL_WIDTH;
	for(i=0; i < width; i++) {
		for(j=0; j < height; j++) {
			blurred_rgb_index[i][j].R = swiss_cheese_rgb(i,j,RED);
			blurred_rgb_index[i][j].G = swiss_cheese_rgb(i,j,GREEN);
			blurred_rgb_index[i][j].B = swiss_cheese_rgb(i,j,BLUE);
		}
	}
}

void main(int argc, char* argv[]) {

	FILE* file = fopen("test1wonderbread.bmp", "rb");
	if (file == NULL) {
		printf("Cannot open this file.");
		exit(1);
	}
	struct BMP_Header head;
	BM_INFO_HEADER infohead;
	int i,j;
	
	fread(&header.signature, sizeof(char)*2, 1, file);
	fread(&header.size, sizeof(int), 1, file);
	fread(&header.reserved1, sizeof(short), 1, file);
	fread(&header.reserved2, sizeof(short), 1, file);
	fread(&header.offset_pixel_arr, sizeof(int), 1, file);

	if('B' != header.signature[0] || 'M' != header.signature[1]) {
		printf("This file is not valid.");
		exit(1);
	}
	printf("signature: %c%c\n", header.signature[0], header.signature[1]);
	printf("size: %d\n", header.size);
	printf("reserved1: %d\n", header.reserved1);
	printf("reserved2: %d\n", header.reserved2);
	printf("offsetted pixel array: %d\n", header.offset_pixel_arr);
	
	fread(&infohead, sizeof(BM_INFO_HEADER), 1, file);
	
	if(24 != infohead.bitsPerPixel) {
		printf("Not supported. Must be 24 bits.");
		exit(1);
	}
	printf("Image size = %d x %d\n", infohead.width, infohead.height);
	
	GLOBAL_HEIGHT = infohead.height;
	GLOBAL_WIDTH = infohead.width;
	
	fseek(file, header.offset_pixel_arr, SEEK_SET);
	
	for(i=0; i < infohead.width; i++) {
		for(j=0; j < infohead.height; j++) {
			fread(&rgb_index[i][j].R, sizeof(char), 1, file);
			fread(&rgb_index[i][j].G, sizeof(char), 1, file);
			fread(&rgb_index[i][j].B, sizeof(char), 1, file);
		}
	}
	fclose(file);
	
	pthread_t top_left_tid, top_right_tid, bot_left_tid, bot_right_tid;
	
	FILE* blurred_file = fopen("output1.bmp", "wb");
		
	if(fp == NULL) {
		printf("This file cannot be created.");
		exit(1);
	}	
	fwrite(&header.signature, sizeof(char)*2, 1, blurred_file);
	fwrite(&header.size, sizeof(int), 1, blurred_file);
	fwrite(&header.reserved1, sizeof(short), 1, blurred_file);
	fwrite(&header.reserved2, sizeof(short), 1, blurred_file);
	fwrite(&header.offset_pixel_arr, sizeof(int), 1, blurred_file);
	fwrite(&infohead, sizeof(BM_INFO_HEADER), 1, blurred_file);
	
	for(i=0; i < infohead.width; i++) {
		for(j=0; j < infohead.height; j++) {
			fwrite(&blurred_rgb_index[i][j].R, sizeof(char), 1, blurred_file);
			fwrite(&blurred_rgb_index[i][j].G, sizeof(char), 1, blurred_file);
			fwrite(&blurred_rgb_index[i][j].B, sizeof(char), 1, blurred_file);
		}
	}
	fclose(blurred_file);	
	printf("Blurred file created.");

	FILE* swiss_cheese_file = fopen("output2.bmp", "wb");
		
	if(fp == NULL) {
		printf("This file cannot be created.");
		exit(1);
	}	
	fwrite(&header.signature, sizeof(char)*2, 1, swiss_cheese_file);
	fwrite(&header.size, sizeof(int), 1, swiss_cheese_file);
	fwrite(&header.reserved1, sizeof(short), 1, swiss_cheese_file);
	fwrite(&header.reserved2, sizeof(short), 1, swiss_cheese_file);
	fwrite(&header.offset_pixel_arr, sizeof(int), 1, swiss_cheese_file);
	fwrite(&infohead, sizeof(BM_INFO_HEADER), 1, swiss_cheese_file);
	
	for(i=0; i < infohead.width; i++) {
		for(j=0; j < infohead.height; j++) {
			fwrite(&blurred_rgb_index[i][j].R, sizeof(char), 1, swiss_cheese_file);
			fwrite(&blurred_rgb_index[i][j].G, sizeof(char), 1, swiss_cheese_file);
			fwrite(&blurred_rgb_index[i][j].B, sizeof(char), 1, swiss_cheese_file);
		}
	}
	fclose(swiss_cheese_file);	
	printf("Swiss cheese file created.");
}
