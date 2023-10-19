/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbalasan <hbalasan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 01:53:08 by hbalasan          #+#    #+#             */
/*   Updated: 2023/10/20 00:50:05 by hbalasan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

typedef enum e_error
{
	EPERM = 1, // permission denied: 126
	EMEM, // no memory left on device 
	NOTDIR, // Not a directory: 
	ISDIR, // Is a directory: 
	NDIR, // No such file or directory: 
	ECMD, // command not found: 127
	EFORK, // fork failed
	EPIPE, // error creating pipe
	EPIPEND, // syntax error near unexpected token `|'
	DUPERR, // dup2 failed
	EQUOTE // error while looking for matching quote
};

// # define GENERR 1 // EQUOTE
// # define MISUSE 2 // Misuse of shell builtins							Bash Error Message: "No such file or directory"
// # define EPERM 126 // Permission problem or command is not executable	Bash Error Message: "Permission denied"
// # define NCMD 127 // Command not found									Bash Error Message: "Command not found"
// # define EARG 128 // Invalid argument to exit							Bash Error Message: "Invalid argument"


/*********mini_error.c*********/
void	error_msg(char *msg);
void	mini_error(int errmsg, char *param, int errcode);

#endif