#ifndef RESOURCE_H
#define RESOURCE_H
#include <stdbool.h>

//function
void get_resources(int, int *);
void release_resources(int, int *);

//variable
extern bool resource_ava[8] ;
#endif
