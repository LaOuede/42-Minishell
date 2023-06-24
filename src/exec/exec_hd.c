#include "../../include/minishell.h"

char	*ft_trim(char *s1, char *set)
{
	int		end;
	int		start;
	char	*s_trim;

	if (!s1)
		return (0);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (end && ft_strchr(set, s1[end]))
		end--;
	s_trim = ft_substr(s1, start, end - start + 1);
	return (s_trim);
}

char	*ft_gnl(void)
{
	char	buf[5000];
	int		rbytes;
	char	*res;
	char	*trim;

	rbytes = read(STDOUT_FILENO, buf, 5000);
	buf[rbytes] = '\0';
	trim = ft_strdup(buf);
	res = ft_trim(trim, "\n");
	ft_freenull(trim);
	return (res);
}

/* void	ft_child_hd(char *delim, t_ms *ms)
{
	ft_init_sig(HD);
	ms->hd = ft_init_hd();
	while (42)
	{
		ms->hd->input = readline("> ");
		printf("hd_input = %s\n", ms->hd->input);
		if (ft_strchr(ms->hd->input, '$'))
			ft_parsing_hd(ms->hd);
		if (ft_strncmp(ms->hd->input, delim, ms->hd->strlen) == 0)
			break ;
		ft_reset_pars(ms->hd);
	}
	ft_free_all(ms);
	exit(0);
} */

void	ft_child_hd(char *delim, int fd_hd, t_ms *ms)
{
	char	*tmp;

	while (1)
	{
		ft_init_sig(HD);
		ft_putstr_fd("> ", 1);
		tmp = ft_gnl();
		if ((ft_strncmp(tmp, delim, ft_strlen(tmp))) == 0)
			break ;
		ft_putstr_fd(tmp, fd_hd);
		ft_putchar_fd('\n', fd_hd);
		ft_freenull(tmp);
	}
	ft_freenull(tmp);
	ft_free_all(ms);
	exit(0);
}

int	ft_exec_hd(char *delim, t_ms *ms)
{
	int		fd_hd;
	pid_t	pid_hd;
	int		status;

	fd_hd = open("/tmp/here_doc", O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (fd_hd < 0)
		perror("Error ! fd_hd:");
	pid_hd = fork();
	if (pid_hd == -1)
		perror("Error! pid_hd:");
	if (pid_hd == 0)
		ft_child_hd(delim, fd_hd, ms);
	waitpid (pid_hd, &status, 0);
/* 	if (WIFEXITED(status))
		ms->flexit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		ms->flexit = WTERMSIG(status); */
	close(fd_hd);
	fd_hd = open("/tmp/here_doc", O_RDONLY, 0644);
	return (fd_hd);
}
