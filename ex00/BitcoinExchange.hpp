/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouyahy <mbouyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 20:44:25 by mbouyahy          #+#    #+#             */
/*   Updated: 2024/02/16 12:38:18 by mbouyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <climits>
#include <ctime>

#define NegativeNumber 1
#define LargeNumber 2
#define BadInput -1
#define LessBitcoinCreationDate -2
#define InvalidDate -3
#define INPUT -4
#define DATAFILE -5

typedef struct s_data
{
    std::map<int , float>   DataMap_;
    std::string             date_s;
    std::string             value;
    unsigned long           date;
    double                  price;
    int                     status;
    int                     month;
    int                     year;
    int                     day;
}	t_data;

int                     IsCorrectDate(t_data *data, std::string line);
unsigned long           ConvertDate(std::string date, t_data *data);
int                     IsCorrectDays(t_data *data);
int                     IsLeap(t_data *data);

int                     CheckErrors(t_data *data);
double                  FindPrice(t_data *data);
std::string             SimpleTrim(std::string str);

void                    InputMap_setup(t_data data, std::string FileName);
std::map<int , float>   DataMap_setup(t_data data);

void	                program(int ac, char **av);

#endif

