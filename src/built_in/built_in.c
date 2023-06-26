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

	if(!builtin)
	{
		builtin = malloc(sizeof(t_builtin));
		if (!builtin)
			perror(NULL);
		builtin->fts[0] = NULL;
		builtin->fts[1] = ft_msh_echo;
		builtin->fts[2] = ft_msh_pwd;
		builtin->fts[3] = ft_msh_env;
		builtin->fts[4] = ft_msh_exit;
		builtin->fts[5] = NULL; //ft_msh_export
		builtin->fts[6] = NULL; //ft_msh_cd
		builtin->fts[7] = NULL; //ft_msh_unset
	}
	return (builtin);
}

int	ft_is_builtin(char **cmd)
{
	if (DEBUG)
		printf(KYEL "-------------------- FT_IS_BUILTIN" KGRN " START " RESET KYEL "--------------------\n" RESET);
	if (ft_strcmp(cmd[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		return (2);
	else if (ft_strcmp(cmd[0], "env") == 0)
		return (3);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		return (4);
/* 
	else if (ft_strcmp(cmd[0], "export") == 0)
		return (5);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		return (6);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		return (7);
*/
	ft_free_tab_char(cmd);
	if (DEBUG)
		printf(KYEL "-------------------- FT_IS_BUILTIN" KRED " END " RESET KYEL "--------------------\n" RESET);
	return (0);
}
