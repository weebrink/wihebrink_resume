/**
*  LoadBalancer.c
*
*  @author Wihebrink
*  @version 9/15/2021
*/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "LoadBalancer.h"
#include "InstanceHost.h"

struct balancer {
	struct host *host;
	struct job_node *head;
	pthread_mutex_t *lock;
	int number_of_requests;
	int batch_size;
};

void balancer_destroy(balancer **lb) {
	free(*lb);
	*lb = NULL;
}

void balancer_add_job(balancer *lb, int user_id, int data, int *data_return) {
	pthread_mutex_lock(lb->lock);
	
	printf("LoadBalancer: Received new job from user #%d to process data = %d and store it at %p. \n", user_id, data, data_return);
	lb->number_of_requests++;

	struct job_node *job = (struct job_node*)malloc(sizeof(struct job_node));
	job->data = data;
	job->data_result = data_return;
	job->next = lb->head;
	lb->head = job;
	
	if (lb->number_of_requests == lb->batch_size) {
		host_request_instance(lb->host, lb->head);
	}

	pthread_mutex_unlock(lb->lock);
}

balancer *balancer_create(int batch_size) {
	balancer *b = (balancer*)malloc(sizeof(balancer));
	b->head = (struct job_node*)malloc(sizeof(struct job_node)*batch_size);
	pthread_mutex_init(b->lock, NULL);
	b->number_of_requests = batch_size;
	b->number_of_requests = 0;
	b->host = host_create();
	return b;
}

