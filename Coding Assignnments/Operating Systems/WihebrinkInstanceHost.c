/**
* Description: Acts as a gateway that is a middle layer between
* server instances and the users. It is used to distribute incoming traffic
* to different servers capable of fulfilling those requests in a manner that
* maximizes throughput, and ensures that no one server is overworked.
*
* @author Wihebrink
* @version 9/15/2021
*/

////////////////////////////////////////////////////////////////////////////
// INCLUDES
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "InstanceHost.h"

struct host {
	int num_instances;
	pthread_t *t;
};

pthread_t* create_instance(host* h);
void add_instance(host* h);
void remove_instance(host* h);

void *runner(void* args) {
	pthread_exit(NULL);
}

/**
* Initializes the host environment.
*/
host *host_create() {
	host* host = (struct host*)malloc(sizeof(host));
	host->num_instances = 0;
	host->t = create_instance(host);
	
	return host;
}

/**
* Shuts down the host environment. Ensures any outstanding batches have
* completed.
*/
void host_destroy(host **h) {
	free(*h);
	*h = NULL;
}

/**
* Creates a new server instance (i.e., thread) to handle processing the items
* contained in a batch (i.e., a listed list of job_node). InstanceHost will
* maintain a list of active instances, and if the host is requested to
* shutdown, ensures that all jobs are completed.
*
* @param job_batch_list A list containing the jobs in a batch to process.
*/
void host_request_instance(host *h, struct job_node *batch) {
	
	// Data must be processed (the data value squared) and returned to
	// the user (using result pass-by-reference).
	pthread_create(&h->t[h->num_instances],NULL,runner,(void*) batch);
}

pthread_t* create_instance(host *h) {
	return (pthread_t*)malloc(sizeof(pthread_t));
}

void add_instance(host *h) {
	h->num_instances++;
	pthread_t* temp = h->t;

	h->t = (pthread_t*)malloc(sizeof(pthread_t)*h->num_instances);
	free(temp);
}

