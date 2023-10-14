/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbalasan <hbalasan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:21:22 by hbalasan          #+#    #+#             */
/*   Updated: 2023/10/14 18:26:06 by hbalasan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	sigstat;

void	error_msg(char *msg)
{
	printf("%s %s\n", "\033[33m✧ minishell:", msg);
	exit (1);
}

int	main(int argc, char **argv, char **env)
{
	char	*cmd = "";
	
	if (argc > 1)
		error_msg("Minishell doesn't take any arguments!\033[0m");
	printf("\n%s\n\n", MINISHELL1);
	while (1)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		cmd = readline(READLINE_MSG);
		if (!cmd || !ft_strncmp(cmd, "exit", 4))
		{
			free(cmd);
			break ;
		}
		if (ft_strlen(cmd) > 0)
    		add_history(cmd);
		free(cmd);
	}
}