#include "../../include/minishell.h"

char	*ft_free_2char(char **tab)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
			if (DEBUG)
			printf("tab[%d] = %p\n", i, tab[i]);
		free(tab[i]);
	}
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
	if (exec->path_var)
		ft_free_tab_char(exec->path_var);
	if (DEBUG)
		printf("exec->path_var address (in ft_free_exit): %p\n", exec->path_var);
	if (exec->pipes)
		ft_free_tab_int(exec->pipes, exec->pipes_nb);
	if (DEBUG)
		printf("exec->pipes address (in ft_free_exit): %p\n", exec->pipes);
	if (exec->pids)
		ft_freenull(exec->pids);
	if (DEBUG)
		printf("exec->pipes address (in ft_free_exit): %p\n", exec->pipes);
	if (DEBUG)
		printf("exec (in ft_free_exit): %p\n", exec);
	ft_freenull(exec);
}
