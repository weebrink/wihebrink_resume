/**
* Description: Computes the total volume for a number of cylinders.
*
* Completion time: 1 hours
*
* @author Wihebrink, Acuna
* @version 8/24/2021
*/

///////////////////////////////////////////////////////////////////
// INCLUDES
#include <stdio.h>

int main(void) {
	float total_sum = 0;
	float cylinder_height = 0;
	float cylinder_radius = 0;
	int cylinder_count = 0;

	int i = 0;
	// Add a prompt for the number of cylinders to sum. Make sure to
	// use the control symbol for integers. [2 points]
	printf("Input the number of cylinders to sum: ");
	scanf("%d", &cylinder_count);

	// Create a loop based on the number of cylinders the user enters. [2 points]
	for (i = 0; i < cylinder_count; i++) {
		// Within the loop, prompt for height and radius parameters
		// (allows floating point numbers), and calculate the volume
		// for that particular cylinder. [4 points]
		printf("What is the height of cylinder %d?\n", i+1);
		scanf("%f", &cylinder_height);
		printf("What is the radius of cylinder %d?\n", i+1);
		scanf("%f", &cylinder_radius);
	
		total_sum += cylinder_height * 3.14159265 * (cylinder_radius*cylinder_radius);
	}
	// display total volume sum back to the user. make sure to use right control symbol. [2 points]
	printf("Total volume sum of cylinders: %f\n", total_sum);

	return 0;
}


