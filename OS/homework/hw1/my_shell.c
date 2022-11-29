#include <sys/wait.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAXLEN 1024
#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

char **lsh_split_line(char *line);
int lsh_execute(char **args);
int lsh_cd(char **args);
int lsh_help(char **args);
int lsh_exit(char **args);
int lsh_echo(char **args);
int lsh_record(char **args);
int lsh_replay(char **args);
int lsh_mypid(char **args);
void read_in(char **args);
int pipeline(char **args, int command_num);
int lsh_launch(char **args);
int count_command(char **args);
void lsh_loop(void);
char *lsh_read_line(void);
void back_ground(char **args);
void write_in(char **args);

char *cmd[100];              // record the multipipeline command
char **history;              // record the history, and its maximum space is 16
int tail = 0;                // record the history' last command address
int pipeline_pattern = 0;    // record whether command has pipeline
int input = 0;               // record whether command has input redirction
int output = 0;              // record whether command has output redirection
int back_ground_pattern = 0; // record whether command has background

char *builtin_str[] = {
    "help",
    "cd",
    "echo",
    "record",
    "replay",
    "mypid",
    "exit",
};
char *builtin_str_info[] = {
    "show all build-in function information",
    "change directory",
    "echo the strings to standard output",
    "show last-16 cmds you typed in",
    "re-execute the cmd showed in record",
    "find and print process-ids",
    "exit shell"};

int (*builtin_func[])(char **) = {
    &lsh_help,
    &lsh_cd,
    &lsh_echo,
    &lsh_record,
    &lsh_replay,
    &lsh_mypid,
    &lsh_exit};

int lsh_num_builtins()
{
    return sizeof(builtin_str) / sizeof(char *);
}

int lsh_cd(char **args)
{
    if (args[1] == NULL)
        fprintf(stderr, "lsh: expected argument to \"cd\"\n");
    else
    {
        if (chdir(args[1]) != 0)
            perror("lsh");
    }
    return 1;
}

int lsh_help(char **args)
{
    int backup = dup(STDOUT_FILENO);
    if (output == 1)
    {
        write_in(args);
    }
    int i;
    printf("----------------------------------------------- \n");
    printf("my little shell                                 \n");
    printf("Type program names and arguments, and hit enter.\n\n");
    printf("the following are built in:                     \n");
    for (i = 1; i <= lsh_num_builtins(); i++)
    {
        printf("%d:  %s   %s\n", i, builtin_str[i - 1], builtin_str_info[i - 1]);
    }

    printf("Use the \"man\" command for information on other programs.\n");
    printf("----------------------------------------------- \n");
    dup2(backup, STDOUT_FILENO);
    return 1;
}

int lsh_echo(char **args)
{
    int backup = dup(STDOUT_FILENO);
    if (output == 1)
        write_in(args);
    int i = 1;
    int cancel_line = 0;

    if (strcmp(args[1], "-n") == 0)// if  have -n, need to newline
    { 
        cancel_line = 1;
        i++;
    }
    while (1)
    {
        printf("%s ", args[i]);
        i++;
        if (args[i] == NULL)
            break;
    }
    if (cancel_line == 0 || output == 1)
        printf("\n");
    dup2(backup, STDOUT_FILENO);
    return 1;
}

int lsh_record(char **args)
{
    int backup = dup(STDOUT_FILENO);

    if (output == 1)
        write_in(args);
    printf("history cmd:\n");
    for (int i = 0; i < tail; i++)
        printf("%d: %s\n", i + 1, history[i]);

    dup2(backup, STDOUT_FILENO);
}
int lsh_replay(char **args)
{
}

int lsh_mypid(char **args)
{
    int backup = dup(STDOUT_FILENO);//change to file
    if (output)
        write_in(args);
    pid_t pid;
    size_t t;
    char path[1000] = "/proc/";
    char *line_of_file;
    if (strcmp(args[1], "-i") == 0) // if find this process pid
    { 
        pid = getpid();
        printf("%d\n", pid);
    }
    else if (strcmp(args[1], "-p") == 0)// if find a specific process's parrent pid
    { 
        strcat(path, args[2]);
        strcat(path, "/status");
        FILE *fp = fopen(path, "r");
        if (fp == NULL)
            printf("mypid -p: process id not exist\n");

        else
        {
            while (getline(&line_of_file, &t, fp) != EOF)
            {
                char parent_id[10] = "";

                char *loc1 = strstr(line_of_file, "PPid");//format: PPid: number
                if (loc1 != NULL)
                {
                    int k = 0;
                    for (int i = 0; line_of_file[i] != '\n'; i++)
                    {
                        if (line_of_file[i] <= 57 && line_of_file[i] >= 48)
                            parent_id[k++] = line_of_file[i];
                    }
                    printf("%s\n", parent_id);
                }
            }
        }
    }
    else if (strcmp(args[1], "-c") == 0)// if find a specific process's child pid
    { 
        strcat(path, args[2]);
        strcat(path, "/task/");
        strcat(path, args[2]);
        strcat(path, "/children");
        FILE *fp = fopen(path, "r");
        if (fp == NULL)
            printf("mypid -c: process id not exist\n");
        else
        {
            getline(&line_of_file, &t, fp);
            printf("%s\n", line_of_file);
        }
    }
    dup2(backup, STDOUT_FILENO);
    return 1;
}

int lsh_exit(char **args)
{
    printf("Good bye\n");
    return 0;
}

void read_in(char **args) //format: a < b, put b into a, and clear "<" and "b"
{
    int i = 0;

    while (args[i] != NULL)
    {
        if (strcmp(args[i], "<") == 0)
            break;
        i++;
    }
    char *p = (char *)malloc(MAXLEN * (sizeof(char)));
    strcpy(p, args[i + 1]);

    args[i] = NULL;
    args[i + 1] = NULL;
    if (output && !pipeline_pattern)
    {
        args[i] = (char *)malloc(sizeof(char) * strlen(args[i + 2]));
        args[i + 1] = (char *)malloc(sizeof(char) * strlen(args[i + 3]));
        strcpy(args[i], args[i + 2]);
        strcpy(args[i + 1], args[i + 3]);
        args[i + 2] = NULL;
        args[i + 3] = NULL;
    }

    int ret = open(p, O_RDONLY);
    dup2(ret, STDIN_FILENO);//stdin
    close(ret);
}
void write_in(char **args)//creat the output file
{
    int i = 0;
    while (args[i + 1] != NULL)
    {
        if (strcmp(args[i], ">") == 0)
            break;
        i++;
    }
    char *p;
    p = (char *)malloc(MAXLEN * (sizeof(char *)));
    strcpy(p, args[i + 1]);
    args[i] = NULL;
    args[i + 1] = NULL;
    int cr = creat(p, 0666);
    if (dup2(cr, STDOUT_FILENO) < 0)
        perror("Error:");
    close(cr);
}

void back_ground(char **args)//claer the pattern & to avoid error 
{
    int i = 0;
    while (strcmp(args[i], "&") != 0)
    {
        i++;
        if (args[i] == NULL)
            break;
    }
    if (args[i] != NULL)
        args[i] = NULL;
}

int count_command(char **args)//count the "|" number and put it in the cmd array
{
    int i = 0;
    int count = 0;
    int cmd_start_loc = 0;
    for (i = 0; args[i] != NULL; i++)
    {
        if (strcmp(args[i], "|") == 0)
        {
            cmd[count] = (char *)malloc(sizeof(char) * 1024);
            for (int j = cmd_start_loc; j != i; j++)
            {
                strcat(cmd[count], args[j]);
                strcat(cmd[count], " ");
            }
            cmd_start_loc = i + 1;
            count++;
        }
    }
    cmd[count] = (char *)malloc(sizeof(char) * 1024);
    for (int j = cmd_start_loc; args[j] != NULL; j++)
    {
        strcat(cmd[count], args[j]);
        strcat(cmd[count], " ");
    }
    count++;
    return count;
}
int pipeline(char **args, int command_num)
{
    char **tmp[100];
    for (int i = 0; i < command_num; i++)
        tmp[i] = lsh_split_line(cmd[i]);        //the array stores all commands
    int fd[command_num - 1][2];                 //don't need to create the first pipe
    for (int i = 0; i < command_num - 1; i++)   //create pipe
        pipe(fd[i]);
    pid_t pid;      //child's pid
    pid_t back_pid; //parent's pid
    for (int i = 0; i < command_num; i++)
    {
        pid = fork();
        if (pid == 0)// child
        { 
            if (i == 0 && input == 1)//if there have read_in redirection, it must in the first command 
            {
                read_in(tmp[i]);
                input = 0;
            }
            else if (i != 0)
                dup2(fd[i - 1][0], 0);//make the front pipe open read

            if (i == (command_num - 1) && output == 1)//if there have write_in redirection, it must in the last command 
            {
                write_in(tmp[i]);
                output = 0;
            }
            else if (i != command_num - 1)
                dup2(fd[i][1], 1);//make the back pipe open write

            if (i == command_num - 1 && back_ground_pattern)//execute to end, if background, printf pid
                printf("[Pid]: %d\n", back_pid);

            for (int k = 0; k < command_num - 1; k++)
            {
                for (int j = 0; j < 2; j++)
                    close(fd[k][j]);//close the pipe
            }

            if (back_ground_pattern)
                back_ground(tmp[i]);
            lsh_execute(tmp[i]);
            exit(0);
        }
        else// parent
        { 
            back_pid = getpid();
            if (i != 0)
            {
                close(fd[i - 1][0]);//close 
                close(fd[i - 1][1]);
            }
        }
        waitpid(pid, NULL, 0);
    }

    return 1;
}
int lsh_launch(char **args)//not built in command
{
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0)// Child process
    {
        if (pipeline_pattern == 0)
        {
            if (input)
                read_in(args);
            if (output)
                write_in(args);
        }

        if (execvp(args[0], args) == -1)
            perror("lsh");

        exit(EXIT_FAILURE);
    }

    else if (pid < 0)// Error forking
        perror("lsh");

    else // Parent process
    {
        do
        {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}

int lsh_execute(char **args)
{
    int i;
    if (args[0] == NULL)// empty command entered
        return 1;

    if (back_ground_pattern == 1 && pipeline_pattern != 1)// if have background but not pipeline
    { 
        back_ground(args);
        printf("[Pid]: %d\n", getpid());
        int status;
        pid_t pid;
        pid = fork(); // fork a child processor
        if (pid == 0) // child
        { 
            int isBuilt = 0;// 判斷是否是內建command
            for (i = 0; i < lsh_num_builtins(); i++)
            {
                if (strcmp(args[0], builtin_str[i]) == 0)
                {
                    (*builtin_func[i])(args);
                    isBuilt = 1;
                }
            } 
            if (isBuilt == 0)
                lsh_launch(args);
            exit(EXIT_FAILURE);
        }
        else if (pid > 0)//parent
        {
            waitpid(pid, &status, WUNTRACED);//wait child finish
            return 1;
        }
    }
    else
    {
        for (i = 0; i < lsh_num_builtins(); i++)
        {
            if (strcmp(args[0], builtin_str[i]) == 0)
                return (*builtin_func[i])(args);
        }
    }
    return lsh_launch(args);
}

char *lsh_read_line(void)
{
    int bufsize = MAXLEN; // put input command
    int position = 0;     // record the next address to put in buffer
    char *buffer = malloc(sizeof(char) * bufsize);
    int c;

    if (!buffer)
    { // error
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    while (1)
    {                  // read input, and check if space is out of limit
        c = getchar(); // read a character
        if (c == EOF)
        {
            exit(EXIT_SUCCESS);
        }
        else if (c == '\n')
        {
            buffer[position] = '\0';
            return buffer;
        }
        else
        {
            buffer[position] = c; // put input into buffer
        }
        position++;

        if (position >= bufsize)
        {
            bufsize += MAXLEN; // if exceed the buffer, reallocate
            buffer = realloc(buffer, bufsize);
            if (!buffer)
            {
                fprintf(stderr, "lsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

char **lsh_split_line(char *line)
{
    int bufsize = LSH_TOK_BUFSIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char *)); // use to put the string which have seperated
    char *token, **tokens_backup;                     // token is use to get the current seperated string, backup is used to saved the tokens when space is out of limit

    if (!tokens)
    {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, LSH_TOK_DELIM); // used to seperate the string
    while (token != NULL)
    {
        tokens[position] = token; // if it's not null, token put to tokens
        position++;

        if (position >= bufsize)
        { // out of limit, neew to realloc
            bufsize += LSH_TOK_BUFSIZE;
            tokens_backup = tokens;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens)
            { // realloc error, like there is nothing in tokens
                free(tokens_backup);
                fprintf(stderr, "lsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, LSH_TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}

void lsh_loop(void)
{
    char *line;  //讀取進來的整行
    char **args; //切割後的string
    int status; // if status = 0, exit. else, continue
    history = (char **)malloc(sizeof(char *) * 16); // create 16 spaces for history
    do
    {
        int i, j;
        int k = 0;
        printf(">>> $ ");
        line = lsh_read_line();

        /* initialize all identifer */
        input = 0;
        output = 0;
        back_ground_pattern = 0;
        pipeline_pattern = 0;

        if (strcmp(line, "\0") == 0 || line[0] == ' ') // input enter or space
            continue;
        if (strstr(line, ">"))// output file
        { 
            output = 1;
        }
        if (strstr(line, "<"))// input file
        { 
            input = 1;
        }
        if (strstr(line, "&"))// background
        { 
            back_ground_pattern = 1;
        }
        if (strstr(line, "|"))// multipipeline
        { 
            pipeline_pattern = 1;
        }
        if (!strstr(line, "replay"))// no replay, just record current command
        { 
            if (tail <= 15) // if doesn't over the space limit, just malloc a new space and put it in the history
            {                                                                
                history[tail] = (char *)malloc(sizeof(char) * strlen(line)); // create a "line" space for every history row
                strcpy(history[tail], line);
                tail++;
            }
            else            // if out of limit, push every space to front, and delete the head space
            {                           
                char *ptr = history[0]; // remember the head pointer, later to delete

                for (int i = 0; i < tail - 1; i++)
                {
                    history[i] = history[i + 1]; // move back pointer to front
                }
                history[tail - 1] = (char *)malloc(sizeof(char) * strlen(line)); // create a new history row
                strcpy(history[tail - 1], line);
                free(ptr); // delete the head pointer
            }
            args = lsh_split_line(line);
        }
        else                        // replay, format: replay 16
        { 
            args = lsh_split_line(line);
            int number = atoi(args[1]);
            if (number >= 1 && number < tail + 1)
            {                                      // check if out of limit
                strcpy(line, history[number - 1]); // use the target address to replace the replay command
                if (tail <= 15)
                {
                    history[tail] = (char *)malloc(sizeof(char) * strlen(line));
                    strcpy(history[tail], line);
                    tail++;
                }
                else
                {
                    char *ptr = history[0];
                    for (int i = 0; i < tail - 1; i++)
                    {
                        history[i] = history[i + 1];
                    }
                    history[tail - 1] = (char *)malloc(sizeof(char) * strlen(line));
                    strcpy(history[tail - 1], line);
                    free(ptr);
                }
                args = lsh_split_line(line);
            }
            else            // if replay + number, the number is error
            { 
                printf("replay: wrong args\n");
            }
        }
        
        if (pipeline_pattern)//if pipeline
        {
            int command_num = count_command(args);
            status = pipeline(args, command_num);//先分割字串後，之後會再執行lsh_execute
        }
        else
            status = lsh_execute(args);

        free(line);
        free(args);

    } while (status);
}

int main(int argc, char **argv)
{
    // Load config files, if any.
    printf("===========================================\n");
    printf("* welcome to my shell:                    *\n");
    printf("*                                         *\n");
    printf("* type \"help\" to see buildin function.  *\n");
    printf("*                                         *\n");
    printf("* if you wants to do things below         *\n");
    printf("* + redirection: \">\" or \">\"           *\n");
    printf("* + pipe: \"|\"                           *\n");
    printf("* + background: \"&\"                     *\n");
    printf("* make sure they are seperated by space   *\n");
    printf("*                                         *\n");
    printf("* have fun!!                              *\n");
    printf("===========================================\n");
    // Run command loop.
    lsh_loop();

    // Perform any shutdown/cleanup.
    return EXIT_SUCCESS;
}
