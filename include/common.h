#ifndef COMMON
#define COMMON 1
	
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <fcntl.h>

#include <types.h>
#include <slist.h>
#include <stack.h>
#include <hashtable.h>

#define swap(X, Y, type) {	\
	type temp;				\
	temp = X;  				\
	X = Y;					\
	Y = temp;				\
}

int BACKGROUND_ISSET;
htable *ptable;
htable *vtable;
stack *curr_cp;

void promptusr();
	
void echo_cmd(char *argv[]);
void exit_cmd(char *argv[]);

void pwd_cmd(char *argv[]);

void cd_cmd(char *argv[]);

void fg_cmd(char *argv[]);

void bg_cmd(char *argv[]);
void jobs_cmd(char *argv[]);

void print_jobs();

status_t process_str(char *str);

status_t init();

int execute_cmd(char *file, char *argv[]);

pid_t child_process_cmd(int argc, char *argv[]);

void print_jobs();
void add_bg(pid_t pid, char *argv[]);
void add_fg(pid_t pid, char *argv[]);
void waitif();
void signal_handler(int signum);
void sigchld_handler(int signum, siginfo_t *sinfo, void *nope);
#endif
