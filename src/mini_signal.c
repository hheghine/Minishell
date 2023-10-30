/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbalasan <hbalasan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:00:08 by hbalasan          #+#    #+#             */
/*   Updated: 2023/10/31 01:53:29 by hbalasan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	gstatus;

// struct sigaction {
//     void (*sa_handler)(int);      // Pointer to the signal handler function
//     void (*sa_sigaction)(int, siginfo_t *, void *); // Alternative signal handler with more information
//     sigset_t sa_mask;             // Signals to be blocked during the execution of the handler
//     int sa_flags;                 // Flags that control the behavior of the handler
//     void (*sa_restorer)(void);    // Not used in modern systems, reserved for future use
// };

void sigaction_handler1(void)
{
    struct sigaction sa;

    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sa.sa_handler = handle_sigint;
    if (sigaction(SIGINT, &sa, NULL) == -1)
        error_msg("Error setting up SIGINT handler");
    sa.sa_handler = SIG_IGN; // maybe i don't need this one
    if (sigaction(SIGQUIT, &sa, NULL) == -1)
        error_msg("Error setting up SIGQUIT handler");
}

void    sigaction_handler2(void)
{
    struct sigaction sa;

    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGINT, &sa, NULL) == -1)
        error_msg("Error setting up SIGINT handler");
    sa.sa_handler = SIG_IGN;
    if (sigaction(SIGQUIT, &sa, NULL) == -1)
        error_msg("Error setting up SIGQUIT handler");
}

void    sigaction_handler3(void)
{
    struct sigaction sa;

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
		gstatus = CTRLC;
		ioctl(STDIN_FILENO, TIOCSTI, "\n"); // Terminal Input Output Control Simulate Terminal Input
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}