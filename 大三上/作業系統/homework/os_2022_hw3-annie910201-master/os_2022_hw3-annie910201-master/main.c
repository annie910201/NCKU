#include <stdlib.h>
#include "include/shell.h"
#include "include/command.h"
#include <stdio.h>
#include <string.h>
#include "include/builtin.h"
// #include "include/task.h"

int alg = 0;
int main(int argc, char *argv[])
{
	history_count = 0;
	for (int i = 0; i < MAX_RECORD_NUM; ++i)
    	history[i] = (char *)malloc(BUF_SIZE * sizeof(char));

	if(strcmp(argv[1], "FCFS") == 0)
		alg = 0;
	
	else if (strcmp(argv[1], "RR") == 0)
		alg = 1;

	else if (strcmp(argv[1], "PP") == 0)
		alg = 2;
	
	count_tid = 0;
	count_rr=0;//record the TERMINATED context
	count_RR_timer = 0;
	shell();

	for (int i = 0; i < MAX_RECORD_NUM; ++i)
    	free(history[i]);

	return 0;
}
