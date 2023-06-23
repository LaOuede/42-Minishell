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

// t_builtin	*ft_get_builtin(void)
// {
// 	static t_builtin	*builtin;

// 	if(!builtin)
// 	{
// 		builtin = malloc(sizeof(t_builtin));
// 		if (!builtin)
// 			perror(NULL);
// 		builtin->operation_funcs[0] = NULL;
// 		builtin->operation_funcs[1] = NULL;
// 		builtin->operation_funcs[2] = NULL;
// 		builtin->operation_funcs[3] = NULL;
// 		builtin->operation_funcs[4] = NULL;
// 		builtin->operation_funcs[5] = NULL;
// 		builtin->operation_funcs[6] = NULL;
// 		builtin->operation_funcs[7] = NULL;
// 	}
// }

void	ft_is_builtin(t_ms *ms, int i)
{
	printf(KYEL "-------------------- FT_IS_BUILTIN" KGRN " START " RESET KYEL "--------------------\n" RESET);
	char	**cmd;

	cmd = ft_split(ms->jct->tab[i][0], ' ');
	if (strcmp(cmd[0], "echo") == 0)
		ft_msh_echo(cmd);
/* 	else if (strcmp(cmd, "cd") == 0)
		ft_msh_cd(); */
	else if (strcmp(cmd[0], "pwd") == 0)
		ft_msh_pwd(ms->exec);
/* 	else if (strcmp(cmd, "export") == 0)
		ft_msh_export();
	else if (strcmp(cmd, "unset") == 0)
		ft_msh_unseto(); */
	else if (strcmp(cmd[0], "env") == 0)
		ft_msh_env(ms->exec);
	else if (strcmp(cmd[0], "exit") == 0)
		ft_msh_exit(ms, cmd);
	ft_free_tab_char(cmd);
	// return (0);
	printf(KYEL "-------------------- FT_IS_BUILTIN" KRED " END " RESET KYEL "--------------------\n" RESET);
}


//TODO only an idea below
bool	ft_check_builtin(t_exec *exec, int i)
{
	char	**cmd;

	cmd = ft_split(exec->jct->tab[i][0], ' ');
	if (strcmp(cmd[0], "echo") == 0 || strcmp(cmd[0], "cd") == 0 || \
		strcmp(cmd[0], "pwd") == 0 || strcmp(cmd[0], "export") == 0 || \
		strcmp(cmd[0], "unset") == 0 || strcmp(cmd[0], "env") == 0 || \
		strcmp(cmd[0], "exit") == 0)
	{
		ft_free_tab_char(cmd);
		return (true);
	}
	else
	{
		ft_free_tab_char(cmd);
		return (false);
	}
}