#include <common.h>
#include <types.h>
#include <slist.h>
#include <stack.h>
#include <hashtable.h>

status_t process_str(char *str)
{
	int idx, argc = 0;
	int cflag = 0, bmode = 0, amode = 0;
	char **argv = NULL;
	for (idx = 0; str[idx] != '\0'; str++)
	{
		switch (str[idx])
		{
			case ' ':
				{
					str[idx] = '\0';
					cflag = 0;
					break;
				}
			case '&':
				{
					str[idx] = '\0';
					bmode = 1;
					break;
				}
			case '=':
				{
					if (cflag)
					{
						str[idx] = '\0';
						cflag = 0;
						amode = 1;
						break;
					}
				}
			default:
				{
					if (!cflag)
					{
						cflag = 1;
						argv = realloc(argv, argc + 1);
						argv[argc++] = str + idx;
					}
				}
		}
	}

	argv = realloc(argv, argc + 1);
	argv[argc] = NULL;

}
