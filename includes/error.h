/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbalasan <hbalasan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 01:53:08 by hbalasan          #+#    #+#             */
/*   Updated: 2023/10/17 03:50:35 by hbalasan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

enum	e_error
{
	EPERM = 1,
	EMEM,
	ENOTDIR,
	EISDIR,
	NDIR,
	ECMD,
	EFORK,
	EPIPE,
	EPIPEND,
	DUPERR,
	EQUOTE
};

/*********mini_error.c*********/
void	error_msg(char *msg); // prints custom error messages

#endif