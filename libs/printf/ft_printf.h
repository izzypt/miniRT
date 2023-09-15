/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagalha <smagalha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 22:58:41 by smagalha          #+#    #+#             */
/*   Updated: 2023/01/08 16:42:27 by smagalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>

int		ft_putnbr(int nb, int fd);
int		ft_putchar(char c, int fd);
int		ft_putstr(char *s, int fd);
size_t	ft_strlen(char *str);
int		ft_puthex(unsigned long n, const char ch);
int		ft_putaddress(unsigned long address);
int		ft_printf(const char *s, ...);
int		ft_putnbru(unsigned int nb, int fd);

#endif
