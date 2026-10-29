/* ************************************************************************** */
/*									      */
/*							  :::	   ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*						      +:+ +:+	      +:+     */
/*   By: imigdady <imigdady@learner.42.tech>	    +#+  +:+	   +#+	      */
/*						  +#+#+#+#+#+	+#+	      */
/*   Created: 2026/10/27 13:19:29 by imigdady	       #+#    #+#	      */
/*   Updated: 2026/10/29 11:43:13 by imigdady         ###   ########.fr       */
/*									      */
/* ************************************************************************** */

#include "get_next_line.h"

char	*fill_leftover(char **stash)
{
	char	*leftover_string;
	int		i;
	int		j;

	i = 0;
	while ((*stash)[i] != '\n' && (*stash)[i] != '\0')
		i++;
	if ((*stash)[i] == '\0')
		return (NULL);
	i++;
	j = 0;
	while ((*stash)[i + j] != '\0')
		j++;
	leftover_string = (char *)malloc(j + 1);
	if (!leftover_string)
		return (NULL);
	copy_leftover_chars(stash, leftover_string, i);
	free(*stash);
	return (leftover_string);
}

char	*copy_line(char *stash, int i)
{
	char	*line;
	int		k;

	line = (char *)malloc(i + 2);
	if (!line)
		return (NULL);
	k = 0;
	while (k <= i)
	{
		line[k] = stash[k];
		k++;
	}
	line[k] = '\0';
	return (line);
}

char	*extract_after_newline(char **stash)
{
	char	*extracted_string;
	char	*leftover_string;
	int		i;

	i = 0;
	while ((*stash)[i] != '\n')
		i++;
	extracted_string = copy_line(*stash, i);
	if (!extracted_string)
		return (free_stash_and_return(stash, NULL));
	if ((*stash)[i + 1] == '\0')
		return (free_stash_and_return(stash, extracted_string));
	leftover_string = fill_leftover(stash);
	if (!leftover_string)
	{
		free(extracted_string);
		return (free_stash_and_return(stash, NULL));
	}
	*stash = leftover_string;
	return (extracted_string);
}

char	*extract_line(char **stash)
{
	char	*extracted_string;

	if (!*stash || (*stash)[0] == '\0')
		return (free_stash_and_return(stash, NULL));
	if (ft_strchr(*stash, '\n') == NULL)
	{
		extracted_string = *stash;
		*stash = NULL;
		return (extracted_string);
	}
	return (extract_after_newline(stash));
}

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	static char	*stash;
	ssize_t		read_bytes;
	char		*temp_string;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (ft_strchr(stash, '\n') == NULL)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes < 0)
			return (free_stash_and_return(&stash, NULL));
		if (read_bytes == 0)
			break ;
		buffer[read_bytes] = '\0';
		temp_string = ft_strjoin(stash, buffer);
		if (!temp_string)
			return (free_stash_and_return(&stash, NULL));
		free(stash);
		stash = temp_string;
	}
	return (extract_line(&stash));
}
