#include "../../include/minishell.h"

void	ft_make_pids(t_ms *ms)
{
	int	i;

	i = -1;
	while (++i < ms->jct->cmd_nb)
	{
		if (DEBUG)
			printf("--- Enter while loop		---\n");
		if (ms->jct->tab[i][0])
		{
			if (ft_built_in(ms, i) == 0)
				return ;
			if (ft_pre_redir(ms, i) == 1)
				exit (127); //TODO mettre le vrai exit status
			ms->exec->pids[i] = fork();
			if (ms->exec->pids[i] == -1)
				perror("Error! PID creation failed:");
			ft_close_old_pipes(ms->exec, i);
			ft_dup_and_run(ms, i, ms->exec->builtin_fts);
		}
	}
	ft_close_all(ms);
	if (DEBUG)
		printf("--- Exit while loop	---\n");
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
