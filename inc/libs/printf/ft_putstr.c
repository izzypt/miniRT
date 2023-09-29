/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagalha <smagalha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:52:52 by smagalha          #+#    #+#             */
/*   Updated: 2023/01/08 17:53:54 by smagalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *s, int fd)
{
	int	len;

	if (!s)
		return (ft_putstr("(null)", 1));
	len = ft_strlen(s);
	if (fd < 0)
		return (0);
	write(fd, s, len);
	return (len);
}

// int main(void)
// {
// 	//int	num = NULL;
// 	char *s = NULL;
// 	ft_putstr_fd(s, 1);
// 	printf("\n%s ", s);

// 	return (0);
// }