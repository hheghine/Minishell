/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_dup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbalasan <hbalasan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 17:11:06 by hbalasan          #+#    #+#             */
/*   Updated: 2023/10/15 19:28:06 by hbalasan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_dup_matrix(char **m)
{
	char	**matrix;
	int		row;
	int		i;

	i = 0;
	row = ft_matrixlen(m);
	matrix = malloc(sizeof(char *) * (row + 1));
	if (!matrix)
		return (NULL);
	while (m[i])
	{
		matrix[i] = ft_strdup(m[i]);
		if (!matrix[i])
		{
			ft_free_matrix(&matrix);
			return (NULL);
		}
		i++;
	}
	matrix[i] = NULL;
	return (matrix);
}