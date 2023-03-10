#include "philosophers.h"

int	check_plus(int a )
{
	if (a == 43 || a == 45)
		return (1);
	return (0);
}

int	ft_isdigit(int a )
{
	if (a > 47 && a < 58)
		return (1);
	else
		return (0);
}

int	ft_strlen(char *a )
{
	int	i;

	i = 0;
	while (a[i] != 0)
		++i;
	return (i);
}

int	chack_number(char *mas)
{
	int	i;

	i = 0;
	if (!ft_strlen(mas))
		return (1);
	while (mas[i] == ' ')
		++i;
	if (!check_plus(mas[i]) && !ft_isdigit(mas[i]))
		return (1);
	while (mas[++i])
	{
		if (!ft_isdigit(mas[i]))
			return (1);
	}
	if (ft_strlen(mas) == 1 && (check_plus(mas[0]) || mas[i] == ' '))
		return (1);
	return (0);
}

int	ft_strlen_zero(char *a , int i, int j, int f)
{
	int	t;

	t = 0;
	while (a[i] == ' ')
		++i;
	t = i;
	while (a[i] != 0)
	{
		if (i > t && a[i] == '0' && !f)
			++i;
		else
		{
			if (i > t)
				f = 1;
			++j;
			++i;
		}
	}
	return (j);
}