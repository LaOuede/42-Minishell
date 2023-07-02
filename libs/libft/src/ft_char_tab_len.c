/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_tab_len.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwenolaleroux <gwenolaleroux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:59:11 by gle-roux          #+#    #+#             */
/*   Updated: 2023/07/01 22:22:54 by gwenolalero      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

//TODO modifier le header
int	ft_char_tab_len(char **tab)
{
	int	i;

	i = 0;
	if (tab[i])
		while (tab[i])
			i++;
	return (i);
}
