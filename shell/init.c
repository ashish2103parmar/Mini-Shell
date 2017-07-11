#include <common.h>
#include <types.h>
#include <slist.h>
#include <stack.h>
#include <hashtable.h>

htable *ptable;
htable *vtable;
stack *cprocess = NULL;
status_t init()
{
	ptable = create_htable(64u);
	vtable = create_htable(64u);

	char buff[200];
	if (hash_insert(vtable, "SHELL", T_STR, (void *)getcwd(buff, 200), 0))
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
}


