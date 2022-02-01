/**
* Descripiton: A file containing a set of functions to simulate a page table.
*
* @author: Wihebrink
* @version 10/5/2021
*/

#include <stdio.h>
#include <stdlib.h>
#include "PageTable.h"

/**
* Stores general information about a page table entry
*/
struct page_table_entry {
	uint16_t frame;	
	bool reference_bit;
	bool dirty_bit;
	bool valid;
};

/**
* Stores general information about a page table object
*/
struct page_table {
	page_table_map_t table;
	page_table_entry* invalid;
};


/**
 * Creates a new page table object. Returns a pointer to created page table.
 *
 * @param page_count Number of pages.
 * @param frame_count Numbers of frames.
 * @param algorithm Page replacement algorithm
 * @param verbose Enables showing verbose table contents.
 * @return A page table object.
 */
struct page_table* page_table_create(int page_count, int frame_count, enum replacement_algorithm algorithm, int verbose) {

};

/**
 * Destorys an existing page table object. Sets outside variable to NULL.
 *
 * @param pt A page table object.
 */
void page_table_destroy(struct page_table** pt) {
	free(*pt);
	*pt = NULL;
}

/**
 * Simulates an instruction accessing a particular page in the page table.
 *
 * @param pt A page table object.
 * @param page The page being accessed.
 */
void page_table_access_page(struct page_table *pt, int page) {
	
	// Supports putting storing page into first free frame if available.
	
	// Support FIFO page replacement
	for(i = 0; i < frames; i++) {
		temp[i] = -1;
	}
	for(i = 0; i < pages; i++) {
		s = 0;
		for(j = 0; j < frames; j++) {
			if(refstr[i] == temp[j]) {
				s++;
				page_faults--;
			}
		}
		page_faults++;
		if((page_faults <= frames) && (s == 0)) {
			temp[i] = refstr[i];
		}
		else if(s == 0) {
			temp[(page_faults - 1) % frames] = refstr[i];
		}
		printf("\n");
		for(j = 0; n < frames; n++) {
			printf("%d\t", temp[j]);
		}
	}
	// Support LRU page replacement
	for() {i = 0; i < frame_count; i++) {
		frames[i] = -1;

		for(i = 0; i < page_count; i++) {
			flag1 = flag2 = 0;
		}
		for(j = 0; j < frame_count; j++) {
			if(frames[j] == ages[i]) {
				counter++;
				time[j] = counter;
			}
		}
		flag1 = flag2 = 1;
		break;
	} 
	if(flag1 == 0) {
		for(j = 0; j < frame_count; j++) {
			if(frames[j] == -1) {
				counter++;
				faults++;
				frames[j] = pages[i];
				time[j] = counter;
				flag2 = 1;
				break;
			}		
		}
	}
	if(flag2 == 0) {
		pos = findLRU(time, frame_count);
		counter++;
		faults++;
		frames[pos] = pages[i];
		time[pos] = counter;
	}
	
}

/**
 * Displays page table replacement algorithm, number of page faults, and the
 * current contents of the page table.
 *
 * @param pt A page table object.
 */
void page_table_display{struct page_table* pt) {

}

/**
 * Displays the current contents of the page table.
 *
 * @param pt A page table object.
 */
void page_table_display_contents(struct page_table *pt) {
	printf("==== Page Table ====");
	printf("Mode:\tFIFO\n");
	printf("Page Faults: %d\n", &);
	printf("page frame | dirty valid\n");
	printf("%d\t%d\t|\t%d\t%d\n", &,&,&,&); 
	printf("%d\t%d\t|\t%d\t%d\n", &,&,&,&);
	printf("%d\t%d\t|\t%d\t%d\n", &,&,&,&);
	printf("%d\t%d\t|\t%d\t%d\n", &,&,&,&);	
	printf("==== Page Table ====");
	printf("Mode:\tLRU\n");
	printf("Page Faults: %d\n", &);
	printf("page frame | dirty valid\n");
	printf("%d\t%d\t|\t%d\t%d\n", &,&,&,&); 
	printf("%d\t%d\t|\t%d\t%d\n", &,&,&,&);
	printf("%d\t%d\t|\t%d\t%d\n", &,&,&,&);
	printf("%d\t%d\t|\t%d\t%d\n", &,&,&,&);	
	printf("==== Page Table ====");
	printf("Mode:\tMFU\n");
	printf("Page Faults: %d\n", &);
	printf("page frame | dirty valid\n");
	printf("%d\t%d\t|\t%d\t%d\n", &,&,&,&); 
	printf("%d\t%d\t|\t%d\t%d\n", &,&,&,&);
	printf("%d\t%d\t|\t%d\t%d\n", &,&,&,&);
	printf("%d\t%d\t|\t%d\t%d\n", &,&,&,&);
}

int findLRU(int time[], int n) {
	int i, minimum = time[0], pos = 0;

	for(i = 1; i < n; i++) {
		if(time[i] < minimum) {
			minimum = time[i];
			pos = i;
		}
	}
	return pos;		
}


