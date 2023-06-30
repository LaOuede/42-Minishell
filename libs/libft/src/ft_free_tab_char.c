/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab_char.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csenand <csenand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 13:51:24 by gwenolalero       #+#    #+#             */
/*   Updated: 2023/06/30 10:38:34 by csenand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_free_tab_char(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{	
		tab[i] = ft_freenull(tab[i]);
		i++;
	}
	tab = ft_freenull(tab);
	return (0);
}
