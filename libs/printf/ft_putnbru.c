/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbru_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagalha <smagalha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:39:53 by smagalha          #+#    #+#             */
/*   Updated: 2023/01/08 18:26:55 by smagalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// Outputs the integer ’n’ to the given file descriptor.
int	ft_putnbru(unsigned int nb, int fd)
{
	int				len;

	len = 0;
	if (nb >= 10)
		len += ft_putnbru(nb / 10, fd);
	len += ft_putchar((char)('0' + nb % 10), fd);
	return (len);
}
