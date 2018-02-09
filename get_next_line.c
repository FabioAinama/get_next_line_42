/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fginja-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 11:16:20 by fginja-d          #+#    #+#             */
/*   Updated: 2018/01/30 11:16:22 by fginja-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/libft.h"

static	t_fd_gnl	*create_new_struct_gnl(int fd)
{
	t_fd_gnl	*new_fd;

	new_fd = (t_fd_gnl *)malloc(sizeof(t_fd_gnl));
	if (!new_fd)
		return (NULL);
	new_fd->fd = fd;
	new_fd->str = NULL;
	new_fd->next = NULL;
	return (new_fd);
}

static char			*ft_text_pointer(const int fd, int i)
{
	char	*buf;
	char	*buf2;
	char	*buf3;

	if (!(buf = ft_strnew(BUFF_SIZE)))
		return (NULL);
	buf2 = ft_strnew(0);
	while ((read(fd, buf, BUFF_SIZE)) > 0)
	{
		i = 0;
		while (buf[i])
			if (buf[i] != '\0' && buf[i] != EOF)
				i++;
		if (!(buf3 = ft_strnew(i)))
			return (NULL);
		ft_strcpy(buf3, buf2);
		free(buf2);
		if (!(buf2 = ft_strnew(i)))
			return (NULL);
		buf2 = ft_strjoin(buf3, buf);
		ft_strclr(buf);
		free(buf3);
	}
	free(buf);
	return (buf2);
}

static	t_fd_gnl	*check_existant_fd(t_fd_gnl *current_fd, int fd)
{
	t_fd_gnl		*new_fd;

	while (current_fd->fd != fd)
	{
		if (current_fd->next != NULL)
			current_fd = current_fd->next;
		else
		{
			if (!(new_fd = create_new_struct_gnl(fd)))
				return (0);
			if (!(new_fd->str = ft_text_pointer(fd, 0)))
				return (0);
			current_fd->next = new_fd;
		}
	}
	return (current_fd);
}

int					get_next_line(const int fd, char **line)
{
	static t_fd_gnl	*first_fd;
	t_fd_gnl		*current_fd;
	char			*one_line;
	int				i;

	if (!first_fd)
		if (!(first_fd = create_new_struct_gnl(fd)))
			return (-1);
	if (first_fd->str == NULL)
		if (!(first_fd->str = ft_text_pointer(fd, 0)))
			return (-1);
	current_fd = first_fd;
	i = 0;
	if (!(current_fd = check_existant_fd(current_fd, fd)))
		return (-1);
	while (current_fd->str[i] != '\n' && current_fd->str[i] != '\0')
		i++;
	if (!(one_line = ft_strnew(i)))
		return (-1);
	one_line = ft_strsub(current_fd->str, 0, (i));
	if (current_fd->str[0] == 0)
		return (0);
	current_fd->str = current_fd->str + (i + 1);
	*line = one_line;
	return (1);
}

int					main(int ac, char **av)
{
	int		fd;
	int		fd2;
	int		fd3;
	char	*line;
	int		i = 0;

	line = ft_strnew(50);
	// printf("Adresse line: %d\n", line);
	fd = open(av[1], O_RDONLY);
	fd2 = open(av[2], O_RDONLY);
	fd3 = open(av[3], O_RDONLY);
	if (fd == -1)
		return (0);
	else
	{
		// while (get_next_line(fd, &line) > 0)
		// 	printf("Res: %s\n", line);
		while (i < 4)
		{
			// printf("Line Finale: %d\n", line);
			// printf("Line Finale: %c\n", *line);
			// printf("Line Finale: %s\n", line);
			// ft_putstr("Yolo\n");
			if (get_next_line(fd, &line))
			{
				ft_putstr("Res: ");
				ft_putstr(line);
				ft_putstr("\n\n");
			}
			if (get_next_line(fd2, &line))
			{
				ft_putstr("Res: ");
				ft_putstr(line);
				ft_putstr("\n\n");
			}
			if (get_next_line(fd3, &line))
			{
				ft_putstr("Res: ");
				ft_putstr(line);
				ft_putstr("\n\n");
			}
			i++;
		}
	}
	return (1);
}
