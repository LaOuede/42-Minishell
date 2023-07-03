/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 08:48:10 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/03 09:44:27 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define READLINE_LIBRARY
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include "../libs/libft/includes/libft.h"
# include "readline.h"
# include "parsing.h"
# include "builtins.h"
# include "execution.h"
# include "history.h"

/* --------------------COLORS--------------------- */
# define KNRM "\x1B[m"
# define BLD "\x1B[1m"
# define KGRE "\x1B[2m"
# define KITA "\x1B[3m"
# define KUND "\x1B[4m"
# define KRST "\x1B[5m"
# define KRED "\x1B[31m"
# define KGRN "\x1B[32m"
# define KYEL "\x1B[33m"
# define KBLU "\x1B[34m"
# define KMAG "\x1B[35m"
# define KCYN "\x1B[36m"
# define KWHT "\x1B[37m"
# define RT   "\033[1;0m"

/* --------------------ERROR MESSAGE--------------------- *///
# define ERR_EXEC	"Usage error : too many arguments.\n--> Usage : ./Minishell\n"
# define ERR_EXI1	"Usage error : exit: too many arguments\n"
# define ERR_EXI2	"Usage error : exit: numeric argument required\n"
# define ERR_HD		"Usage error : bad substitution\n"
# define ERR_ENV	"Error : env path not found\n"
# define ERR_MEM	"Error : memory allocation failed\n"

# ifndef EVALUATOR
#  define EVALUATOR "Antoine"
# endif
# ifndef BANNER
#  define BANNER "color"
# endif
# define LOULOU_IS_MAGIC 17
# define MAIN 42
# define EXEC 666
# define HD 7
# define CHILD 1

typedef struct s_ms
{
	char			**envp;
	struct s_jct	*jct;
	struct s_pars	*pars;
	struct s_exec	*exec;
	struct s_pars	*hd;
	int				flexit;
	bool			ctrlbs;
	bool			ctrlc;
	int				banner;
}	t_ms;

typedef struct s_jct
{
	int		*fds_in;
	int		*fds_out;
	char	***tab;
	char	**envp;
	int		cmd_nb;
	int		fd_hd;
	bool	err_pars;
	bool	echo;
	int		flag_var;
	int		flag_err_var;
}			t_jct;

/* 		MS functions 							*/
t_ms	*ft_init_ms(char **envp);
void	ft_exit_free(t_ms *ms, int flexit, char *err);

/* 		Jct functions 							*/
t_jct	*ft_init_jct(t_ms *ms, char **envp);
void	ft_free_jct(t_jct *jct);
void	ft_free_child(t_ms *ms);
void	ft_free_all(t_ms *ms);
void	ft_reset_jct(t_jct *jct);

/* 		Signal functions 						*/
void	ft_init_sig(int phase);

/* 		hd parsing functions 					*/
void	ft_hd_parser(t_ms *ms);
void	ft_str_hd(int *i, t_ms *ms);
void	ft_envvar_hd(int *i, char *str, t_ms *ms);
bool	ft_check_expand_brackets_hd(char *str, t_ms *ms);
void	ft_get_expand_brackets_hd(int *i, char *str, t_ms *ms);
void	ft_envvar_token_hd(int *i, char *str, t_ms *ms);
void	ft_reset_pars(t_pars *pars);
void	print_hd(t_pars *hd, int fd_hd);
void	ft_merge_hd(t_pars *hd);

/* 		Banner functions 							*/
void	ft_banner_start(t_ms *ms);
void	ft_banner_exit(t_ms *ms);
void	*ft_calloc_msh(size_t count, size_t size, t_ms *ms);

#endif
