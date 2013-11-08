#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "strtowordtab.h"
#include "itoa.h"

char		*strdup(const char *s);

static char	*add_zero(char *str)
{
  char		*ret;
  int		i;
  int		nb;

  ret = malloc(4096 * sizeof(*ret));
  nb = 8 - strlen(str);
  for (i = 0; i != nb; i++)
    ret[i] = '0';
  ret[i] = '\0';
  ret = strcat(ret, str);
  return (ret);
}

static char	*ipcat(char *ip)
{
  char		**tab;
  char		*tmp;
  char		*ret;
  int		i;

  tab = strtowordtab(ip, '.');
  tmp = malloc(4096 * sizeof(*tmp));
  ret = malloc(4096 * sizeof(*ret));
  for (i = 0; tab[i]; i++)
    {
      if (i != 0)
	sprintf(ret, "%s%c", ret, '.');
      itoa(atoi(tab[i]), tmp, 2);
      sprintf(ret, "%s%s", ret, add_zero(tmp));
    }
  return (ret);
}

static char	*getip(char *ip)
{
  ip[strlen(ip) - 3] = '\0';
  return (ip);
}

static char	*removeslash(char *str)
{
  char		*ret;
  int		i;
  int		n;

  ret = strdup(str);
  n = 0;
  for (i = 1; str[i]; i++)
    {
      ret[n] = str[i];
      n++;
    }
  ret[n] = '\0';
  return (ret);
}

static int	getstrongermask(char *ip1, char *ip2)
{
  int		mask1;
  int		mask2;

  ip1 = removeslash(strstr(ip1, "/"));
  ip2 = removeslash(strstr(ip2, "/"));
  mask1 = atoi(ip1);
  mask2 = atoi(ip2);
  if (mask1 >= mask2)
    return (mask1);
  return (mask2);
}

static void	printip(char *ip, int n)
{
  int		i;
  int		count;

  count = 0;
  printf("\033[31m");
  for (i = 0; ip[i]; i++)
    {
      if (count == n)
        printf("\033[0m");
      if (ip[i] != '.')
        count++;
      putchar(ip[i]);
      if (count > n)
	printf("\033[0m");
    }
  putchar('\n');
}

static char	*removepoint(char *str)
{
  char		*ret;
  int		i;
  int		n;

  n = 0;
  ret = strdup(str);
  for (i =0; str[i]; i++)
    {
      if (str[i] != '.')
	{
	  ret[n] = str[i];
	  n++;
	}
    }
  ret[n] = '\0';
  return (ret);
}

static void	ipcomp(char *ip1, char *ip2)
{
  int		n;

  n = getstrongermask(ip1, ip2);
  printf("Stronger Mask : %d\n", n);
  ip1 = ipcat(getip(strdup(ip1)));
  ip2 = ipcat(getip(strdup(ip2)));
  printip(ip1, n);
  printip(ip2, n);
  if (strncmp(removepoint(ip1), removepoint(ip2), n) == 0)
    printf("Yes.\n");
  else
    printf("No.\n");
}

int		main(int ac, char **av)
{
  if (ac == 2)
    printf("%s\n", ipcat(av[1]));
  if (ac == 3)
    ipcomp(av[1], av[2]);
  return (EXIT_SUCCESS);
}
