/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 19:11:17 by gdemetra          #+#    #+#             */
/*   Updated: 2025/06/12 19:11:17 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static size_t	ft_count_words(const char *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			count++;
		i++;
	}
	return (count);
}

static void	ft_free_array(char **arr, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
		free(arr[i++]);
	free(arr);
}

static char	**ft_alloc_array(const char *s, char c, size_t *word_count)
{
	char	**result;

	*word_count = ft_count_words(s, c);
	result = NULL;
	result = (char **)malloc(sizeof(char *) * (*word_count + 1));
	if (!result)
		return (NULL);
	return (result);
}

static char	**ft_fill_array(char **result, const char *s, char c,
		size_t word_count)
{
	size_t	i;
	size_t	start;
	size_t	len;

	i = 0;
	start = 0;
	while (i < word_count)
	{
		while (s[start] == c)
			start++;
		len = 0;
		while (s[start + len] && s[start + len] != c)
			len++;
		result[i] = ft_substr(s, start, len);
		if (!result[i])
		{
			ft_free_array(result, i);
			return (NULL);
		}
		start += len;
		i++;
	}
	result[i] = NULL;
	return (result);
}

char	**ft_split(const char *s, char c)
{
	char	**result;
	size_t	word_count;

	if (!s)
		return (NULL);
	result = NULL;
	word_count = 0;
	result = ft_alloc_array(s, c, &word_count);
	if (!result)
		return (NULL);
	if (word_count == 0)
	{
		result[0] = NULL;
		return (result);
	}
	return (ft_fill_array(result, s, c, word_count));
}
