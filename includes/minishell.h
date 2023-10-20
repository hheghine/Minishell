/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbalasan <hbalasan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:06:09 by hbalasan          #+#    #+#             */
/*   Updated: 2023/10/21 02:33:40 by hbalasan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libraries/libft/libft.h"
# include "visuals.h"
# include "error.h"
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
/*******************/
/******Signals******/
# define SIGINT 2	// the signal number for SIGINT (Signal Interrupt)
# define CTRLC 130	// the exit status code of the program that was terminated by receiving the SIGINT signal
/******************/
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

/*********mini_signal.c*********/
void	handle_sigint(int sig);	// handles Ctrl+C
/**********************mini_env.c**********************/
char	**set_env(char *var, char *value, char **envp); // sets the new environment variable
char	*get_env(char *varname, char **envp, int n1); // allocates a string with malloc containing the value of an env var
/**************mini_free.c**************/
void	free_prompt(t_prompt *prompt);
void	free_content(void *content);
/*************mini_prompt.c*************/
char	*get_prompt(t_prompt prompt);
/*****************mini_parse.c*****************/
void	*check_args(char *cmd, t_prompt *prompt);
/****************mini_cmdtrim.c****************/
char	**cmd_trim(const char *s, char *set);
/**************************mini_expand.c**************************/
char	*expand_vars(char *s, t_prompt *prompt, int q[2], int i);
char	*expand_path(char *s, int q[2], char *getpath, int i);

#endif