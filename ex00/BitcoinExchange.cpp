/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouyahy <mbouyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 20:44:28 by mbouyahy          #+#    #+#             */
/*   Updated: 2024/02/16 13:48:25 by mbouyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int IsLeap(t_data *data)
{
    if ((data->year % 4 == 0 && data->year % 100 != 0) || (data->year % 400 == 0))
        return (1);
    return (0);
}

int IsCorrectDays(t_data *data)
{
    int daysInMonthLeap[13] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};//Leap Year Array
    int daysInMonthNonLeap[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};//Non-Leap Year Array
    if (IsLeap(data))
    {
        if (data->day <= 0 || data->day > daysInMonthLeap[data->month])
            return (1);
    }
    else
    {
        if (data->day <= 0 || data->day > daysInMonthNonLeap[data->month])
            return (1);
    }
    return (0);
}

int IsCorrectDate(t_data *data, std::string line)
{
    if ((data->status == 1 || data->status == 2) && line.size() != 2)
    {
        data->status = BadInput;
        return (1);
    }
    if (data->status == 0 && data->year < 2009)
    {
        data->status = LessBitcoinCreationDate;
        return (1);
    }
    else if (data->status == 0 && line.size() < 4)
    {
        data->status = LessBitcoinCreationDate;
    }
    if (data->status == 2 && (data->year == 2009 && data->month == 1 && data->day < 2))
    {
        data->status = LessBitcoinCreationDate;
        return (1);
    }
    if (data->status == 2 && (data->year <= 0 || data->month <= 0 || data->day <= 0))
    {
        data->status = BadInput;
        return (1);
    }
    if (data->status == 2 && IsCorrectDays(data))
    {
        data->status = BadInput;
        return (1);
    }
    return (0);
}

unsigned long ConvertDate(std::string date, t_data *data)
{
    data->status 	= 0;
    data->month 	= 0;
    data->year 		= 0;
    data->day 		= 0;

    std::stringstream s(date);
    std::string line;
    while (getline(s, line, '-'))
    {
        data->status == 0 ? data->year = strtod(line.c_str(), NULL) :  data->year;
        data->status == 1 ? data->month = strtod(line.c_str(), NULL) : data->month;
        data->status == 2 ? data->day = strtod(line.c_str(), NULL) :   data->day;
        if (IsCorrectDate(data, line))
            return (0);
        data->status++;
    }
	if (data->year <= 0 || data->month <= 0 || data->day <= 0)
		data->status = InvalidDate;
    return((data->year * 10000) + (data->month * 100) + data->day);
}

std::string SimpleTrim(std::string str)
{
	int i;
	int begin;
	int end;

	i = 0;
	begin = 0;
	end = str.size();
    while (str[begin] == ' ' || str[begin] == '	')
		begin++;
	i = str.size() - 1;
    while (str[i] && (str[i] == ' ' || str[i] == '	'))
	{
		i--;
		end--;
	}
	str.erase(0, begin);
	int temp = str.size();
    if (end && end < temp)
	    str.erase(end, str.size());
    return (str);
}
int CheckErrors(t_data *data)
{
    //if date < date of bitcoin creation
    if (data->status == LessBitcoinCreationDate)
    {
        std::cout << "Error: bitcoin creation date is 3 janvier 2009 => " << data->date_s << std::endl;
        data->status = 0;
        return (1);
    }
    if (data->month > 12 || data->day > 31 || data->value == "" || data->date_s == "" || data->status == BadInput || data->status == InvalidDate)
    {
        std::cout << "Error: bad input => " << data->date_s << std::endl;
        data->status = 0;
        return (1);
    }
    else if (data->price < 0)
    {
        std::cout << "Error: not a positive number." << std::endl;
        return (NegativeNumber);
    }
    else if (data->price > (double)INT_MAX)
    {
        std::cout << "Error: too large a number." << std::endl;
        return (LargeNumber);
    }
    return (0);
}

std::map<int , float> DataMap_setup(t_data data)
{
    std::map<int , float> 	Map_;
    std::string 			line;
    int 					counter;

    data.price = 0;
    data.date = 0;
	counter = 1;
    std::ifstream File_1("data.csv");
	if (!File_1.is_open())
		throw std::out_of_range("Open File Fails!");
    getline(File_1, line, '\n');//skeping the first line
	line = SimpleTrim(line);
    if (line != "date,exchange_rate")
        throw std::out_of_range("Error!");
    data.value = "";
    data.date_s = "";
    while (getline(File_1, line, '\n'))
    {
        std::stringstream s(line);
        getline(s, data.date_s, ',');
		data.date_s = SimpleTrim(data.date_s);
        getline(s, data.value, ',');
        counter++;//for error handling (Line Number)
        if (data.date_s != "")
            data.date = ConvertDate(data.date_s, &data);
        if (data.value != "")
            data.price = strtod(data.value.c_str(), NULL);
        if (CheckErrors(&data))
        {
            std::cout << "Check the line Number : " << counter << std::endl;
			throw std::out_of_range("");
        }
        Map_.insert(std::pair<int, float>(data.date , data.price));
        data.value = "";
        data.date_s = "";
        data.price = 0;
        data.date = 0;
    }
    return (Map_);
}

double  FindPrice(t_data *data)
{
    unsigned long  	SmallDate;
    double         	price;
    int 			status;
    
	SmallDate 	= 0;
	status 		= 0;
	price 		= 0;
    std::map<int, float>::iterator iter;
    std::map<int, float>::iterator begin = data->DataMap_.begin();
    std::map<int, float>::iterator end = data->DataMap_.end();

    for(iter = begin; iter != end; iter++)
    {
        if ((unsigned long)(*iter).first == data->date)
            return ((*iter).second * data->price);
        else if ((unsigned long)(*iter).first < data->date)
        {
            SmallDate = (*iter).first;
            price = (*iter).second;
            status = 1;
        }
    }
    if (status == 1)
        return (price * data->price);
    return (price);
}

void InputMap_setup(t_data data, std::string FileName)
{
    std::string line;
    
    data.price 	= 0;
    data.date 	= 0;
    std::ifstream File_1(FileName);
	if (!File_1.is_open())
		throw std::out_of_range("Open File Fails!");
    getline(File_1, line, '\n');//skeping the first line
	line = SimpleTrim(line);
    if (line != "date | value")
		std::cout << "Error: bad input"<< std::endl;
    data.value = "";
    data.date_s = "";
    while (getline(File_1, line, '\n'))
    {
        std::stringstream s(line);
        getline(s, data.date_s, '|');
		data.date_s = SimpleTrim(data.date_s);
        getline(s, data.value, '|');
        if (data.date_s != "")
            data.date = ConvertDate(data.date_s, &data);
		if (data.date == 0)
		{
			std::cout << "Error: bad input => " << data.date_s << std::endl;
			continue;
		}
		char *remain;
        if (data.value != "")
            data.price = strtod(data.value.c_str(), &remain);
		if (strlen(remain))
		{
			std::cout << "Error: bad input"<< std::endl;
			continue;
		}
        if (CheckErrors(&data))
        {
            data.value = "";
            data.date_s = "";
            data.price = 0;
            data.date = 0;
            continue;
        }
		//A valid value must be either a float or a positive integer, between 0 and 1000!!!
		else if (!(data.price >= 0 && data.price <= 1000))
		{
			std::cout << "Error: A valid value must be between 0 and 1000!!!" << std::endl;
			continue;
		}
		std::cout << data.date_s << "=> " << data.price << " = " << FindPrice(&data) << std::endl;
        data.value = "";
        data.date_s = "";
        data.price = 0;
        data.date = 0;
    }
}

void	program(int ac, char **av)
{
    try
    {
        if (ac == 2)
        {
            std::map<int , float> 	DataMap_;
            t_data 					data;

            DataMap_ 		= DataMap_setup(data);
            data.DataMap_ 	= DataMap_;

            InputMap_setup(data, av[1]);
        }
        else
            throw std::out_of_range("Param Error!");
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
}
