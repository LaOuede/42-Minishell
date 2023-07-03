#include "../include/minishell.h"

void	*ft_calloc_msh(size_t count, size_t size, t_ms *ms)
{
	size_t	i;
	char	*dest;

	dest = (void *)malloc(size * count);
	if (!dest)
		ft_exit_free(ms, 666, ERR_MEM);
	i = 0;
	while (i < (count * size))
		dest[i++] = 0;
	return (dest);
}

t_ms	*ft_init_ms(char **envp)
{
	static t_ms	*ms;

	(void)envp;
	if (!ms)
	{
		if (!getenv("PATH"))
		{
			printf(ERR_ENV);
			exit(1);
		}
		ms = ft_calloc(1, sizeof(t_ms));
		if (!ms)
			ft_error_exit(ERR_MEM, 666);
		ms->envp = NULL;
		ft_copy_env(ms, envp);
		ms->envp = ft_sort_parrams(ms->envp);
		ms->jct = ft_init_jct(ms, envp);
		ms->pars = ft_init_pars(ms);
		ms->exec = ft_init_exec(ms);
		ms->ctrlbs = false;
		ms->ctrlc = false;
		ms->hd = NULL;
		ms->flexit = 0;
	}
	return (ms);
}

void	ft_minishell(t_ms *ms)
{
	ft_banner_start(ms);
	while (LOULOU_IS_MAGIC)
	{
		ft_init_sig(MAIN);
		ms->pars->input = readline("Miniꞩhell$ ");
		if (!ms->pars->input)
		{
			ft_banner_exit(ms);
			ft_exit_free(ms, ms->flexit, 0);
		}
		add_history(ms->pars->input);
		ft_parsing(ms);
		if (ms->jct->err_pars == false)
			ft_exec(ms);
		ft_reset_jct(ms->jct);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_ms	*ms;

	(void)av;
	ms = ft_init_ms(envp);
	if (ac != 1)
	{
		ft_error(ERR_EXEC);
		exit(127);
	}
	ft_minishell(ms);
	return (0);
}
