/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouyahy <mbouyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 19:10:51 by mbouyahy          #+#    #+#             */
/*   Updated: 2024/02/14 19:52:27 by mbouyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <list>
#include <ctime>

class PmergeMe
{
	private:
		//Vector
		std::vector<std::vector<unsigned int> > 	_VectorCollection;
		std::vector<std::vector<unsigned int> > 	_VectorStock;
		std::vector<unsigned int> 					_VectorElements;
		int 										_VectorNbrComp;
		
		//List
		std::list<std::list<unsigned int> > 		_ListCollection;
		std::list<std::list<unsigned int> > 		_ListStock;
		std::list<unsigned int> 					_ListElements;
		int 										_ListNbrComp;
		
		
		std::vector<unsigned int> 					_ElementsBeforeSorting;
		int 										_PairsNumber;
		int											_nArguments;
		char 										**_arguments;

	public:
		PmergeMe(void);
		~PmergeMe(void);
		PmergeMe(const PmergeMe &src);
		PmergeMe &operator=(const PmergeMe &src);

		PmergeMe(int ac, char **av);

		//Getters
		std::vector<unsigned int> 					getElementsBeforeSorting();

		//Check Functions
		void										StoreElements(int ac, char **av);
		bool										iSValidArgument(std::string av);

		//Vector Functions
		void										VectorInsertPendIntoMainChain(std::vector<std::vector<unsigned int> >& MainChain, std::vector<std::vector<unsigned int> > &Pend);
		void										VectorFillMainChainAndPend(std::vector<std::vector<unsigned int> > &Reste, std::vector<std::vector<unsigned int> > &MainChain, std::vector<std::vector<unsigned int> > &Pend);
		void										VectorFillCollection(std::vector<unsigned int> Elements, int PairsNumber);
		void										ToVectorOfVector();
		void										VectorUpdateElements();
		std::vector<std::vector<unsigned int> >		VectorFillReste();
		void										VectorFordJohnsonAlgorithm();
		void										VectorReverseRecursion(std::vector<std::vector<unsigned int> > &Reste, std::vector<std::vector<unsigned int> >& MainChain, std::vector<std::vector<unsigned int> > &Pend);
		void										VectorRecursion(std::vector<std::vector<unsigned int> >	&Reste);

		//Vector Getters
		std::vector<std::vector<unsigned int> > 	getVectorCollection(void);
		std::vector<std::vector<unsigned int> > 	getVectorStock(void);
		int 										getVectorNbrComp(void);


		//List Functions
		void										ListInsertPendIntoMainChain(std::list<std::list<unsigned int> >& MainChain, std::list<std::list<unsigned int> > &Pend);
		void										ListFillMainChainAndPend(std::list<std::list<unsigned int> > &Reste, std::list<std::list<unsigned int> > &MainChain, std::list<std::list<unsigned int> > &Pend);
		void										ListFillCollection(std::list<unsigned int> Elements, int PairsNumber);
		void										ToListOfList();
		void										ListUpdateElements();
		std::vector<std::vector<unsigned int> >		ListFillReste();
		void										ListFordJohnsonAlgorithm();
		void										ListReverseRecursion(std::list<std::list<unsigned int> > &Reste, std::list<std::list<unsigned int> >& MainChain, std::list<std::list<unsigned int> > &Pend);
		void										ListRecursion(std::list<std::list<unsigned int> >	&Reste);
		
		//List getters 
		std::list<std::list<unsigned int> > 		getListCollection(void);
		std::list<std::list<unsigned int> > 		getListStock(void);
		int 										getListNbrComp(void);
};

#endif

