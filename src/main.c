/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbalasan <hbalasan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:21:22 by hbalasan          #+#    #+#             */
/*   Updated: 2023/10/13 20:23:45 by hbalasan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cmd;

int	main()
{
	printf("\n%s\n\n", MINISHELL1);

	while (1)
	{
		cmd = readline(READLINE_MSG);
		if (cmd != NULL && ft_strlen(cmd) > 0)
    		add_history(cmd);
		if (!ft_strncmp(cmd, "ifconfig", 8))
			system("ifconfig");
		else if (!ft_strncmp(cmd, "date", 4))
			system("date");
		else if (!ft_strncmp(cmd, "ls", 2))
			system("ls");
		else if (!ft_strncmp(cmd, "exit", 4))
		{
			free(cmd);	
			break ;
		}
	}
}