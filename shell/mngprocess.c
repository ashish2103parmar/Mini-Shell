#include <common.h>

typedef enum
{
	done,
	running,
	stopped,
	killed,
	terminated
} pstate_t;

typedef struct {
	int id;
	pid_t pid;
	char **argv;
	pstate_t state;
} my_ps;

int waiting = 0;
stack mprocess = NULL;
my_ps fg_process;

void print(my_ps *tmp)
{
	printf("%d\t", tmp->pid);
			switch (tmp->state)
			{
				case done:
					printf("done");
					break;
				case running:
					printf("running");
					break;
				case stopped:
					printf("stopped");
					break;
				case killed:
					printf("killed");
					break;
				case terminated:
					printf("terminated");
					break;
				default:
					printf("unknown");
			}
			printf("\t\t");
			int idx = 0;
			while (tmp->argv[idx])
				printf("%s ", tmp->argv[idx++]);
			printf("\n");

}

status_t push_pdata()
{
	my_ps *tmp = malloc(sizeof (my_ps));
	if (tmp)
	{
		if (mprocess)
			tmp->id = ((my_ps *)mprocess->data)->id + 1;
		else
			tmp->id = 1;
		tmp->pid = fg_process.pid;
		tmp->argv = fg_process.argv;
		tmp->state = fg_process.state;
		if (push(&mprocess, create_node(T_PRO, (void *)tmp)))
		{
			print(tmp);
			fg_process.id = 0;
			fg_process.pid = 0;
			waiting = 0;
		}
		else
		{
			error_msg("process stack");
			return failure;
		}
		return success;
	}
	return failure;
}

void print_jobs()
{
	slist *ptr = mprocess;
	if (!ptr)
		error_msg("jobs: No such jobs");
	else
		while (ptr)
		{	
			print((my_ps *)ptr->data);	
			ptr = ptr->next;
		}
}

char **make_copy(char **argv)
{
	int idx = 0;
	char **ptr = NULL;
	while (argv[idx])
	{
		ptr = realloc(ptr, sizeof (char *) * (idx + 1));
		ptr[idx] = malloc(strlen(argv[idx]) + 1);
		strcpy(ptr[idx], argv[idx]);
		idx++;
	}
	return ptr;
}

void free_copy(char **argv)
{
	int idx = 0;
	while (argv[idx])
	{
		free(argv[idx]);
		idx++;
	}
	free(argv);
}

void add_bg(pid_t pid, char *argv[])
{
	if (pid)
	{
		fg_process.pid = pid;
		fg_process.argv = make_copy(argv);
		fg_process.state = running;
		if (!push_pdata())
			error_msg("push failure");
	}
	else
	{
		int status = ((my_ps *)mprocess->data)->state;
		switch (status)
		{
			case running:
				error_msg("bg: job already in background");
				break;
			case stopped:
				((my_ps *)mprocess->data)->state = running;
				print((my_ps *)mprocess->data);	
				kill(((my_ps *)mprocess->data)->pid, SIGCONT);
				break;
			default:
				error_msg("bg: invalid state or not yet added");
				break;
		}
	}
}

void add_fg(pid_t pid, char *argv[])
{	
	if (!pid)
	{
		slist *node = NULL;
		if (pop(&mprocess, &node))
		{
			if (node)
			{
				my_ps *tmp = (my_ps *)node->data;
				if (tmp)
				{	
					switch (tmp->state)
					{
						case running:
							break;
						case stopped:
							kill(tmp->pid, SIGCONT);
							break;
						default:
							error_msg("fg: invalid state or not yet added");
							break;
					}
					fg_process.pid = tmp->pid;
					fg_process.argv = tmp->argv;
					fg_process.state = running;
					print(&fg_process);
				}
				else
				{
					error_msg("fg: data not found");
					return;
				}
			}
			else
			{
				error_msg("fg: Node is NULL");
				return;
			}
		}
		else
		{
			error_msg("fg: No such jobs");
			return;
		}
	}
	else
	{
		fg_process.pid = pid;
		fg_process.argv = make_copy(argv);
	}
	waiting = 1;
}

void waitif()
{
	while (waiting);
}

void signal_handler(int signum)
{
	switch (signum)
	{
		case SIGINT:
			{
				printf("\n");
				if (waiting)
				{
					kill(fg_process.pid, SIGINT);	
					waiting = 0;
					fg_process.id = 0;
					fg_process.pid = 0;
				}
				else
				{
					promptusr();
					fflush(stdout);
				}
				break;
			}
		case SIGTSTP:
			{	

				printf("\n");		
				if (waiting)
				{
					kill(fg_process.pid, SIGSTOP);
					fg_process.state = stopped;
					if (!push_pdata())
						error_msg("push failure");
					else
						waiting = 0;
				}
				else
				{
					promptusr();	
					fflush(stdout);
				}
			}
		default:
			break;
	}
}

void sigchld_handler(int signum, siginfo_t *sinfo, void *nope)
{
	waitpid(sinfo->si_pid, NULL, 0);
	if (sinfo->si_pid == fg_process.pid)
	{
		waiting = 0;
		fg_process.id = 0;
		fg_process.pid = 0;
	}
	else
	{
		slist *ptr = mprocess, *prev = NULL;
		while (ptr)
		{
			if (((my_ps *)ptr->data)->pid == sinfo->si_pid)
			{
				((my_ps *)ptr->data)->state = done;
				print((my_ps *)ptr->data);	
				if (ptr->next)
					ptr = ptr->next;
				delete_first(prev ? &prev->next: &mprocess);
			}
			prev = ptr;
			ptr = ptr->next;
		}
	}
	if ((void *)-1 == hash_insert(vtable, "?", T_INT, (void *)sinfo->si_status, 1))
	{
		error_msg("error : ? : insert\n");
	}
}
