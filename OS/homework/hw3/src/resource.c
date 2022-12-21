#include "../include/resource.h"
#include <stdio.h>
#include <stdlib.h>
#include "../include/task.h"
#include <ucontext.h>
bool resource_ava[8] = {false,false,false,false,false,false,false,false };
void get_resources(int count, int *resources)
{
    bool get_res = true;
    running->task->resource_num = running->count_after_schedule;
    running->task->wait_to_runnung = 0;
    for(int i=running->count_after_schedule; i<running->count_after_schedule+count ;i++){
        if(resource_ava[resources[i]]){
            get_res = false;
        }
        running->task->resource[i] = resources[i - running->count_after_schedule];
    }
    if(get_res){
        printf("Task %s gets resources", running->task->task_name );
        for(int i=0;i<count;i++){
            printf(" %d",resources[i]);
            resource_ava[resources[i]] = trus;

        }

        printf("\n");
        running->task->resource_num+=count;
        running->count_after_schedule = running->task->resource_num;
    }
    else{
        running->task->wait_to_runnung = 1;
        running->task->runnung_time ++;
        running->task->resource_num+=count;
        running->task->state = "WAITING";
        setcontext(&idle_context);
    }
}

void release_resources(int count, int *resources)
{
    for(int i=0;i<count;i++){
        resource_ava[resources[i]] = false;
        running->task->resource[i] = resources[i];
    }
    printf("Task %s releases resource", running->task->task_name);
    for(int i=0;i<count;i++){
        printf(" %d", resources[i]);
    }
    printf("\n");
}
