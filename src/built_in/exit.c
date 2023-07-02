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
	if (DEBUG)
		printf(KYEL "-------------------- FT_MSH_EXIT" KGRN " START " RT KYEL "--------------------\n" RT);
	int	ac;

	ac = ft_get_ac(cmd);
	if (ac > 2)
	{
		ft_error(ERR_EXI1);
		ms->flexit = 1;
		return ;
	}
	if (ac == 2)
	{
		if (ft_str_isdigit(cmd[1]) == false)
		{
			ms->flexit = 255;
			ft_banner_exit(ms);
			ft_exit_free(ms, ms->flexit, ERR_EXI2);
		}
		else
		{
			ms->flexit = ft_atoi(cmd[1]) % 256;
			ft_banner_exit(ms);
			ft_exit_free(ms, ms->flexit, 0);
		}
	}
	ft_exit_free(ms, 0, 0);
	if (DEBUG)
		printf(KYEL "-------------------- FT_MSH_EXIT" KRED " END " RT KYEL "--------------------\n" RT);
}
