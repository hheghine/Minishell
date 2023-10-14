/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbalasan <hbalasan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:06:09 by hbalasan          #+#    #+#             */
/*   Updated: 2023/10/14 16:23:20 by hbalasan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libraries/libft/libft.h"
# include "visuals.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>

/*******Pipes*******/
# define READ_END 0
# define WRITE_END 1

/******Signals******/
# define SIGINT 2	// the signal number for SIGINT (Signal Interrupt)
# define CtrlC 130	// the exit status code of the program that was terminated by receiving the SIGINT signal

typedef struct s_prompt
{
	t_list	*cmds;
	char	**envp;
	pid_t	pid;
}			t_prompt;

typedef struct s_command
{
	char	**full_cmd;
	char	*full_path;
	int		infile;
	int		outfile;
}			t_command;

/*       Handles Ctrl+C       */
void	handle_sigint(int sig);

#endif