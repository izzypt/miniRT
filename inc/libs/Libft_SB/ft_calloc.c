/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagalha <smagalha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 22:21:01 by smagalha          #+#    #+#             */
/*   Updated: 2022/12/09 15:45:56 by smagalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t elements, size_t bytes)
{
	void	*ptr;

	ptr = malloc(elements * bytes);
	if (!ptr)
		return (NULL);
	else
		ft_bzero(ptr, (elements * bytes));
	return (ptr);
}
