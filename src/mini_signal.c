/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmnatsak <tmnatsak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:00:08 by hbalasan          #+#    #+#             */
/*   Updated: 2023/11/09 19:39:40 by tmnatsak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_gstatus;

static int	quit_handler(void)
{
	return (0);
}

void	sigaction_handler1(void)
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handle_sigint;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		error_msg("Error setting up SIGINT handler");
	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		error_msg("Error setting up SIGQUIT handler");
	rl_catch_signals = 0;
	rl_event_hook = &quit_handler;
}

void	sigaction_handler2(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		error_msg("Error setting up SIGINT handler");
	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		error_msg("Error setting up SIGQUIT handler");
}

void	sigaction_handler3(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		error_msg("Error setting up SIGQUIT handler");
	sa.sa_handler = SIG_DFL;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		error_msg("Error setting up SIGQUIT handler");
}

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		g_gstatus = CTRLC;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
	}
}
