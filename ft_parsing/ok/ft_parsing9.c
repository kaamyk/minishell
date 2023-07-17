#include "../minishell.h"

/*************************************/
/* Put the file redirection at first */
/*************************************/

/*
[pwd > file > file2 > file3] --> [pwd > file3 > file2 > file]
*/
char	*ft_put_file_direction2(char **tab, int end, int i)
{
	int		start;
	char	*new_str;

	while (tab[i])
	{
		tab[i] = ft_delete_space(tab[i]);
		if (i == 0)
			new_str = ft_copy_str(tab[i]);
		else
		{
			new_str = ft_add_string(new_str, " ; ");
			if (i > 0 && tab[i][0] == '>' && tab[i - 1][0] != '>')
			{
				start = i;
				new_str = ft_add_string(new_str, tab[end]);
			}
			else if (tab[i + 1] == 0 && tab[i][0] == '>')
				new_str = ft_add_string(new_str, tab[start]);
			else
				new_str = ft_add_string(new_str, tab[i]);
		}
		i++;
	}
	return (new_str);
}

char	*ft_put_file_direction(char *str)
{
	int		i;
	int		end;
	char	**tab;
	char	*new_str;

	if (str[0] == '>' || str[0] == '<')
		return (str);
	tab = ft_split(str, ';');
	i = 0;
	while (tab[i])
		i++;
	end = i - 1;
	new_str = ft_put_file_direction2(tab, end, 0);
	ft_free_tab(tab);
	free(str);
	return (new_str);
}
