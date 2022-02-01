/**
* Description: Checks to see if a particular integer entered by the
* user satisfies the collatz conjecture.
*
* Completion time: 1 hour
*
* @author W/ihebrink, Acuna
* @version 8/24/2021
*/

#include <stdio.h>

// Write a C program to implement the algorithm as a function called termination
// that is called from main. [4 points]
int termination(int n) {
	int count = 0;
	while (n != 1) {
		if (n % 2 == 0) { // even number
			n = n/2;
		} else { 	  // odd number
			n = (3*n) + 1;
		}
		count++;
	}	
	return count;
}

int main(void) {
	int input;
	printf("Enter a number: ");
	scanf("%d", &input);
	// Call termination from main on an input integer given by the user. [2 points]	
	termination(input);

	// Count and display how many iterations are executed for the input. [2 points]
	if (input > 0) {
		input = termination(input);

		printf("\n The input number is reduced to %d \n\n", input);
	} else {
		printf("\n The input number does not satisfy the collatz conjecture. \n\n");
	}
	return 0;
}
