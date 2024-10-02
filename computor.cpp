#include <iostream>
#include <string>
#include <cstring>
#include <map>

bool ft_check_map(std::map<int, float> numbers)
{
	if (numbers.begin()->first != 0)
		return (false);
	std::map<int, float>::iterator it = numbers.begin();
	std::map<int, float>::iterator it2 = it;
	it2++;
	for (; it2 != numbers.end(); it2++, it++)
	{
		if (it->first + 1 != it2->first)
			return (false);
	}
	return (true);
}

void ft_print_map(std::map<int, float> numbers)
{
	for (std::map<int, float>::iterator it = numbers.begin(); it != numbers.end(); it++)
	{
		std::cout << "Key: " << it->first << std::endl;
		std::cout << "Value: " << it->second << std::endl << std::endl;
	}
}

bool ft_parse(std::map<int, float>& map, std::string str)
{
	int i;
	int j;
	int index;

	i = 0;
	index = 0;
	while (i < str.size() - 1)
	{
		j = 0;
		while(str[i + j] && (std::isdigit(str[i + j]) || str[i + j] == '.'))
			j++;
		std::string temp;
		temp.append(str, i, j);
		while (str[i + j] && !std::isdigit(str[i + j]))
			j++;
		index = atoi(&str[i + j]);
		if (map.find(index) != map.end())
			return (false);
		map[index] = std::stof(temp);
		if (str[i + j + 1])
			j++;
		while (str[i + j] && !std::isdigit(str[i + j]))
			j++;
		i += j;
	}
	return (true);
}

bool ft_create_equation_strings(char *input, std::string& equation, std::string& equal)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (input[j] && input[j] == ' ')
		j++;
	while (input[i])
	{
		if (input[i] == '=')
		{
			equation.append(input, j, i - 1);
			i++;
			while (input[i] && input[i] == ' ')
				i++;
			if (input[i] == '\0')
				return (false);
			equal.append(input, i, strlen(input));
			return (true);
		}
		i++;
	}
	return (false);
}

int main(int argc, char **argv)
{
	std::map<int, float> equation_map;
	std::map<int, float> equal_map;
	std::string equation_str;
	std::string equal_str;

	if (argc != 2)
	{
		std::cerr << "Wrong number of arguments" << std::endl;
		return (1);
	}
	if (ft_create_equation_strings(argv[1], equation_str, equal_str) == false)
	{
		std::cerr << "Error equal" << std::endl;
		return (1);	
	}
	if (ft_parse(equation_map, equation_str) == false || ft_parse(equal_map, equal_str) == false)
	{
		std::cerr << "Error parsing" << std::endl;
		return (1);
	}
	if (ft_check_map(equation_map) == false)
	{
		std::cerr << "Error exponent" << std::endl;
		return (1);
	}
	
	ft_print_map(equation_map);
	std::cout << "------------" << std::endl;
	ft_print_map(equal_map);
	return (0);
}
