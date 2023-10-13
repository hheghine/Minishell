/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbalasan <hbalasan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 21:29:05 by hbalasan          #+#    #+#             */
/*   Updated: 2023/10/13 23:45:07 by hbalasan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
- command separators: ; && ||
- command:
	- identifier
	- argument
	- pipes(separated by)
- redirections:	> < >>
	- [name] file that needs to be created, read or updated (single word)
	- following commands (separated by pipes)
	- ****CHECK***	echo okay baby > a sure| cat
*/

/*
- environment variables
	-USER=hbalasan42 used by our 42 header
	- PATH used everytime we write a command (shell will look for executables in different directories specified in the variable)
	- PWD and OLDPWDupdated everytime we change directories. OLDPWD is used for cd - to go back to previous directory.
	- HOME used for cd (with no arguments)
	- SHLVL used in case we call ./minishell
	- ***CHECK***	echo $PWD$USER	-> /Users/hbalasan42/Desktop/Minishellhbalasan42
*/