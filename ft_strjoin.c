char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		slen;
	char	*res;

	i = 0;
	j = 0;
	slen = ft_strlen(s1) + ft_strlen(s2);
	if (!s1 || !s2)
		return (NULL);
	res = malloc((slen + 1) * sizeof(char));
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	res[i] = 0;
    free(s1);
    free(s2);
	return (res);
}