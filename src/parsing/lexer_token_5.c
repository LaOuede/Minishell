#include "../../include/minishell.h"

char	*ft_get_expand_brackets_quotes(int *i, char *str, t_pars *pars)
{
	printf(KYEL "-------------------- FT_GET_EXPAND_BRACKETS_QUOTES" KGRN KBLD" START " RESET KYEL "--------------------\n" RESET);
	char	*tmp;

	tmp = NULL;
	(*i)++;
	while (ft_isenvvarchar(str[++(*i)]))
		tmp = ft_stock_char(tmp, str[(*i)]);
	if (!tmp)
	{
		(*i)++;
		return (tmp);
	}
	else
	{
		tmp = ft_stock_char(tmp, '=');
		tmp = ft_find_envvar(tmp, pars);
		printf("tmp = %s\n", tmp);
	}
	if (str[(*i)] != '}')
	{
		ft_error_parsing(ERR_TOKEN, LEXER, pars);
		tmp = NULL ;
	}
	else
		(*i)++;
	printf("char get expand = %c\n", str[(*i)]);
	printf(KYEL "-------------------- FT_GET_EXPAND_BRACKETS_QUOTES" KRED KBLD" END " RESET KYEL "--------------------\n" RESET);
	return (tmp);
}

void	ft_get_expand_brackets(int *i, t_pars *pars)
{
	printf(KYEL "-------------------- FT_GET_EXPAND_BRACKETS" KGRN KBLD" START " RESET KYEL "--------------------\n" RESET);
	char	*tmp;

	tmp = NULL;
	(*i)++;
	printf("char get expand = %c\n", pars->input[(*i)]);
	while (ft_isenvvarchar(pars->input[++(*i)]))
		tmp = ft_stock_char(tmp, pars->input[(*i)]);
	if (!tmp)
	{
		tmp = ft_stock_char(tmp, '$');
		(*i)++;
	}
	else
	{
		tmp = ft_stock_char(tmp, '=');
		tmp = ft_find_envvar(tmp, pars);
		if (tmp)
			ft_add_token_bottom(&pars->line, ft_create_node(tmp, pars));
	}
	ft_freenull(tmp);
	if (pars->input[(*i)] != '}')
	{
		ft_error_parsing(ERR_TOKEN, LEXER, pars);
		tmp = NULL ;
	}
	else
		(*i)++;
	ft_reset_node(pars);
	printf(KYEL "-------------------- FT_GET_EXPAND_BRACKETS" KRED KBLD" END " RESET KYEL "--------------------\n" RESET);
}

bool	ft_check_expand_brackets(char *str, t_pars *pars)
{
	printf(KYEL "-------------------- FT_CHECK_EXPAND_BRACKETS" KGRN KBLD" START " RESET KYEL "--------------------\n" RESET);
	pars->c_brackets = OPEN;
	while (*str++)
	{
		if (*str == '}')
		{
			pars->c_brackets = CLOSE;
			break ;
		}
	}
	if (pars->c_brackets != 2)
		ft_error_parsing(ERR_QUOTE, LEXER, pars);
	printf("pars->c_brackets = %d\n", pars->c_brackets);
	printf(KYEL "-------------------- FT_CHECK_EXPAND_BRACKETS" KRED KBLD" END " RESET KYEL "--------------------\n" RESET);
	if (pars->c_brackets == CLOSE)
		return (true);
	return (false);
}
