#include <common.h>


		
void promptusr()
{
	char *prmt;
	if (hash_search(vtable, "PS1", (void **)&prmt))		
		printf("%s:>", prmt);
	else
	{
		char buff[256];
		printf("myshell@%s:>", getcwd(buff, 256));
	}


}

void echo_cmd(char *argv[])
{
	if (argv && argv[1])
		printf("%s\n", argv[1]);
}

void exit_cmd(char *argv[])
{
	_exit(0);
}

void pwd_cmd(char *argv[])
{
	char buff[100];
	if (getcwd(buff, 100))
		printf("%s\n", buff);
	else
		perror("pwd");
}

void cd_cmd(char *argv[])
{
	if (argv[1])
	{
		if (chdir(argv[1]))
			error_msg("cd");
	}
	else
		if (chdir("/home/emertxe"))
			error_msg("cd");
}

void fg_cmd(char *argv[])
{
	add_fg(0, NULL);
}

void bg_cmd(char *argv[])
{
	add_bg(0, NULL);
}

void jobs_cmd(char *argv[])
{
	print_jobs();
}
