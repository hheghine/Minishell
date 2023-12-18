/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_iofiles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbalasan <hbalasan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 04:06:25 by hbalasan          #+#    #+#             */
/*   Updated: 2023/12/18 20:52:49 by hbalasan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// extern int	g_status;

t_command	*open_outfile1(t_command *node, char **args, int *i)
{
	int		flags[2];

	flags[0] = 1;
	flags[1] = 0;
	(*i)++;
	if (args && args[(*i)])
		node->outfile = get_fd(node->outfile, args[*i], flags);
	else if (!args[(*i)] || node->outfile == -1)
	{
		*i = -1;
		if (node->outfile == -1)
			g_status = 1;
		else
		{
			print_error_msg_fd("syntax error near unexpected token `newline'" \
																		, 1);
			g_status = 2;
		}
	}
	return (node);
}

t_command	*open_outfile2(t_command *node, char **args, int *i)
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
			g_status = 1;
		else
		{
			print_error_msg_fd("syntax error near unexpected token `newline'", \
																			1);
			g_status = 2;
		}
	}
	return (node);
}

t_command	*open_infile1(t_command *node, char **args, int *i)
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
			print_error_msg_fd("syntax error near unexpected token `newline'", \
																			1);
			g_status = 2;
		}
		else
			g_status = 1;
	}
	return (node);
}

t_command	*open_infile2(t_prompt *prompt, t_command *node, char **av, int *i)
{
	char	*str[2];
	char	*temp;

	str[0] = NULL;
	str[1] = NULL;
	(*i)++;
	if (av[++(*i)])
	{
		temp = av[*i];
		node->infile = mini_here_doc(prompt, str, temp);
	}
	if (!av[*i] || node->infile == -1)
	{
		*i = -1;
		if (node->infile != -1)
		{
			print_error_msg_fd("syntax error near unexpected token `newline'", \
																			1);
			g_status = 2;
		}
	}
	return (node);
}
