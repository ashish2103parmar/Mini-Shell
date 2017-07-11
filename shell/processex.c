#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <types.h>
#include <hashtable.h>

extern htable *ptable;

int execute_cmd(char *file, char *argv[])
{
	void (*fptr)(char *[]);
	if (hash_search(ptable, file, (void **)&fptr))
	{
		fptr(argv);
	}
	else
	{
		if (-1 == execvp(file, argv))
		{
			perror(argv[1]);
			_exit(3);
		}
	}
	return -1;
}

pid_t child_process_cmd(int argc, char *argv[])
{
	int idx, jdx = 0, status;
	pid_t pid;
	int *cmd = malloc(sizeof (int));

	cmd[jdx++] = 1;
	for (idx = 1; idx < argc; idx++)
	{
		if (!strcmp(argv[idx], "|"))
		{
			cmd = realloc(cmd, sizeof (int) * (jdx + 1));
			if (cmd == NULL)
				return 0;
			argv[idx++] = NULL;
			cmd[jdx++] = idx;
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

	/* create multiple childs(3)*/
	for (idx = 0; idx < jdx; idx++)
	{
		/* switch parent child */
		switch (fork())
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

				/* exec ls */
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



	return pid;
}
