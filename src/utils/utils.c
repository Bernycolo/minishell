/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bconejo- <bconejo-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 19:00:02 by bconejo-          #+#    #+#             */
/*   Updated: 2026/09/04 19:00:03 by bconejo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/**
 * @brief Compares two strings
 * 
 * @param s1 The string one
 * @param s2 The string two
 * @return Returns an integer indicating the result of the comparison
 * 
 * - 0, if the s1 and s2 are equal
 * 
 * - a negative value if s1 is less than s2
 * 
 * - a positive value if s1 is greater than s2
 */
int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/**
 * @brief Joins two strings and frees the allocated memory
 *
 * @param s1 The string one
 * @param s2 The string two
 * @return The join of the two strings
 */
char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*join;

	join = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (join);
}

/**
 * @brief Frees the memory allocated by a pointer void
 * 
 * @param ptr The pointer to free
 */
void	free_mem(void *ptr)
{
	if (!ptr)
		return ;
	free(ptr);
	ptr = NULL;
}

/**
 * @brief Frees the memory allocated by a double pointer void
 * 
 * @param ptr The pointer to free
 */
void	free_mem_all(char **ptr)
{
	int	i;

	if (!ptr)
		return ;
	i = 0;
	while (ptr[i])
		free_mem(ptr[i++]);
	free(ptr);
	ptr = NULL;
}

/**
 * @brief Reads a line from standard input for non-interactive mode
 * 
 * Uses get_next_line to read from STDIN (fd 0). If a line is successfully 
 * read, it removes the trailing newline character ('\n') before returning it,
 * mimicking the behavior of the standard readline function
 * 
 * @return A dynamically allocated string containing the line read, 
 *         or NULL if EOF is reached or an error occurs
 */
char	*read_line(void)
{
	char	*line;
	int		len;

	line = get_next_line(0);
	if (!line)
		return (NULL);
	len = ft_strlen(line);
	if (len > 0)
	{
		if (line[len - 1] == '\n')
			line[len -1] = '\0';
	}
	return (line);
}
