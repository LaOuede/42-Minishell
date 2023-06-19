#include "../../include/minishell.h"

char	*ft_free_2char(char **tab)
{
	int	i;

	i = -1;
	while (++i < 3)
		free(tab[i]);
	free(tab);
	return (0);
}

void	ft_free_3tab(t_jct *jct)
{
	int		i;
	char	***tmp;

	if (!jct->tab)
		return ;
	tmp = jct->tab;
	i = -1;
	while (++i < jct->cmd_nb)
		ft_free_2char(tmp[i]);
	free(tmp);
	jct->tab = NULL;
}

void	ft_free_exec(t_exec *exec)
{
	if (exec->envp)
		ft_free_tab_char(exec->envp);
	if (exec->path_var)
		ft_free_tab_char(exec->path_var);
	if (exec->pipes)
		ft_free_tab_int(exec->pipes, exec->pipes_nb);
	if (exec->pids)
		ft_freenull(exec->pids);
	ft_freenull(exec);
}
