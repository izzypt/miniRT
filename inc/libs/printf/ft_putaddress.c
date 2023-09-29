/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddress.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagalha <smagalha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 19:41:23 by smagalha          #+#    #+#             */
/*   Updated: 2023/01/07 22:24:16 by smagalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putaddress(unsigned long address)
{
	int				len;
	char			*address_prefix;

	address_prefix = "0x";
	len = 0;
	if (!address)
	{
		return (ft_putstr("(nil)", 1));
	}
	len += ft_putstr(address_prefix, 1);
	len += ft_puthex(address, 'x');
	return (len);
}
