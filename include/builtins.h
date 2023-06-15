#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_exec	t_exec;

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

/* 		Built_in functions 							*/
bool	ft_check_builtin(t_exec *exec, int i);
void	ft_is_builtin(t_exec *exec, int i);

void	ft_msh_echo(char **cmd);
void	ft_msh_env(t_exec *exec);
void	ft_msh_pwd(t_exec *exec);

#endif