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
