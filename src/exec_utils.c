#include "../include/minishell.h"

# define PRINT_DEBUG 1


void	ft_print_debug(t_exec *exec)
{
	if (PRINT_DEBUG)
	{
		int j = -1;

		//Printing What's inside 'exec->readline' variable
		printf("\n---------------------------------------------------\n");
		printf("---		Print_debug "GRN"starts"RESET"		---\n");
		printf("---------------------------------------------------\n\n");

		printf("---------------------------------------------------\n");
		printf("---	Printing exec->readline[i]		---\n");
		printf("|\n");
		while(exec->readline[++j])
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
		printf("---	Printing exec->pipe_op and flag		---\n");
		printf("|\n");
		printf("|	pipe_op = %d\n", exec->pipes_op);
		printf("|	fl_pipe_op = %d\n", exec->fl_pipe_op);
		printf("|\n");
		printf("---	Printing exec->pipe_op and flag ends	---\n");
		printf("---------------------------------------------------\n\n");

		printf("---------------------------------------------------\n");
		printf("---	Printing input_file_name and flag	---\n");
		printf("|\n");
		printf("|	input_file_name = %s\n", exec->input_file_name);
		printf("|	fl_redirin = %d\n", exec->fl_redirin);
		printf("|\n");
		printf("---	Printing input_file_name and flag ends	---\n");
		printf("---------------------------------------------------\n\n");

		printf("---------------------------------------------------\n");
		printf("---	Printing output_file_name and flag	---\n");
		printf("|\n");
		printf("|	output_file_name = %s\n", exec->output_file_name);
		printf("|	fl_redirout = %d\n", exec->fl_redirout);
		printf("|\n");
		printf("---	Printing output_file_name and flag ends	---\n");
		printf("---------------------------------------------------\n\n");

		printf("---------------------------------------------------\n");
		printf("---		Print_debug "RED"ends"RESET"		---\n");
		printf("---------------------------------------------------\n\n");
	}
}

void	ft_is_operator(t_exec *exec)
{
	// TODO Write a fct that raise flags depending if there is an operatior (|, <, >, <<, >>) or not.
	int		i;
	char	**tmp;

	tmp = exec->readline;
	i = -1;
	exec->pipes_op = 0;
	exec->fl_pipe_op = 0;
	exec->fl_redirin = 0;
	exec->input_file_name = NULL;
	exec->output_file_name = NULL;
	while(tmp[++i])
	{
		// if 'pipe' then count pipes operator and raise flag
		if (*tmp[i] == '|')
		{
			exec->pipes_op++;
			exec->fl_pipe_op = 1;
		}
		// if '<' then redirin
		if (*tmp[i] == '<')
		{
			exec->input_file_name = tmp[i + 1];
			exec->fl_redirin = 1;
			exec->input  = open(exec->input_file_name, O_RDONLY);
		}
		// if '>' then redirout
		if (*tmp[i] == '>')
		{
			exec->output_file_name = tmp[i + 1];
			exec->fl_redirout = 1;
			exec->output = open(exec->output_file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
		}
		// if '>>' then ??

		// if '<<' then ??
	}

}

void	ft_copy_env(t_exec *exec, char **envp)
{
	int i;
	int j;

	i = 0;
	while(envp[i])
		i++;
	exec->envp = ft_calloc(sizeof(char **), i + 1);
	i = -1;
	j = 0;
	while (envp[++i])
		exec->envp[j++] = ft_strdup(envp[i]);
	exec->envp[j] = NULL;
}

void	ft_cmd_nb(t_exec *exec)
{
	int	j = 0;
	char	**tmp;

	tmp = ft_split(exec->line, '|');
	while(tmp[j])
		j++;
	exec->cmd_nb = j;
	exec->pipes_nb = exec->cmd_nb - 1;
}

void	ft_is_redirin(t_exec *exec)
{
	int i = 0;
	char **tmp;
	exec->fl_redirin = 0;

	printf("\n--- ft_is_redirin starts ---\n");
	int j = -1;
	while(exec->readline[++j])
		printf("exec->readline[%d] : %s\n", j, exec->readline[j]);

	tmp = exec->readline;
	while(tmp[i])
	{
		if (ft_strchr(tmp[i], '<') != 0)
			exec->fl_redirin = 1;
		i++;
	}
	printf("exec->fl_redirin = %d\n", exec->fl_redirin);
	printf("--- ft_is_redirin ends ---\n");
}

int	ft_is_redirout(t_exec *exec)
{
	int i = 0;
	char **tmp;

	printf("\n--- ft_is_redirout starts ---\n");
	int j = -1;
	while(exec->readline[++j])
		printf("exec->readline[%d] : %s\n", j, exec->readline[j]);
	exec->fl_redirout = 0;
	tmp = exec->readline;
	while(tmp[i])
	{
		if (ft_strchr(tmp[i], '>') != 0)
		{
			exec->fl_redirout = 1;
			exec->fl_redirout_i = i;
			printf("exec->fl_redirout = %d\n", exec->fl_redirout);
			printf("exec->fl_redirout_i = %d\n", exec->fl_redirout_i);
			printf("--- ft_is_redirout ends ---\n\n");
			return (exec->fl_redirout);
		}
		i++;
	}
	printf("exec->fl_redirout = %d\n", exec->fl_redirout);
	printf("--- ft_is_redirout ends ---\n\n");
	return (0);
}

void	ft_free_exec(t_exec *exec)
{
	int	i;
	if (exec)
	{
		i = 0;
		if (exec->path_var)
		{
			while (exec->path_var[i])
				ft_freenull(exec->path_var[i++]);
			ft_freenull(exec->path_var);
			exec->path_var = NULL;
		}
		i = 0;
		if (exec->pipes)
		{
			while (i < exec->pipes_nb)
				ft_freenull(exec->pipes[i++]);
			ft_freenull(exec->pipes);
			exec->pipes = NULL;
		}
		i = 0;
		if (exec->readline)
		{
			while (exec->readline[i])
				ft_freenull(exec->readline[i++]);
			ft_freenull(exec->readline);
			exec->readline = NULL;
		}
		if (exec->pids)
			ft_freenull(exec->pids);
		// freenull(exec);
	}
}

void	ft_err(char *msg, t_exec *exec)
{
	ft_free_exec(exec);
	perror(msg);
	exit(1);
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

t_exec	*ft_init_exec(int ac, char **av, char **envp)
{
	static t_exec	*exec;

	(void)ac;
	(void)av;
	exec = malloc(sizeof(t_exec));
	if (!exec)
			perror(NULL);
	ft_copy_env(exec, envp);
	exec->path_var = ft_get_path(exec->envp, 0);
	exec->pipes = 0;
	exec->index = 0;
	exec->readline = ft_calloc(sizeof(char *), 1);
	exec->pids = 0;
	exec->line = NULL;

	// if (exec->output == -1)
	// 	ft_err("Error ! Couldn't create the output file", exec);
	return(exec);
}

/*
*-----------------------------------------------------------------------------------------------------------------------------------------------*
|			|	cmds	|	args	|	redirin		|	redirout	|			|			|			|			|			|			|			|																																	
*-----------------------------------------------------------------------------------------------------------------------------------------------*
|	cmd0	|	echo	|	allo	|				|				|			|			|			|			|			|			|			|																																	
*-----------------------------------------------------------------------------------------------------------------------------------------------*
|	cmd1	|	cat		|			|	< Makefile	|	> outfile	|			|			|			|			|			|			|			|																																	
*-----------------------------------------------------------------------------------------------------------------------------------------------*
|	cmd2	|			|			|				|				|			|			|			|			|			|			|			|																																	
*-----------------------------------------------------------------------------------------------------------------------------------------------*
|			|			|			|				|				|			|			|			|			|			|			|			|																																	
*-----------------------------------------------------------------------------------------------------------------------------------------------*
|			|			|			|				|				|			|			|			|			|			|			|			|																																	
*-----------------------------------------------------------------------------------------------------------------------------------------------*

each cmds[i] should be stored in a 2D array
-> make a fct that recognize if there an operator (| , <, >, <<, >>) and switch flags 


*/