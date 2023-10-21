/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbalasan <hbalasan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 21:35:14 by hbalasan          #+#    #+#             */
/*   Updated: 2023/10/21 18:02:29 by hbalasan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char **split_final(char **args, t_prompt *prompt)
{
	char	**subsplit;
	int		i;
	int		q[2];

	i = -1;
	while (args && args[++i])
	{
		args[i] = expand_vars(args[i], prompt, q, -1);
		args[i] = expand_path(args[i], q, \
			get_env("HOME", prompt->envp, -1), -1);
		//subsplit = cmd_subsplit(args[i], "<>|"); // split commands with <, >, or | 
		// then i need to replace n-th line with another matrix, yes, i think it's gonna be a ***BIG_MATRIX
		//i += ft_matrix_len(subsplit);
		// ft_free_subsplit(subsplit);
	}
	return (args);
}

void	*parse_args(char **args, t_prompt *prompt)
{
	char	**splitted;
	int		i;
	int		exitcode;

	exitcode = 0;
	splitted = split_final(args, prompt);
	
	for (int i = 0; splitted[i]; i++)
	{
		for (int j = 0; splitted[i][j]; j++)
			printf("%c", splitted[i][j]);
		printf("\n");
	}
	
	ft_free_matrix(&splitted);
	// prompt->cmds = fill_nodes(splitted);
}

void	*check_args(char *cmd, t_prompt *prompt)
{
	char		**trim;
	t_command	command;

	if (!cmd || !ft_strncmp(cmd, "exit", 4))
	{
		printf("\033[1;35mexit⋆⁺₊⋆ ☾⋆⁺₊⋆\033[0m\n");
		free(cmd);
		return (NULL);
	}
	if (ft_strlen(cmd) > 0)
    	add_history(cmd);
	trim = cmd_trim(cmd, " ");
	if (!trim)
		return ("");
	free(cmd);
	prompt = parse_args(trim, prompt);
	return ("a"); // temporary
}