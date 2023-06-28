#include "../../include/minishell.h"

/* PWD
Definition :
	The pwd command writes to standard output the full path name of
	your current directory (from the root directory).
	All directories are separated by a / (slash).
	The root directory is represented by the first /,
	and the last directory named is your current directory.
Prototype :
	pwd
Exit Status :
	0 successful completion
	>0 An error occurred
*/

/* GETCWD
Definition :
	It determines the path name of the working directory and stores it in buffer.
Return value :
	If successful, getcwd() returns a pointer to the buffer.
	If unsuccessful, getcwd() returns a NULL pointer and sets errno to a value.
*/
void	ft_msh_pwd(t_ms *ms, char **cmd)
{
	(void)ms;
	printf(KYEL "-------------------- FT_MSH_PWD" KGRN " START " RESET KYEL "--------------------\n" RESET);
	char	*buf;

	if (cmd[1])
	{
		ft_putstr_fd("Too many args\nUsage: pwd [no args]\n", 2);
		exit(127);
	}
	buf = getcwd(NULL, 0);
	if (buf)
		printf("%s\n", buf);
	ft_freenull(buf);
	printf(KYEL "-------------------- FT_MSH_PWD" KRED " END " RESET KYEL "--------------------\n" RESET);
}
