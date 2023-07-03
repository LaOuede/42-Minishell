/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 08:48:10 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/03 09:41:03 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_make_pids(t_ms *ms)
{
	int	i;

	i = -1;
	while (++i < ms->jct->cmd_nb)
	{
		if (ms->jct->tab[i][0])
		{
			if (ft_built_in(ms, i) == 0)
				return ;
			if (ft_pre_redir(ms, i) == 1)
				exit (1);
			ms->exec->pids[i] = fork();
			if (ms->exec->pids[i] == -1)
				perror("Error! PID creation failed:");
			ft_close_old_pipes(ms->exec, i);
			ft_dup_and_run(ms, i, ms->exec->builtin_fts);
		}
	}
	ft_close_all(ms);
}

void	ft_exec(t_ms *ms)
{
	int	i;
	int	status;

	ft_init_sig(EXEC);
	if (ft_mem_pipes(ms) == 2)
		return ;
	ms->exec->pids = ft_calloc_msh(ms->jct->cmd_nb, sizeof(pid_t *), ms);
	ft_make_pids(ms);
	i = -1;
	status = 0;
	while (++i < ms->jct->cmd_nb)
	{
		waitpid(ms->exec->pids[i], &status, 0);
		if (WIFEXITED(status))
			ms->flexit = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			ms->flexit = WTERMSIG(status);
	}
	ft_reset_exec(ms);
}
