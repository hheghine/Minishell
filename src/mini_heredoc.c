/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmnatsak <tmnatsak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 22:28:09 by hbalasan          #+#    #+#             */
/*   Updated: 2023/11/09 19:30:30 by tmnatsak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_gstatus;

char	*here_doc(char *str[2], char *limiter, char *warning, uint64_t len)
{
	char	*temp;

	while (g_gstatus != 130 && (!str[0] || ft_strncmp(str[0], limiter, len) \
		|| (uint64_t)ft_strlen(limiter) != len))
	{
		temp = str[1];
		str[1] = ft_strjoin(str[1], str[0]);
		free(str[0]);
		free(temp);
		str[0] = readline("\033[0;35m> \033[0m");
		if (!str[0])
		{
			printf("\033[1;35mminishell: \033[0;35m%s (wanted `%s\')\033[0m\n", \
															warning, limiter);
			break ;
		}
		temp = str[0];
		str[0] = ft_strjoin(str[0], "\n");
		free(temp);
		len = ft_strlen(str[0]) - 1;
	}
	free(str[0]);
	return (str[1]);
}

int	mini_here_doc(t_prompt *prompt, char *str[2], char *limiter)
{
	int	fd[2];
	int	q[2];

	g_gstatus = 0;
	if (pipe(fd) < 0)
	{
		mini_error(EPIPE, NULL, 1);
		return (-1);
	}
	str[1] = here_doc(str, limiter, \
		"warning: here-document delimited by end-of-file", 0);
	str[0] = expand_vars(str[1], prompt, q, -1);
	write(fd[WRITE_END], str[0], ft_strlen(str[0]));
	free(str[0]);
	close(fd[WRITE_END]);
	if (g_gstatus == 130)
	{
		close(fd[READ_END]);
		return (-1);
	}
	return (fd[READ_END]);
}
