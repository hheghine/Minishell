/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbalasan <hbalasan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 21:54:45 by hbalasan          #+#    #+#             */
/*   Updated: 2023/10/23 17:46:22 by hbalasan         ###   ########.fr       */
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

static t_command	*cmd_parameters(t_command *node, char **args[2], int *i)
{
	if (args[0][*i])
	{
		
	}
}

t_list	*fill_nodes(char **args, int i)
{
	char	**temp[2];
	t_list	*nodes[2];

	nodes[0] = NULL;
	temp[1] = trim_args(args);
	while (args[++i])
	{
		nodes[1] = ft_lstlast(nodes[0]);
		if (i == 0 || (args[i][0] == '|' && args[i + 1] && args[i + 1][0]))
		{
			i += (args[i][0] == '|');
			ft_lstadd_back(&nodes[0], ft_lstnew(mini_init()));
			nodes[1] = ft_lstlast(nodes[0]);
		}
		temp[0] = args;
		nodes[1]->content = cmd_parameters(nodes[1]->content, temp, &i);
	}
	
	// ft_free_matrix(&temp[1]); // temporary
	// ft_free_matrix(&args); // temporary
	return (NULL);
}