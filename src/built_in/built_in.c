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

/*
**	List of builtin
*/
/* char	*built_in[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};

int		(*builtin_fct[])(char **) = \
{
	&ft_msh_echo,
	&ft_msh_cd,
	&ft_msh_pwd,
	&ft_msh_export,
	&ft_msh_unset,
	&ft_msh_env,
	&ft_msh_exit
}; */

t_builtin	*ft_get_builtin(void)
{
	static t_builtin	*builtin;

	if(!builtin)
	{
		builtin = malloc(sizeof(t_builtin));
		if (!builtin)
			perror(NULL);
		builtin->fts[0] = NULL;
		builtin->fts[1] = NULL; //ft_msh_echo
		builtin->fts[2] = NULL; //ft_msh_cd
		builtin->fts[3] = ft_msh_pwd; //pwd
		builtin->fts[4] = NULL; //ft_msh_export
		builtin->fts[5] = NULL; //ft_msh_unset
		builtin->fts[6] = ft_msh_env;
		//TODO 'exit' est bloqué au parsing car exit n'existe pas dans une des variables de 'PATH='
		builtin->fts[7] = ft_msh_exit; 
	}
	return (builtin);
}

int	ft_is_builtin(t_ms *ms, int i)
{
	if (DEBUG)
		printf(KYEL "-------------------- FT_IS_BUILTIN" KGRN " START " RESET KYEL "--------------------\n" RESET);
	char	**cmd;

	ms->exec->builtin = ft_get_builtin();
	ms->exec->builtin_cmd = ft_split(ms->jct->tab[i][0], ' ');
	cmd = ms->exec->builtin_cmd;
/* 
	if (ft_strcmp(cmd[0], "echo") == 0)
		return (1);
		//ft_msh_echo(ms, cmd);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (2);
		ft_msh_cd(); */
	// else if (ft_strcmp(cmd[0], "pwd") == 0)
	if (ft_strcmp(cmd[0], "pwd") == 0)
		return (3);
		// ft_msh_pwd(ms->exec);
/* 	else if (ft_strcmp(cmd[0], "export") == 0)
		return (4);
		ft_msh_export();
	else if (ft_strcmp(cmd[0], "unset") == 0)
		return (5);
		ft_msh_unseto(); */
	else if (ft_strcmp(cmd[0], "env") == 0)
		return (6);
		// ft_msh_env(ms->exec);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		return (7);
		// ft_msh_exit(ms, cmd[0]);
	ft_free_tab_char(cmd);
	if (DEBUG)
		printf(KYEL "-------------------- FT_IS_BUILTIN" KRED " END " RESET KYEL "--------------------\n" RESET);
	return (0);
}


//TODO only an idea below
// bool	ft_check_builtin(t_exec *exec, int i)
// {
// 	char	**cmd;

// 	cmd = ft_split(exec->jct->tab[i][0], ' ');
// 	if (strcmp(cmd[0], "echo") == 0 || strcmp(cmd[0], "cd") == 0 || \
// 		strcmp(cmd[0], "pwd") == 0 || strcmp(cmd[0], "export") == 0 || \
// 		strcmp(cmd[0], "unset") == 0 || strcmp(cmd[0], "env") == 0 || \
// 		strcmp(cmd[0], "exit") == 0)
// 	{
// 		ft_free_tab_char(cmd);
// 		return (true);
// 	}
// 	else
// 	{
// 		ft_free_tab_char(cmd);
// 		return (false);
// 	}
// }