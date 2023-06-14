#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_jct	t_jct;

bool	ft_check_builtin(t_jct *jct, int i);
void	ft_is_builtin(t_jct *jct, int i);
/*
**	Function Declarations for builtin shell commands
*/
/* int	ft_msh_echo(t_jct *jct, int i);
int	ft_msh_cd(char **args);
int	ft_msh_pwd(char **args);
int	ft_msh_export(char **args);
int	ft_msh_unset(char **args);
int	ft_msh_env(char **args);
int	ft_msh_exit(char **args); */

void	ft_msh_echo(t_jct *jct, int i);

#endif