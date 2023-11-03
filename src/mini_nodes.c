/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbalasan <hbalasan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 21:54:45 by hbalasan          #+#    #+#             */
/*   Updated: 2023/11/03 16:47:05 by hbalasan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_command	*init_t_command(void)
{
	t_command	*command;

	command = (t_command *)malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->full_cmd = NULL;
	command->full_path = NULL;
	command->infile = STDIN_FILENO;
	command->outfile = STDOUT_FILENO;
	return (command);
}

void	*free_nodes(t_list *node, char **args, char **temp)
{
	ft_lstclear(&node, free_content);
	ft_free_matrix(&args);
	ft_free_matrix(&temp);
	return (NULL);
}

static char	**trim_args(char **args)
{
	char	**trimmed;
	char	*str;
	int		i;

	i = -1;
	trimmed = ft_dup_matrix(args);
	while (trimmed && trimmed[++i])
	{
		str = strtrim_quotes(trimmed[i], 0, 0);
		free(trimmed[i]);
		trimmed[i] = str;
	}
	return (trimmed);
}

static t_command	*cmd_parameters(t_prompt *prompt, t_command *cmd, char **args[2], int *i)
{
	if (args[0][*i])
	{
		// printf("%s %d\n", *args[1], *i);
		if (args[0][*i][0] == '>' && args[0][*i + 1] && args[0][*i + 1][0] == '>')
			cmd = open_outfile2(cmd, args[1], i);
		else if (args[0][*i][0] == '>')
			cmd = open_outfile1(cmd, args[1], i);
		else if (args[0][*i][0] == '<' && args[0][*i + 1] \
			&& args[0][*i + 1][0] == '<')
			cmd = open_infile2(prompt, cmd, args[1], i);
		else if (args[0][*i][0] == '<')
			cmd = open_infile1(cmd, args[1], i);
		else if (args[0][*i][0] != '|')
			cmd->full_cmd = ft_extend_matrix(cmd->full_cmd, args[1][*i]);
		else
		{
			mini_error(EPIPEND, NULL, 2);
			*i = -2;
		}
		return(cmd);
	}
	mini_error(EPIPEND, NULL, 2);
	*i = -2;
	return (cmd);
}

t_list	*fill_nodes(t_prompt *prompt, char **args, int i)
{
	char	**temp[2];
	t_list	*nodes[2];

	temp[0] = args;
	temp[1] = trim_args(args);
	nodes[0] = NULL;
	while (args[++i])
	{
		nodes[1] = ft_lstlast(nodes[0]);
		if (i == 0 || (args[i][0] == '|' && args[i + 1] && args[i + 1][0]))
		{
			i += (args[i][0] == '|'); // (args[i][0] == '<' && args[i][1] && args[i][1] == '<')
			ft_lstadd_back(&nodes[0], ft_lstnew(init_t_command()));
			nodes[1] = ft_lstlast(nodes[0]);
		}
		nodes[1]->content = cmd_parameters(prompt, nodes[1]->content, temp, &i);
		if (i < 0)
			return (free_nodes(nodes[0], args, temp[1]));
		if (!args[i])
			break ;
	}
	ft_free_matrix(&temp[1]);
	ft_free_matrix(&args);
	return (nodes[0]);
}