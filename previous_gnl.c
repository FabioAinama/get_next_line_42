int					get_next_line(const int fd, char **line)
{
	static t_fd_gnl	*first_fd;
	t_fd_gnl		*current_fd;
	t_fd_gnl		*new_fd;
	char			*one_line;
	int				i;

	printf("---New call GNL---\n");
	if (!first_fd)
		if (!(first_fd = create_new_struct_gnl(fd)))
			return (-1);
	if (first_fd->str == NULL)
		if (!(first_fd->str = ft_text_pointer(fd, 0)))
			return (-1);
	current_fd = first_fd;
	while (current_fd->fd != fd)
	{
		if (current_fd->next != NULL)
			current_fd = current_fd->next;
		else
		{
			if (!(new_fd = create_new_struct_gnl(fd)))
				return (-1);
			if (!(new_fd->str = ft_text_pointer(fd, 0)))
				return (-1);
			current_fd->next = new_fd;
		}
	}
	i = 0;
	while (current_fd->str[i] != '\n' && current_fd->str[i] != '\0')
		i++;
	if (!(one_line = ft_strnew(i)))
		return (-1)
	one_line = ft_strsub(current_fd->str, 0, (i));
	if (current_fd->str[0] == 0)
		return (0);
	current_fd->str = current_fd->str + (i + 1);
	*line = one_line;
	return (1);
}