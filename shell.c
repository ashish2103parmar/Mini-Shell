#include <common.h>

int main()
{

	char buff[256], c;
	if (!init())
	{
		error_msg("shell initializtion failed");
		_exit(0);
	}

	while (1)
	{
		promptusr();
		scanf("%[^\n]", buff);
		while ((c = getchar()) != '\n');
		if (!process_str(buff))
			error_msg("failed");
		waitif();
		*buff = '\0';
	}
}
