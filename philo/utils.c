/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:33:32 by authomas          #+#    #+#             */
/*   Updated: 2025/09/16 15:39:43 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int     ft_atoi(char *s)
{
		int i;
		int res;
		int sign;

		res = 0;
		i = 0;
		sign = 1;
		while (s[i] == ' ' || (s[i] >= '\t' && s[i] <= '\r'))
			i++;
		if (s[i] == '-' || s[i] == '+')
		{
			if (s[i] == '-')
				sign = sign * -1;
			i++;
		}
		while (s[i] >= '0' && s[i] <= '9')
		{
			res = res * 10 + (s[i] - '0');
			i++;
		}
		return (res * sign);
}
