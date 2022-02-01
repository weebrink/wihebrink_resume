/**
* Descrpition: A file containing a set of functions to load a data file.
*
* @author: Wihebrink
* @version: 10/5/2021
*/

#include <stdio.h>
#include <stdlib.h>
#include "DataLoader.h"

/**
 * Loads a test_scenario struct from a textfile.
 *
 * @param filename The name of the file to load.
 * @return A struct containing the loaded file.
 */
struct test_scenario* load_test_data(char* filename) {
	struct test_scenario* ts = fopen(filename, "r");
	fscanf(filename, "%d", &page_count);
	fscanf(filename, "%d", &frame_count);

	return ts;
}
