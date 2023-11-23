/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbalasan <hbalasan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 17:36:26 by hbalasan          #+#    #+#             */
/*   Updated: 2023/11/23 18:36:31 by hbalasan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

int	get_fd(int prev_fd, char *path, int flags[2])
{
	int	fd;

	if (prev_fd > 2)
		close(prev_fd);
	if (!path)
		return (-1);
	if (!flags[0] && access(path, F_OK) == -1)
		mini_error(NDIR, path, 127);
	else if (!flags[0] && access(path, R_OK) == -1)
		mini_error(EPERM, path, 126);
	else if (flags[0] && access(path, F_OK) == 0 && access(path, W_OK) == -1)
		mini_error(EPERM, path, 126);
	if (flags[0] && flags[1])
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0666);
	else if (flags[0] && !flags[1])
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (!flags[0] && prev_fd != -1)
		fd = open(path, O_RDONLY);
	else
		fd = prev_fd;
	return (fd);
}
