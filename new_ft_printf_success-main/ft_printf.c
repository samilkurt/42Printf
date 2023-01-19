/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhkurt <muhkurt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 01:29:50 by hece              #+#    #+#             */
/*   Updated: 2023/01/19 16:20:13 by muhkurt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *str)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	if (!str)
		return (ft_putstr("(null)"));
	while (str[i] != '\0')
		len += ft_putchar(str[i++]);
	return (len);
}

int	ft_itoa_base(unsigned long long nbr, int base, char *str, int mod)//nbr neden unsigned long long?
{
	int	nbr_list[100];// yer açma durumu
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (mod == 1 && (int)nbr < 0)//neden typcast
	{
		nbr *= -1;
		len += ft_putchar('-');
	}
	if (mod == 2)
		len += ft_putstr("0x");
	if (nbr == 0)
		len += ft_putchar('0');
	while (nbr)
	{
		nbr_list[i++] = nbr % base;
		nbr = nbr / base;
	}
	while (i--)
		len += ft_putchar(str[nbr_list[i]]);
	return (len);
}

int	ft_check_format(va_list args, char format)
{
	int	len;

	len = 0;
	if (format == 'c')
		len += ft_putchar(va_arg(args, int));//va_arg argümnalara ulaşmayı sağlıyor her çağrıldığında bir sonraki argümanı çağrıyor burdaki int de typcast int gelmesi gerekiyor.
	else if (format == 's')
		len += ft_putstr(va_arg(args, char *));
	else if (format == 'u')
		len += ft_itoa_base(va_arg(args, unsigned int), 10, "0123456789", 0);
	else if (format == 'd' || format == 'i' || format == 'u')
		len += ft_itoa_base(va_arg(args, int), 10, "0123456789", 1);
	else if (format == 'p')
		len += ft_itoa_base(va_arg(args, unsigned long long), 16,
				"0123456789abcdef", 2);
	else if (format == 'x')
		len += ft_itoa_base(va_arg(args, unsigned int), 16,
				"0123456789abcdef", 0);
	else if (format == 'X')
		len += ft_itoa_base(va_arg(args, unsigned int), 16,
				"0123456789ABCDEF", 0);
	else if (format == '%')
		len += ft_putchar('%');
	return (len);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		len;
	va_list	args;//args sınırsız argümanları tutuyor.

	i = 0;
	len = 0;
	va_start(args, str);//fonksiyondaki src değişkeninden sonraki karakterleri başlangıç olarak al.
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			i++;
			len += ft_check_format(args, str[i]);
		}
		else
			len += ft_putchar(str[i]);
		i++;
	}
	va_end(args);
	return (len);
}

int main(){
	ft_printf("%d", 55);
}
