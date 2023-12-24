/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbalasan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:57:39 by hbalasan          #+#    #+#             */
/*   Updated: 2023/01/26 17:29:43 by hbalasan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	neg;
	int	res;

	i = 0;
	neg = 1;
	res = 0;
	while (*(str + i) == ' ' || (*(str + i) > 8 && *(str + i) < 14))
		i++;
	if (*(str + i) == '-' || *(str + i) == '+')
	{
		if (*(str + i) == '-')
			neg *= -1;
		i++;
	}
	while (*(str + i) >= '0' && *(str + i) <= '9')
	{
		res *= 10;
		res += *(str + i) - '0';
		i++;
	}
	return (res * neg);
}

int	ft_atoi_ext(const char *c, long *num)
{
	int	sign;
	int	i;

	*num = 0;
	sign = 1;
	i = 0;
	while (c[i] == ' ' || (c[i] >= 9 && c[i] <= 13))
		i++;
	if (*c == '-')
		sign *= -1;
	if (*c == '-' || *c == '+')
		c++;
	if (!ft_isdigit(*c))
		return (-1);
	while (ft_isdigit(*c))
	{
		*num = 10 * *num + (*c - '0');
		c++;
	}
	if (*c && !(c[i] == ' ' || (c[i] >= 9 && c[i] <= 13)))
		return (-1);
	*num *= sign;
	return (0);
}

int		ft_isspace(int c)
{
	const char	*str;
	int			i;

	i = 0;
	str = " \n\t\v\f\r";
	while (c != str[i])
	{
		if (str[i] == '\0')
			return (0);
		i++;
	}
	return (1);
}

long	ft_atol(const char *s)
{
	int		i;
	long	res;
	long	coeff;

	i = 0;
	res = 0;
	coeff = 1;
	while (s[i] && ft_isspace(s[i]))
		i++;
	if (!s[i])
		return (0);
	if (s[i] == '+')
		i++;
	else if (s[i] == '-')
	{
		coeff = -1;
		i++;
	}
	while (s[i] && ft_isdigit(s[i]))
	{
		res = res * 10 + s[i] - '0';
		i++;
	}
	return (res * coeff);
}