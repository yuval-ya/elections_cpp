#pragma once
#include <iostream>

namespace mySTL
{

	template <class iterator>
	void myIterSwap(iterator& i, iterator& j)
	{
		auto temp = *i;
		*i = *j;
		*j = temp;
	}

	template <class iterator>
	void myIterSort(const iterator& begin, const iterator& end)
	{
		for (iterator i = begin; i != end; ++i) 
			for (iterator j = begin; j != i; ++j) 
				if (*i < *j) 
					myIterSwap(i, j);
	}

	template <class iterator>
	void print(const iterator& begin, const iterator& end) {
		for (iterator it = begin; it != end; ++it) {
			std::cout << *it << std::endl;
		}
	}

	template <class T>
	int myCmp(const T& a, const T& b) {
		if (a < b) return -1;
		else if (a > b) return 1;
		else return 0;
	}

}