/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 16:47:20 by simao             #+#    #+#             */
/*   Updated: 2023/10/03 12:29:05 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	result;
	int	signal;

	i = 0;
	result = 0;
	signal = 1;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signal = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9' && str[i])
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result * signal);
}

float ft_atof(const char *str)
{
    int i = 0;
    int signal = 1;
    float result = 0.0;
    float decimalPlace = 0.1;

    while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
        || str[i] == '\v' || str[i] == '\f' || str[i] == '\r') {
        i++;
    }
    if (str[i] == '-') {
        signal = -1;
        i++;
    } else if (str[i] == '+') {
        i++;
    }

    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10.0 + (str[i] - '0');
        i++;
    }
    if (str[i] == '.') 
	{
        i++;

        while (str[i] >= '0' && str[i] <= '9') {
            result = result + (str[i] - '0') * decimalPlace;
            decimalPlace *= 0.1;
            i++;
        }
    }
    result *= signal;
    return result;
}