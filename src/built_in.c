#include "../include/minishell.h"

/*
** Your shell must implement the following builtins:
**		◦ echo with option -n
**		◦ cd with only a relative or absolute path
**		◦ pwd with no options
**		◦ export with no options
**		◦ unset with no options
**		◦ env with no options or arguments
**		◦ exit with no options
**
*/

/*
**	List of builtin
*/
char	*built_in[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};

int		(*builtin_fct[])(char **) = \
{
	&ft_msh_echo,
	&ft_msh_cd,
	&ft_msh_pwd,
	&ft_msh_export,
	&ft_msh_unset,
	&ft_msh_env,
	&ft_msh_exit
};