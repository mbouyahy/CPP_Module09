/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouyahy <mbouyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 19:10:56 by mbouyahy          #+#    #+#             */
/*   Updated: 2024/02/15 19:48:21 by mbouyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

// int g_VectorNbrComp = 0;
// int g_ListNbrComp 	= 0;

PmergeMe::PmergeMe(void)
{
	_VectorNbrComp 	= 0;
	_ListNbrComp 	= 0;
	_arguments 		= NULL;
	_nArguments 	= 0;
}

PmergeMe::PmergeMe(int ac, char **av)
{
    _VectorNbrComp 	= 0;
    _ListNbrComp	= 0;
	_arguments 		= av;
	_nArguments 	= ac;
    StoreElements(ac, av);
}

PmergeMe::~PmergeMe(void)
{
	
}

PmergeMe::PmergeMe(const PmergeMe &src)
{
	*this = src;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &src)
{
	if (this != &src)
	{
		_VectorCollection 			= src._VectorCollection;
		_VectorStock 				= src._VectorStock;
		_ListCollection 			= src._ListCollection;
		_ListStock 					= src._ListStock;
		_VectorNbrComp 				= src._VectorNbrComp;
		_ListNbrComp 				= src._ListNbrComp;
		_PairsNumber 				= src._PairsNumber;
		_ElementsBeforeSorting 		= src._ElementsBeforeSorting;
	}
	return (*this);
}

std::vector<unsigned int> PmergeMe::getElementsBeforeSorting()
{
	return (_ElementsBeforeSorting);
}

std::vector<std::vector<unsigned int> > 	PmergeMe::getVectorCollection(void)
{
	return (_VectorCollection);
}

std::vector<std::vector<unsigned int> > 	PmergeMe::getVectorStock(void)
{
	return (_VectorStock);
}

int 										PmergeMe::getVectorNbrComp(void)
{
	return (_VectorNbrComp);
}

void PmergeMe::StoreElements(int ac, char **av)
{
    for (int i = 1; i < ac; i++)
    {
		char *remain;

		if (!iSValidArgument(av[i]))
			throw std::out_of_range("Error");
       	_ElementsBeforeSorting.push_back(strtod(av[i], &remain));
		std::vector<unsigned int> VectorTmp;
        VectorTmp.push_back(strtod(av[i], &remain));
		_VectorCollection.push_back(VectorTmp);
		if (strlen(remain))
			throw std::out_of_range("Error");
		std::list<unsigned int> ListTmp;
        ListTmp.push_back(strtod(av[i], &remain));
		_ListCollection.push_back(ListTmp);
    }
}

bool PmergeMe::iSValidArgument(std::string av)
{
	for (size_t i = 0; i < av.size(); i++)
	{
		if (!std::isdigit(av[i]) && av[i] != '+')
			return (false);
	}
	return (true);
}

//<------------------Vector Container <Start>--------------------->

std::vector<unsigned int> FillGVector(std::vector<unsigned int> FirstVector, std::vector<unsigned int> SecondVector)
{
    std::vector<unsigned int> GVector;

    if (!FirstVector.empty())
        GVector.insert(GVector.end(), FirstVector.begin() , FirstVector.end());
    if (!SecondVector.empty())
        GVector.insert(GVector.end(), SecondVector.begin() , SecondVector.end());
    return (GVector);
}

void	PmergeMe::VectorFillCollection(std::vector<unsigned int> Elements, int PairsNumber)
{
    std::vector<unsigned int>               GVector;
    std::vector<unsigned int>::iterator     it;
    
	_VectorStock.clear();
    if (Elements.empty())
        return ;
    it = Elements.begin();
    while (it != Elements.end())
    {
        for (int i = 0; i < PairsNumber && it != Elements.end(); i++)
        {
            GVector.push_back(*it);
            it++;
        }
        if (GVector.empty())
            break ;
        _VectorStock.push_back(GVector);
        GVector.clear();
    }
}

void	PmergeMe::VectorUpdateElements()
{
	_VectorElements.clear();
    for (std::vector<std::vector<unsigned int> >::iterator Citer = _VectorStock.begin(); Citer != _VectorStock.end(); Citer++)
        _VectorElements.insert(_VectorElements.end(), Citer->begin(), Citer->end());
}

void    PmergeMe::VectorFillMainChainAndPend(std::vector<std::vector<unsigned int> > &Reste, std::vector<std::vector<unsigned int> > &MainChain, 
        std::vector<std::vector<unsigned int> > &Pend)
{
    int i;

	i = 0;
    for (std::vector<std::vector<unsigned int> >::iterator Citer = _VectorStock.begin(); Citer != _VectorStock.end(); Citer++)
    {
        if (i % 2 != 0)
            MainChain.push_back(*Citer);
        else
            Pend.push_back(*Citer);
        i++;
    }
	if (!Reste.empty())
	{
		Pend.insert(Pend.end(), Reste.begin(), Reste.end());
		Reste.clear();
	}
}

bool VectorCompareElements(std::vector<unsigned int> A , std::vector<unsigned int> B)
{
    if (A.empty() || B.empty())
        return (false);
    // g_VectorNbrComp++;
    return (A.back() < B.back());
}

void PmergeMe::VectorInsertPendIntoMainChain(std::vector<std::vector<unsigned int> >& MainChain, std::vector<std::vector<unsigned int> > &Pend)
{
  size_t JaaKobStaalSequence[34] = {1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731, 5461, 10923, 21845, 43691, 87381, 174763, 349525, 699051, 1398101, 2796203, 5592405, 
		11184811, 22369621, 44739243, 89478485, 178956971, 357913941, 715827883, 1431655765, 2863311531, 5726623061, 11453246123};
  size_t times = 0;
  size_t PreviousJaaKobStaalValue = 0;
  for (size_t i = 0; i < Pend.size() && i < 34; i++)
  {
	size_t CurrentJaaKobStaalValue = JaaKobStaalSequence[i];
    while (CurrentJaaKobStaalValue > PreviousJaaKobStaalValue) {
        if (CurrentJaaKobStaalValue - 1 >= Pend.size()) {
            CurrentJaaKobStaalValue = Pend.size();
            continue;
        }
        if (CurrentJaaKobStaalValue - 1 == 0) {
            MainChain.insert(MainChain.begin(), Pend[i]);
            times++;
        }
        else {
            std::vector<unsigned int> original = Pend[CurrentJaaKobStaalValue - 1];
            std::vector<std::vector<unsigned int> >::iterator position = lower_bound(MainChain.begin(), 
                MainChain.begin() + CurrentJaaKobStaalValue + times - 1, original, VectorCompareElements);
            MainChain.insert(position, original);
            times++;
        }
        CurrentJaaKobStaalValue--;
      }
    PreviousJaaKobStaalValue = JaaKobStaalSequence[i];
  }
  _VectorStock = MainChain;
  VectorUpdateElements();
}

void PmergeMe::ToVectorOfVector()
{
    for (std::vector<unsigned int>::iterator it = _VectorElements.begin(); it != _VectorElements.end(); it++)
    {
        std::vector<unsigned int> tmp;
        tmp.push_back(*it);
        _VectorCollection.push_back(tmp);
    }
}

void	PmergeMe::VectorReverseRecursion(std::vector<std::vector<unsigned int> > &Reste, std::vector<std::vector<unsigned int> >& MainChain, std::vector<std::vector<unsigned int> > &Pend)
{
	_PairsNumber/=2;
	VectorFillCollection(_VectorElements, _PairsNumber);
	VectorFillMainChainAndPend(Reste, MainChain, Pend);
	VectorInsertPendIntoMainChain(MainChain, Pend);
    _VectorCollection = MainChain;
    // _VectorNbrComp = g_VectorNbrComp;
}

void	PmergeMe::VectorRecursion(std::vector<std::vector<unsigned int> >	&Reste)
{
	if (_VectorCollection.size() % 2)
	{
		std::vector<unsigned int> it = _VectorCollection.back();
		Reste.push_back(it);
		_VectorCollection.pop_back();
	}
	if ( _VectorCollection.size() > 1)
    {
        std::vector<std::vector<unsigned int> > temp;
        std::vector<std::vector<unsigned int> >::iterator it = _VectorCollection.begin();
        for (size_t c = 0; c < _VectorCollection.size(); c += 2 , it += 2)
        {
            std::vector<unsigned int>first;
            if (c < _VectorCollection.size())
               first = *it;
            std::vector<unsigned int> second;
            if (c + 1 < _VectorCollection.size())
                second = *(it + 1);
            // g_VectorNbrComp++;
            if (first.back() > second.back())
                std::swap(first, second);
            temp.push_back(FillGVector(first, second));
        }
        _VectorCollection = temp;
        if (_VectorCollection.size() > 1)
            VectorFordJohnsonAlgorithm();
        _PairsNumber = _VectorCollection.begin()->size();
		if (_VectorCollection.size() == 1)
		{
			_VectorStock = _VectorCollection;
			VectorUpdateElements();
		}
        // std::cout << "<-------------Recursion------------>" << std::endl;
    }
}

void PmergeMe::VectorFordJohnsonAlgorithm()
{
    std::vector<std::vector<unsigned int> >   	Reste;

	// std::cout << "<-------------Recursion------------>" << std::endl;
	VectorRecursion(Reste);
	// std::cout << "<-------------Reverse Recursion------------>"<< _VectorNbrComp << std::endl;
    std::vector<std::vector<unsigned int> >       MainChain;
    std::vector<std::vector<unsigned int> >       Pend;
	VectorReverseRecursion(Reste, MainChain, Pend);
}

//<------------------Vector Container <End>--------------------->


//<------------------List Container <Start>--------------------->

std::list<std::list<unsigned int> > 	PmergeMe::getListCollection(void)
{
	return (_ListCollection);
}

std::list<std::list<unsigned int> > 	PmergeMe::getListStock(void)
{
	return (_ListStock);
}

int 										PmergeMe::getListNbrComp(void)
{
	return (_ListNbrComp);
}

std::list<unsigned int> FillGList(std::list<unsigned int> FirstList, std::list<unsigned int> SecondList)
{
    std::list<unsigned int> GList;

    if (!FirstList.empty())
        GList.insert(GList.end(), FirstList.begin() , FirstList.end());
    if (!SecondList.empty())
        GList.insert(GList.end(), SecondList.begin() , SecondList.end());
    return (GList);
}

void PmergeMe::ToListOfList()
{
    for (std::list<unsigned int>::iterator it = _ListElements.begin(); it != _ListElements.end(); it++)
    {
        std::list<unsigned int> tmp;
        tmp.push_back(*it);
        _ListCollection.push_back(tmp);
    }
}

void	PmergeMe::ListFillCollection(std::list<unsigned int> Elements, int PairsNumber)
{
    std::list<unsigned int>               GList;
    std::list<unsigned int>::iterator     it;
    
	_ListStock.clear();
    if (Elements.empty())
        return ;
    it = Elements.begin();
    while (it != Elements.end())
    {
        for (int i = 0; i < PairsNumber && it != Elements.end(); i++)
        {
            GList.push_back(*it);
            it++;
        }
        if (GList.empty())
            break ;
        _ListStock.push_back(GList);
        GList.clear();
    }
}

void	PmergeMe::ListUpdateElements()
{
	_ListElements.clear();
    for (std::list<std::list<unsigned int> >::iterator Citer = _ListStock.begin(); Citer != _ListStock.end(); Citer++)
        _ListElements.insert(_ListElements.end(), Citer->begin(), Citer->end());
}

void    PmergeMe::ListFillMainChainAndPend(std::list<std::list<unsigned int> > &Reste, std::list<std::list<unsigned int> > &MainChain, 
        std::list<std::list<unsigned int> > &Pend)
{
    int i = 0;
    for (std::list<std::list<unsigned int> >::iterator Citer = _ListStock.begin(); Citer != _ListStock.end(); Citer++)
    {
        if (i % 2 != 0)
            MainChain.push_back(*Citer);
        else
            Pend.push_back(*Citer);
        i++;
    }
	if (!Reste.empty())
	{
		Pend.insert(Pend.end(), Reste.begin(), Reste.end());
		Reste.clear();
	}
}

bool ListCompareElements(std::list<unsigned int> A , std::list<unsigned int> B)
{
    if (A.empty() || B.empty())
        return (false);
    // g_ListNbrComp++;
    return (A.back() < B.back());
}

void PmergeMe::ListInsertPendIntoMainChain(std::list<std::list<unsigned int> >& MainChain, std::list<std::list<unsigned int> > &Pend)
{
  size_t JaaKobStaalSequence[34] = {1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731, 5461, 10923, 21845, 43691, 87381, 174763, 349525, 699051, 1398101, 2796203, 5592405, 
		11184811, 22369621, 44739243, 89478485, 178956971, 357913941, 715827883, 1431655765, 2863311531, 5726623061, 11453246123};
  size_t times = 0;
  size_t PreviousJaaKobStaalValue = 0;
  for (size_t i = 0; i < Pend.size() && i < 34; i++)
  {
	size_t CurrentJaaKobStaalValue = JaaKobStaalSequence[i];
    while (CurrentJaaKobStaalValue > PreviousJaaKobStaalValue) {
        if (CurrentJaaKobStaalValue - 1 >= Pend.size()) {
            CurrentJaaKobStaalValue = Pend.size();
            continue;
        }
        if (CurrentJaaKobStaalValue - 1 == 0) {
			std::list<std::list<unsigned int> >::iterator it = Pend.begin();
			std::advance(it, i);
            MainChain.insert(MainChain.begin(), *it);
            times++;
        }
        else {
			std::list<std::list<unsigned int> >::iterator Pend_iter = Pend.begin();
			std::advance(Pend_iter, CurrentJaaKobStaalValue - 1);
			std::list<std::list<unsigned int> >::iterator MainChain_iter = MainChain.begin();
			std::advance(MainChain_iter, CurrentJaaKobStaalValue + times - 1);
            std::list<std::list<unsigned int> >::iterator position = lower_bound(MainChain.begin(), 
                MainChain_iter, *Pend_iter, ListCompareElements);
            MainChain.insert(position, *Pend_iter);
            times++;
        }
        CurrentJaaKobStaalValue--;
      }
    PreviousJaaKobStaalValue = JaaKobStaalSequence[i];
  }
  _ListStock = MainChain;
  ListUpdateElements();
}

void	PmergeMe::ListRecursion(std::list<std::list<unsigned int> >	&Reste)
{
	if (_ListCollection.size() % 2)
	{
		std::list<unsigned int> it = _ListCollection.back();
		Reste.push_back(it);
		_ListCollection.pop_back();
	}
	if (_ListCollection.size() > 1)
    {
        std::list<std::list<unsigned int> > temp;
        std::list<std::list<unsigned int> >::iterator it = _ListCollection.begin();
        for (size_t c = 0; c < _ListCollection.size(); c += 2 , std::advance(it, 1))
        {
            std::list<unsigned int>first;
            if (c < _ListCollection.size())
               first = *it;
            std::list<unsigned int> second;
            if (c + 1 < _ListCollection.size())
			{
				std::advance(it,1);
                second = *it;
			}
            // g_ListNbrComp++;
            if (first.back() > second.back())
                std::swap(first, second);
            temp.push_back(FillGList(first, second));
        }
        _ListCollection = temp;
        if (_ListCollection.size() > 1)
            ListFordJohnsonAlgorithm();
        _PairsNumber = _ListCollection.begin()->size();
		if (_ListCollection.size() == 1)
		{
			_ListStock = _ListCollection;
			ListUpdateElements();
		}
        // std::cout << "<-------------Recursion------------>" << std::endl;
    }
}

void	PmergeMe::ListReverseRecursion(std::list<std::list<unsigned int> > &Reste, std::list<std::list<unsigned int> >& MainChain, std::list<std::list<unsigned int> > &Pend)
{
	_PairsNumber/=2;
	ListFillCollection(_ListElements, _PairsNumber);
	ListFillMainChainAndPend(Reste, MainChain, Pend);
	ListInsertPendIntoMainChain(MainChain, Pend);
    _ListCollection = MainChain;
    // _ListNbrComp 	= g_ListNbrComp;
}

void PmergeMe::ListFordJohnsonAlgorithm()
{
    std::list<std::list<unsigned int> >   	Reste;

	// std::cout << "<-------------Recursion------------>" << std::endl;
	ListRecursion(Reste);
	// std::cout << "<-------------List Reverse Recursion------------>"<< _ListNbrComp << std::endl;
    std::list<std::list<unsigned int> >       MainChain;
    std::list<std::list<unsigned int> >       Pend;
	ListReverseRecursion(Reste, MainChain, Pend);
}

//<------------------List Container <End>--------------------->
