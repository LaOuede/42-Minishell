#include "../../include/minishell.h"

/* EXIT
Definition :
	exit command in linux is used to exit the shell where it is currently running.
	It takes one more parameter as [N] and exits the shell with a return
	of status N. If n is not provided, then it simply returns the status
	of last command that is executed.
Prototype :
	exit
*/

void	ft_msh_exit(t_exec *exec, char **cmd)
{
	printf(KYEL "-------------------- FT_MSH_EXIT" KGRN " START " RESET KYEL "--------------------\n" RESET);
	if (cmd[1] && !cmd[2])
	{
		if (0 <= ft_atoi(cmd[1]) && ft_atoi(cmd[1]) <= 255)
		{
			g_exit_status = ft_atoi(cmd[1]);
			printf("%d\n", g_exit_status);
		}
		ft_free_tab_char(cmd);
		ft_exit(exec);
	}
	printf(KYEL "-------------------- FT_MSH_EXIT" KRED " END " RESET KYEL "--------------------\n" RESET);
}
