#include "DistrictArray.h"
#include <iostream>
using namespace std;

namespace elections {

	DistrictArray::DistrictArray(int size) :
		_arr(new District*[size]), _log_size(size), _pys_size(size) {
	}

	DistrictArray::~DistrictArray() {
		for (int i = 0; i < _log_size; i++)
		{
			delete _arr[i];
		}
		delete[] _arr;
	}
	void DistrictArray::resize(int new_size) {

		District** temp = new District*[new_size];

		int copy = _log_size <= new_size ? _log_size : new_size;
		for (int i = 0; i < copy; ++i)
			temp[i] = _arr[i];

		for (int j = copy; j < _log_size; j++) {
			delete _arr[j];
		}

		delete[] _arr;
		_arr = temp;
		this->_pys_size = new_size;
	}

	District& DistrictArray::get(int id) {
		check_valid_idx(id - 1);
		return *_arr[id - 1];
	}

	void DistrictArray::set(int idx, District* d) {
		check_valid_idx(idx);
		_arr[idx] = d;
	}
	void DistrictArray::add(const District& d) {
		if (_log_size == _pys_size) {
			resize(_log_size * 2 + 1);
		}

		_arr[_log_size] = new District(d);
		++_log_size;
	}
	void DistrictArray::set_length(int new_size) {
		if (new_size > _pys_size) {
			resize(new_size);
		}
		_log_size = new_size;
	}

	District& DistrictArray::operator[](int idx) {
		check_valid_idx(idx);
		return *_arr[idx];
	}

	const District& DistrictArray::operator[](int idx) const {
		check_valid_idx(idx);
		return *_arr[idx];
	}

	void DistrictArray::print() const {
		for (int i = 0; i < _log_size; i++)
		{
			cout << *_arr[i] << endl;
		}
	}

	void DistrictArray::add_party_to_district() {
		for (int i = 0; i < _log_size; i++)
		{
			_arr[i]->add_party_to_district();
		}
	}

	void DistrictArray::check_valid_idx(int idx) const {
		if (idx >= _log_size || idx < 0) {
			exit(1); // index error
		}
	}

}