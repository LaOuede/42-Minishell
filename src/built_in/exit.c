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
	int	ac;

	ac = ft_get_ac(cmd);
	if (ac > 2)
	{
		ft_error(ERR_EXI1);
		ft_free_all(ms);
		exit(1);
	} 
	if (ac == 2)
	{
		if (ft_str_isdigit(cmd[1]) == false)
		{
			ft_error(ERR_EXI2);
			ft_exit_free(ms, 255);
		}	
		if (0 <= ft_atoi(cmd[1]) && ft_atoi(cmd[1]) <= 255)
			ms->flexit = ft_atoi(cmd[1]) % 256;
		ft_free_tab_char(cmd);
		ft_exit_free(ms, ms->flexit);
	}
	ft_free_tab_char(cmd);
	ft_exit_free(ms, 0);
	printf(KYEL "-------------------- FT_MSH_EXIT" KRED " END " RESET KYEL "--------------------\n" RESET);
}
