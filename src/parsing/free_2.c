#include "../../include/minishell.h"

void	ft_free_child(t_ms *ms)
{
	if (ms)
	{
		if (ms->pars)
			ft_free_pars(ms->pars);
		if (ms->exec)
			ft_free_exec(ms->exec);
		ft_freenull(ms);
	}
}

void	ft_free_all(t_ms *ms)
{
	if (ms)
	{
		if (ms->jct)
			ft_free_jct(ms->jct);
		if (ms->pars)
			ft_free_pars(ms->pars);
		if (ms->exec)
			ft_free_exec(ms->exec);
		if (ms->hd)
			ft_free_pars(ms->hd);
		if (ms->envp)
			ft_free_tab_char(ms->envp);
		ft_freenull(ms);
	}
}
