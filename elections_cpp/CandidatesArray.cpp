#include "CandidatesArray.h"

CandidatesArray::CandidatesArray(int size) : _arr(new PersonList*[size]), _log_size(size), _pys_size(size)
{
    for (int i = 0; i < size; i++)
        _arr[i] = new PersonList;
    cout << "CandidatesArray ctor" <<endl;
}

CandidatesArray::~CandidatesArray() {
	for (int i = 0; i < _log_size; i++)
	{
		delete _arr[i];
	}
	delete[] _arr;
}
void CandidatesArray::resize(int new_size) {

	PersonList** temp = new PersonList*[new_size];

	int copy = _log_size <= new_size ? _log_size : new_size;
	for (int i = 0; i < copy; ++i)
		temp[i] = _arr[i];

	delete[] _arr;
	_arr = temp;
	this->_pys_size = new_size;
}

PersonList& CandidatesArray::get(int district_id) {
	return *_arr[district_id - 1];
}

void CandidatesArray::add() {
	if (_log_size == _pys_size) {
		resize(_log_size * 2 + 1);
	}
  	_arr[_log_size] = new PersonList();
	_log_size++;
}
void CandidatesArray::set_length(int new_size) {
	if (new_size > _pys_size) {
		resize(new_size);
	}
	_log_size = new_size;
}

PersonList& CandidatesArray::operator[](int idx) {
	return *_arr[idx];
}

const PersonList& CandidatesArray::operator[](int idx) const {
	return *_arr[idx];
}

ostream& operator<<(ostream& os, const CandidatesArray& c_arr) {
	int size = c_arr.get_length();
	for (int i = 0; i < size; i++) {
		os << "District No." << (i + 1) << " :" << endl;
		os << c_arr[i] << endl;
	}
	return os;
}