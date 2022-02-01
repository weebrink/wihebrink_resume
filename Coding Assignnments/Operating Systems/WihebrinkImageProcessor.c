/**
* Description: Loads an image file from a local BMP or PPM file (specified
*              by the user) and then transforms it using a simple color shift 
*              filter also specified by the user.
*
* @author Wihebrink
* @version 9/1/2021
*/

///////////////////////////////////////////////////////////////////////////////
// INCLUDES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "PixelProcessor.c"
#include "BmpProcessor.c"
#include "PpmProcessor.c"

//assumptions
#define MAX_IMG_SIZE 256
#define BMP_HEADER_BYTES 14
#define BMP_HEADER_BYTES_DIB 40
#define BI_RGB 0

void main(void) {

	FILE* file = fopen("test2.bmp","wb");
	if (file == NULL) {
		printf("\nCannot open this file\n");
	}

	struct BMP_Header *header;
	struct DIB_Header *header2;
	struct PPM_Header *header3;
	struct Pixel *pixels;
	

	printf("COMMAND LINE ARGUMENTS\n");
	printf("Input: %s,\n", &file);
	printf("Output: %s,\n", &output);
	printf("RGB: %d %d %d\n\n\n", pixels->R, pixels->G, pixels->B);

	// start if-else conditionls for file type

	// if BMP to BMP copy
	printf("INPUT HEADER\n");
	printf("signature: %c%c\n", header->signature[0], header->signature[1]);
	printf("size: %d\n", header->size);
	printf("reserved1: %d\n", header->reserved1);
	printf("reserved2: %d\n", header->reserved2);
	printf("offset_pixel_array: %d\n", header->offset_pixel_array);
	printf("DIB header size: %d\n", header2->DIB_size);
	printf("Image width: %d\n", header2->width);
	printf("Image height: %d\n", header2->height);
	printf("Planes: %d\n", header2->planes);
	printf("Bits per pixel: %d\n", header2->bits_per_pixel);
	printf("Compression: %d\n", header2->compression);
	printf("Image size: %d\n", header2->image_size);
	printf("X resolution: %d\n", header2->pixelsX);
	printf("Y resolution: %d\n", header2->pixelsY);
	printf("Colors in color table: %d\n", header2->color);
	printf("Important color count: %d\n\n\n", header2->importantColor);

	printf("OUTPUT HEADER\n");
	printf("signature: %c%c\n", header->signature[0], header->signature[1]);
	printf("size: %d\n", header->size);
	printf("reserved1: %d\n", header->reserved1);
	printf("reserved2: %d\n", header->reserved2);
	printf("offset_pixel_array: %d\n", header->offset_pixel_array);
	printf("DIB header size: %d\n", header2->DIB_size);
	printf("Image width: %d\n", header2->width);
	printf("Image height: %d\n", header2->height);
	printf("Planes: %d\n", header2->planes);
	printf("Bits per pixel: %d\n", header2->bits_per_pixel);
	printf("Compression: %d\n", header2->compression);
	printf("Image size: %d\n", header2->image_size);
	printf("X resolution: %d\n", header2->pixelsX);
	printf("Y resolution: %d\n", header2->pixelsY);
	printf("Colors in color table: %d\n", header2->color);
	printf("Important color count: %d\n\n\n", header2->importantColor);
	// if PPM to PPM copy
	printf("INPUT HEADER\n");
	printf("Magic number: %c%c\n", header3->magicNum[0], header3->magicNum[1]);
	printf("Height: %d\n", header3->height);
	printf("Width: %d\n", header3->width);
	printf("Maxval: %d\n", header3->maxValue);

	printf("OUTPUT HEADER\n");
	printf("Magic number: %c%c\n", header3->magicNum[0], header3->magicNum[1]);
	printf("Height: %d\n", header3->height);
	printf("Width: %d\n", header3->width);
	printf("Maxval: %d\n", header3->maxValue);
	// if BPM to PPM convert
	printf("INPUT HEADER\n");
	printf("signature: %c%c\n", header->signature[0], header->signature[1]);
	printf("size: %d\n", header->size);
	printf("reserved1: %d\n", header->reserved1);
	printf("reserved2: %d\n", header->reserved2);
	printf("offset_pixel_array: %d\n", header->offset_pixel_array);
	printf("DIB header size: %d\n", header2->DIB_size);
	printf("Image width: %d\n", header2->width);
	printf("Image height: %d\n", header2->height);
	printf("Planes: %d\n", header2->planes);
	printf("Bits per pixel: %d\n", header2->bits_per_pixel);
	printf("Compression: %d\n", header2->compression);
	printf("Image size: %d\n", header2->image_size);
	printf("X resolution: %d\n", header2->pixelsX);
	printf("Y resolution: %d\n", header2->pixelsY);
	printf("Colors in color table: %d\n", header2->color);
	printf("Important color count: %d\n\n\n", header2->importantColor);

	printf("OUTPUT HEADER\n");
	printf("Magic number: %c%c\n", header3->magicNum[0], header3->magicNum[1]);
	printf("Height: %d\n", header3->height);
	printf("Width: %d\n", header3->width);
	printf("Maxval: %d\n", header3->maxValue);

	// if PPM to BMP convert
	printf("INPUT HEADER\n");
	printf("Magic number: %c%c\n", header3->magicNum[0], header3->magicNum[1]);
	printf("Height: %d\n", header3->height);
	printf("Width: %d\n", header3->width);
	printf("Maxval: %d\n", header3->maxValue);

	printf("OUTPUT HEADER\n");
	printf("signature: %c%c\n", header->signature[0], header->signature[1]);
	printf("size: %d\n", header->size);
	printf("reserved1: %d\n", header->reserved1);
	printf("reserved2: %d\n", header->reserved2);
	printf("offset_pixel_array: %d\n", header->offset_pixel_array);
	printf("DIB header size: %d\n", header2->DIB_size);
	printf("Image width: %d\n", header2->width);
	printf("Image height: %d\n", header2->height);
	printf("Planes: %d\n", header2->planes);
	printf("Bits per pixel: %d\n", header2->bits_per_pixel);
	printf("Compression: %d\n", header2->compression);
	printf("Image size: %d\n", header2->image_size);
	printf("X resolution: %d\n", header2->pixelsX);
	printf("Y resolution: %d\n", header2->pixelsY);
	printf("Colors in color table: %d\n", header2->color);
	printf("Important color count: %d\n\n\n", header2->importantColor);

	free(file);
	fclose(file);
}
