#include <common.h>


		
void promptusr()
{
	char *prmt;
	if (hash_search(vtable, "PS1", (void **)&prmt))		
		printf("%s :>", prmt);
	else
	{
		char buff[256];
		printf("myshell@%s :>", getcwd(buff, 256));
	}


}


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
