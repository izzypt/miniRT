/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagalha <smagalha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 19:05:13 by smagalha          #+#    #+#             */
/*   Updated: 2023/01/07 23:13:01 by smagalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthex(unsigned long n, const char ch)
{
	int			len;
	const char	*hex;
	const char	*hexm;

	len = 0;
	hex = "0123456789abcdef";
	hexm = "0123456789ABCDEF";
	if (n >= 16)
	{
		len += ft_puthex(n / 16, ch);
		len += ft_puthex(n % 16, ch);
	}
	if (n < 16)
	{
		if (ch == 'x')
			len += ft_putchar(hex[n], 1);
		else if (ch == 'X')
			len += ft_putchar(hexm[n], 1);
	}
	return (len);
}
