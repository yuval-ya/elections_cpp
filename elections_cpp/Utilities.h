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

	template <class iterator, class Func>
	void myIterSort(const iterator& begin, const iterator& end, const Func& cmp)
	{
		for (iterator i = begin; i != end; ++i) 
			for (iterator j = begin; j != i; ++j) 
				if (cmp(*i,*j))
					myIterSwap(i, j);
	}

	template <class T>
	void print(const T& PointrsStruct) {
		for (auto obj : PointrsStruct) {
			std::cout << *obj << std::endl;
		}
    }

    template <class T>
    void print(const T& PointrsStruct, int size) {
        int i = 0;
        for (auto obj : PointrsStruct) {
            if (i < size)
                std::cout << *obj << std::endl;
            else
                break;
            i++;
        }
        
        if (i < size) throw "There is no engouh object in is struct";
    }

}
