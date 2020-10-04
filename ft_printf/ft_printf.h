/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <fflores@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 10:25:14 by fflores           #+#    #+#             */
/*   Updated: 2020/08/03 10:29:13 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct	s_flags
{
	int			zero_flag;
	int			negative;
	int			width;
	int			dot;
	int			precision;
	int			star;
}				t_flags;

typedef struct	s_parameters
{
	va_list		ap;
	const char	*format_copy;
	size_t		count;
	char		line;
	int			head_zero;
	int			back_zero;
	size_t		length;
}				t_parameters;

int				ft_printf(const char *format, ...);
int				ft_check_string(t_parameters prmtrs);
int				ft_check_parameters(t_parameters *prmtrs);
int				ft_set_flag(t_flags *flag, char symbol, t_parameters *prmtrs);
int				ft_atoi_length(int n);
int				ft_atoi(const char *str, t_parameters *param);
int				ft_type(int type);
int				ft_flag_and_digit(int c);
int				ft_isdigit(int c);
void			ft_putchar(char c);
void			ft_start(t_flags *flag, t_parameters *prmtrs);
void			ft_null_str(char *str, t_parameters *prmtrs);
void			ft_combine_flags(t_flags *flag);
char			*ft_get_type(t_flags flag, t_parameters *prmtrs);
char			*ft_ch(t_flags flag, t_parameters *prmtrs);
char			*ft_char(int c);
char			*ft_apply_width(size_t counter, char *string, char ch);
char			*ft_align_left_side(char *ptr);
char			*ft_str(t_flags flag, t_parameters *prmtrs);
char			*ft_get_precision(int counter, char *string);
char			*ft_strdup(const char *s1);
char			*ft_percent(t_flags flag);
char			*ft_apply_rightwidth(size_t counter, char *string, char ch);
char			*ft_int_decimal(t_flags flag, t_parameters *prmtrs);
char			*ft_itoa(long n);
char			*ft_precision_integer(int znak, t_flags flag, char *ptr);
char			*ft_without_precision(int znak, t_flags flag, char *ptr);
char			*ft_pointer(t_flags flag, t_parameters *prmtrs);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_hex_trunc(t_flags flag, t_parameters *prmtrs);
char			*ft_hex_itoa(unsigned long long number);
char			*ft_hex_full(char *string);
char			*ft_unsigned(t_flags flag, t_parameters *prmtrs);
size_t			ft_strlen(const char *str);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
#endif
