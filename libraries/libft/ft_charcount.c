/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charcount.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbalasan <hbalasan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 00:43:40 by hbalasan          #+#    #+#             */
/*   Updated: 2024/01/07 19:00:12 by hbalasan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_charcount(char *str, char c)
{
	int	count;

	count = 0;
	while (str && *str)
	{
		if (*str == c)
			count++;
		str++;
	}
	return (count);
}
