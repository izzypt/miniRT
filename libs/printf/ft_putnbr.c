/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagalha <smagalha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 18:56:32 by smagalha          #+#    #+#             */
/*   Updated: 2023/01/07 23:03:13 by smagalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// Outputs the integer ’n’ to the given file descriptor.
int	ft_putnbr(int nb, int fd)
{
	unsigned int	nbr;
	int				len;

	len = 0;
	if (nb < 0)
	{
		len += ft_putchar('-', fd);
		nbr = (unsigned int)(nb * -1);
	}
	else
		nbr = (unsigned int)nb;
	if (nbr >= 10)
		len += ft_putnbr(nbr / 10, fd);
	len += ft_putchar((char)('0' + nbr % 10), fd);
	return (len);
}
