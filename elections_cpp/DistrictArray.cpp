#include "DistrictArray.h"
#include <iostream>
using namespace std;

namespace elections {

DistrictArray::DistrictArray(int size) : 
	_arr(new District*[size]), _logSize(0), _pysSize(size){
}

DistrictArray::~DistrictArray() {
	for (int i = 0; i < _logSize; i++)
	{
		delete _arr[i];
	}
}


void DistrictArray::resize(int new_size) {
	District** temp = new District*[new_size];

	int copy = _logSize <= new_size ? _logSize : new_size;
	for (int i = 0; i < copy; ++i)
		temp[i] = _arr[i];

	for (int j = copy; j < _logSize; j++) {
		delete _arr[j];
	}

	delete[] _arr;
	_arr = temp;
	this->_pysSize = new_size;
}

const District& DistrictArray::get(int id) const {  
    District* p = nullptr;
    
    for (int i = 0; i < _logSize && !p; i++)
    {
        if (_arr[i]->getId() == id)
            p = _arr[i];
    }
    
    if (p == nullptr)
        exit(1);  // Handle Error 
    
    return *p;
}

District& DistrictArray::get(int id) {    
    District* p = nullptr;

    for (int i = 0; i < _logSize && !p; i++)
    {
        if (_arr[i]->getId() == id)
            p = _arr[i];
    }
    
    if (p == nullptr)
        exit(1);  // Handle Error

    return *p;
}

void DistrictArray::set(int idx, District* d) {
	checkValidIdx(idx);
	_arr[idx] = d;
}
    
District& DistrictArray::add(const District& d) {
	if (_logSize == _pysSize) {
		resize(_logSize * 2 + 1);
	}
	
    if (typeid(d) == typeid(UnifiedDistrict))
        _arr[_logSize] = new UnifiedDistrict(dynamic_cast<const UnifiedDistrict&>(d));
    else if (typeid(d) == typeid(DividedDistrict))
         _arr[_logSize] = new DividedDistrict(dynamic_cast<const DividedDistrict&>(d));
    
	++_logSize;
    return *_arr[_logSize - 1];
}
void DistrictArray::setLength(int new_size) {
	if (new_size > _pysSize) {
		resize(new_size);
	}
	_logSize = new_size;
}

District& DistrictArray::operator[](int idx) {
	checkValidIdx(idx);
	return *_arr[idx];
}

const District& DistrictArray::operator[](int idx) const {
	checkValidIdx(idx);
	return *_arr[idx];
}

void DistrictArray::print() const {
	for (int i = 0; i < _logSize; i++)
	{
		cout << *_arr[i] << endl;
	}
}

void DistrictArray::addPartyToDistrict(Party* p) {
	for (int i = 0; i < _logSize; i++)
	{
		_arr[i]->getPartiesData().add(p);
	}
}


void DistrictArray::checkValidIdx(int idx) const {
	if (idx >= _logSize || idx < 0) {
		exit(1); // index error

	}
}

}
