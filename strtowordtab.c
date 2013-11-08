#include <stdlib.h>
#include <string.h>

char		*strdup(const char *s);

int		count_words(char *str, char decoup)
{
  int		nb_word;
  int		i;

  i = 0;
  nb_word = 1;
  while (str[i])
    {
      if (str[i] == decoup)
	nb_word++;
      i++;
    }
  return (nb_word);
}

int		wordlen(char *str, char decoup)
{
  int		i;

  i = 0;
  while (str[i] != '\0' && str[i] != decoup)
    i++;
  return (i);
}

char		*complete_line(char *str, int nb, char decoup)
{
  char		*new;
  int		len;
  int		i;
  int		j;

  i = 0;
  j = 0;
  new = NULL;
  while (j++ < nb)
    {
      while (str[i] != '\0' && str[i] != decoup)
	i++;
      i++;
    }
  if ((new = malloc(((len = wordlen(&str[i], decoup)) + 1)
		    * sizeof(char))) == NULL)
    return (NULL);
  j = 0;
  while (str[i] != decoup && str[i] != '\0')
    new[j++] = str[i++];
  new[j] = '\0';
  return (new);
}

char		**small_tab(char *str)
{
  char		**tab;

  if ((tab = malloc(2 * sizeof(char *))) == NULL)
    return (NULL);
  tab[0] = strdup(str);
  tab[1] = NULL;
  return (tab);
}

char		**strtowordtab(char *str, char decoup)
{
  char		**tab;
  int		nb_word;
  int		i;

  i = 0;
  tab = NULL;
  if (str == NULL)
    return (NULL);
  if ((nb_word = count_words(str, decoup)) == 1)
    return (small_tab(str));
  if ((tab = malloc((nb_word + 1) * sizeof(char *))) == NULL)
    return (0);
  tab[nb_word] = NULL;
  while (nb_word--)
    {
      tab[i] = complete_line(str, i, decoup);
      i++;
    }
  return (tab);
}
