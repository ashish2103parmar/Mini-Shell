#include <common.h>
#include <types.h>
#include <slist.h>
#include <stack.h>
#include <hashtable.h>

char **replace_str(char *argv[])
{
	int idx;
	for (idx = 0; argv && argv[idx]; idx++)
	{
		if (argv[idx][0] == '$')
		{
			void *ptr;
			char buff[100];
			/*
			argv[idx] = malloc(strlen(ptr) + 1);
			strcpy(argv[idx], ptr);
			*/
			int type;
			if (type = hash_search(vtable, &argv[idx][1], (void **)&ptr))
			{
		//		printf("debug : %sa\n", ptr);
				if (type == T_INT)
				{
					sprintf(buff, "%d", (int)ptr);
					ptr = malloc(strlen(buff) + 1);
					strcpy(ptr, buff);
				}
				argv[idx] = ptr;
			}
			else
				argv[idx] = "";
		/*	else
			if (hash_search(vtable, "a", (void **)&ptr))
			{
				printf("debug2 : %s\n", ptr);
				argv[idx] = ptr;
			}*/
		}
	}
	return argv;
}

status_t process_str(char *str)
{
	if (!*str)
		return success;
	int idx, argc = 0;
	int cflag = 0, bmode = 0, amode = 0, pmode = 0;
	char **argv = NULL;
	for (idx = 0; str[idx] != '\0'; idx++)
	{
		switch (str[idx])
		{
			case ' ':
				{
					str[idx] = '\0';
					cflag = 0;
					if (amode)
						idx--;
					break;
				}
			case '&':
				{
					str[idx] = '\0';
					idx--;
					bmode = 1;
					break;
				}
			case '=':
				{
					if (amode)
					{
						printf("found '=' at %d\n", idx + 1);
						return failure;
					}
					if (cflag)
					{
						str[idx] = '\0';
						cflag = 0;
						amode = 1;
						break;
					}
				}
			case '|':
				{
					pmode = 1;	
					str[idx] = '\0';
					cflag = 0;
					argv = realloc(argv,sizeof (char *) * (argc + 1));
					argv[argc++] = "|";
					break;
				}
			default:
				{
					if (!cflag)
					{
						cflag = 1;
						argv = realloc(argv,sizeof (char *) * (argc + 1));
						argv[argc++] = str + idx;
						if (str[idx] == '"')
						{
							idx++;
							argv[argc - 1] = str + idx;
							while (str[idx] != '"')
								idx++;
							str[idx] = '\0';
							cflag = 0;
						}
					}
				}
		}
	}

	/*
	   int i;
	   for (i = 0; i < argc; i++)
	   printf("%s ", argv[i]);
	   printf("\n");	   
	 */
	if (amode)
	{
		char *str = malloc(strlen(argv[1]) + 1);
		char *var = malloc(strlen(argv[0]) + 1);
		if ((void *)-1 == hash_insert(vtable, strcpy(var, argv[0]), T_STR, (void *)strcpy(str, argv[1]), 1))
		{
			error_msg("error : init : insert\n");
			return failure;
		}

		/*
		   char *ptr;
		   if (hash_search(vtable, argv[0], (void **)&ptr))
		   printf("inserted : %s to %s\n", ptr, argv[0]);
		   else
		   printf("but why?\n");
		 */
	}
	else
	{
		argv = realloc(argv, sizeof (char *) * (argc + 1));
		argv[argc] = NULL;
		replace_str(argv);
		if (bmode)
			BACKGROUND_ISSET = 1;
		pid_t pid = (bmode || pmode) ? child_process_cmd(argc, argv) : execute_cmd(argv[0], argv);

		if (!bmode && pid > 0)
			add_fg(pid, argv);
		else if (bmode)
			add_bg(pid, argv);
	}
	return success;
}
