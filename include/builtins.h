/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 08:48:10 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/03 09:55:24 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

/*	--	Function Declarations for the execution of built_in commands	--	*/
/*	--	Main functions	--	*/
int		ft_built_in(t_ms *ms, int i);
int		ft_is_builtin(char **cmd);

/*	--	Built_in functions	--	*/
void	ft_msh_echo(t_ms *ms, char **cmd);
void	ft_msh_env(t_ms *ms, char **cmd);
void	ft_msh_exit(t_ms *ms, char **cmd);
void	ft_msh_pwd(t_ms *ms, char **cmd);
void	ft_msh_cd(t_ms *ms, char **cmd);
void	ft_msh_unset(t_ms *ms, char **cmd);
void	ft_msh_export(t_ms *ms, char **cmd);

/*	-- Utils & Tools functions	--	*/
int		ft_get_ac(char **cmd);
bool	ft_1st_part_valid(t_ms *ms, char *cmd);
char	*ft_trim_arg(char *cmd);
void	ft_print_err(t_ms *ms, char *cmd);
int		ft_isexist(t_ms *ms, char *home);
char	*ft_getenv(t_ms *ms, char *home);
int		ft_find_index_var(t_ms *ms, char *cmd);

#endif