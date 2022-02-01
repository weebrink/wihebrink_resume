/*
* Description: Writes a LKM for the Linux kernel that displays the following details
* 	       for all the processes whose PID is greater than an integer given by the user
*	       as a module parameter.
*
* @author Wihebrink
* @version 9/8/2021
*/

MODULE_LICENSE("GPL")

#define DEVICE_NAME "WihebrinkLKM"

#include <linux/init.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/printk.h>

#define PROCESS_NAME 
#define PID 
#define STATE 1
#define PRIORITY 120
#define STATIC-PRIORITY 120
#define NORMAL-PRIORITY 120

struct Modules {
	char* process_name;
	int pid;
	int state;
	int priority;
	int static-priority;
	int normal-priority;
};

int inp_pid = 0;

module_param(inp_pid, int, S_IRUSR | S_IWUSR);

/* This function is called when the module is loaded. */
int lkm_init(void) {
	printk(KERN_INFO "Loading Module...\n");
	(Modules*) kernels = malloc(sizeof(Modules*));
	pid_t pid;
	
	pid = fork();
	if (pid > 0) {
		printk(KERN_ALERT "This is the parent process");
		printf("PROCESS     PID        STATE     PRIO     ST_PRIO    NORM_PRIO");
		printf("            %d         %d        %d        %d        %d", +
			PROCESS_NAME, pid = getpid(), STATE, PRIORITY, STATIC-PRIORITY, +
			NORMAL-PRIORITY);
	}
	else {
		printk(KERN_ALERT "This is the child process");
		printf("PROCESS     PID        STATE     PRIO     ST_PRIO    NORM_PRIO");
		printf("            %d         %d        %d        %d        %d", +
			PROCESS_NAME, pid = getpid(), STATE, PRIORITY, STATIC-PRIORITY, +
			NORMAL-PRIORITY);
	}
	
	return 0;
}

/* This function is called when the module is removed. */
void lkm_exit(void) {
	printk(KERN_INFO "Removing Module...\n");
	free(kernels);
}

module_init( lkm_init );
module_exit( lkm_exit );
