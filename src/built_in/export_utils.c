/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 08:48:10 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/03 09:39:51 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	ft_1st_part_valid(t_ms *ms, char *cmd)
{
	int	j;

	j = -1;
	while (cmd[++j])
	{
		while (cmd[j] == '_')
			j++;
		if (cmd[j] == '$' || cmd[j] == '?' || cmd[j] == '_')
			j++;
		if ((!ft_isalpha(cmd[0]) && cmd[0] != '_' && cmd[0] != '=') \
			|| !ft_isalnum(cmd[j]))
		{
			ms->flexit = EXIT_FAILURE;
			return (false);
		}
	}
	return (true);
}

char	*ft_trim_arg_util(char **var)
{
	int		i;
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;

	i = 0;
	tmp1 = NULL;
	tmp2 = NULL;
	tmp3 = NULL;
	while (var[++i])
	{
		tmp1 = ft_strtrim(var[i], " ");
		if (tmp3)
		{
			tmp2 = ft_strjoin(tmp3, "=");
			tmp3 = ft_freenull(tmp3);
		}
		else
			tmp2 = ft_strjoin(var[0], "=");
		tmp3 = ft_strjoin(tmp2, tmp1);
		tmp1 = ft_freenull(tmp1);
		tmp2 = ft_freenull(tmp2);
	}
	return (tmp3);
}

char	*ft_trim_arg(char *cmd)
{
	char	*tmp;
	char	**var;

	tmp = NULL;
	var = ft_split(cmd, '=');
	if (var[1])
	{
		tmp = ft_trim_arg_util(var);
		ft_free_tab_char(var);
		return (tmp);
	}
	ft_free_tab_char(var);
	return (ft_strdup(cmd));
}
