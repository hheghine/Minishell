/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbalasan <hbalasan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:06:09 by hbalasan          #+#    #+#             */
/*   Updated: 2023/12/22 18:56:42 by hbalasan         ###   ########.fr       */
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
# include <stdbool.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>

/********Pipes********/
# define READ_END 0  //
# define WRITE_END 1 //
/*********************/
/*******Signals*******/
# define SIGINT 2	 // the signal number for SIGINT (Signal Interrupt)
# define CTRLC 1	 // the exit status code of the program that was terminated by receiving the SIGINT signal
/*********************/

int	g_status;

typedef struct s_prompt
{
	t_list	*cmds;
	char	**envp;
	pid_t	pid;
	int		has_comma;
}			t_prompt;

typedef struct s_command
{
	char	**full_cmd;
	char	*full_path;
	int		infile;
	int		outfile;
}			t_command;

/***************************mini_signal.c***************************/
void		sigaction_handler1(void);
void    	sigaction_handler2(void);
void    	sigaction_handler3(void);
void		handle_sigint(int sig);
/*****************************mini_env.c****************************/
char		**set_env(char *var, char *value, char **envp);
char		*get_env(char *varname, char **envp, int n1);
/****************************mini_free.c****************************/
void		free_prompt(t_prompt *prompt);
void		free_content(void *content);
/***************************mini_prompt.c***************************/
char		*get_prompt(t_prompt prompt);
/****************************mini_parse.c***************************/
void		*check_args(char *cmd, t_prompt *prompt);
/***************************mini_cmdtrim.c**************************/
char		**cmd_trim(const char *str, char *set, t_prompt *prompt);
/***************************mini_expand.c***************************/
char		*expand_vars(char *s, t_prompt *prompt, int q[2], int i);
char		*expand_path(char *s, int q[2], char *getpath, int i);
/**************************mini_subsplit.c**************************/
char		**cmd_subsplit(const char *str, char *set);
/**************************mini_strtrim_q.c*************************/
char		*strtrim_quotes(const char *str, int squote, int dquote);
/****************************mini_nodes.c***************************/
// t_list		*fill_nodes(char **args, int i);
t_list	*fill_nodes(t_prompt *prompt, char **args, int i);
/*****************************mini_fd.c*****************************/
int			get_fd(int prev_fd, char *path, int flags[2]);
/***************************mini_iofiles.c**************************/
t_command	*open_outfile1(t_command *node, char **args, int *i);
t_command	*open_outfile2(t_command *node, char **args, int *i);
t_command	*open_infile1(t_command *node, char **args, int *i);
// t_command	*open_infile2(t_command *node, char **args, int *i);
t_command	*open_infile2(t_prompt *prompt, t_command *node, char **args, int *i);
/***************************mini_heredoc.c**************************/
int				mini_here_doc(t_prompt *prompt, char *str[2], char *limiter);
/***************************mini_builtin1.c*************************/
int			mini_builtin(t_prompt *prompt, t_list *cmd, int *isexit, int n);
bool		is_builtin(t_command *cmd);
/**************************mini_builtin2.c**************************/
int			mini_cd(t_prompt *prompt);
int			mini_echo(t_list *cmd);
int			mini_pwd(void);
int			mini_exit(t_list *cmd, int *isexit);
/**************************mini_builtin3.c**************************/
int			mini_unset(t_prompt *prompt);
int			mini_export(t_prompt *prompt, t_list *cmd);
/************************mini_export_utils.c************************/
void		mini_export_noarg(t_prompt *prompt);
void		export_declare_x(char **m);
int			mini_unset(t_prompt *prompt);
int			find_from_envp(char *var, char **envp, int i[2]);
/****************************mini_exec1.c***************************/
void		*exec_command(t_prompt *prompt, t_list *cmd);
void		get_command(t_prompt *prompt, t_list *cmd);
/***************************mini_exec2.c***************************/
void		*mini_fork_check(t_prompt *prompt, t_list *cmd, int fd[2]);
/*******************************************************************/

#endif