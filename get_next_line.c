/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarnos- <jfarnos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 20:41:30 by jfarnos-          #+#    #+#             */
/*   Updated: 2023/04/07 15:35:06 by jfarnos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_update_fd(char *str, int i, int j)
{
	char	*aux;

	if (ft_strchr(str, '\n') == NULL)
	{
		if (str)
			free(str);
		return (NULL);
	}
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	i = i + 1;
	if (str[i - 1] == '\0')
	{
		return (str);
	}
	aux = malloc((ft_strlen(str) - i) + 1);
	if (!aux)
		return (NULL);
	while (str[i] != 0)
		aux[j++] = str[i++];
	aux[j] = '\0';
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

char	*ft_strdup(char *s1)
{
	char	*s2;
	int		s1len;
	int		i;

	s1len = ft_strlen(s1);
	s2 = (char *)malloc(sizeof(char) * (s1len + 1));
	if (s2 == '\0')
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*get_next_line(int fd)
{
	static char	*buffer_fd;
	char		temp[BUFFER_SIZE + 1];
	int			nbr;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if (!buffer_fd)
		buffer_fd = ft_strdup("");
	nbr = 1;
	while (nbr > 0 && ft_strchr(buffer_fd, '\n') == NULL)
	{
		ft_bzero(temp, BUFFER_SIZE + 1);
		nbr = read(fd, temp, BUFFER_SIZE);
		if (nbr > 0)
			buffer_fd = ft_strjoin(buffer_fd, temp);
	}
	if (nbr <= 0)
	{
		free(buffer_fd);
		buffer_fd = NULL;
		return (0);
	}
	line = ft_find_end_of_line(buffer_fd);
	buffer_fd = ft_update_fd(buffer_fd, 0, 0);
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
