#include "PartyArray.h"

PartyArray::PartyArray(int size) :
	_arr(new Party*[size]), _log_size(size), _pys_size(size){
}

PartyArray::~PartyArray() {
	for (int i = 0; i < _log_size; i++)
	{
		delete _arr[i];
	}
	delete[] _arr;
}
void PartyArray::resize(int new_size) {

	Party** temp = new Party*[new_size];

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

Party& PartyArray::get(int id) {
	check_valid_idx(id - 1);
	return *_arr[id - 1];
}

void PartyArray::set(int idx, Party* d) {
	check_valid_idx(idx);
	_arr[idx] = d;
}
void PartyArray::add(const Party& d) {
	if (_log_size == _pys_size) {
		resize(_log_size * 2 + 1);
	}

	_arr[_log_size] = new Party(d);
	++_log_size;
}
void PartyArray::set_length(int new_size) {
	if (new_size > _pys_size) {
		resize(new_size);
	}
	_log_size = new_size;
}

Party& PartyArray::operator[](int idx) {
	check_valid_idx(idx);
	return *_arr[idx];
}

const Party& PartyArray::operator[](int idx) const {
	check_valid_idx(idx);
	return *_arr[idx];
}

void PartyArray::print() const {
	for (int i = 0; i < _log_size; i++)
	{
		cout << *_arr[i] << endl;
		cout << _arr[i]->get_candidates_array() << endl;
	}
}

void PartyArray::add_district_to_party(){
	for (int i = 0; i < _log_size; i++)
	{
		_arr[i]->add_district_to_candidates_arr();
	}
}

void PartyArray::check_valid_idx(int idx) const {
	if (idx >= _log_size || idx < 0) {
		exit(1); // index error
	}
}