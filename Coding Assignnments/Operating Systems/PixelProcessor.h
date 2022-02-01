/**
* Description: Header file for the Pixel Preprocessor file
*
* @author Wihebrink, Acuna
* @version 09/1/2021
*/

#ifndef PixelProcessor_H
#define PixelProcessor_H

struct Pixel {
	unsigned char R, G, B; // Structure to load BMP file color pixels
};

/**
 * Shift color of Pixel array. The dimension of the array is width * height. The shift value of RGB is 
 * rShift, gShift，bShift. Useful for color shift.
 *
 * @param  pArr: Pixel array of the image that this header is for
 * @param  width: Width of the image that this header is for
 * @param  height: Height of the image that this header is for
 * @param  rShift: the shift value of color r shift
 * @param  gShift: the shift value of color g shift 
 * @param  bShift: the shift value of color b shift 
 */
void colorShiftPixels(struct Pixel** pArr, int width, int height, int rShift, int gShift, int bShift);

#endif