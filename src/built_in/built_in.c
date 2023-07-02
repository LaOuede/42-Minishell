#include "../../include/minishell.h"

/*
** Your shell must implement the following builtins:
**		◦ echo with option -n (-n remove \n)
**		◦ cd with only a relative or absolute path
**		◦ pwd with no options
**		◦ export with no options
**		◦ unset with no options
**		◦ env with no options or arguments
**		◦ exit with no options
*/

t_builtin	*ft_get_builtin(void)
{
	static t_builtin	*builtin;

	if (!builtin)
	{
		builtin = malloc(sizeof(t_builtin));
		if (!builtin)
			perror(NULL);
		builtin->fts[0] = NULL;
		builtin->fts[1] = ft_msh_echo;
		builtin->fts[2] = ft_msh_pwd;
		builtin->fts[3] = ft_msh_env;
		builtin->fts[4] = ft_msh_exit;
		builtin->fts[5] = ft_msh_export;
		builtin->fts[6] = ft_msh_cd;
		builtin->fts[7] = ft_msh_unset;
	}
	return (builtin);
}

int	ft_is_builtin(char **cmd)
{
	if (ft_strcmp(cmd[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		return (2);
	else if (ft_strcmp(cmd[0], "env") == 0)
		return (3);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		return (4);
	else if (ft_strcmp(cmd[0], "export") == 0)
		return (5);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		return (6);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		return (7);
	return (0);
}

int	ft_built_in(t_ms *ms, int i)
{
	int	builtin_fts;

	ms->exec->builtin_cmd = ft_split(ms->jct->tab[i][0], 29);
	ms->exec->builtin_fts = ft_is_builtin(ms->exec->builtin_cmd);
	builtin_fts = ms->exec->builtin_fts;
	if (ms->jct->cmd_nb == 1 && (builtin_fts > 4 \
		|| (builtin_fts == 4 && ms->exec->builtin_cmd[i][1])))
	{
		ms->exec->builtin->fts[builtin_fts](ms, ms->exec->builtin_cmd);
		ft_free_tab_char(ms->exec->builtin_cmd);
		ms->exec->builtin_cmd = NULL;
		return (0);
	}
	return (1);
}
