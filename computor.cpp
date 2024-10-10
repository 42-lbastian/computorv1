#include <iostream>
#include <string>
#include <cstring>
#include <map>
#include <math.h>

bool ft_check_map_equal(std::map<int, float>& numbers, int max)
{
	if (numbers.size() == 0)
		numbers[0] = 0.0;
	else if (numbers.size() > 1 || numbers.begin()->first > max)
		return (false);
	return (true);
}

bool ft_check_map_equation(std::map<int, float> numbers)
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
		if (it == numbers.begin())
			std::cout << it->second << " * X^" << it->first << " ";
		else
		{
			if (it->second >= 0)
				std::cout << "+ " << it->second << " * X^" << it->first << " ";
			else
				std::cout << "- " << (it->second  * - 1) << " * X^" << it->first << " ";
		}
	}
}

bool ft_parse(std::map<int, float>& map, std::string str)
{
	int i;
	int j;
	int index;
	std::string temp;

	i = 0;
	index = 0;
	while (i < (int)str.size() - 1)
	{
		if (std::isdigit(str[i]))
			temp = "";
		else
		{
			temp = str[i];
			while (str[i] && !std::isdigit(str[i]))
				i++;
		}
		j = 0;
		while(str[i + j] && (std::isdigit(str[i + j]) || str[i + j] == '.'))
			j++;
		temp.append(str, i, j);
		while (str[i + j] && !std::isdigit(str[i + j]))
			j++;
		index = atoi(&str[i + j]);
		if (map.find(index) != map.end())
			return (false);
		try
		{
			map[index] = std::stof(temp);
		}
		catch (std::invalid_argument& error)
		{
			return (false);
		}
		if (str[i + j + 1])
			j++;
		while (str[i + j] && str[i + j] == ' ')
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

void ft_create_reduced_form(std::map<int, float>& equation_map, std::map<int, float>& equal_map)
{
	equation_map.at(equal_map.begin()->first) += (equal_map.begin()->second * -1);
	equal_map.begin()->second = 0.0;
}

void ft_solve_second(std::map<int, float> equation_map)
{
	double delta;
	double solution1;
	double solution2;
	float a;
	float b;
	float c;

	a = equation_map.at(2);
	b = equation_map.at(1);
	c = equation_map.at(0);
	delta = (b * b) - 4 * a * c;
	if (a == 0)
	{
		std::cout << "Not divisible by 0" << std::endl;
		return ;
	}
	if (delta > 0)
	{
		solution1 = ((b * -1) - sqrt(delta)) / (2 * a);
		solution2 = ((b * -1) + sqrt(delta)) / (2 * a);
		std::cout << "Delta is strictly positive" << std::endl;
		std::cout << "Solution 1: " << solution1 << std::endl;
		std::cout << "Solution 2: " << solution2 << std::endl;
	}
	else if (delta < 0)
	{
		std::cout << "Delta is negativ" << std::endl;
		std::cout << "No solutions" << std::endl;
	}
	else
	{
		solution1 = (b * -1) / (2 * a);
		std::cout << "Delta is nul" << std::endl;
		std::cout << "Solution: " << solution1 << std::endl;
	}
}

void ft_solve_one(std::map<int, float> equation_map)
{
	double solution;
	float a;
	float b;

	a = equation_map.at(1);
	b = equation_map.at(0);
	solution = (b * -1) / a;
	std::cout << "Solution: " << solution << std::endl;
}

void ft_solve_zero(std::map<int, float> equation_map)
{
	if (equation_map.at(0) == 0)
		std::cout << "True" << std::endl;
	else
		std::cout << "False" << std::endl;
}

bool ft_check_empty(std::map<int, float> equation_map)
{
	std::map<int, float>::iterator it = equation_map.begin();
	it++;
	for (; it != equation_map.end(); it++)
	{
		if (it->second != 0)
			return (false);
	}
	return (true);
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
	if (ft_check_map_equation(equation_map) == false)
	{
		std::cerr << "Error exponent equation" << std::endl;
		return (1);
	}
	if (ft_check_map_equal(equal_map, equation_map.size() - 1) == false)
	{
		std::cerr << "Error equal format" << std::endl;
		return (1);
	}

	ft_create_reduced_form(equation_map, equal_map);
	std::cout << "Reduced form: ";
	ft_print_map(equation_map);
	std::cout << "= 0" << std::endl;

	std::cout << "Polynomial degree: ";
	std::cout << prev(equation_map.end())->first << std::endl;
	if (prev(equation_map.end())->first > 2)
	{
		std::cout << "The polynomial degree is strictly greater than 2, I can't solve" << std::endl;
		return (0);
	}
	else if (equation_map.size() == 1 || ft_check_empty(equation_map))
		ft_solve_zero(equation_map);
	else if (equation_map.size() == 2)
		ft_solve_one(equation_map);
	else if (equation_map.size() == 3)
		ft_solve_second(equation_map);
	else
	return (0);
}
