/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbalasan <hbalasan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 21:54:45 by hbalasan          #+#    #+#             */
/*   Updated: 2023/10/23 02:47:49 by hbalasan         ###   ########.fr       */
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

t_list	*fill_nodes(char **args, int i)
{
	char	**temp[2];

	temp[0] = trim_args(args);

	for (int i = 0; temp[0][i]; i++)
	{
		for (int j = 0; temp[0][i][j]; j++)
			printf("%c", temp[0][i][j]);
		printf("\n");
	}
	ft_free_matrix(&temp[0]); // temporary
	ft_free_matrix(&args); // temporary
	return (NULL);
}