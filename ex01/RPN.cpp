/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouyahy <mbouyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 12:58:09 by mbouyahy          #+#    #+#             */
/*   Updated: 2024/02/15 19:37:55 by mbouyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int IsOperator(char c)
{
    for (int i = 0; Operators[i]; i++)
    {
        if (Operators[i] == c)
            return (1);
    }
    return (0);
}

int IsNotNumber(std::string str)
{
	for (int i = 0; Operators[i]; i++)
    {
        if (str == "+" || str == "-" || str == "*" || str == "/")
            return (1);
    }
	return (0);
}

bool	isInvalidSyntax(t_data *data)
{
	std::stack<std::string> TempStack;
	int 					digit;
	int 					op;

	digit 		= 0;
	op 			= 0;
	TempStack 	= data->TempStack;
	while (TempStack.size())
	{
		if (!IsNotNumber(TempStack.top()))
			digit++;
		else
			op++;
		TempStack.pop();
    }
	if (digit - 1 != op)
		throw std::out_of_range("invalid Syntax");
	return (false);
}

int CheckErrors(std::string str)
{
    for(int i = 0; str[i]; i++)
    {
        if (!std::isdigit(str[i]) && !IsOperator(str[i]))
            return(1);
    }
    return (0);
}

void    ReversePush(t_data *data)
{
    while (data->TempStack.size() > 0)
    {
        data->Stack.push(data->TempStack.top());
        data->TempStack.pop();
    }
}

void FillStack(t_data *data)
{
    std::string		n;
	long long		nbr;

    std::stringstream s(data->param);
    if (CheckErrors(data->param))
        throw std::out_of_range("Error");
    while (getline(s, n, ' '))
    {
        if (n != "" && n != " " && n != "	")
        {
			nbr = strtod(n.c_str(), NULL);
			if (nbr >= 10)
				throw std::out_of_range("The Number Must Be less than 10");
            data->TempStack.push(n);
        }
    }
	isInvalidSyntax(data);
}

int IsCorrectNumber(t_data *data)
{
    if (data->FisrtNbr >= 10 || data->SecondNbr >= 10)
        return (1);
    return (0);
}

long long  SpecialDetectOperator(t_data *data, std::string op)
{
    if (op == "*")
        return (data->FisrtNbr * data->SecondNbr);
    else if (op == "+")
        return (data->FisrtNbr + data->SecondNbr);
    else if (op == "-")
        return (data->FisrtNbr - data->SecondNbr);
    else if (op == "/")
    {
        if (data->SecondNbr == 0)
            throw std::out_of_range("Error : we can't devide by 0");
        return (data->FisrtNbr / data->SecondNbr);
    }
    else
        throw std::out_of_range("invalid Operator!");
    return(0);
}

void	FindOperator(t_data *data)
{
	std::string FisrtNbr;
    std::string SecondNbr;
    std::string result;
	bool		status;


	status 		= false;
	FisrtNbr 	= "";
	SecondNbr 	= "";
	std::stack<std::string> TempStack;
	while(data->Stack.size() >= 2)
	{
		if (!status)
		{
			FisrtNbr = data->Stack.top();
			data->Stack.pop();
			SecondNbr = data->Stack.top();
			data->Stack.pop();
			status = true;
		}
		if (IsNotNumber(SecondNbr) || IsNotNumber(FisrtNbr))
			throw std::out_of_range("Error");
		if (!data->Stack.empty() && IsOperator(data->Stack.top()[0]))
		{
			data->SecondNbr = strtod(SecondNbr.c_str(), NULL);
			data->FisrtNbr = strtod(FisrtNbr.c_str(), NULL);
			data->result = SpecialDetectOperator(data,  data->Stack.top());
			data->Stack.pop();
            std::stringstream s;
			s << data->result;
			s >> result;
			data->Stack.push(result);
			while(TempStack.size())
			{
				data->Stack.push(TempStack.top());
				TempStack.pop();
			}
			status = false;
		}
		else if (std::isdigit(data->Stack.top()[0]))
		{
			TempStack.push(FisrtNbr);
			std::swap(FisrtNbr, SecondNbr);
			SecondNbr = data->Stack.top();
			data->Stack.pop();
		}
		else
			throw std::out_of_range("Error");
	}
}

void    PolishNotation(t_data *data)
{
    data->FisrtNbr 	= 0;
    data->SecondNbr = 0;

	FindOperator(data);
    std::cout << data->result << std::endl;
}

void    program(int ac, char **av)
{
    if (ac == 2)
    {
        try
        {
            t_data 		data;

            data.param 	= av[1];

            FillStack(&data);
            ReversePush(&data);
            PolishNotation(&data);
        }
        catch (std::exception &e)
        {
            std::cout << e.what() << std::endl;
        }
    }
    else
        std::cout << "Param Error!" << std::endl;
}
