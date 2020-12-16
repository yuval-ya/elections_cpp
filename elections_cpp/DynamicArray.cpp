#include "DynamicArray.h"
#include <iostream>

DynamicArray::DynamicArray(int size)
	: _arr(new int[size]), _logSize(size), _pysSize(size)
{
	for (int i = 0; i < size; i++){
		_arr[i] = 0;
	}
}

DynamicArray::~DynamicArray()
{
	delete[] _arr;
}

bool DynamicArray::set(int idx, int val)
{
    _arr[idx] = val;
    return true;
}

void DynamicArray::resize(int new_size)
{
	int* temp = new int[new_size];
	int copy = _logSize <= new_size ? _logSize : new_size;
	for (int i = 0; i < copy; ++i)
		temp[i] = _arr[i];

	delete[] _arr;

	_arr = temp;
	this->_pysSize = new_size;
}

void DynamicArray::setLength(int new_size) {
	if (new_size > _pysSize) {
		resize(new_size);
	}
	_logSize = new_size;
}


bool DynamicArray::add(int val)
{
	if (_logSize == _pysSize) {
		resize(_logSize * 2 + 1);
	}

	_arr[_logSize] = val;
	++_logSize;
    return true;
}

int DynamicArray::get(int id) const{
	check_valid_idx(id - 1);
	return _arr[id - 1];
}

int DynamicArray::get_max() const {
	if (_logSize == 0) return -1;

	int max_val = _arr[0], max_idx = 0;
	for (int i = 1; i < _logSize; i++) {
		if (_arr[i] > max_val) {
			max_val = _arr[i];
			max_idx = i;
		}
	}
	return max_idx;
}


int& DynamicArray::operator[](int idx)
{
	check_valid_idx(idx);
	return _arr[idx];
}
const int& DynamicArray::operator[](int idx) const
{
	check_valid_idx(idx);
	return _arr[idx];
}

void DynamicArray::check_valid_idx(int idx) const {
	if (idx >= _logSize || idx < 0) {
		exit(1); // index error
	}
}
