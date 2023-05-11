#ifndef BUILTINS_H
# define BUILTINS_H

/*
**	Function Declarations for builtin shell commands
*/
int	ft_msh_echo(char **args);
int	ft_msh_cd(char **args);
int	ft_msh_pwd(char **args);
int	ft_msh_export(char **args);
int	ft_msh_unset(char **args);
int	ft_msh_env(char **args);
int	ft_msh_exit(char **args);

#endif