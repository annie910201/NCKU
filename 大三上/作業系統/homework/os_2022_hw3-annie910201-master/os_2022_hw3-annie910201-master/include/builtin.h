#ifndef BUILTIN_H
#define BUILTIN_H
//function
int help(char **args);
int cd(char **args);
int echo(char **args);
int exit_shell(char **args);
int record(char **args);
int mypid(char **args);
int add(char **args);
int del(char **args);
int ps(char **args);
int start(char **args);
void timer();
void signal_handler();

//record
extern const char *builtin_str[];
extern const int (*builtin_func[]) (char **);
extern const char *task_str[];
extern const void (*task_func[])(void);
extern int num_builtins();

//variable
int count_tid;
int count_rr;
int count_RR_timer;

#endif
