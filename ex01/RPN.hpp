/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouyahy <mbouyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 12:58:11 by mbouyahy          #+#    #+#             */
/*   Updated: 2024/02/15 19:37:46 by mbouyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <sstream>
#include <stack>
#include <stdlib.h>
#include <cctype>

#define Operators " +-/*"

typedef struct s_data
{
    std::stack<std::string> TempStack;
    std::stack<std::string> Stack;
    std::string 			param;
    long long 				result;
    int 					status;
    int 					FisrtNbr;
    int 					SecondNbr;
} t_data;

int         IsOperator(char c);
int         CheckErrors(std::string str);
void        ReversePush(t_data *data);
void        FillStack(t_data *data);
int         IsCorrectNumber(t_data *data);
long long   DetectOperator(t_data *data);
void        PolishNotation(t_data *data);
void        program(int ac, char **av);

#endif