#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>
#include <ucontext.h>
#include "../include/builtin.h"
#include "../include/command.h"
#include "../include/function.h"
#include "../include/task.h"
# define STACK_SIZE 1024

const char *task_str[] = {"task1", "task2", "task3", "task4", "task5", "task6", "task7", "task8", "task9", "test_exit", "test_sleep", "test_resource1", "test_resource2", "idle" };
const void (*task_func[])(void)={&task1, &task2, &task3, &task4, &task5, &task6, &task7, &task8, &task9, &test_exit, &test_sleep, &test_resource1, &test_resource2, &idle };
ucontext_t current_task;
char *state[] = {"READY", "RUNNING", "TERMINATED", "WAITING"};
struct Task
{
	ucontext_t new_task;
	char* task_name;
	char* fun_name;
	char* state;
	int priority;
	int waiting_time;
	int tid;
	int runnung_time;
	struct Task *next;
	int resource_num;
	int *resource;
	int turnaround_time;
};
struct Schedule{
	struct Task *task;
	struct Schedule *next;
};
int help(char **args)
{
	int i;
    printf("--------------------------------------------------\n");
  	printf("My Little Shell!!\n");
	printf("The following are built in:\n");
	for (i = 0; i < num_builtins(); i++) {
    	printf("%d: %s\n", i, builtin_str[i]);
  	}
	printf("%d: replay\n", i);
    printf("--------------------------------------------------\n");
	return 1;
}

int cd(char **args)
{
	if (args[1] == NULL) {
    	fprintf(stderr, "lsh: expected argument to \"cd\"\n");
  	} else {
    	if (chdir(args[1]) != 0)
      		perror("lsh");
	}
	return 1;
}

int echo(char **args)
{
	bool newline = true;
	for (int i = 1; args[i]; ++i) {
		if (i == 1 && strcmp(args[i], "-n") == 0) {
			newline = false;
			continue;
		}
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
	}
	if (newline)
		printf("\n");

	return 1;
}

int exit_shell(char **args)
{
	return 0;
}

int record(char **args)
{
	if (history_count < MAX_RECORD_NUM) {
		for (int i = 0; i < history_count; ++i)
			printf("%2d: %s\n", i + 1, history[i]);
	} else {
		for (int i = history_count % MAX_RECORD_NUM; i < history_count % MAX_RECORD_NUM + MAX_RECORD_NUM; ++i)
			printf("%2d: %s\n", i - history_count % MAX_RECORD_NUM + 1, history[i % MAX_RECORD_NUM]);
	}
	return 1;
}

bool isnum(char *str)
{
	for (int i = 0; i < strlen(str); ++i) {
    	if(str[i] >= 48 && str[i] <= 57)
			continue;
        else
		    return false;
  	}
  	return true;
}

int mypid(char **args)
{
	char fname[BUF_SIZE];
	char buffer[BUF_SIZE];
	if(strcmp(args[1], "-i") == 0) {

	    pid_t pid = getpid();
	    printf("%d\n", pid);
	
	} else if (strcmp(args[1], "-p") == 0) {
	
		if (args[2] == NULL) {
      		printf("mypid -p: too few argument\n");
      		return 1;
    	}

    	sprintf(fname, "/proc/%s/stat", args[2]);
    	int fd = open(fname, O_RDONLY);
    	if(fd == -1) {
      		printf("mypid -p: process id not exist\n");
     		return 1;
    	}

    	read(fd, buffer, BUF_SIZE);
	    strtok(buffer, " ");
    	strtok(NULL, " ");
	    strtok(NULL, " ");
    	char *s_ppid = strtok(NULL, " ");
	    int ppid = strtol(s_ppid, NULL, 10);
    	printf("%d\n", ppid);
	    
		close(fd);

  	} else if (strcmp(args[1], "-c") == 0) {

		if (args[2] == NULL) {
      		printf("mypid -c: too few argument\n");
      		return 1;
    	}

    	DIR *dirp;
    	if ((dirp = opendir("/proc/")) == NULL){
      		printf("open directory error!\n");
      		return 1;
    	}

    	struct dirent *direntp;
    	while ((direntp = readdir(dirp)) != NULL) {
      		if (!isnum(direntp->d_name)) {
        		continue;
      		} else {
        		sprintf(fname, "/proc/%s/stat", direntp->d_name);
		        int fd = open(fname, O_RDONLY);
        		if (fd == -1) {
          			printf("mypid -p: process id not exist\n");
          			return 1;
        		}

        		read(fd, buffer, BUF_SIZE);
        		strtok(buffer, " ");
        		strtok(NULL, " ");
        		strtok(NULL, " ");
		        char *s_ppid = strtok(NULL, " ");
		        if(strcmp(s_ppid, args[2]) == 0)
		            printf("%s\n", direntp->d_name);

        		close(fd);
     		}
	   	}
    	
		closedir(dirp);
	
	} else {
    	printf("wrong type! Please type again!\n");
  	}
	
	return 1;
}

int add(char **args)//add {task name} {function name} {priority}
{
	struct Task task;
	task.fun_name = args[2];
	task.task_name = args[1];
	task.state =state[0];
	task.priority = atoi(args[3]);
	task.waiting_time=0;
	task.runnung_time=0;
	task.next = NULL;
	
	getcontext(&current_task);
	current_task.uc_link = NULL;
	current_task.uc_stack.ss_sp = malloc(STACK_SIZE);
	current_task.uc_stack.ss_size = STACK_SIZE;
	current_task.uc_flags = 0;
	
	task.new_task = current_task;

	for(int i=0;i<14;i++){
		if(strcmp(task.fun_name, task_str[i])==0){
			makecontext(&task.new_task, task_func[i], 0);
		}
	}
	printf("Task %s is ready.\n", task.task_name);
	// setcontext(&task.new_task);
	return 1;
}

int del(char **args)//del {task name}
{
	struct Task* tmp;
	getcontext(&current_task);
	tmp->new_task = current_task;  
	while(1){
		if(strcmp(tmp->task_name,args[1])==0){
			tmp->state = state[2];//terminated
			break;
		}
		else{
			tmp= tmp->next;
		}
	}
	printf("Task %s is killed.\n", tmp->task_name);
	// free(tmp);
	return 1;
}

int ps(char **args)
{
	// struct Task* tmp;
	// while(1){
	// 	if(tmp->next==NULL){
	// 		break;
	// 	}
	// 	else{
	// 		tmp= tmp ->next;
	// 		if(strcmp(tmp->state, "TERMINATED")==0){//state == terminated
	// 			printf("%3d|%10s|%10s|%8d|%8d|%10s|%10s|%8d", getpid(), tmp->task_name, tmp->state, , , , ,tmp->priority);
	// 		}
	// 		else{
	// 			printf("%3d|%10s|%10s|%8d|%8d|%10s|%10s|%8d", getpid(), tmp->task_name, tmp->state, , , "none", ,tmp->priority);
	// 		}
			
	// 	}
	// }
	return 1;
}

int start(char **args)
{
	// printf("Start simulation\n");
	// getcontext(&current_task);
	// setcontext(&current_task);
	return 1;
}

const char *builtin_str[] = {
 	"help",
 	"cd",
	"echo",
 	"exit",
 	"record",
	"mypid",
	"add",
	"del",
	"ps",
	"start"
};

const int (*builtin_func[]) (char **) = {
	&help,
	&cd,
	&echo,
	&exit_shell,
  	&record,
	&mypid,
	&add,
	&del,
	&ps,
	&start
};

int num_builtins() {
	return sizeof(builtin_str) / sizeof(char *);
}
