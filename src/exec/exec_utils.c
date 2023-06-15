#include "../../include/minishell.h"

#define PRINT_DEBUG 0

void	ft_print_debug(t_exec *exec)
{
	int	j;

	if (PRINT_DEBUG)
	{
		j = -1;
		//Printing What's inside 'exec->readline' variable
		printf(BLD);
		printf("\n---------------------------------------------------\n");
		printf("---		Print_debug " GRN "starts" RESET BLD "		---\n");
		printf("---------------------------------------------------" RESET "\n\n");
		printf("---------------------------------------------------\n");
		printf("---	Printing exec->readline[i]		---\n");
		printf("|\n");
		while (exec->readline[++j])
			printf("|	exec->readline[%d] : %s\n", j, exec->readline[j]);
		printf("|\n");
		printf("---	Printing exec->readline ends		---\n");
		printf("---------------------------------------------------\n\n");
		printf("---------------------------------------------------\n");
		printf("---	Printing exec->cmd_nb			---\n");
		printf("|\n");
		printf("|	cmd_nb = %d\n", exec->cmd_nb);
		printf("|	pipes_nb = %d\n", exec->pipes_nb);
		printf("|\n");
		printf("---	Printing exec->cmb_nb ends		---\n");
		printf("---------------------------------------------------\n\n");
		printf("---------------------------------------------------\n");
		printf("---	Printing exec->pipe_op & flag		---\n");
		printf("|\n");
		printf("|	pipe_op = %d\n", exec->pipes_op);
		printf("|	fl_pipe_op = %d\n", exec->fl_pipe_op);
		printf("|\n");
		printf("---	Printing exec->pipe_op & flag ends	---\n");
		printf("---------------------------------------------------\n\n");
		printf("---------------------------------------------------\n");
		printf("---	Printing input_file_name & flag		---\n");
		printf("|\n");
		printf("|	input_file_name = %s\n", exec->file_in);
		printf("|	fl_redirin = %d\n", exec->fl_redirin);
		printf("|\n");
		printf("---	Printing input_file_name & flag ends	---\n");
		printf("---------------------------------------------------\n\n");
		printf("---------------------------------------------------\n");
		printf("---	Printing output_file_name & flag	---\n");
		printf("|\n");
		printf("|	output_file_name = %s\n", exec->file_out);
		printf("|	fl_redirout = %d\n", exec->fl_redirout);
		printf("|\n");
		printf("---	Printing output_file_name & flag ends	---\n");
		printf("---------------------------------------------------\n\n");
		printf(BLD);
		printf("---------------------------------------------------\n");
		printf("---		Print_debug " RED "ends" RESET BLD "		---\n");
		printf("---------------------------------------------------" RESET "\n\n");
	}
}

void	ft_copy_env(t_exec *exec, char **envp)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
		i++;
	exec->envp = ft_calloc(sizeof(char **), i + 1);
	i = -1;
	j = 0;
	while (envp[++i])
		exec->envp[j++] = ft_strdup(envp[i]);
	exec->envp[j] = NULL;
}

char	*ft_free_2char(char **tab)
{
	int	i;

	i = -1;
	while (++i < 3)
		free(tab[i]);
	free(tab);
	return (0);
}

void	ft_free_3tab(t_jct *jct)
{
	int		i;
	char	***tmp;

	if (!jct->tab)
		return ;
	tmp = jct->tab;
	i = -1;
	while (++i < jct->cmd_nb)
		ft_free_2char(tmp[i]);
	free(tmp);
	jct->tab = NULL;
}

void	ft_free_exec(t_exec *exec)
{
	if (exec->envp)
		ft_free_tab_char(exec->envp);
	if (exec->path_var)
		ft_free_tab_char(exec->path_var);
	if (exec->pipes)
		ft_freenull(exec->pipes);
		// ft_free_tab_int(exec->pipes, exec->pipes_nb);
	if (exec->pids)
		ft_freenull(exec->pids);
	if (exec->file_in)
		ft_freenull(exec->file_in);
	if (exec->file_out)
		ft_freenull(exec->file_out);
	// if (exec->path_var)
	// 	ft_free_tab_char(exec->path_var);
	// ft_freenull(exec);
}

int	ft_path_var_qty(char **path_var)
{
	int	i;

	i = 0;
	while (path_var[i])
		i++;
	return (i);
}

char	**ft_get_path(char **envp, int i)
{
	char	**path_var;
	char	**new_path_var;

	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
	{
		new_path_var = ft_calloc(1, sizeof(char *));
		new_path_var[0] = ft_calloc(1, sizeof(char));
		return (new_path_var);
	}
	path_var = ft_split(&envp[i][5], ':');
	if (!path_var)
		return (NULL);
	new_path_var = ft_calloc(ft_path_var_qty(path_var) + 1, sizeof(char *));
	if (!new_path_var)
		return (NULL);
	i = -1;
	while (path_var[++i])
	{
		new_path_var[i] = ft_strjoin(path_var[i], "/");
		free(path_var[i]);
	}
	free(path_var);
	return (new_path_var);
}

t_exec	*ft_init_exec(char **envp, t_jct *jct)
{
	static t_exec	*exec;

	exec = malloc(sizeof(t_exec));
	if (!exec)
		perror(NULL);
	exec->envp = NULL;
	exec->jct = ft_init_jct();
	ft_copy_env(exec, envp);
	exec->path_var = ft_get_path(exec->envp, 0);
	exec->input = 0;
	exec->file_in = NULL;
	exec->fl_redirin = 0;
	exec->output = 0;
	exec->file_out = NULL;
	exec->fl_redirout = 0;
	exec->index = 0;
	exec->fl_hd_in = 0;
	exec->fl_hd_out = 0;
	exec->pids = 0;
	exec->pipes = 0;
	exec->cmd_nb = jct->cmd_nb;
	exec->pipes_nb = exec->cmd_nb - 1;
	return (exec);
}

/*
*-----------------------------------------------------------------------------------------------------------------------------------------------*
|			|	cmds			|	args			|	redirin		|	redirout	|			|			|			|			|			|
*-----------------------------------------------------------------------------------------------------------------------------------------------*
|	*cmd0	|	echo cmd0[0]	|	allo cmd0[1]	|				|				|			|			|			|			|			|
*-----------------------------------------------------------------------------------------------------------------------------------------------*
|	*cmd1	|	cat	cmd1[0]		|					|	< Makefile	|	> outfile	|			|			|			|			|			|
*-----------------------------------------------------------------------------------------------------------------------------------------------*

each cmds[i] should be stored in a 2D array
-> make a fct that recognize if there an operator (| , <, >, <<,
		>>) and switch flags 

typedef struct s_jct
{
	char	**tab;
	int		pipe_nb;
	int		cmd_nb;
} 	t_jct

*/