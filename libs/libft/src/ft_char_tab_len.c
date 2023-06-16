/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_tab_len.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csenand <csenand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:59:11 by csenand           #+#    #+#             */
/*   Updated: 2023/06/16 14:59:47 by csenand          ###   ########.fr       */
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
