/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedurand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:02:35 by jedurand          #+#    #+#             */
/*   Updated: 2023/10/10 13:08:20 by jedurand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

typedef struct s_format
{
	int		minus_flag;
	int		zero_flag;
	int		hash_flag;
	int		space_flag;
	int		plus_flag;
	int		width;
	int		precision;
	char	specifier;
}		t_format;

int			is_specifier(int c);
int			is_digit(int c);
int			ft_atoi(const char *nptr);
const char	*fill_list(t_format *format, const char *str, int *error,
				va_list var);
int			ft_printf(const char *str, ...);
void		list_processing(t_format *format);
int			ft_slen(char *s);

int			print_space(int i);
int			print_zero(int i);

int			print_char(t_format *format, int c);
int			print_string(t_format *format, char *str);
int			print_adress(t_format *format, void *adr);
int			print_numb(t_format *format, long n);
int			print_u_numb(t_format *format, unsigned int n);
int			print_x_numb(t_format *format, unsigned int n);

#endif
