/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarnos- <jfarnos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 20:41:30 by jfarnos-          #+#    #+#             */
/*   Updated: 2023/04/06 01:10:18 by jfarnos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_update_fd(char *str)
{
	int		i;
	int		j;
	char	*aux;

	if (ft_strchr(str,  '\n') == '\0')
	{
		aux = malloc(sizeof (char) * 1);
		if (!aux)
			return (NULL);
		aux[0] = '\0';
		return (aux);
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
	return (aux);
}

char	*ft_find_end_of_line(char *str)
{
	int		i;
	char	*aux;

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
	static char	*mander = NULL;
	char		temp[BUFFER_SIZE + 1];
	int			nbr;
	char		*line;
	// char	*old;

	if (!mander)
	{
		mander = malloc(sizeof (char) * 1);
		mander[0] = '\0';
		if (!mander)
			return (NULL);
	}
	nbr = 1;
	while (nbr > 0 && ft_strchr(mander, '\n') == '\0')
	{
		ft_bzero(temp, BUFFER_SIZE + 1);
		nbr = read(fd, temp, BUFFER_SIZE);
		mander = ft_strjoin(mander, temp);
	}
	line = ft_find_end_of_line(mander);
	mander = ft_update_fd(mander);
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;
// 	int		i;

// 	i = 8;
// 	fd = open("fd.txt", O_RDONLY);
// 	while (i >= 0)
// 	{
// 		line = get_next_line(fd);
// 		printf("%s", line);
// 		free(line);
// 		i--;
// 	}
// }
