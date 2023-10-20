/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbalasan <hbalasan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 21:35:14 by hbalasan          #+#    #+#             */
/*   Updated: 2023/10/20 23:59:55 by hbalasan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*check_args(char *cmd, t_prompt prompt)
{
	char		**trim;
	t_command	command;

	if (!cmd || !ft_strncmp(cmd, "exit", 4))
	{
		printf("\033[1;35mexit ⋆⁺₊⋆ ☾⋆⁺₊⋆\033[0m\n");
		free(cmd);
		return (NULL);
	}
	if (ft_strlen(cmd) > 0)
    	add_history(cmd);
	trim = cmd_trim(cmd, " ");
	if (!trim)
		return ("");
	free(cmd);
	ft_free_matrix(&trim); // temporary 
	return ("a"); // temporary
}