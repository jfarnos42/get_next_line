/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarnos- <jfarnos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 20:41:30 by jfarnos-          #+#    #+#             */
/*   Updated: 2023/04/06 16:53:10 by jfarnos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * The function updates a string by removing the first line and returning the 
 * updated string.
 * 
 * @param str The input string that needs to be updated.
 * It is assumed that this string contains at least one newline character.
 * 
 * @return a pointer to a newly allocated string that contains the remaining 
 * characters after the first line break character in the input string. 
 * If the input string does not contain a line break character, or if the 
 * line break character is the last character in the string, the function 
 * returns  NULL or the original input string, respectively.
 */
char	*ft_update_fd(char *str, int i, int j)
{
	char	*aux;

	if (ft_strchr(str, '\n') == '\0')
	{
		if (str)
			free(str);
		return (NULL);
	}
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	i = i + 1;
	if (str[i - 1] == '\0')
	{
		return (str);
	}
	j = 0;
	aux = malloc((ft_strlen(str) - i) + 1);
	if (!aux)
		return (NULL);
	while (str[i] != 0)
		aux[j++] = str[i++];
	aux[j] = str[i];
	free(str);
	return (aux);
}

char	*ft_find_end_of_line(char *str)
{
	int		i;
	char	*aux;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i])
		i++;
	aux = malloc(i + 2);
	if (!aux)
		return (NULL);
	aux[i + 1] = '\0';
	while (i >= 0)
	{
		aux[i] = str[i];
		i--;
	}
	return (aux);
}

char	*get_next_line(int fd)
{
	static char	*buffer_fd;
	char		temp[BUFFER_SIZE + 1];
	int			nbr;
	char		*line;

	if (!buffer_fd)
	{
		buffer_fd = malloc(sizeof(char) * 1);
		buffer_fd[0] = '\0';
		if (!buffer_fd)
			return (NULL);
	}
	nbr = 1;
	while (nbr > 0 && ft_strchr(buffer_fd, '\n') == '\0')
	{
		ft_bzero(temp, BUFFER_SIZE + 1);
		nbr = read(fd, temp, BUFFER_SIZE);
		if (nbr > 0)
			buffer_fd = ft_strjoin(buffer_fd, temp);
	}
	if (nbr < 0)
		return (NULL);
	line = ft_find_end_of_line(buffer_fd);
	buffer_fd = ft_update_fd(buffer_fd);
	return (line);
}

void	get_next_leak(void)
{
	system("leaks -q a.out");
}

/* int	main(void)
{
	int		fd;
	char	*line;
	int		i;

	atexit(get_next_leak);
	i = 8;
	fd = open("fd.txt", O_RDONLY);
	while (i >= 0)
	{
		line = get_next_line(fd);
		printf("%s", line);
		i--;
	}
} */
