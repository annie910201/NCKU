#ifndef SHELL_H
#define SHELL_H

#include "command.h"

//function
int execute(struct pipes *);
int spawn_proc(int, int, struct cmd *, struct pipes *);
int fork_pipes(struct cmd *);
void shell();

//variable
int alg;//record algorithm
#endif
