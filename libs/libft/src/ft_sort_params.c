/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csenand <csenand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 11:48:41 by csenand           #+#    #+#             */
/*   Updated: 2023/06/28 15:29:45 by csenand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	**ft_sort_parrams(char **envp)
{
	int		i;
	char	*tmp;

	i = 0;
	while (envp[i] && envp[i + 1])
	{
		if (ft_strcmp(envp[i], envp[i + 1]) > 0)
		{
			tmp = envp[i];
			envp[i] = envp[i + 1];
			envp[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
	return (envp);
}