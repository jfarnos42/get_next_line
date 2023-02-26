/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarnos- <jfarnos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 20:41:30 by jfarnos-          #+#    #+#             */
/*   Updated: 2023/02/24 00:51:04 by jfarnos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_update_fd(char *str)
{
	int		i;
	int		j;
	char	*aux;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	i = i + 1;
	if (str[i - 1] == '\0'){
		//free(str);
		return (str);
	}
	j = 0;
	aux = malloc((ft_strlen(str) - i) + 1);
	if (!aux)
		return (NULL);
	while (str[i] != 0)
		aux[j++] = str[i++];
	aux[j] = str[i];
	if (str)
		free(str);
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

	if (!mander)
	{
		mander = malloc(BUFFER_SIZE + 1);
		if (!mander)
			return (NULL);
	}
	ft_bzero(temp, BUFFER_SIZE + 1);
	nbr = 1;
	while (nbr > 0 && ft_strchr(mander, '\n') == '\0')
	{
		nbr = read(fd, temp, BUFFER_SIZE);
		mander = ft_strjoin(mander, temp);
	}
	if (((nbr == 0 && mander[0] == 0)) || nbr == -1)
		return (NULL);
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
// 		line = get_next_line(-1);
// 		printf("\n\n%s\n\n\n", line);
// 		free(line);
// 		i--;
// 	}
// 	system("leaks a.out");
// }
