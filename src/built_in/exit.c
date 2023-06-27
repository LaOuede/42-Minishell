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

void	ft_msh_exit(t_ms *ms, char **cmd)
{
	printf(KYEL "-------------------- FT_MSH_EXIT" KGRN " START " RESET KYEL "--------------------\n" RESET);
	if (cmd[0] && cmd[1])
	{
		if (0 <= ft_atoi(cmd[1]) && ft_atoi(cmd[1]) <= 255)
		{
			ms->flexit = ft_atoi(cmd[1]) % 256;
			printf("%d\n", ms->flexit);
		}
		ft_free_tab_char(cmd);
		ft_exit_free(ms, ms->flexit);
	}
	else if (ft_str_isdigit(cmd[1]) == false)
	{
		ft_error(ERR_EXI2);
		ft_exit_free(ms, 1);
	}
	else if (cmd[2])
	{
		ft_error(ERR_EXI1);
		ft_exit_free(ms, 255);
	}
	printf(KYEL "-------------------- FT_MSH_EXIT" KRED " END " RESET KYEL "--------------------\n" RESET);
}
