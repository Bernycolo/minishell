/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bconejo- <bconejo-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:16:45 by bconejo-          #+#    #+#             */
/*   Updated: 2026/04/26 16:54:33 by bconejo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

static void	free_mem(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
		free(str[i++]);
	free(str);
}

static char	**copy_words(char **dst, char const *src, int n_words, char sep)
{
	int		i;
	int		j;
	int		start;
	int		len_word;

	i = 0;
	j = 0;
	while (src[i] && j < n_words)
	{
		while (src[i] == sep)
			i++;
		start = i;
		while (src[i] && src[i] != sep)
			i++;
		len_word = i - start;
		dst[j] = malloc(len_word + 1);
		if (!dst[j])
		{
			free_mem(dst);
			return (NULL);
		}
		ft_strlcpy(dst[j++], src + start, len_word + 1);
	}
	dst[j] = NULL;
	return (dst);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	split = ft_calloc(words + 1, sizeof(char *));
	if (!split)
		return (NULL);
	if (!copy_words(split, s, words, c))
		return (NULL);
	return (split);
}
