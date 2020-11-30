#include "DynamicArray.h"

DynamicArray::DynamicArray(int size)
	: _arr(new int[size]), _log_size(size), _pys_size(size)
{
	for (int i = 0; i < size; i++){
		_arr[i] = 0;
	}
}

DynamicArray::~DynamicArray()
{
	delete[] _arr;
}

void DynamicArray::resize(int new_size)
{
	int* temp = new int[new_size];
	int copy = _log_size <= new_size ? _log_size : new_size;
	for (int i = 0; i < copy; ++i)
		temp[i] = _arr[i];

	delete[] _arr;

	_arr = temp;
	this->_pys_size = new_size;
}

void DynamicArray::set_length(int new_size) {
	if (new_size > _pys_size) {
		resize(new_size);
	}
	_log_size = new_size;
}


void DynamicArray::add(int val)
{
	if (_log_size == _pys_size) {
		resize(_log_size * 2 + 1);
	}

	_arr[_log_size] = val;
	++_log_size;
}

int DynamicArray::get_max_votes() const {
	int max_val = _arr[0] , max_idx = 0;
	for (int i = 1; i < _log_size; i++) {
		if (_arr[i] > max_val) {
			max_val = _arr[i];
			max_idx = i;
		}
	}
	return max_idx;
}