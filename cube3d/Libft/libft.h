/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbischof <bbischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 10:32:51 by bbischof          #+#    #+#             */
/*   Updated: 2022/05/26 10:04:51 by bbischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>

# define BUFFER_SIZE 2048 // Get next line 

# define PI		3.14
# define PI_2	1.57
# define PI_3	1.047
# define PI_4	0.785
# define PI_6	0.523

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_vector2_d
{
	int	x;
	int	y;
}	t_vector2_d;

typedef struct s_vector2_f
{
	float	x;
	float	y;
}	t_vector2_f;

// Memory
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memset(void *b, int c, size_t len);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);

// Lists
t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **alst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **alst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void*));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void*(f)(void *), void (*del)(void *));

// Strings
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
char		*ft_strchr(const char *s, int c);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
int			ft_strlen(char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_strrchr(const char *s, int c);
char		*ft_strdup(const char *s1);
int			ft_tolower(int c);
int			ft_toupper(int c);
int			ft_atoi(const char *str);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void f(unsigned int, char*));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
int			ft_is_empty_str(char *str);
char		*ft_get_word(char *str);

// Get next line
int			is_newline_gnl(char *str);
char		*ft_strjoin_gnl(char *s1, char *s2);
char		*get_next_line(int fd);

// Math functions
int			ft_clamp_d(int value, int min, int max);
float		ft_clamp_f(float value, float min, float max);
double		get_angle(t_vector2_d start, t_vector2_d end);
double		get_angle_f(t_vector2_f start, t_vector2_f end);
double		radian_to_degree(double radian);
double		degree_to_radian(double degree);
void		set_vector_d(t_vector2_d *vector, int x, int y);
void		set_vector_f(t_vector2_f *vector, float x, float y);
t_vector2_f	vector_d_to_f(t_vector2_d vector_d);
t_vector2_d	vector_f_to_d(t_vector2_f vector_f);
t_vector2_d	vector_d_lerp(t_vector2_d start, t_vector2_d end, float timestamp);
t_vector2_f	vector_f_lerp(t_vector2_f start, t_vector2_f end, float timestamp);
float		vector_d_inv_lerp(t_vector2_d start, t_vector2_d end, \
				t_vector2_d curr);
float		vector_d_inv_lerp_length(t_vector2_d start, int max_length, \
				t_vector2_d curr);
t_vector2_d	rotate_vector_d(t_vector2_d vector, double radian);
t_vector2_f	rotate_vector_f(t_vector2_f vector, double radian);
t_vector2_d	create_vector_d(int x, int y);
t_vector2_f	create_vector_f(float x, float y);
t_vector2_d	create_vect_d_from_origin(t_vector2_d origin, double radian, \
				double length);
t_vector2_f	create_vect_f_from_origin(t_vector2_f origin, double radian, \
				double length);
float		get_vector_d_length(t_vector2_d start, t_vector2_d end);
double		get_vector_f_length(t_vector2_f start, t_vector2_f end);
float		get_vector_d_length_squared(t_vector2_d start, t_vector2_d end);
float		get_vector_f_length_squared(t_vector2_f start, t_vector2_f end);
int			ft_lerp_d(int min, int max, float timestamp);
float		ft_lerp_f(float min, float max, float timestamp);
float		ft_inv_lerp_d(int min, int max, int curr);
float		ft_inv_lerp_f(float min, float max, float curr);
int			ft_abs_d(int nbr);
float		ft_abs_f(float nbr);

// Color
int			get_r(int color);
int			get_g(int color);
int			get_b(int color);
int			create_rgbt(int r, int g, int b, int t);
int			color_lerp(int color1, int color2, float timestamp);
int			create_trgb(int t, int r, int g, int b);

#endif
