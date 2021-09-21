/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emtran <emtran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 13:53:24 by emtran            #+#    #+#             */
/*   Updated: 2021/09/03 21:28:08 by emtran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
/*
void 	ft_putstr(char *str)
{
	int a = -1;

	while(str[++a])
		write(1, &str[a], 1);
}
*/

static char	*ft_pushinyourline(char *save)
{
	char	*str;
	int		i;

	i = 0;
	if (!save)
		return (0);
	while (save[i])
	{
		if (save[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	str = ft_strcalloc(i);
	if (!str)
		return (NULL);
	i = 0;
	while (save[i])
	{
		if (i > 0 && save[i - 1] == '\n')
			break ;
		str[i] = save[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	*ft_secu_av_tout(char *save)
{
	if (save)
	{
		free(save);
		save = 0;
	}
	return (NULL);
}

static int	ft_n_ta_race(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_savebryan(char *save)
{
	char	*str;
	int		i;
	int		j;
	int		len;

//	printf("Save : %s\n", save);
	i = 0;
	j = 0;
	len = ft_strlen(save);
	while (save[i] != '\0' && save[i] != '\n')
		i++;
	str = ft_strcalloc(len - i + 1);
	if (!str)
		return (NULL);
	i++;
	while (i < len)
		str[j++] = save[i++];
	str[j] = '\0';
	free(save);
	save = NULL;
	return (str);
}

char	*get_next_line(int fd)
{
	char			*line = NULL;
	char			buff[BUFFER_SIZE + 1];
	static char		*save;
	int				ret;

	if (BUFFER_SIZE < 1 || fd < 0 || fd > 1024
		|| read(fd, NULL, 0) != 0)
		return (ft_secu_av_tout(save));
	ret = 1;
	while (ft_n_ta_race(save) == 0 && ret != 0)
	{
		ret = read(fd, buff, BUFFER_SIZE);
		if (ret == -1)
			return (ft_secu_av_tout(save));
		buff[ret] = '\0';
		save = ft_strjoin(save, buff);
	}
	line = ft_pushinyourline(save);
	save = ft_savebryan(save);
//	printf("ret : %d\n", ret);
//	printf("Line : %s", line);
	if (ret <= 0)
	{
		free(save);
		save = 0;
		if (*line)
			return (line);
		free(line);
		line = 0;
	}
	return (line);
}
/*
int	main(int argc, char **argv)
{
	char *line;
	int fd;

	line = (char*)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (argc != 2)
		exit (0);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		printf("An error ocurred while opening the fd");
		return (-1);
	}
	while (line != NULL)
	{
		line = get_next_line(fd);
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}*/
