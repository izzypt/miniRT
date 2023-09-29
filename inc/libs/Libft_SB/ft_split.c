/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagalha <smagalha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 20:09:43 by smagalha          #+#    #+#             */
/*   Updated: 2022/12/10 21:39:51 by smagalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*extract_string(char const *s, char c, size_t i, size_t j)
{
	char	*substr;

	if (s[i + j] == c || s[i + j] == '\0')
	{
		substr = (char *)malloc(sizeof(char) * (j + 1));
		if (!substr)
			return (NULL);
		substr[j] = '\0';
		return (substr);
	}
	else
	{
		substr = extract_string(s, c, i, (j + 1));
		substr[j] = s[i + j];
		return (substr);
	}
}

static size_t	nstrings(char const *s, char c)
{
	size_t	strings;
	size_t	i;

	i = 0;
	strings = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i])
		{
			strings++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
	}
	return (strings);
}

char	**ft_split(char const *s, char c)
{
	char	**output;
	size_t	strings;
	size_t	i;
	size_t	ii;

	strings = nstrings(s, c);
	i = 0;
	ii = -1;
	output = (char **)malloc(sizeof(char *) * (strings + 1));
	if (!output)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			ii++;
			output[ii] = extract_string(s, c, i, 0);
			i = i + ft_strlen(output[ii]);
		}
		while (s[i] == c && c)
			i++;
	}
	output[ii + 1] = NULL;
	return (output);
}
