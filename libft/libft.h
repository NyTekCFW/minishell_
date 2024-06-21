/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossa <nrossa@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 12:37:39 by nrossa            #+#    #+#             */
/*   Updated: 2024/01/10 21:39:54 by nrossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_flags
{
	char	conversion;
	int		minus;
	int		zero;
	int		dot;
	int		width;
	int		hash;
	int		space;
	int		plus;
}	t_flags;

char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_itoa(int n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*get_next_line(int fd);
char	*ft_gnldup(const char *s, ssize_t nb);
char	*ft_gnljoin(char *s1, char *s2, ssize_t nb);
char	*ft_utoa(unsigned int n);
char	*ft_end_of_string(char *str);
int		ft_atoi(const char *nptr);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_iswhitespace(int c);
int		ft_issign(int c);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_lstsize(t_list *lst);
int		ft_printf(const char *str, ...);
int		ft_print_char(va_list args, t_flags flags);
int		ft_print_str(va_list args, t_flags flags);
int		ft_print_dori(va_list args, t_flags flags);
int		ft_print_unsigned(va_list args, t_flags flags);
int		ft_print_hexa(va_list args, t_flags flags);
int		ft_print_aptr(va_list args, t_flags flags);
int		ft_putncount_char(char c);
int		ft_putncount_str(char *s);
int		ft_isconversion(char c);
int		ft_flags_length(const char *str);
int		ft_print_space(t_flags flags, int length);
int		ft_print_zero(t_flags flags, int length, char option);
int		ft_print_flags(t_flags flags, int length);
int		ft_print_hash(t_flags flags, unsigned int hexa);
int		ft_print_mors(t_flags flags, int nb);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	ft_check_flags(t_flags *flags);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *s);
t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
