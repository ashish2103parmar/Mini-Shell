#include <common.h>


void exit_cmd(char *argv[])
{
	kill(getppid(), SIGKILL);
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
	if (chdir(argv[1]))
		perror("cd");
}

void fg_cmd(char *argv[])
{
}

void bg_cmd(char *argv[])
{
}
