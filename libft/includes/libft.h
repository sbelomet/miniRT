/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:41:38 by lgosselk          #+#    #+#             */
/*   Updated: 2024/04/26 10:29:27 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 30
# endif

typedef struct s_alloc
{
	void			*ptr;
	struct s_alloc	*next;
}				t_alloc;

char	*ft_itoa(int n);
double	ft_abs(double n);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
double	ft_atof(char *str);
int		ft_atoi(const char *nptr);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *str);
void	ft_putnbr_fd(int n, int fd);
void	ft_bzero(void *s, size_t n);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
char	*ft_strchr(const char *s, int c);
char	**ft_split(const char *s, char c);
char	*ft_strrchr(const char *s, int c);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memset(void *set, int c, size_t n);
void	*ft_malloc(int size, t_alloc	**lst);
void	*ft_memchr(const void *s, int c, size_t n);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strtrim(const char *s1, const char *set);
int		malloc_add(t_alloc **lst, t_alloc *new_node);
int		ft_equal_strs(const char *s1, const char *s2);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strmapi(const char *s, char (*f)(unsigned int, char));
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

/* Get next line */

char	*get_next_line(int fd);
char	*ft_get_line(char *remind);
char	*ft_substr_remind(char *s);
char	*ft_read(int fd, char *remind);
char	*ft_to_remind(char	*remind, char *buff);

/* Garbage collextor versions */
void	ft_malloc_clear(t_alloc **lst);
char	*ft_strdup_allocated(const char *s1, t_alloc **alloc);
char	**ft_split_alloc(const char *s, char c, t_alloc **alloc);
char	*ft_strjoin_alloc(char const *s1, char const *s2, t_alloc **alloc);

#endif
