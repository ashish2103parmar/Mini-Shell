#include <common.h>
#include <types.h>
#include <hashtable.h>


int execute_cmd(char *file, char *argv[])
{
	/*
	printf("file : %s\nargs : ", file);
	   int i;
	   for (i = 0; argv[i]; i++)
	   printf("%s ", argv[i]);
	   printf("\n");	
	*/
	void (*fptr)(char *argv[]);
	if (hash_search(ptable, file, (void **)&fptr))
	{
		fptr(argv);
		return 0;
	}
	else
	{
		
		pid_t pid;
		switch (pid = fork())
		{
			case -1:
				perror("fork");
				break;
			case 0:
			
				if (-1 == execvp(file, argv))
				{
					perror(argv[1]);
					_exit(3);
				}
				
				break;
			default:
				return pid;
		}			
	}
	return -1;
}

pid_t child_process_cmd(int argc, char *argv[])

{
	int idx, jdx = 0, status;
	pid_t pid;
	int *cmd = malloc(sizeof (int));

	cmd[jdx++] = 0;
	for (idx = 1; idx < argc; idx++)
	{
		if (!strcmp(argv[idx], "|"))
		{
			cmd = realloc(cmd, sizeof (int) * (jdx + 1));
			if (cmd == NULL)
				return 0;
			argv[idx] = NULL;
			cmd[jdx++] = idx + 1;
		}
	}

	int pd[jdx - 1][2], pidx;
/* create pipe */


	for (idx = 0; idx < jdx - 1; idx++)
		if (pipe(pd[idx]) == -1)
		{
			perror("pipe");
			_exit(1);
		}

	/* create multiple childs(3) */
	for (idx = 0; idx < jdx; idx++)
	{
		/* switch parent child */
		switch (pid = fork())
		{
			case -1:
				/* fork error */
				perror("fork");
				_exit(2);
			case 0:
				/* child - ls */
				/* dup stdout */
				for (pidx = 0; pidx < jdx - 1; pidx++)
				{
					if ( pidx == idx)
						dup2(pd[idx][1], 1);
					else
						close(pd[pidx][1]);
				}
				if (idx)
					dup2(pd[idx - 1][0], 0);
				
				/*
				   printf("file : %s\nargs : ", argv[cmd[idx]]);
				   int i;
				   for (i = 0; (argv + cmd[idx])[i]; i++)
				   printf("%s ", (argv + cmd[idx])[i]);
				   printf("\n");	
				 */
				/* exec ls */
				if (BACKGROUND_ISSET)
				{
					BACKGROUND_ISSET = 0;
				}
				if (-1 == execvp(argv[cmd[idx]], argv + cmd[idx]))
				{
					perror(argv[1]);
					_exit(3);
				}
				_exit(0);
				break;
			default:
				continue;
		}
	}		

	for (pidx = 0; pidx < jdx; pidx++)
	{
		close(pd[pidx][1]);
	}	
	
	
	free(cmd);
	return pid;
}

