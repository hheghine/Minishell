/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbalasan <hbalasan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:21:22 by hbalasan          #+#    #+#             */
/*   Updated: 2023/10/13 23:46:13 by hbalasan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_msg(char *msg)
{
	printf("%s", msg);
	exit (1);
}

int	main(int argc, char **argv, char **env)
{
	char	*cmd = "";
	
	if (argc > 1)
		error_msg("\033[33mMinishell doesn't take any arguments!\033[0m\n");
	printf("\n%s\n\n", MINISHELL1);
	while (1)
	{
		cmd = readline(READLINE_MSG);
		if (!cmd || !ft_strncmp(cmd, "exit", 4))
		{
			free(cmd);
			break ;
		}
		if (ft_strlen(cmd) > 0)
    		add_history(cmd);
	}
}