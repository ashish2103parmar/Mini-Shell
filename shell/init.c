#include <common.h>
#include <types.h>
#include <slist.h>
#include <stack.h>
#include <hashtable.h>
#include <signal.h>

status_t init()
{
	ptable = create_htable(64u);
	vtable = create_htable(64u);
	curr_cp = NULL;

	struct sigaction *act = malloc(sizeof (struct sigaction));
	memset(act, 0, sizeof (sizeof (struct sigaction)));
	act->sa_sigaction = sigchld_handler;
	act->sa_flags = SA_NOCLDSTOP | SA_SIGINFO;
	if (sigaction(SIGCHLD, act, NULL))
	{
		error_msg("error : init : sigaction\n");
		return failure;
	}
	if (signal(SIGINT, signal_handler))
	{
		error_msg("error : init : sigaction\n");
		return failure;
	}
	if (signal(SIGTSTP, signal_handler))
	{
		error_msg("error : init : sigaction\n");
		return failure;
	}

	char *buff = malloc(200);
	getcwd(buff, 200);
	if (hash_insert(vtable, "SHELL", T_STR, (void *)buff, 0))
	{
		error_msg("error : init : insert\n");
		return failure;
	}
	if (hash_insert(vtable, "$", T_INT, (void *)getpid(), 0))
	{
		error_msg("error : init : insert\n");
		return failure;
	}
	
	
	if (hash_insert(ptable, "cd", T_FUN, (void *)cd_cmd, 0))
	{
		error_msg("error : init : insert\n");
		return failure;
	}
	
	if (hash_insert(ptable, "pwd", T_FUN, (void *)pwd_cmd, 0))
	{
		error_msg("error : init : insert\n");
		return failure;
	}
	
	if (hash_insert(ptable, "echo", T_FUN, (void *)echo_cmd, 0))
	{
		error_msg("error : init : insert\n");
		return failure;
	}

	if (hash_insert(ptable, "exit", T_FUN, (void *)exit_cmd, 0))
	{
		error_msg("error : init : insert\n");
		return failure;
	}
	
	if (hash_insert(ptable, "fg", T_FUN, (void *)fg_cmd, 0))
	{
		error_msg("error : init : insert\n");
		return failure;
	}
	
	if (hash_insert(ptable, "bg", T_FUN, (void *)bg_cmd, 0))
	{
		error_msg("error : init : insert\n");
		return failure;
	}
	if (hash_insert(ptable, "jobs", T_FUN, (void *)jobs_cmd, 0))
	{
		error_msg("error : init : insert\n");
		return failure;
	}
	return success;
}


