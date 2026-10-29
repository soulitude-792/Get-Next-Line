/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imigdady <imigdady@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 08:07:36 by imigdady          #+#    #+#             */
/*   Updated: 2026/10/29 11:40:19 by imigdady         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# if BUFFER_SIZE < 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(char *str, char c);
char	*extract_line(char **stash);
char	*extract_after_newline(char **stash);
char	*fill_leftover(char **stash);
char	*free_stash_and_return(char **stash, char *extracted_string);
char	*copy_line(char *stash, int i);
void	copy_strings(char *newstr, char *s1, char *s2);
void	copy_leftover_chars(char **stash, char *leftover, int i);

#endif
