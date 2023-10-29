/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbalasan <hbalasan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 23:05:52 by hbalasan          #+#    #+#             */
/*   Updated: 2023/10/29 23:09:59 by hbalasan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_printmatrix_fd(char **matrix, int fd)
{
	int	i;

	i = -1;
	while (matrix && matrix[++i])
		ft_putendl_fd(matrix[i], fd);
}