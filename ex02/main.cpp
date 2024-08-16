/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouyahy <mbouyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 19:10:37 by mbouyahy          #+#    #+#             */
/*   Updated: 2024/02/16 13:54:14 by mbouyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

void PrintElementsBeforeSort(PmergeMe FordJohnson)
{
	std::cout << "Before : ";
	std::vector<unsigned int> Elements = FordJohnson.getElementsBeforeSorting();
	for (std::vector<unsigned int>::iterator it = Elements.begin(); it != Elements.end(); it++)
	{
		std::cout << *it << " ";
	}
}

// void isSorted(PmergeMe FordJohnson)
// {
// 	{
// 		std::vector<std::vector<unsigned int> >::iterator Citer;
// 		std::vector<std::vector<unsigned int> > Collection = FordJohnson.getVectorCollection();
// 		for (Citer = Collection.begin(); Citer != Collection.end(); Citer++)
// 		{
// 			if ((Citer + 1) != Collection.end() && Citer->back() > (Citer + 1)->back())
// 			{
// 				std::cout << "Vector : Not Sorted" << std::endl;
// 				break ;
// 			}
// 		}
// 		std::cout << "Vector : Sorted" << std::endl;
// 	}
// 	{
// 		std::list<std::list<unsigned int> >::iterator Citer;
// 		std::list<std::list<unsigned int> > Collection = FordJohnson.getListCollection();
// 		for (Citer = Collection.begin(); Citer != Collection.end(); Citer++)
// 		{
// 			if (std::next(Citer, 1) != Collection.end() && Citer->back() > std::next(Citer, 1)->back())
// 			{
// 				std::cout << "List : Not Sorted" << std::endl;
// 				break ;
// 			}
// 		}
// 		std::cout << "List : Sorted" << std::endl;
// 	}
// }

void Print(PmergeMe FordJohnson)
{
	std::vector<std::vector<unsigned int> >::iterator Citer;
	std::vector<std::vector<unsigned int> > Collection = FordJohnson.getVectorCollection();
	PrintElementsBeforeSort(FordJohnson);
	std::cout << std::endl << "After : ";
	for (Citer = Collection.begin(); Citer != Collection.end(); Citer++)
	{
		for (std::vector<unsigned int>::iterator iter = Citer->begin(); iter != Citer->end(); iter++)
		{
			std::cout << *iter << " ";
		}
	}
	std::cout << std::endl;
}

int main(int ac, char **av)
{
    if (ac >= 2)
    {
		try
		{
			PmergeMe	FordJohnson(ac, av);

			double ListStart, ListEnd;
			double VectorStart, VectorEnd;

			VectorStart = clock();
			FordJohnson.VectorFordJohnsonAlgorithm();
			VectorEnd = clock();

			ListStart = clock();
			FordJohnson.ListFordJohnsonAlgorithm();
			ListEnd = clock();

			Print(FordJohnson);
			// isSorted(FordJohnson);
			std::cout << "Time to process a range of " << ac - 1 << " elements with std::vector : " << ((VectorEnd - VectorStart)/CLOCKS_PER_SEC) << " us" << std::endl;
			std::cout << "Time to process a range of " << ac - 1 << " elements with std::list   : " << ((ListEnd - ListStart)/CLOCKS_PER_SEC) << " us" << std::endl;
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	else
	{
		std::cout << "Usage: ./PmergeMe [elements]" << std::endl;
    }
}
