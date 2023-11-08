/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 22:18:51 by simao             #+#    #+#             */
/*   Updated: 2023/11/07 22:30:24 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\n' || c == '\t' || \
	c == '\v' || c == '\f' || c == '\r');
}

int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

float	parse_integer(const char *str, int *i, float *result)
{
	while (is_digit(str[*i]))
	{
		*result = *result * 10.0 + (str[*i] - '0');
		(*i)++;
	}
	return (*result);
}

float	parse_float(const char *str, int *i, float *result)
{
	float	decimal_place;

	decimal_place = 0.1;
	(*i)++;
	while (is_digit(str[*i]))
	{
		*result = *result + (str[*i] - '0') * decimal_place;
		decimal_place *= 0.1;
		(*i)++;
	}
	return (*result);
}

float	ft_atof(const char *str)
{
	int		i;
	int		signal;
	float	result;

	i = 0;
	signal = 1;
	result = 0.0;
	while (is_whitespace(str[i]))
		i++;
	if (str[i] == '-')
	{
		signal = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	parse_integer(str, &i, &result);
	if (str[i] == '.')
		parse_float(str, &i, &result);
	result *= signal;
	return (result);
}
