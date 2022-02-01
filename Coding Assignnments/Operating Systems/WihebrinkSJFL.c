/**
* Description: Runs the Shortest-Job-First and Shortest-Job-First Live 
*              Algorithms and displays them back to the user.
*
* @author Wihebrink
* @version 9/22/2021
*/

///////////////////////////////////////////////////////////////////////
//INCLUDES
#include <stdio.h>
#include <stdlib.h>

struct value_node {
	int value;
	struct value_node* next;
};

struct process_node {
	int pid;
	float alpha;
	float tau;
	struct value_node* burst_list;
	struct value_node* current_burst;
	struct process_node* next;
};

typedef struct value_node value_node;
typedef struct process_node process_node;

//////////////////////////////////////////////////////////////////////
//GLOBALS
int tick_counter = -1;
int process_counter = -1;
process_node* process_list = NULL;
value_node* turnaround_list = NULL;
value_node* wait_list = NULL;
value_node* est_time_list = NULL;

void add_process_node(process_node* new_node, process_node* list) {
	if (list == NULL) {
		list = new_node;
		return;
	}
	process_node* temp = list;
	while(temp->next != NULL) {
		temp = temp->next;
	}
	temp->next = new_node;
}

void add_value_node(value_node* new_node, value_node* list) {
	if (list == NULL) {
		list = new_node;
		return;
	}
	value_node* temp = list;
	while(temp->next != NULL) {
		temp = temp->next;
	}
	temp->next = new_node;
}

void spawn_processes(FILE* file) {
	int i;
	char* line = NULL;
	size_t len = 0;
	__ssize_t line_size;
	process_node* new_process = NULL;
	value_node* new_value = NULL;
	
	while (line_size = getline(&line, &len, file) != -1) {
		new_process = malloc(sizeof(new_process));
		new_process->pid = atoi(line);

		line_size = getline(&line, &len, file);
		new_process->tau = atof(line);

		line_size = getline(&line, &len, file);
		new_process->alpha = atof(line);

		for (i = 0; i < tick_counter; i++) {
			new_value = malloc(sizeof(value_node));

			line_size = getline(&line, &len, file);
			new_value->value = atoi(line);
			add_value_node(new_value, new_process->burst_list);
		}
		new_process->current_burst = new_process->burst_list;
		add_process_node(new_process, process_list);
	}
}

void value_list_cleanup(value_node* list) {
	while (list) {
		value_node* current_node = list;
		list = list->next;
		free(current_node);
	}
}

void process_list_cleanup(process_node* list) {
	while (list) {
		process_node* current_node = list;
		list = list->next;
		value_list_cleanup(current_node->burst_list);
		free(current_node->burst_list);
		free(current_node->current_burst);
		free(current_node);
	}
}

void read_file(const char* file_path) {

	FILE* file = fopen(file_path, "r");
	if (file == NULL) {
		printf("No file detected. Please try again.\n");
		exit(0);
	}
	char* line = NULL;
	size_t len = 0;
	__ssize_t line_size = getline(&line, &len, file);
	tick_counter = atoi(line);
	line_size = getline(&line, &len, file);
	process_counter = atoi(line);
	
	if (tick_counter == -1) {
		printf("There was an error reading the tick counter\n");
		exit(0);
	}

	if (process_counter == -1) {
		printf("There was an error reading the process counter\n");
		exit(0);
	}

	spawn_processes(file);
	fclose(file);
	if (line) {
		free(line);
	}
}

void compute_tau(process_node* process, int previous_burst) {
	process->tau = process->alpha * previous_burst + (1 - process->alpha) * process->tau;
}

float compute_total_time(value_node* list) {
	float total_time = 0;
	
	value_node* temp = list;
	while (temp != NULL) {
		total_time += temp->value;
		temp = temp->next;
	}

	return total_time;
}

void sort_process_burst(process_node* output) {
	int i;

	for(i = 0; i < process_counter; i++) {
		process_node* temp = process_list;
		process_node* low = temp;
		temp = temp->next;
		while (temp != NULL) {
			if (low->current_burst->value > temp->current_burst->value) {
				low = temp;
			}
		}
		add_process_node(low, output);
	}
}

void sort_process_tau(process_node* output) {
	int i;

	for (i = 0; i < process_counter; i++) {
		process_node* temp = process_list;
		process_node* low = temp;
		temp = temp->next;
		while (temp != NULL) {
			if (low->tau > temp->tau) {
				low = temp;
			}
		}
		add_process_node(low, output);
	}
}

void run_process(process_node* list) {
	process_node* temp = list;
	value_node* turnaround_node = malloc(sizeof(value_node));
	turnaround_node->value = 0;
	value_node* wait_node = malloc(sizeof(value_node));
	wait_node->value = 0;
	while (temp != NULL) {
		printf("\tProcess %d took %d. \n", temp->pid, temp->current_burst->value);
		wait_node->value += turnaround_node->value;
		turnaround_node->value += temp->current_burst->value;
		temp->current_burst = temp->current_burst->next;
	}
	add_value_node(turnaround_node, turnaround_list);
	add_value_node(wait_node, wait_list);
}

void run_process_live(process_node* list) {
	process_node* temp = list;
	value_node* turnaround_node = malloc(sizeof(value_node));
	turnaround_node-> value = 0;
	value_node* est_node = malloc(sizeof(value_node));
	est_node->value = 0;
	value_node* wait_node = malloc(sizeof(value_node));
	wait_node->value = 0;
	while(temp != NULL) {
		printf("\tProcess %d was estimated for %f and took %d.\n", temp->pid, temp->tau, temp->current_burst->value);
		wait_node->value += turnaround_node->value;
		est_node->value += temp->tau;
		turnaround_node->value += temp->current_burst->value;
		compute_tau(temp, temp->current_burst->value);
		temp->current_burst = temp->current_burst->next;
	}
}

void SJF() {
	process_node* sorted_list;
	int tick;
	int current_time = 0;
	printf("========== SHORTEST - JOB - FIRST ==========\n");
	
	for(tick = 0; tick < tick_counter; tick++) {
		printf("Simulating %d th tick of processes @ time %d:\n", tick, current_time);
		sort_process_burst(sorted_list);
		run_process(sorted_list);
	}

	float time = compute_total_time(turnaround_list);
	printf("Turnaround time:\t%d\n", (int)time);
	time = compute_total_time(wait_list);
	printf("Waiting time:\t%d\n", (int)time);
}

void SJFL() {
	process_node* sorted_list;
	int tick;
	int current_time = 0;
	printf("========== SHORTEST - JOB - FIRST - LIVE ==========\n");
	
	for(tick = 0; tick < tick_counter; tick++) {
		printf("Simulating %d th tick of processes @ time %d:\n", tick, current_time);
		sort_process_tau(sorted_list);
		run_process_live(sorted_list);
	}

	float turn_time = compute_total_time(turnaround_list);
	printf("Turnaround time:\t%d\n", (int) turn_time);
	float wait_time = compute_total_time(wait_list);
	printf("Waiting time:\t%d\n", (int) wait_time);
	float est_time = compute_total_time(est_time_list);
	printf("Estimation error:\t%d\n", abs(turn_time - est_time));
}

int main(int argc, const char* argv[]) {
	if (argc == 0) {
		printf("File path to process definition not passed as an argument, exiting program!");
		exit(0);
	}
	
	read_file(argv[1]);
	
	SJF();
	
	process_node* temp = process_list;
	while(temp != NULL) {
		temp->current_burst = temp->burst_list;
		temp = temp->next;
	}
	
	value_list_cleanup(turnaround_list);
	value_list_cleanup(wait_list);
	
	SJFL();
	
	process_list_cleanup(process_list);	
	free(process_list);
	value_list_cleanup(turnaround_list);
	value_list_cleanup(wait_list);
	value_list_cleanup(est_time_list);
	free(turnaround_list);
	free(wait_list);
	free(est_time_list);
}
