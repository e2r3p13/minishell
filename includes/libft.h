/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 11:57:03 by lfalkau           #+#    #+#             */
/*   Updated: 2020/03/29 12:07:33 by lfalkau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

typedef struct	s_ls
{
	void		*content;
	struct s_ls	*next;
}				t_ls;

typedef struct	s_lf
{
	int			fd;
	char		*mem;
	struct s_lf	*next;
}				t_lf;

typedef enum	e_bool
{
	false = 0,
	failure = 0,
	true = 1,
	success = 1,
}				t_bool;

size_t			ft_strlen(const char *s);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
t_bool			ft_toupper(int c);
t_bool			ft_tolower(int c);
t_bool			ft_isalpha(int c);
t_bool			ft_isdigit(int c);
t_bool			ft_isalnum(int c);
t_bool			ft_isascii(int c);
t_bool			ft_isprint(int c);
t_bool			ft_isinset(char const *set, char c);
t_bool			ft_isrgb(char **array);
t_bool			ft_isstrdigit(char *str);
int				ft_atoi(const char *str);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
int				ft_lstsize(t_ls *lst);
int				ft_bit_ctoi(char *oct);
int				ft_pow(int nb, int pow);
int				ft_color_from_rgb(char **colors);
char			*ft_itoa(int n);
char			*ft_realloc(char *line);
char			*ft_strdup(const char *s1);
char			*ft_strndup(const char *s1, size_t n);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strncpy(char *dst, const char *src, size_t len);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strncat(char *s1, const char *s2, size_t n);
char			*ft_strstr(const char *haystack, const char *needle);
char			*ft_strnstr(const char *h, const char *n, size_t len);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strcjoin(char const *s1, char const *s2, char c);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_bit_cctwo(char *oct);
char			*ft_bit_itoc(char nb);
char			*ft_remove_spaces(char *str);
char			**ft_split(char const *s, char c);
void			ft_bzero(void *s, size_t n);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putchar(char c);
void			ft_putstr(char *s);
void			ft_putendl(char *s);
void			ft_putnbr(int n);
void			ft_lstdelone(t_ls *lst, void (*del)(void *));
void			ft_lstadd_front(t_ls **alst, t_ls *new);
void			ft_lstadd_back(t_ls **alst, t_ls *new);
void			ft_lstclear(t_ls **lst, void (*del)(void *));
void			ft_lstiter(t_ls *lst, void (*f)(void *));
void			ft_free_array(char **array);
void			*ft_calloc(size_t count, size_t size);
void			*ft_memalloc(size_t size);
void			*ft_memset(void *b, int c, size_t len);
void			*ft_memcpy(void *dst, const void *src, size_t len);
void			*ft_memccpy(void *dst, const void *src, int c, size_t len);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memchr(const void *s, int c, size_t n);
t_ls			*ft_lstlast(t_ls *lst);
t_ls			*ft_lstnew(void *content);
t_ls			*ft_lstmap(t_ls *lst, void *(*f)(void *), void (*dl)(void *));
int				get_next_line(int fd, char **line);

#endif
