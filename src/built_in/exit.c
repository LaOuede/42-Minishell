/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 08:48:10 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/03 09:39:39 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	ft_exit_util(t_ms *ms, char *str)
{
	if (ft_str_isdigit(str) == false)
	{
		ms->flexit = 255;
		ft_banner_exit(ms);
		ft_exit_free(ms, ms->flexit, ERR_EXI2);
	}
	else
	{
		ms->flexit = ft_atoi(str) % 256;
		ft_banner_exit(ms);
		ft_exit_free(ms, ms->flexit, 0);
	}
}

void	ft_msh_exit(t_ms *ms, char **cmd)
{
	int	ac;

	ac = ft_get_ac(cmd);
	if (ac > 2)
	{
		ft_error(ERR_EXI1);
		ms->flexit = 1;
		return ;
	}
	if (ac == 2)
		ft_exit_util(ms, cmd[1]);
	ft_banner_exit(ms);
	ft_exit_free(ms, 0, 0);
}
