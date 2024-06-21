/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossa <nrossa@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 18:18:26 by nrossa            #+#    #+#             */
/*   Updated: 2023/11/01 19:15:50 by nrossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_setbuf(size_t n)
{
	char	*result;

	result = malloc(sizeof(char) * (n + 1));
	if (!result)
		return (NULL);
	return (result);
}

static char	*ft_clean_stash(char *stash)
{
	char	*temp;
	char	*search;

	if (!stash)
		return (NULL);
	search = ft_strchr(stash, '\n') + 1;
	temp = ft_gnldup(search, ft_strlen(search));
	free(stash);
	if (*temp)
		return (temp);
	else
	{
		free(temp);
		return (NULL);
	}
}

static char	*ft_get_line(char *stash)
{
	char	*search;
	char	*result;
	size_t	size;

	if (!stash)
		return (NULL);
	search = ft_strchr(stash, '\n');
	if (!search)
		return (NULL);
	else
	{
		size = search - stash + 2;
		result = malloc(sizeof(char) * (size));
		if (!result)
			return (NULL);
		ft_strlcpy(result, stash, size);
		return (result);
	}
}

static char	*ft_get_stash(char **stash)
{
	char	*result;

	if (!*stash[0])
	{
		free(*stash);
		stash = NULL;
		return (NULL);
	}
	result = ft_get_line(*stash);
	if (result)
	{
		*stash = ft_clean_stash(*stash);
		return (result);
	}
	else
	{
		result = ft_gnldup(*stash, ft_strlen(*stash));
		free(*stash);
		*stash = NULL;
		return (result);
	}
}

char	*get_next_line(int fd)
{
	char		*buf;
	char		*result;
	static char	*stash[1024];
	ssize_t		count;

	if (fd < 0 || 1024 < fd)
		return (NULL);
	buf = ft_setbuf(BUFFER_SIZE);
	count = read(fd, buf, BUFFER_SIZE);
	while (0 < count)
	{
		stash[fd] = ft_gnljoin(stash[fd], buf, count);
		result = ft_get_line(stash[fd]);
		if (result)
		{
			stash[fd] = ft_clean_stash(stash[fd]);
			free(buf);
			return (result);
		}
		count = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	if (!count && stash[fd])
		return (result = ft_get_stash(&stash[fd]));
	return (NULL);
}
