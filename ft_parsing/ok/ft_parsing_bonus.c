#include "../minishell.h"

int	ft_count_len_bonus(char *str)
{
	int	i;
	int	nb_signe;

	nb_signe = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '|' || str[i] == '&')
		{
			if (i > 0 && str[i - 1] == str[i])
				nb_signe++;
		}
		i++;
	}
	return (nb_signe);
}

void	ft_print_tab_logic(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_logic)
	{
		printf("[%d]\n", data->tab_logic[i]);
		i++;
	}
	free(data->tab_logic);
}

bool	*ft_create_tab_bonus(char *str, int len)
{
	int		i;
	int		m;
	bool	*tab;

	tab = (bool *)malloc(len * sizeof(bool));
	if (!tab)
		return (0);
	m = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '|' || str[i] == '&')
		{
			if (str[i + 1] != 0 && str[i + 1] == str[i])
			{
				if (str[i] == '|')
					tab[m++] = true;
				else
					tab[m++] = false;
				i += 2;
			}
		}
		i++;
	}
	return (tab);
}

char	*ft_create_new_str_bonus(char *str, int len)
{
	int		i;
	int		m;
	char	*new_str;

	new_str = (char *)malloc((ft_strlen(str) - len + 1) * sizeof(char));
	if (!new_str)
		return (0);
	m = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '|' || str[i] == '&')
		{
			if (str[i + 1] != 0 && str[i + 1] == str[i])
			{
				new_str[m++] = ';';
				i += 2;
			}
		}
		new_str[m++] = str[i];
		i++;
	}
	new_str[m] = 0;
	return (new_str);
}

void	ft_parsing_bonus(t_data *data, char *str)
{
	int		len;
	bool	*tab;
	char	*new_str;

	len = ft_count_len_bonus(str);
	if (len > 0)
	{
		tab = ft_create_tab_bonus(str, len);
		new_str = ft_create_new_str_bonus(str, len);
		data->tab_logic = tab;
		data->nb_logic = len;
		data->tab_cmd_logic = ft_create_tab_cmd(data, new_str);
		free(str);
	}
}
