/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbalasan <hbalasan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:35:22 by hbalasan          #+#    #+#             */
/*   Updated: 2023/10/20 23:55:14 by hbalasan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	gstatus;

void	error_msg(char *msg)
{
	printf("%s %s %s\n", "\033[1;33m⚠ minishell: \033[0;33m", msg, DEFAULT);
	exit (1);
}

static void	set_status(int errcode)
{
	gstatus = errcode;
	ft_putstr_fd("\033[1;33m⚠ minishell: ", 2);
}

void	*mini_error(int errmsg, char *param, int errcode)
{
	set_status(errcode);
	if (errmsg == EPERM)
		ft_putstr_fd("\033[0;33mpermission denied: \033[0m", 2);
	else if (errmsg == EMEM)
		ft_putstr_fd("\033[0;33mno memory left on device\033[0m\n", 2);
	else if (errmsg == NOTDIR)
		ft_putstr_fd("\033[0;33mNot a directory: \033[0m", 2);
	else if (errmsg == ISDIR)
		ft_putstr_fd("\033[0;33mIs a directory: \033[0m", 2);
	else if (errmsg == NDIR)
		ft_putstr_fd("\033[0;33mNo such file or directory: ", 2);
	else if (errmsg == ECMD)
		ft_putstr_fd("\033[0;33mcommand not found: ", 2);
	else if (errmsg == EFORK)
		ft_putstr_fd("\033[0;33mfork failed\n", 2);
	else if (errmsg == EPIPE)
		ft_putstr_fd("\033[0;33merror creating pipe\n", 2);
	else if (errmsg == EPIPEND)
		ft_putstr_fd("\033[0;33msyntax error near unexpected token `|'\n", 2);
	else if (errmsg == DUPERR)
		ft_putstr_fd("\033[0;33mdup2 failed\n", 2);
	else if (errmsg == EQUOTE)
		ft_putstr_fd("\033[0;33merror while looking for matching quote\n", 2);
	ft_putendl_fd(param, 2);
	return (NULL);
}