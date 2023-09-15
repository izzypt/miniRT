/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagalha <smagalha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:27:36 by smagalha          #+#    #+#             */
/*   Updated: 2022/12/09 14:28:18 by smagalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int chr, size_t n)
{
	size_t			i;
	unsigned char	*string;
	unsigned char	carachter;

	i = 0;
	string = (unsigned char *)str;
	carachter = (unsigned char)chr;
	while (i < n)
	{
		if (string[i] == carachter)
			return ((void *)str + i);
		i++;
	}
	return (NULL);
}
