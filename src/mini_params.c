/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbalasan <hbalasan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 17:36:26 by hbalasan          #+#    #+#             */
/*   Updated: 2023/10/23 22:22:04 by hbalasan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	gstatus;

/***********************************************/
/* F_OK checks if the file or path exists.     */
/* X_OK checks if you have execute permission. */
/* R_OK checks if you have read permission.    */
/* W_OK checks if you have write permission.   */
/***********************************************/

/*********************************************************************************/
/* flags[0] = 1 expectation that the file exists                                 */
/*                                                                               */
/* flags[1] = 1 data is appended to the file                                     */
/* flags[1] = 0 the file is truncated before writing new data aka overwriting    */
/*********************************************************************************/

/*********************************************************************************/
/* 6 -> 110 (1) read permission, (1) write permission, (0) no execute permission */
/*********************************************************************************/

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
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0666); // >>
	else if (flags[0] && !flags[1])
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666);  // >
	else if (!flags[0] && prev_fd != -1)
		fd = open(path, O_RDONLY);
	else
		fd = prev_fd;
	return (fd);
}

t_command	*get_outfile1(t_command *node, char **args, int *i)
{
	int		flags[2];

	flags[0] = 1;
	flags[1] = 0;
	(*i)++;
	if (args[++(*i)])
		node->outfile = get_fd(node->outfile, args[*i], flags);
	if (!args[*i] || node->outfile == -1)
	{
		*i = -1;
		if (node->outfile == -1)
		{
			print_error_msg_fd("syntax error near unexpected token `newline'");
			gstatus = 2;
		}
		else
			gstatus = 1;
	}
	return (node);
}

t_command	*get_outfile2(t_command *node, char **args, int *i)
{
	int		flags[2];

	flags[0] = 1;
	flags[1] = 1;
	(*i)++;
	if (args[++(*i)])
		node->outfile = get_fd(node->outfile, args[*i], flags);
	if (!args[*i] || node->outfile == -1)
	{
		*i = -1;
		if (node->outfile == -1)
		{
			print_error_msg_fd("syntax error near unexpected token `newline'");
			gstatus = 2;
		}
		else
			gstatus = 1;
	}
	return (node);
}

t_command	*get_infile1(t_command *node, char **args, int *i)
{
	int		flags[2];

	flags[0] = 0;
	flags[1] = 0;
	(*i)++;
	if (args[*i])
		node->infile = get_fd(node->infile, args[*i], flags);
	if (!args[*i] || node->infile == -1)
	{
		*i = -1;
		if (node->infile != -1)
		{
			print_error_msg_fd("syntax error near unexpected token `newline'");
			gstatus = 2;
		}
		else
			gstatus = 1;
	}
	return (node);
}

t_command	*get_infile2(t_command *node, char **args, int *i)
{
	char	*str[2];
	char	*temp[2];
	
	str[0] = NULL;
	str[1] = NULL;
	temp[0] = NULL;
	temp[1] = "warning: here-document delimited by end-of-file";
	(*i)++;
	if (args[++(*i)])
	{
		temp[0] = args[*i];
		node->infile = mini_here_doc(str, temp);
	}
	if (!args[*i] || node->infile == -1)
	{
		*i = -1;
		if (node->infile != -1)
		{
			print_error_msg_fd("yntax error near unexpected token `newline'");
			gstatus = 2;
		}
	}
	return (node);
}
