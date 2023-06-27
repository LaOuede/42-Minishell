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
// bool	ft_check_builtin(t_exec *exec, int i);
int		ft_built_in(t_ms *ms, int i);
int		ft_is_builtin(char **cmd);
void	ft_msh_echo(t_ms *ms, char **cmd);
void	ft_msh_env(t_ms *ms, char **cmd);
void	ft_msh_exit(t_ms *ms, char **cmd);
void	ft_msh_pwd(t_ms *ms, char **cmd);
void	ft_msh_cd(t_ms *ms, char **cmd);
void	ft_msh_unset(t_ms *ms, char **cmd);

#endif